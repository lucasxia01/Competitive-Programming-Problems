from enum import Enum, auto
from dataclasses import dataclass, is_dataclass
import sys
from typing import Callable, Dict, List, Optional, Union

debug_print = False

class Register(Enum):
    RA = 0
    RB = auto()
    RC = auto()
    RD = auto()
    RE = auto()
    RF = auto()
    RG = auto()
    RR = auto()
    RINS = auto()
    RST = auto()
    RFLAG = auto()

    @classmethod
    def count(cls) -> int:
        return len(cls)

    @classmethod
    def from_integer(cls, i: int) -> Optional["Register"]:
        values = list(cls)
        if 0 <= i < len(values):
            return values[i]
        elif i == len(values):
            return None
        else:
            raise RuntimeError("Illegal register")

@dataclass
class Expression:
    register: Optional[Register] = None
    immediate: int = 0  # if no register just a value


class Operation:
    pass


@dataclass
class NoOp(Operation):
    pass

@dataclass
class LoadOp(Operation):
    destination: Register
    address: Expression


@dataclass
class StoreOp(Operation):
    source: Register
    address: Expression


class JumpCondition(Enum):
    ALWAYS = auto()
    ZERO = auto()
    NONZERO = auto()
    CARRY = auto()
    NOTCARRY = auto()


@dataclass
class JumpOp(Operation):
    condition: JumpCondition
    address: Expression


@dataclass
class PushOp(Operation):
    expression: Expression


@dataclass
class PopOp(Operation):
    register: Register


@dataclass
class HaltOp(Operation):
    expression: Expression


@dataclass
class SetOp(Operation):
    register: Register
    expression: Expression


class OperationType(Enum):
    ADD = auto()
    SUB = auto()
    MULT = auto()


@dataclass
class BinaryOp(Operation):
    op: OperationType
    dst: Register
    a: Register
    b: Register


@dataclass
class DebugOp(Operation):
    tag: int  # Using int in place of UByte (Python doesn't limit ints)


@dataclass
class Exit:
    code: int  # Using int in place of UInt

class ByteUtils:
    @staticmethod
    def get_byte(num: int, byte_index: int) -> int:
        return (num >> (8 * byte_index)) & 0xFF

    @staticmethod
    def read_byte(byte: int, byte_index: int) -> int:
        return byte << (8 * byte_index)


