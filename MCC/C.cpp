#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <stdexcept>
#include <functional>
#include <sstream>
#include <optional>
#include <memory>

using namespace std;

// -----------------------------------------------------------------------------
// Enums and Constants

// Registers (11 registers: RA, RB, RC, RD, RE, RF, RG, RR, RINS, RST, RFLAG)
enum class Register {
    RA = 0, RB, RC, RD, RE, RF, RG, RR, RINS, RST, RFLAG
};

constexpr int REGISTER_COUNT = 11;

optional<Register> registerFromInt(int i) {
    if(i >= 0 && i < REGISTER_COUNT)
        return static_cast<Register>(i);
    else if(i == REGISTER_COUNT)
        return nullopt;
    else 
        throw runtime_error("Illegal register");
}

// Jump conditions
enum class JumpCondition {
    ALWAYS, ZERO, NONZERO, CARRY, NOTCARRY
};

// Operation types (for Binary operations)
enum class OperationType {
    ADD, SUB, MULT
};

// -----------------------------------------------------------------------------
// Expression structure
struct Expression {
    // The register is optional (if none, then a “pure” immediate value)
    optional<Register> reg;
    int immediate;  // signed immediate (treated as a byte in encoding)

    Expression(optional<Register> r = nullopt, int imm = 0)
        : reg(r), immediate(imm) {}
};

// -----------------------------------------------------------------------------
// Operation hierarchy

// Base class (abstract)
struct Operation {
    virtual ~Operation() {}
};

struct NoOp : public Operation { };

struct LoadOp : public Operation {
    Register destination;
    Expression address;
    LoadOp(Register dest, Expression addr) : destination(dest), address(addr) {}
};

struct StoreOp : public Operation {
    Register source;
    Expression address;
    StoreOp(Register src, Expression addr) : source(src), address(addr) {}
};

struct JumpOp : public Operation {
    JumpCondition condition;
    Expression address;
    JumpOp(JumpCondition cond, Expression addr) : condition(cond), address(addr) {}
};

struct PushOp : public Operation {
    Expression expression;
    PushOp(Expression expr) : expression(expr) {}
};

struct PopOp : public Operation {
    Register reg;
    PopOp(Register r) : reg(r) {}
};

struct HaltOp : public Operation {
    Expression expression;
    HaltOp(Expression expr) : expression(expr) {}
};

struct SetOp : public Operation {
    Register reg;
    Expression expression;
    SetOp(Register r, Expression expr) : reg(r), expression(expr) {}
};

struct BinaryOp : public Operation {
    OperationType op;
    Register dst;
    Register a;
    Register b;
    BinaryOp(OperationType op_, Register dst_, Register a_, Register b_)
        : op(op_), dst(dst_), a(a_), b(b_) {}
};

struct DebugOp : public Operation {
    int tag;
    DebugOp(int t) : tag(t) {}
};

// Exit structure (when the simulation halts)
struct Exit {
    int code;
    Exit(int c) : code(c) {}
};

// -----------------------------------------------------------------------------
// Byte utilities for encoding/decoding (working in little-endian)
class ByteUtils {
public:
    static uint8_t get_byte(uint32_t num, int byte_index) {
        return (num >> (8 * byte_index)) & 0xFF;
    }
    static uint32_t read_byte(uint8_t byte, int byte_index) {
        return static_cast<uint32_t>(byte) << (8 * byte_index);
    }
};

