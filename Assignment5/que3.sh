#!/bin/bash

echo -n -e "file name:"
read path

if [ -e $path ]
then 
	if [ -d $path ] 
	then
		
	echo "enter file is directory"
	ls $path


elif [ -f $path ]
then
	echo "file regular file:"
	if [ -x $path ]
	then 
		echo "file has exicutable permission"
		ls -l -a $path
	fi
fi

else
	echo " file not exit"
fi

