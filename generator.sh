num=100
cnt=0

if [ $# -eq 1 ]; then
    num=$1
fi

while [ $num -gt 0 ]
do
    testcase=`./main -s $cnt`
    check=`echo $testcase | ocaml | grep " : "`
    if [ -n "$check" ]; then
	num=`expr $num - 1`
	echo $testcase
    fi
    cnt=`expr $cnt + 1`
done