// -----------------------------------------------------------------------------
// Operation Encoding/Decoding
class CoderDecoder {
public:
    // Decodes a 32‐bit word into an operation object.
    static unique_ptr<Operation> decode(uint32_t data) {
        uint8_t opcode = ByteUtils::get_byte(data, 0);
        uint8_t byte2  = ByteUtils::get_byte(data, 1);
        uint8_t byte3  = ByteUtils::get_byte(data, 2);
        uint8_t byte4  = ByteUtils::get_byte(data, 3);

        auto register1 = [&]() -> Register {
            auto r = registerFromInt(byte2);
            if(!r.has_value())
                throw runtime_error("Invalid register value in decode");
            return r.value();
        };
        auto register2 = [&]() -> optional<Register> {
            return registerFromInt(byte3);
        };
        auto expr = [&]() -> Expression {
            return Expression(register2(), byte4);
        };
        auto register3 = [&]() -> Register {
            auto r = registerFromInt(byte4);
            if (!r.has_value())
                throw runtime_error("Invalid register value in decode");
            return r.value();
        };

        if (opcode == 0) {
            return make_unique<NoOp>();
        } else if (opcode == 1) {
            return make_unique<LoadOp>(register1(), expr());
        } else if (opcode == 2) {
            return make_unique<StoreOp>(register1(), expr());
        } else if (opcode == 3) {
            return make_unique<PushOp>(expr());
        } else if (opcode == 4) {
            return make_unique<PopOp>(register1());
        } else if (opcode == 5) {
            return make_unique<HaltOp>(expr());
        } else if (opcode == 6) {
            return make_unique<SetOp>(register1(), expr());
        } else if (opcode == 7) {
            return make_unique<DebugOp>(byte2);
        } else if (opcode >= 10 && opcode < 10 + 5) { // 5 jump conditions
            int condIndex = opcode - 10;
            JumpCondition cond = static_cast<JumpCondition>(condIndex);
            return make_unique<JumpOp>(cond, expr());
        } else if (opcode >= 20 && opcode < 20 + 3) { // 3 binary operation types
            int opIndex = opcode - 20;
            OperationType opType = static_cast<OperationType>(opIndex);
            return make_unique<BinaryOp>(opType, register1(), register2().value(), register3());
        } else {
            throw runtime_error("Illegal instruction " + to_string(opcode));
        }
    }

    // Encodes an Operation into a 32‐bit word.
    static uint32_t encode(const Operation &op) {
        auto is_byte = [&](int x) {
            return x >= 0 && x <= 255;
        };

        auto from_bytes = [&](int a, int b, int c, int d) -> uint32_t {
            if (!is_byte(a) || !is_byte(b) || !is_byte(c) || !is_byte(d))
                throw runtime_error("Byte value out of range in from_bytes");
            return ByteUtils::read_byte(a, 0) |
                   ByteUtils::read_byte(b, 1) |
                   ByteUtils::read_byte(c, 2) |
                   ByteUtils::read_byte(d, 3);
        };

        auto convert_register_opt = [&](const optional<Register>& r) -> int {
            return r.has_value() ? static_cast<int>(r.value()) : REGISTER_COUNT;
        };
        auto convert_register_val = [&](Register r) -> int {
            return static_cast<int>(r);
        };

        auto from_register_and_expr = [&](int opcode, const optional<Register>& r, const Expression &expr) -> uint32_t {
            return from_bytes(opcode, convert_register_opt(r),
                              convert_register_opt(expr.reg), expr.immediate & 0xFF);
        };
        auto from_register = [&](int opcode, const optional<Register>& r) -> uint32_t {
            return from_bytes(opcode, convert_register_opt(r), 0, 0);
        };
        auto from_three_registers = [&](int opcode, Register r1, Register r2, Register r3) -> uint32_t {
            return from_bytes(opcode, convert_register_val(r1),
                              convert_register_val(r2), convert_register_val(r3));
        };

        if (dynamic_cast<const NoOp*>(&op))
            return from_register(0, nullopt);
        else if (auto p = dynamic_cast<const LoadOp*>(&op))
            return from_register_and_expr(1, optional<Register>(p->destination), p->address);
        else if (auto p = dynamic_cast<const StoreOp*>(&op))
            return from_register_and_expr(2, optional<Register>(p->source), p->address);
        else if (auto p = dynamic_cast<const PushOp*>(&op))
            return from_register_and_expr(3, nullopt, p->expression);
        else if (auto p = dynamic_cast<const PopOp*>(&op))
            return from_register(4, optional<Register>(p->reg));
        else if (auto p = dynamic_cast<const HaltOp*>(&op))
            return from_register_and_expr(5, nullopt, p->expression);
        else if (auto p = dynamic_cast<const SetOp*>(&op))
            return from_register_and_expr(6, optional<Register>(p->reg), p->expression);
        else if (auto p = dynamic_cast<const DebugOp*>(&op))
            return from_bytes(7, p->tag, 0, 0);
        else if (auto p = dynamic_cast<const JumpOp*>(&op)) {
            int opcode_val = 10 + static_cast<int>(p->condition);
            return from_register_and_expr(opcode_val, nullopt, p->address);
        } else if (auto p = dynamic_cast<const BinaryOp*>(&op)) {
            int opcode_val = 20 + static_cast<int>(p->op);
            return from_three_registers(opcode_val, p->dst, p->a, p->b);
        } else {
            throw runtime_error("Unknown operation type in encode");
        }
    }
};

