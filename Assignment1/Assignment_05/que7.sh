#!/bin/bash

echo -n -e "Enter the number :"
read num

if [ $num -ge  0 ]
then
	echo "number is Positive "
else
	echo "Number is Negative"
fi
