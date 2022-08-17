ins=`ls /Users/lucasxia/Downloads/data/hopscotch500/data/secret/*.in`
for IN in $ins
do
    echo $IN
    ./a.out < $IN
    cat ${IN/.in/.ans}
done