// -----------------------------------------------------------------------------
// Cassette: a container for code bytes
class Cassette {
public:
    vector<uint8_t> code;
    Cassette(const vector<uint8_t>& data) : code(data) { }
};

// -----------------------------------------------------------------------------
// Memory
class Memory {
public:
    static const int SIZE = 4 * (1 << 20);      // 4 MB of memory
    static const int INPUT_BEGIN = 0;
    static const int USER_MEMORY = 1 * (1 << 20);
    static const int CODE_BEGIN = 2 * (1 << 20);
    static const int STACK_BEGIN = SIZE;

    vector<uint8_t> data;

    Memory(const Cassette &codeCassette, const Cassette &inputCassette) {
        data.resize(SIZE, 0);
        bind(INPUT_BEGIN, inputCassette);
        bind(CODE_BEGIN, codeCassette);
    }

    void bind(int addr, const Cassette &cassette) {
        if(addr < 0 || addr + cassette.code.size() > data.size())
            throw runtime_error("Memory bind out of range");
        for (size_t i = 0; i < cassette.code.size(); ++i)
            data[addr + i] = cassette.code[i];
    }

    uint32_t load(int addr) {
        if (addr > SIZE - 4)
            throw runtime_error("Segmentation fault: read " + to_string(addr));
        uint32_t value = 0;
        // Read 4 bytes in little-endian order
        for (int i = 0; i < 4; ++i)
            value |= (static_cast<uint32_t>(data[addr + i]) << (8 * i));
        return value;
    }

    void store(int addr, uint32_t value) {
        if (addr > SIZE - 4)
            throw runtime_error("Segmentation fault: store " + to_string(addr) +
                                 " <- " + to_string(value));
        for (int i = 0; i < 4; ++i)
            data[addr + i] = ByteUtils::get_byte(value, i);
    }
};

// -----------------------------------------------------------------------------
// Computer Simulator

class Computer {
public:
    static const uint32_t FLAG_ZERO = 1;
    static const uint32_t FLAG_OVERFLOW = 2;

    Memory memory;
    vector<uint32_t> registers;  // indexed by Register::(value)

    Computer(const Cassette &code_disk, const Cassette &input)
        : memory(code_disk, input), registers(REGISTER_COUNT, 0)
    {
        cerr << "Greetings from JetBrains! Running chip simulation." << endl;
        store(Register::RINS, Memory::CODE_BEGIN);
        store(Register::RST, Memory::STACK_BEGIN);
    }

    void store(Register reg, uint32_t value) {
        registers[static_cast<int>(reg)] = value;
    }

    uint32_t value(Register reg) {
        return registers[static_cast<int>(reg)];
    }

    uint32_t& instruction_pointer() {
        return registers[static_cast<int>(Register::RINS)];
    }

    uint32_t& stack_pointer() {
        return registers[static_cast<int>(Register::RST)];
    }

    // Evaluate an Expression: adds an (8‐bit signed) immediate to (optionally) a register value.
    uint32_t value_from_expr(const Expression &expr) {
        int imm_int = (expr.immediate < 128) ? expr.immediate : expr.immediate - 256;
        uint32_t imm = (imm_int >= 0) ? imm_int : imm_int + (1ULL << 32);
        uint32_t reg_val = expr.reg.has_value() ? value(expr.reg.value()) : 0;
        uint32_t result = (imm + reg_val) & 0xFFFFFFFF;

        uint32_t carry_flag = 0;
        if (imm_int >= 0) {
            if (result < static_cast<uint32_t>(imm_int))
                carry_flag = FLAG_OVERFLOW;
            if (result > reg_val)
                carry_flag = FLAG_OVERFLOW;
        }
        uint32_t flags = carry_flag | ((result == 0) ? FLAG_ZERO : 0);
        store(Register::RFLAG, flags);
        return result;
    }

