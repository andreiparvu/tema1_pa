#!/bin/bash

for file in checker/sauron*.in; do

  echo $file
  echo ==============

  n=`wc -l $file | cut -d ' ' -f 1`
  tail -n $((n - 1)) $file > aux

  head -1 $file > new

  while read line; do
    t1=`echo $line | cut -d ' ' -f 1`
    t2=`echo $line | cut -d ' ' -f 2`

    r=$((RANDOM % 2))

    if [ $r -eq 0 ]; then
      echo "$t2 $t1" >> new
    else
      echo "$t1 $t2" >> new
    fi
  done < aux

  cp new $file

  rm -f aux new
done

