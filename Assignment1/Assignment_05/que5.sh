#!/bin/bash

echo -n -e "Enter the number :"
read n1
echo -n -e "Enter the Num2:"
read n2
echo -n -e "Enter the Num3:"
read n3


if [ $n1 -ge $n2 ]
then
	if [ $n1 -gt $n3 ]
	then

	echo "Num1 is greater :$n1"
else
	echo "Num2 is greater :$n3"
fi

else

if [ $n2 -gt $n3  ]
then
	echo "Num1 is greater: $n2"
else
	echo "Num3 is greater: $n3"
fi
fi
