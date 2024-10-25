#!/bin/bash

echo -n -e "Enter the Number:"
read n

i=1
res=1
while [ $i -le $n ]
do
	res=`expr $i \* $res`
	
	i=`expr $i + 1`

done
 echo "$res"

