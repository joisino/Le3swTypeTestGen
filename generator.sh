num=100
comp=3
cnt=0
level=4

function usage() {
    cat <<EOF
Usage: $0 [OPTION]

Options:
-h: show help
-c COMP: set complexity
-n NUM: num of tests
-1: generate only ML1 case
-2: generate only ML2 case
-3: generate only ML3 case
EOF
    exit 1
}

while getopts hc:n:123 OPT
do
    case $OPT in
        "h" ) usage ;;
        "c" ) comp="$OPTARG" ;;
        "n" ) num="$OPTARG" ;;
        "1" ) level=1 ;;
        "2" ) level=2 ;;
        "3" ) level=3 ;;
        * ) usage ;;
    esac
done

while [ $num -gt 0 ]
do
    
    testcase=`./main -s $cnt -c $comp -l $level`
    check=`echo $testcase | ocaml | grep " : "`
    if [ -n "$check" ]; then
	num=`expr $num - 1`
	echo $testcase
    fi
    cnt=`expr $cnt + 1`
done
