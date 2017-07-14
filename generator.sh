num=100
while [ $num -gt 0 ]
do
    testcase=`./main`
    check=`echo $testcase | ocaml | grep " : "`
    if [ -n "$check" ]; then
	num=`expr $num - 1`
	echo $testcase
    fi
done