    void handle_binary_op(const BinaryOp &op) {
        uint32_t a = value(op.a);
        uint32_t b = value(op.b);
        uint32_t result = 0;
        bool carry = false;
        if(op.op == OperationType::ADD) {
            result = (a + b) % (1ULL << 32);
            carry = (result < a);
        } else if(op.op == OperationType::SUB) {
            result = (a - b) % (1ULL << 32);
            carry = (a < b);
        } else if(op.op == OperationType::MULT) {
            result = (static_cast<uint64_t>(a) * static_cast<uint64_t>(b)) % (1ULL << 32);
            carry = false;
        }
        uint32_t flags = (carry ? FLAG_OVERFLOW : 0) | ((result == 0) ? FLAG_ZERO : 0);
        store(op.dst, result);
        store(Register::RFLAG, flags);
    }

    void handle_jump(const JumpOp &op) {
        uint32_t flags = value(Register::RFLAG);
        bool should_jump = false;
        switch(op.condition) {
            case JumpCondition::ALWAYS:  should_jump = true; break;
            case JumpCondition::ZERO:    should_jump = (flags & FLAG_ZERO); break;
            case JumpCondition::NONZERO: should_jump = !(flags & FLAG_ZERO); break;
            case JumpCondition::CARRY:   should_jump = (flags & FLAG_OVERFLOW); break;
            case JumpCondition::NOTCARRY:should_jump = !(flags & FLAG_OVERFLOW); break;
        }
        if(should_jump) {
            registers[static_cast<int>(Register::RINS)] = value_from_expr(op.address);
        }
    }

    // For debug instructions: print current registers state.
    void print_debug(const DebugOp &op) {
        // string regNames[REGISTER_COUNT] = {"RA", "RB", "RC", "RD", "RE",
        //                                      "RF", "RG", "RR", "RINS", "RST", "RFLAG"};
        // stringstream ss;
        // for (int i = 0; i < REGISTER_COUNT; i++) {
        //     ss << regNames[i] << "=" << registers[i] << " ";
        // }
        // cerr << "debugop[tag=" << op.tag << "] " << ss.str() << endl;
    }

    // Execute one operation. Returns an Exit if a halt instruction is encountered.
    optional<Exit> exec_op(const Operation &op) {
        if (auto p = dynamic_cast<const HaltOp*>(&op))
            return Exit(int(value_from_expr(p->expression)));
        else if (auto p = dynamic_cast<const JumpOp*>(&op))
            handle_jump(*p);
        else if (auto p = dynamic_cast<const LoadOp*>(&op))
            store(p->destination, memory.load(value_from_expr(p->address)));
        else if (auto p = dynamic_cast<const StoreOp*>(&op))
            memory.store(value_from_expr(p->address), value(p->source));
        else if (auto p = dynamic_cast<const PopOp*>(&op)) {
            uint32_t val = memory.load(stack_pointer());
            stack_pointer() += 4;
            store(p->reg, val);
        }
        else if (auto p = dynamic_cast<const PushOp*>(&op)) {
            stack_pointer() -= 4;
            memory.store(stack_pointer(), value_from_expr(p->expression));
        }
        else if (auto p = dynamic_cast<const BinaryOp*>(&op))
            handle_binary_op(*p);
        else if (auto p = dynamic_cast<const SetOp*>(&op))
            store(p->reg, value_from_expr(p->expression));
        else if (auto p = dynamic_cast<const DebugOp*>(&op))
            print_debug(*p);
        return nullopt;
    }

    // Execute one step (one 4-byte instruction)
    optional<Exit> step() {
        uint32_t opcode = memory.load(instruction_pointer());
        unique_ptr<Operation> op = CoderDecoder::decode(opcode);
        instruction_pointer() += 4;
        return exec_op(*op);
    }

    // Execute up to 'limit' steps.
    optional<Exit> exec(int limit) {
        for (int i = 0; i < limit; ++i) {
            auto exit_val = step();
            if(exit_val.has_value())
                return exit_val;
        }
        return nullopt;
    }

    // Run until a Halt instruction returns an Exit.
    Exit exec_till_exit() {
        while(true) {
            auto exit_val = step();
            if(exit_val.has_value())
                return exit_val.value();
        }
    }
};

// -----------------------------------------------------------------------------
// CodeBuilder: helps build a sequence of instructions
class CodeBuilder {
public:
    int segment_start;
    vector<uint8_t> code;  // Each element is a byte (0-255)
    map<string, int> labels;
    bool raw_pass;

