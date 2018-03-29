#!/bin/bash
for i in {1..5};
do
	echo "Test case $i";
	./a.out ./Public_cases/Testcase$i/top.cir
	# firefox -new-tab ./Circuit.html &
	# sleep 10;
	echo "---------------";
	
done;
