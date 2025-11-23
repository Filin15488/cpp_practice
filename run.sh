first=true
while IFS= read -r line; do
    if $first; then
        echo "$line" | ./main > output.txt   # перезапись
        first=false
    else
        echo "$line" | ./main >> output.txt  # добавление
    fi
done < input.txt