    CodeBuilder(int seg_start) : segment_start(seg_start), raw_pass(true) { }

    void label(const string &lbl) {
        labels[lbl] = address();
    }

    int get_label(const string &lbl) {
        if (raw_pass) return address();
        if (labels.find(lbl) == labels.end())
            throw runtime_error("Label not found: " + lbl);
        return labels[lbl];
    }

    int address() {
        return segment_start + code.size();
    }

    void byte(uint8_t b) {
        code.push_back(b);
    }

    // Write a 32-bit integer (little-endian) as four bytes.
    void int32(uint32_t i) {
        for (int it = 0; it < 4; ++it)
            byte(ByteUtils::get_byte(i, it));
    }

    // Converts an int to a signed byte (ensuring it fits in -128..127)
    uint8_t to_byte_safe(int val) {
        if(val < -128 || val > 127)
            throw runtime_error("Can't convert to byte: value too large: " + to_string(val));
        return static_cast<uint8_t>(val & 0xFF);
    }

    // Append an operation (its 4-byte encoding) to the code.
    void op(const Operation &op) {
        uint32_t encoded = CoderDecoder::encode(op);
        int32(encoded);
    }

    // Append a jump_if instruction.
    void jump_if(JumpCondition condition, const string &goto_label) {
        int pnow = address() + 4;  // After this op, RINS will be at a new offset.
        int pwant = get_label(goto_label);
        int delta = pwant - pnow;
        JumpOp jop(condition, Expression(Register::RINS, to_byte_safe(delta)));
        op(jop);
    }

    // Unconditional jump.
    void jump(const string &goto_label) {
        jump_if(JumpCondition::ALWAYS, goto_label);
    }

    // Set a constant value into a register (using a two‐instruction sequence).
    void set_const(Register reg, int constant) {
        LoadOp lop(reg, Expression(Register::RINS, 4));
        op(lop);
        JumpOp jop(JumpCondition::ALWAYS, Expression(Register::RINS, 4));
        op(jop);
        int32(constant);
    }

    // Generate a “call” sequence.
    void call(const string &goto_label) {
        PushOp pop1{ Expression(Register::RINS, 16) };
        op(pop1);
        PushOp pop2{ Expression(Register::RG) };
        op(pop2);
        LoadOp lop{ Register::RG, Expression(Register::RINS, 4) };
        op(lop);
        JumpOp jop{ JumpCondition::ALWAYS, Expression(Register::RG) };
        op(jop);
        int32(get_label(goto_label));
        NoOp noop;
        op(noop);
    }

    // Call a routine while preserving a given set of registers.
    void call_preserving_registers(const string &goto_label, const vector<Register> &regs) {
        for (auto r : regs) {
            PushOp pop{ Expression(r) };
            op(pop);
        }
        call(goto_label);
        for (auto it = regs.rbegin(); it != regs.rend(); ++it) {
            PopOp pop{ *it };
            op(pop);
        }
    }

    // Generate a return (pop routine pointer and instruction pointer).
    void ret() {
        PopOp pop1(Register::RG);
        op(pop1);
        PopOp pop2(Register::RINS);
        op(pop2);
    }

    // Convert the built code into a Cassette.
    Cassette to_cassette() {
        return Cassette(code);
    }

    // Switch from the “raw” first pass to a clean second pass.
    void set_clean_pass() {
        raw_pass = false;
        code.clear();
    }

    // Static helper: build a cassette from a script lambda.
    static Cassette build_with_params(int segment_start,
            function<void(CodeBuilder&)> script, bool print_sym = false) {
        CodeBuilder builder(segment_start);
        script(builder);
        builder.set_clean_pass();
        script(builder);
        if(print_sym) {
            for(auto &pair : builder.labels)
                cerr << "sym: " << pair.first << " to " << pair.second << endl;
        }
        return builder.to_cassette();
    }
};

// Helper functions to build code and data cassettes.
Cassette build_code(bool print_sym, function<void(CodeBuilder&)> script) {
    return CodeBuilder::build_with_params(Memory::CODE_BEGIN, script, print_sym);
}

Cassette build_data(function<void(CodeBuilder&)> script) {
    return CodeBuilder::build_with_params(Memory::INPUT_BEGIN, script);
}