class CoderDecoder:
    @staticmethod
    def decode(data: int) -> Operation:
        opcode = ByteUtils.get_byte(data, 0)
        byte2 = ByteUtils.get_byte(data, 1)
        byte3 = ByteUtils.get_byte(data, 2)
        byte4 = ByteUtils.get_byte(data, 3)

        register1 = lambda : Register.from_integer(byte2)
        register2 = lambda : Register.from_integer(byte3)   # to int
        expr =      lambda : Expression(register2(), byte4) # to byte
        register3 = lambda : Register.from_integer(byte4)

        if opcode == 0:
            return NoOp()
        elif opcode == 1:
            return LoadOp(register1(), expr())
        elif opcode == 2:
            return StoreOp(register1(), expr())
        elif opcode == 3:
            return PushOp(expr())
        elif opcode == 4:
            return PopOp(register1())
        elif opcode == 5:
            return HaltOp(expr())
        elif opcode == 6:
            return SetOp(register1(), expr())
        elif opcode == 7:
            return DebugOp(byte2)
        elif 10 <= opcode < 10 + len(JumpCondition):
            condition = list(JumpCondition)[opcode - 10]
            return JumpOp(condition, expr())
        elif 20 <= opcode < 20 + len(OperationType):
            op_type = list(OperationType)[opcode - 20]
            return BinaryOp(op_type, register1(), register2(), register3())
        else:
            raise RuntimeError(f"Illegal instruction {opcode}")

    @staticmethod
    def encode(op: Operation) -> int:
        def from_bytes(a: int, b: int, c: int, d: int) -> int:
            def is_byte(x:int):
                return 0 <= x <= 255 
            assert is_byte(a)
            assert is_byte(b)
            assert is_byte(c)
            assert is_byte(d)

            return (
                ByteUtils.read_byte(a, 0) |
                ByteUtils.read_byte(b, 1) |
                ByteUtils.read_byte(c, 2) |
                ByteUtils.read_byte(d, 3)
            )

        def convert_register(r: Optional[Register]) -> int:
            return r.value if r else Register.count()

        def from_register_and_expr(opcode: int, r: Optional[Register], expr: Expression) -> int:
            return from_bytes(opcode, convert_register(r), convert_register(expr.register), expr.immediate & 0xFF)

        def from_register(opcode: int, r: Optional[Register]) -> int:
            return from_bytes(opcode, convert_register(r), 0, 0)

        def from_three_registers(opcode: int, r1: Register, r2: Register, r3: Register) -> int:
            return from_bytes(opcode, convert_register(r1), convert_register(r2), convert_register(r3))

        if isinstance(op, NoOp):
            return from_register(0, None)
        elif isinstance(op, LoadOp):
            return from_register_and_expr(1, op.destination, op.address)
        elif isinstance(op, StoreOp):
            return from_register_and_expr(2, op.source, op.address)
        elif isinstance(op, PushOp):
            return from_register_and_expr(3, None, op.expression)
        elif isinstance(op, PopOp):
            return from_register(4, op.register)
        elif isinstance(op, HaltOp):
            return from_register_and_expr(5, None, op.expression)
        elif isinstance(op, SetOp):
            return from_register_and_expr(6, op.register, op.expression)
        elif isinstance(op, DebugOp):
            return from_bytes(7, op.tag, 0, 0)
        elif isinstance(op, JumpOp):
            return from_register_and_expr(10 + op.condition.value - 1, None, op.address)
        elif isinstance(op, BinaryOp):
            return from_three_registers(20 + op.op.value - 1, op.dst, op.a, op.b)
        else:
            raise RuntimeError(f"Unknown operation type: {type(op)}")
        
class Cassette:
    def __init__(self, code: bytes):
        self.code = code

class Memory:
    SIZE = 4 * (1 << 20)
    INPUT_BEGIN = 0
    USER_MEMORY = 1 * (1 << 20)
    CODE_BEGIN = 2 * (1 << 20)
    STACK_BEGIN = SIZE

    def __init__(self, code: Cassette, input: Cassette):
        self.data = bytearray(self.SIZE)
        self.bind(self.INPUT_BEGIN, input)
        self.bind(self.CODE_BEGIN, code)

    def bind(self, addr: int, cassette: Cassette):
        self.data[addr:addr + len(cassette.code)] = cassette.code

    def load(self, addr: int) -> int:
        if addr > self.SIZE - 4:
            raise RuntimeError(f"Segmentation fault: read {addr}")
        return int.from_bytes(self.data[addr:addr + 4], 'little')

    def store(self, addr: int, value: int):
        if addr > self.SIZE - 4:
            raise RuntimeError(f"Segmentation fault: store {addr} <- {value}")
        self.data[addr:addr + 4] = value.to_bytes(4, 'little')

