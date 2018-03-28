#!/bin/bash
for i in {1..5};
do
	echo "Test case $i";
	./a.out ./Public_cases/Testcase$i/top.cir 
	echo "---------------";
done;
