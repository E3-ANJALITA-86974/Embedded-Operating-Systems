#!/bin/bash

a=1
b=1
i=2
res=0

echo -n -e "Enter the number:"
read n
echo "$a"
echo "$b"

while [ $i -lt $n ]

do
  res=`expr $a + $b`
   a=$b
   b=$res
  echo "$res"
i=`expr $i + 1`
done