class Computer:
    FLAG_ZERO = 1
    FLAG_OVERFLOW = 2

    def __init__(self, code_disk: Cassette, input: Cassette):
        self.memory = Memory(code_disk, input)
        self.registers = [0] * Register.count()
        print("Greetings from JetBrains! Running chip simulation.", file=sys.stderr)
        self.store(Register.RINS, Memory.CODE_BEGIN)
        self.store(Register.RST, Memory.STACK_BEGIN)

    def store(self, register: Register, value: int):
        if debug_print: print(f"debug: stored {register} <- {value}", file=sys.stderr)
        self.registers[register.value] = value

    def value(self, register: Register) -> int:
        return self.registers[register.value]

    @property
    def instruction_pointer(self) -> int:
        return self.value(Register.RINS)

    @instruction_pointer.setter
    def instruction_pointer(self, val: int):
        self.store(Register.RINS, val)

    @property
    def stack_pointer(self) -> int:
        return self.value(Register.RST)

    @stack_pointer.setter
    def stack_pointer(self, val: int):
        self.store(Register.RST, val)

    def value_from_expr(self, expr: Expression) -> int: # uint
        imm_int = expr.immediate if expr.immediate < 128 else expr.immediate - 256
        imm = imm_int if imm_int >= 0 else imm_int + 2 ** 32
        # imm = uint(byte)
        reg_val = self.value(expr.register) if expr.register else 0

        result = (imm + reg_val) & 0xFFFFFFFF # it's a uint
        
        carry_flag = 0 
        if imm_int >= 0:
            if result < imm_int: carry_flag = self.FLAG_OVERFLOW
            if result > reg_val:  carry_flag = self.FLAG_OVERFLOW
        flags = carry_flag | (self.FLAG_ZERO if (result == 0) else 0)

        self.store(Register.RFLAG, flags)
        return result

    def handle_binary_op(self, op: BinaryOp):
        a = self.value(op.a)
        b = self.value(op.b)
        if op.op == OperationType.ADD:
            result = (a + b) % (2 ** 32)
            carry = result < a
        elif op.op == OperationType.SUB:
            result = (a - b) % (2 ** 32)
            carry = a < b
        elif op.op == OperationType.MULT:
            result = (a * b) % (2 ** 32)
            carry = False
        flags = (self.FLAG_OVERFLOW if carry else 0) | (self.FLAG_ZERO if result == 0 else 0)
        self.store(op.dst, result)
        self.store(Register.RFLAG, flags)

    def handle_jump(self, op: JumpOp):
        flags = self.value(Register.RFLAG)
        cond = op.condition
        should_jump = (
            cond == JumpCondition.ALWAYS or
            (cond == JumpCondition.ZERO and (flags & self.FLAG_ZERO)) or
            (cond == JumpCondition.NONZERO and not (flags & self.FLAG_ZERO)) or
            (cond == JumpCondition.CARRY and (flags & self.FLAG_OVERFLOW)) or
            (cond == JumpCondition.NOTCARRY and not (flags & self.FLAG_OVERFLOW))
        )
        if should_jump:
            self.registers[Register.RINS.value] = self.value_from_expr(op.address)

    def print_debug(self, op: DebugOp):
        reg_state = " ".join(f"{r}={self.value(r)}" for r in Register)
        if debug_print: print(f"debugop[tag={op.tag}] {reg_state}", file=sys.stderr)

    def exec_op(self, op: Operation):
        if isinstance(op, HaltOp):
            return Exit(self.value_from_expr(op.expression))
        elif isinstance(op, JumpOp):
            self.handle_jump(op)
        elif isinstance(op, LoadOp):
            self.store(op.destination, self.memory.load(self.value_from_expr(op.address)))
        elif isinstance(op, StoreOp):
            self.memory.store(self.value_from_expr(op.address), self.value(op.source))
        elif isinstance(op, PopOp):
            val = self.memory.load(self.stack_pointer)
            self.stack_pointer += 4
            self.store(op.register, val)
        elif isinstance(op, PushOp):
            self.stack_pointer -= 4
            self.memory.store(self.stack_pointer, self.value_from_expr(op.expression))
        elif isinstance(op, BinaryOp):
            self.handle_binary_op(op)
        elif isinstance(op, SetOp):
            self.store(op.register, self.value_from_expr(op.expression))
        elif isinstance(op, DebugOp):
            self.print_debug(op)

    def step(self):
        opcode = self.memory.load(self.instruction_pointer)
        op = CoderDecoder.decode(opcode)
        if debug_print: print(f"executing {op} at {self.instruction_pointer}", file=sys.stderr)
        self.instruction_pointer += 4
        return self.exec_op(op)

    def exec(self, limit: int):
        for _ in range(limit):
            exit_val = self.step()
            if exit_val:
                return exit_val

    def exec_till_exit(self):
        while True:
            exit_val = self.step()
            if exit_val:
                return exit_val

