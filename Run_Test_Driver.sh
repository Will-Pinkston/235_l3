#!/bin/bash
EXE=dont_run_me

g++ -g -Wall -std=c++14 -o$EXE Student_Code/*.cpp ignoreme.a
if (( $? )) ;
then 
	echo Compilation Failed;
	read -p "Press enter to exit";
else 
	chmod 755 $EXE;
	./$EXE -c; 
	rm ./$EXE
	read -p "Press any key to exit..."
fi;
