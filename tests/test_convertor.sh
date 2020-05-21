i=913

for file in test_shell/tests/*; do
    echo "["$i"]"
    echo "NAME=\"$i\""
    echo 'SETUP=""'
    echo 'CLEAN=""'
    echo "TESTS="
    cat $file | sed s/^/"echo '"/ | sed s/$/\'/
    echo "'"
    echo "["$i"-END]"
    echo ""
    ((i++))
done