# MyProject2
The program calculate Vertex Cover set using SAT Solver in one thread. The it run 4 other algorithms to generate approximate vertex cover. Then I calculate the approximation ratio of the algorithm . The project was made for course ECE 650. According to the instruction I submitted all necessary source codes and The final report. THe gnuplot file for plotting graphs is also given. For the readers background knowledge I have provided the specification for this project. THe specification will refer assignment 4 for SAT solver. I have include the SAT solver library. Its a project to practice posix thread and applying SAT solver to find minimum Vertex cover. The SAT SOlver's compiled version is used in my code. SO I am pushing all folders.

My code use SAT solver to find the minimum vertex cover. If you try more than 15 nodes, the SAT solver will be really slow, and might take more than 1 hour. YOu can try with both 64 and 32 bit version of the SAT solver.

PLease find the Makefile in Librery folder Change your path in .c filles according to your computing environment. My Root folder is MyProject. So I used MyProject in path, please change your path accordingly.

First make your exe files. Give the following commands:

$cd librery

$make clean

$make

To run the program withut statistics:

$./a5-ece650

And then type input in following format:

V 5 E {<2,1>,<2,0>,<2,3>,<1,4>,<4,3>}

you will get output:

CNF-SAT-VC: 2 4 APPROX-VC-1: 2 4 REFINED-APPROX-VC-1: 2 4 APPROX-VC-2: 0 1 2 4 REFINED-APPROX-VC-2: 2 4

CNF-SAT is the output invoking SAT SOlver from my code Other four algotithms are the approximation algorithms which can give approximate result.

It will continue to take input until you give end of file. we use graphGen exe file to generate random graphs. This file was given by the instructor. Zchaff SAT solver library was downloaded from website. Other instructions are given bellow:

To run in normal mode use in_normal.sh

The input generated is saved in input file for this. graphGen generate different graphs for each run.

The exe file is named a5-ece650 You can run the shell script in_normal.sh after running make file. You should see output in stdout. The output is generated without any statistical result

Instruction to run my code for statistics:

My Makefile will make all exe files for you.

Run time:

The code for this is a5-ece650_stat.c All the shell scripts are given run without statistics: in_normal.sh

run with time statistics: in_run.sh

run with approximation ratio statistics: in_apr.sh

So my program work as follows:

It runs each graph 10 times to find average running time of a single graph. Then you give another graph with same number of vertex, it first find average of 10 times run, then it calculates the average of these two graphs. This is repeat for 10 different graphs. As I mentioned, some graph can crash, so I am printing the average of 1 graph, then average 2 different graph, then average of 3 different graph and upto 10 different graphs.

At the end of execution you will find 10 lines of output in the result file for each vertex range from 5 to 15. If some of them could not generate 10 lines, that means they might have crashed while running 10 times, or somewhere else. Its not predicatable, as CNF SAT is not visible to us. If you find all 100 lines, that means you have find average for all 10 different graphs for each vertex. Sometimes, if number of vertices are large you might see some output like extra newline from SAT solver, this is not conrtollable by me.

If you did not find 10 lines, for any number of vertex, run: rm result. That will remove the result file. Run in_run.sh again. Repeat the process until you find 100 lines in the result file. Now after finding 100 lines, take only the 10 th line for each vertex, becuse this is the average running time of 10 different graphs of that vertex. Insert them in runtime.dat file. So at last in runtime.dat file you will have 10 lines, each of them are the average running time and standard deviation for 5 to 15 vertices.

Now go to terminal. Give command gnuplot. Type load 'rSAT.p' for getting the plot for CNF_SAT's running time. You can comment the "set logscale y" line and active unsat log for generating plot without log scale. You can do vise versa for generating plot with logscale.

Now Type load 'rother.p' for getting plot of other approaches.

For your convenience I have already given the runtime.dat file with gnuplot script files rSAT.p and rother.p

N.B: Don't try the program with more than 10 different graphs at a time, as we have instructed to find average for 10 different fgraphs. So I have an array of size 10 to have differnt run time of different approaches. You will get segmentation fault if you try more than 10 graphs at one execution.

Approximation Ratio: The code for this is a5-ece650_apr.c run in_apr.sh

Similar process repeat as finding running time. Here I am not running each graph for 10 times, because my refined versions are deleting vertex one by one. So there is no randomness in result. So you will find the same vertex cover every time for a graph. That is why this process might take very less time compare to finding run time. I take average of approximation ratio of 10 diferent graphs for same number of vertex. For example 10 for 5, 10 for 6 and so on.

In this case your 100 line output will be saved in result2 file. So do the same as running time, but use result2 instead of result. In this case save your final 10 lines of different graphs in runappr.dat file. Again type gnuplot in terminal. Then type load 'ropr.p'

For your convinience I have provided ther gnuplot script file ropr.p and runappr.dat files.

I hope everything is reproducable now.

This is all about getting every part of assignment 5. Still if something missing, please email me at t3chakra@uwaterloo.ca

Thank you for your kind co-operation.

    Status API Training Shop Blog About Help 

    © 2015 GitHub, Inc. Terms Privacy Security Contact 

