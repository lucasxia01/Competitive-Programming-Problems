files=`ls data/secret/*.in`
for file in $files
do
    pref=`echo "$file" | sed 's/\..*//'`
    echo $pref
    ./a.out < "$pref.in" > tmp.txt
    diff tmp.txt "$pref.ans"
    ret=`echo $?`
    echo $ret
    if [ $ret == 1 ]
    then
        exit
    fi
done