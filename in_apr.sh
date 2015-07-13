#!/bin/bash

chmod +x graphGen
for i in {5..15}
do	
	for j in {1..10}
	do
   		./graphGen $i >> generated_Input/inva$i
	done
done

for i in {5..15}
do
	cat generated_Input/inva$i|exefiles/./a5_apr >> output/result2
done
rm inva*	