class CodeBuilder:
    def __init__(self, segment_start: int):
        self.segment_start: int = segment_start
        self.code: List[int] = []  # Each byte is stored as int (0-255)
        self.labels: Dict[str, int] = {}
        self.raw_pass: bool = True

    def label(self, label: str):
        self.labels[label] = self.address()

    def get_label(self, l: str) -> int:
        if self.raw_pass:
            return self.address()
        return self.labels[l]

    def address(self) -> int:
        return self.segment_start + len(self.code)

    def byte(self, b: int):
        self.code.append(b)

    def int(self, i: int):
        for it in range(4):
            self.byte(ByteUtils.get_byte(i, it))

    def to_byte_safe(self, val: int) -> int:
        if not -128 <= val <= 127:
            raise ValueError(f"Can't convert to byte: value too large: {val}")
        return val & 0xFF

    def op(self, op: Operation):
        if debug_print: print("Adding " + str(op), file=sys.stderr)
        self.int(CoderDecoder.encode(op))

    def jump_if(self, condition: JumpCondition, goto: str):
        pnow = self.address() + 4  # RINS will shift after this op
        pwant = self.get_label(goto)
        delta = pwant - pnow
        self.op(JumpOp(condition, Expression(Register.RINS, self.to_byte_safe(delta))))

    def jump(self, goto: str):
        self.jump_if(JumpCondition.ALWAYS, goto)

    def set_const(self, register: Register, constant: int):
        self.op(LoadOp(register, Expression(Register.RINS, 4)))
        self.op(JumpOp(JumpCondition.ALWAYS, Expression(Register.RINS, 4)))
        self.int(constant)

    def call(self, goto: str):
        self.op(PushOp(Expression(Register.RINS, 16)))
        self.op(PushOp(Expression(Register.RG)))
        self.op(LoadOp(Register.RG, Expression(Register.RINS, 4)))
        self.op(JumpOp(JumpCondition.ALWAYS, Expression(Register.RG)))
        self.int(self.get_label(goto))
        self.op(NoOp())

    def call_preserving_registers(self, goto: str, *registers: Register):
        for r in registers:
            self.op(PushOp(Expression(r)))
        self.call(goto)
        for r in reversed(registers):
            self.op(PopOp(r))

    def ret(self):
        self.op(PopOp(Register.RG))
        self.op(PopOp(Register.RINS))

    def to_cassette(self) -> Cassette:
        return Cassette(bytes(self.code))

    def set_clean_pass(self):
        self.raw_pass = False
        self.code.clear()

    @staticmethod
    def build_with_params(segment_start: int, script: Callable[['CodeBuilder'], None], print_sym: bool = False) -> Cassette:
        builder = CodeBuilder(segment_start)
        script(builder)
        builder.set_clean_pass()
        script(builder)
        if print_sym:
            for k, v in sorted(builder.labels.items(), key=lambda item: item[1]):
                print(f"sym: {k} to {v}", file=sys.stderr)
        return builder.to_cassette()

def build_code(print_sym: bool = False, script: Callable[[CodeBuilder], None] = None) -> Cassette:
    return CodeBuilder.build_with_params(Memory.CODE_BEGIN, script, print_sym)

def build_data(script: Callable[[CodeBuilder], None]) -> Cassette:
    return CodeBuilder.build_with_params(Memory.INPUT_BEGIN, script)


