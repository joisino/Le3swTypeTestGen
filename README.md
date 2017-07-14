# automatical testcase generator for le3sw type inference


## usage

```
make
bash generator.sh
```

```
make
bash generator.sh -n 10 > tmp
cat tmp | ocaml -w -a
cat tmp | ./your_interpreter
```
