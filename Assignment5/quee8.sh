#!/bin/bash

echo "Enter the Number:"
read n

i=1
while [ $i -le 10 ]
do
	res=`expr $i \* $n`
	echo "$res"
	i=`expr $i + 1`
done