def program():
    def code(builder:CodeBuilder) -> None:
        builder.label("main")
        builder.call("run")
        builder.op(HaltOp(Expression(Register.RR)))

        builder.label("loadinput")
        builder.op(LoadOp(Register.RA, Expression(None, Memory.INPUT_BEGIN + 0)))
        builder.op(LoadOp(Register.RB, Expression(None, Memory.INPUT_BEGIN + 4)))
        builder.op(LoadOp(Register.RC, Expression(None, Memory.INPUT_BEGIN + 8)))
        builder.ret()

        builder.label("getn")
        builder.call("loadinput")
        builder.op(BinaryOp(OperationType.ADD, Register.RR, Register.RA, Register.RB))
        builder.op(BinaryOp(OperationType.ADD, Register.RR, Register.RR, Register.RC))
        builder.ret()

        builder.label("run")
        builder.call("getn")
        builder.op(SetOp(Register.RA, Expression(Register.RR)))
        builder.op(SetOp(Register.RB, Expression(None, 0)))
        builder.op(SetOp(Register.RC, Expression(None, 0)))
        builder.call("brute")
        builder.op(SetOp(Register.RR, Expression(Register.RC)))
        builder.ret()

        builder.label("brute")
        builder.op(BinaryOp(OperationType.SUB, Register.RR, Register.RA, Register.RB))
        builder.jump_if(JumpCondition.NONZERO, "brute@continue")
        builder.op(DebugOp(1))
        builder.call_preserving_registers("check", Register.RA, Register.RB, Register.RC)
        builder.op(BinaryOp(OperationType.ADD, Register.RC, Register.RC, Register.RR))
        builder.op(DebugOp(2))
        builder.ret()

        builder.label("brute@continue")
        builder.op(SetOp(Register.RB, Expression(Register.RB, 1)))
        builder.op(SetOp(Register.RE, Expression(None, ord('A'))))

        builder.label("inner")
        builder.call_preserving_registers("push", Register.RA, Register.RB)
        builder.call_preserving_registers("brute", Register.RE)
        builder.call_preserving_registers("pop", Register.RA, Register.RB)
        builder.op(SetOp(Register.RE, Expression(Register.RE, 1)))
        builder.op(SetOp(Register.RG, Expression(Register.RE, -ord('D'))))
        builder.jump_if(JumpCondition.NONZERO, "inner")
        builder.op(SetOp(Register.RB, Expression(Register.RB, -1)))
        builder.ret()

        builder.label("#begin")
        builder.int(Memory.USER_MEMORY)
        builder.label("#head")
        builder.int(Memory.USER_MEMORY)

        builder.label("push")
        builder.op(SetOp(Register.RA, Expression(Register.RINS,
            builder.get_label("#head") - builder.address() - 4)))
        builder.op(LoadOp(Register.RB, Expression(Register.RA)))
        builder.op(StoreOp(Register.RE, Expression(Register.RB)))
        builder.op(SetOp(Register.RB, Expression(Register.RB, 4)))
        builder.op(StoreOp(Register.RB, Expression(Register.RA)))
        builder.ret()

        builder.label("pop")
        builder.op(SetOp(Register.RA, Expression(Register.RINS,
            builder.get_label("#head") - builder.address() - 4)))
        builder.op(LoadOp(Register.RB, Expression(Register.RA)))
        builder.op(SetOp(Register.RB, Expression(Register.RB, -4)))
        builder.op(StoreOp(Register.RB, Expression(Register.RA)))
        builder.ret()

        builder.label("check")
        builder.call("loadinput")
        builder.op(SetOp(Register.RR, Expression(None, 1)))
        builder.op(DebugOp(tag=30))
        builder.op(SetOp(Register.RD, Expression(Register.RINS,
            builder.get_label("#begin") - builder.address() - 4)))
        builder.op(SetOp(Register.RE, Expression(Register.RINS,
            builder.get_label("#head") - builder.address() - 4)))
        builder.op(LoadOp(Register.RD, Expression(Register.RD)))
        builder.op(LoadOp(Register.RE, Expression(Register.RE)))
        builder.op(SetOp(Register.RF, Expression(None, 0)))

        builder.label("check@loop")
        builder.op(SetOp(Register.RG, Expression(Register.RF)))
        builder.op(LoadOp(Register.RF, Expression(Register.RD)))
        builder.op(DebugOp(tag=31))
        builder.op(BinaryOp(OperationType.SUB, Register.RG, Register.RF, Register.RG))
        builder.op(JumpOp(JumpCondition.NONZERO, Expression(Register.RINS, 4)))
        builder.op(SetOp(Register.RR, Expression(None, 0)))
        builder.op(DebugOp(tag=32))
        builder.op(PushOp(Expression(Register.RE)))
        builder.op(SetOp(Register.RE, Expression(None, 4)))
        builder.op(SetOp(Register.RG, Expression(Register.RF, -ord('='))))
        builder.op(BinaryOp(OperationType.MULT, Register.RG, Register.RE, Register.RG))
        builder.op(BinaryOp(OperationType.ADD, Register.RG, Register.RINS, Register.RG))
        builder.op(LoadOp(Register.RE, Expression(Register.RG)))
        builder.op(StoreOp(Register.RE, Expression(Register.RINS)))
        builder.op(DebugOp(tag=39))

        builder.op(SetOp(Register.RINS, Expression(Register.RINS, 16)))
        builder.op(SetOp(Register.RA, Expression(Register.RA, -1)))
        builder.op(SetOp(Register.RB, Expression(Register.RB, -1)))
        builder.op(SetOp(Register.RC, Expression(Register.RC, -1)))
        builder.op(SetOp(Register.RD, Expression(Register.RD, -1)))
        builder.op(PopOp(Register.RE))
        builder.op(DebugOp(tag=33))
        builder.op(SetOp(Register.RD, Expression(Register.RD, 4)))
        builder.op(BinaryOp(OperationType.SUB, Register.RG, Register.RD, Register.RE))
        builder.jump_if(JumpCondition.NONZERO, "check@loop")

        for reg in [Register.RA, Register.RB, Register.RC]:
            builder.op(SetOp(Register.RG, Expression(reg)))
            builder.op(JumpOp(JumpCondition.ZERO, Expression(Register.RINS, 4)))
            builder.op(SetOp(Register.RR, Expression(None, 0)))

        builder.op(DebugOp(tag=35))
        builder.ret()

        builder.label("check@false")
        builder.op(SetOp(Register.RR, Expression(None, -1)))
        builder.ret()
    
    return build_code(False, code)

