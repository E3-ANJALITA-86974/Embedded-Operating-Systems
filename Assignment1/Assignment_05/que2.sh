#!/bin/bash


echo -n e "1.Date 2.calende 3.ls 4.home_dir 5.exit"
echo -n -e "Enter the choice"
read choice

case $choice in

	1)date
		;;
	2)cal
		;;
	3)ls
		;;
	4)pwd
		;;
	5)exit
		;;

	esac
