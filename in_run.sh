#!/bin/bash

chmod +x graphGen
for i in {5..15}
do	
	for j in {1..10}
	do
   		./graphGen $i >> generated_Input/inv$i
	done
done

for i in {5..15}
do
	cat generated_Input/inv$i|exefiles/./a5_stat >> output/result
done
rm inv*	