def test_program():
    def code(builder: CodeBuilder):
        builder.op(LoadOp(Register.RA, Expression(None, Memory.INPUT_BEGIN + 0)))
        builder.call("sumall")
        builder.op(HaltOp(Expression(Register.RR)))

        builder.label("squareOf")
        builder.op(BinaryOp(OperationType.MULT, Register.RR, Register.RC, Register.RC))
        builder.ret()

        builder.label("sumall")
        builder.op(SetOp(Register.RC, Expression(Register.RA)))
        builder.op(SetOp(Register.RF, Expression(None)))

        builder.label("sumall@loop")
        builder.call("squareOf")
        builder.op(BinaryOp(OperationType.ADD, Register.RF, Register.RF, Register.RR))
        builder.op(SetOp(Register.RC, Expression(Register.RC, -1)))
        builder.jump_if(JumpCondition.NONZERO, "sumall@loop")

        builder.op(SetOp(Register.RR, Expression(Register.RF)))
        builder.ret()

    return build_code(False, code)

def input_data(a: int, b: int, c: int):
    def data(builder):
        builder.int(a)
        builder.int(b)
        builder.int(c)
    return build_data(data)

def main():
    p = program()
    a, b, c = map(int, input().split())
    input_mem = input_data(a, b, c)
    computer = Computer(p, input_mem)
    exit_result = computer.exec_till_exit()
    print(exit_result.code)

if __name__ == "__main__":
    main()