// -----------------------------------------------------------------------------
// Program Code (the “main” program script)

Cassette program() {
    auto code = [](CodeBuilder &builder) {
        builder.label("main");
        builder.call("run");
        builder.op(HaltOp(Expression(Register::RR)));

        builder.label("loadinput");
        builder.op(LoadOp(Register::RA, Expression(nullopt, Memory::INPUT_BEGIN + 0)));
        builder.op(LoadOp(Register::RB, Expression(nullopt, Memory::INPUT_BEGIN + 4)));
        builder.op(LoadOp(Register::RC, Expression(nullopt, Memory::INPUT_BEGIN + 8)));
        builder.ret();

        builder.label("getn");
        builder.call("loadinput");
        builder.op(BinaryOp(OperationType::ADD, Register::RR, Register::RA, Register::RB));
        builder.op(BinaryOp(OperationType::ADD, Register::RR, Register::RR, Register::RC));
        builder.ret();

        builder.label("run");
        builder.call("getn");
        builder.op(SetOp(Register::RA, Expression(Register::RR)));
        builder.op(SetOp(Register::RB, Expression(nullopt, 0)));
        builder.op(SetOp(Register::RC, Expression(nullopt, 0)));
        builder.call("brute");
        builder.op(SetOp(Register::RR, Expression(Register::RC)));
        builder.ret();

        builder.label("brute");
        builder.op(BinaryOp(OperationType::SUB, Register::RR, Register::RA, Register::RB));
        builder.jump_if(JumpCondition::NONZERO, "brute@continue");
        builder.op(DebugOp(1));
        builder.call_preserving_registers("check", {Register::RA, Register::RB, Register::RC});
        builder.op(BinaryOp(OperationType::ADD, Register::RC, Register::RC, Register::RR));
        builder.op(DebugOp(2));
        builder.ret();

        builder.label("brute@continue");
        builder.op(SetOp(Register::RB, Expression(Register::RB, 1)));
        builder.op(SetOp(Register::RE, Expression(nullopt, int('A'))));

        builder.label("inner");
        builder.call_preserving_registers("push", {Register::RA, Register::RB});
        builder.call_preserving_registers("brute", {Register::RE});
        builder.call_preserving_registers("pop", {Register::RA, Register::RB});
        builder.op(SetOp(Register::RE, Expression(Register::RE, 1)));
        builder.op(SetOp(Register::RG, Expression(Register::RE, -int('D'))));
        builder.jump_if(JumpCondition::NONZERO, "inner");
        builder.op(SetOp(Register::RB, Expression(Register::RB, -1)));
        builder.ret();

        builder.label("#begin");
        builder.int32(Memory::USER_MEMORY);
        builder.label("#head");
        builder.int32(Memory::USER_MEMORY);

        builder.label("push");
        builder.op(SetOp(Register::RA, Expression(Register::RINS,
            builder.get_label("#head") - builder.address() - 4)));
        builder.op(LoadOp(Register::RB, Expression(Register::RA)));
        builder.op(StoreOp(Register::RE, Expression(Register::RB)));
        builder.op(SetOp(Register::RB, Expression(Register::RB, 4)));
        builder.op(StoreOp(Register::RB, Expression(Register::RA)));
        builder.ret();

        builder.label("pop");
        builder.op(SetOp(Register::RA, Expression(Register::RINS,
            builder.get_label("#head") - builder.address() - 4)));
        builder.op(LoadOp(Register::RB, Expression(Register::RA)));
        builder.op(SetOp(Register::RB, Expression(Register::RB, -4)));
        builder.op(StoreOp(Register::RB, Expression(Register::RA)));
        builder.ret();

        builder.label("check");
        builder.call("loadinput");
        builder.op(SetOp(Register::RR, Expression(nullopt, 1)));
        builder.op(DebugOp(30));
        builder.op(SetOp(Register::RD, Expression(Register::RINS,
            builder.get_label("#begin") - builder.address() - 4)));
        builder.op(SetOp(Register::RE, Expression(Register::RINS,
            builder.get_label("#head") - builder.address() - 4)));
        builder.op(LoadOp(Register::RD, Expression(Register::RD)));
        builder.op(LoadOp(Register::RE, Expression(Register::RE)));
        builder.op(SetOp(Register::RF, Expression(nullopt, 0)));

        builder.label("check@loop");
        builder.op(SetOp(Register::RG, Expression(Register::RF)));
        builder.op(LoadOp(Register::RF, Expression(Register::RD)));
        builder.op(DebugOp(31));
        builder.op(BinaryOp(OperationType::SUB, Register::RG, Register::RF, Register::RG));
        builder.op(JumpOp(JumpCondition::NONZERO, Expression(Register::RINS, 4)));
        builder.op(SetOp(Register::RR, Expression(nullopt, 0)));
        builder.op(DebugOp(32));
        builder.op(PushOp(Expression(Register::RE)));
        builder.op(SetOp(Register::RE, Expression(nullopt, 4)));
        builder.op(SetOp(Register::RG, Expression(Register::RF, -int('='))));
        builder.op(BinaryOp(OperationType::MULT, Register::RG, Register::RE, Register::RG));
        builder.op(BinaryOp(OperationType::ADD, Register::RG, Register::RINS, Register::RG));
        builder.op(LoadOp(Register::RE, Expression(Register::RG)));
        builder.op(StoreOp(Register::RE, Expression(Register::RINS)));
        builder.op(DebugOp(39));

        builder.op(SetOp(Register::RINS, Expression(Register::RINS, 16)));
        builder.op(SetOp(Register::RA, Expression(Register::RA, -1)));
        builder.op(SetOp(Register::RB, Expression(Register::RB, -1)));
        builder.op(SetOp(Register::RC, Expression(Register::RC, -1)));
        builder.op(SetOp(Register::RD, Expression(Register::RD, -1)));
        builder.op(PopOp(Register::RE));
        builder.op(DebugOp(33));
        builder.op(SetOp(Register::RD, Expression(Register::RD, 4)));
        builder.op(BinaryOp(OperationType::SUB, Register::RG, Register::RD, Register::RE));
        builder.jump_if(JumpCondition::NONZERO, "check@loop");

        for (Register reg : {Register::RA, Register::RB, Register::RC}) {
            builder.op(SetOp(Register::RG, Expression(reg)));
            builder.op(JumpOp(JumpCondition::ZERO, Expression(Register::RINS, 4)));
            builder.op(SetOp(Register::RR, Expression(nullopt, 0)));
        }

        builder.op(DebugOp(35));
        builder.ret();

        builder.label("check@false");
        builder.op(SetOp(Register::RR, Expression(nullopt, -1)));
        builder.ret();
    };
    return build_code(false, code);
}

