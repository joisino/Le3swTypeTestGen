num=100

if [ $# -eq 1 ]; then
    num=$1
fi

while [ $num -gt 0 ]
do
    testcase=`./main`
    check=`echo $testcase | ocaml | grep " : "`
    if [ -n "$check" ]; then
	num=`expr $num - 1`
	echo $testcase
    fi
done
