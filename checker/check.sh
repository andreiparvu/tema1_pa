#!/bin/bash

total=0

count_java=`ls -l *.java 2> /dev/null | wc -l`

make -f Makefile-checker build-checker

run_problem() {
  name=$1
  id=$2
  start=$3
  end=$4

  for i in $(seq $start $end); do
    cp $name$i.in date.in
    cp $name$i.ok res.ok

    if [ -z "`cat Makefile | grep run-p2`" ]; then
      echo "Test $i problema $id .......... 0/5 - Regula make inexistenta!"
      continue
    fi

    timeout=`cat c.timeout$id`

    if [ $count_java -gt 0 ]; then
      timeout=`cat java.timeout$id`
    fi

    ./tracker run-p$id $timeout

    if [ -z "`cat error.exec | grep \"Clock skew detected\"`" ]; then
      cat error.exec > errors
    else
      n=`wc -l error.exec | cut -d ' ' -f 1`
      head -$((n - 2)) error.exec > errors
    fi

    if [ ! -z "`cat errors`" ]; then
      echo "Test $i problema $id ......... 0/5 -"
      cat error.exec
    elif [ ! -z "`cat error.time`" ]; then
      echo "Test $i problema $id .......... 0/5 - Timp de excutie depasit!"
    else
     ./checker$id

     echo "Test $i problema $id .......... $(cat score.verif)/5 - $(cat output.verif) - $(cat output.time) secunde"

     total=$(($total + `cat score.verif`))

    fi

    rm -f date.in date.out res.ok score.verif output.verif output.time \
      error.time error.exec errors

  done
}

run_problem sauron 1 1 8
run_problem matrix 2 1 8
run_problem bonus 3 1 4

make clean
make -f Makefile-checker clean

echo "Total: $total/100"

