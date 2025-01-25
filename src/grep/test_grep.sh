  #${#___[@]} вычисление количества элементов в массиве
#+=  добавляю элементы к массиву
#"-i" "-c" "-v" "-l" "-h" "-s" "f"
#"haski2.txt"
flag=("-i" "-c" "-v" "-l" "-h" "-s" "-e")
pattern=(
"Siberian"
"You"
)

file=("haski.txt" "haski2.txt")
fail=0
success=0

numb=1

if [ -d "differ" ];
then
    rm -rf differ
    mkdir differ
else 
    mkdir differ
fi

echo "LETS BEGIN!"
for ((c = 0; c < 500; c++));
do 
    chosen_flag=""
    chosen_pattern=""
    chosen_file=""

    numb_flag=$((0 + RANDOM % ${#flag[@]}))
    numb_file=$((1 + RANDOM % ${#file[@]}))
    numb_pattern=$((1 + RANDOM % ${#pattern[@]}))

    for ((f=0; f<numb_flag; f++));
    do 
        index=$((RANDOM % ${#flag[@]}))
        chosen_flag+=" ${flag[index]}"
    done

    for ((i=0; i<numb_file; i++));
    do 
        index=$((RANDOM % ${#file[@]})) 
        chosen_file+=" ${file[index]}"
    done 

    for ((p=0; p<numb_pattern; p++));
    do
        index=$((RANDOM % ${#pattern[@]}))
        chosen_pattern+=" ${pattern[index]}"
    done

    ./s21_grep $chosen_flag $chosen_pattern $chosen_file > cmp1
    grep $chosen_flag $chosen_pattern $chosen_file >cmp2
    if diff -q cmp1 cmp2 > /dev/null 2>&1;
    then
        echo "Test $numb | $chosen_flag $chosen_pattern $chosen_file : success"
        ((success++))
    else 
        echo "Test $numb : | $chosen_flag $chosen_pattern $chosen_file :     FAIL"
        touch differ/diff.txt
        echo "Test $numb : | $chosen_flag $chosen_pattern $chosen_file :     FAIL" >> differ/diff.txt
        ((fail++))
    fi
    ((numb++))
done

echo "Успешно: $success"
echo "Провал: $fail"
echo "Всего: $((numb - 1))"