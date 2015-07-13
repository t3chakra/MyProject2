#!/bin/bash

chmod +x graphGen
for i in {5..15}
do	
   	./graphGen $i >> generated_Input/input
	
done

cat generated_Input/input|exefiles/./a5-ece650
