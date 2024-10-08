#!/usr/bin/env zsh
 
cp ~/Competitive-Programming-Problems/Library/runner.py runner.py #Replace the first string with the path to runner.py!
 
for ((testNum=0;testNum<$3;testNum++))
do
    python3 runner.py --command1-stdout-prefix "Pro: " --command2-stdout-prefix "Int: " ./$1 ./$2 > out
 
    if [ "$(awk 'NF{p=$0}END{print p}' out)" != "Int: OK" ] 
    then
        echo "Error found!"
        echo "Interaction:"
        cat out
        exit
    fi
done
echo Passed $3 tests