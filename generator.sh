num=100
comp=3
cnt=0

function usage() {
    cat <<EOF
Usage: $0 [OPTION]

Options:
-h: show help
-c COMP: set complexity
-n NUM: num of tests
EOF
    exit 1
}

while getopts hc:n: OPT
do
    case $OPT in
        "h" ) usage ;;
        "c" ) comp="$OPTARG" ;;
        "n" ) num="$OPTARG" ;;
        * ) usage ;;
    esac
done

if [ $# -eq 1 ]; then
    num=$1
fi

while [ $num -gt 0 ]
do
    testcase=`./main -s $cnt -c $comp`
    check=`echo $testcase | ocaml | grep " : "`
    if [ -n "$check" ]; then
	num=`expr $num - 1`
	echo $testcase
    fi
    cnt=`expr $cnt + 1`
done