// -----------------------------------------------------------------------------
// Test Program (an alternate script example)

Cassette test_program() {
    auto code = [](CodeBuilder &builder) {
        builder.op(LoadOp(Register::RA, Expression(nullopt, Memory::INPUT_BEGIN + 0)));
        builder.call("sumall");
        builder.op(HaltOp(Expression(Register::RR)));

        builder.label("squareOf");
        builder.op(BinaryOp(OperationType::MULT, Register::RR, Register::RC, Register::RC));
        builder.ret();

        builder.label("sumall");
        builder.op(SetOp(Register::RC, Expression(Register::RA)));
        builder.op(SetOp(Register::RF, Expression(nullopt, 0)));

        builder.label("sumall@loop");
        builder.call("squareOf");
        builder.op(BinaryOp(OperationType::ADD, Register::RF, Register::RF, Register::RR));
        builder.op(SetOp(Register::RC, Expression(Register::RC, -1)));
        builder.jump_if(JumpCondition::NONZERO, "sumall@loop");

        builder.op(SetOp(Register::RR, Expression(Register::RF)));
        builder.ret();
    };
    return build_code(false, code);
}

// -----------------------------------------------------------------------------
// Input Data: Build a cassette for input values.
Cassette input_data(int a, int b, int c) {
    auto data = [a, b, c](CodeBuilder &builder) {
        builder.int32(a);
        builder.int32(b);
        builder.int32(c);
    };
    return build_data(data);
}

// -----------------------------------------------------------------------------
// main: read input, build memory images, run the simulation.
int main() {
    Cassette p = program();
    int a, b, c;
    cin >> a >> b >> c;
    Cassette input_mem = input_data(a, b, c);
    Computer computer(p, input_mem);
    Exit exit_result = computer.exec_till_exit();
    cout << exit_result.code << endl;
    return 0;
}
