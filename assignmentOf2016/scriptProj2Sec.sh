#!/bin/bash
echo ' '
echo '######################## RUN COMBINATIONS #########################'
echo ' '
echo 'INPUT  FILE     POSSIBILITY     N     RESENDTIMES    ACCURACY
echo ----------------------------------------------------------------------
#----------- N = 1 ------------- P N
./ergasia2 inputFile.txt outputFile.txt 0 1	#P=0%
./ergasia2 inputFile.txt outputFile.txt 2 1	#P=2%
./ergasia2 inputFile.txt outputFile.txt 5 1	#P=5%
./ergasia2 inputFile.txt outputFile.txt 10 1	#P=10%
echo ' '
#----------- N = 2 ------------- P N
./ergasia2 inputFile.txt outputFile.txt 0 2	#P=0%
./ergasia2 inputFile.txt outputFile.txt 2 2	#P=2%
./ergasia2 inputFile.txt outputFile.txt 5 2	#P=5%
./ergasia2 inputFile.txt outputFile.txt 10 2	#P=10%
echo ' '
#----------- N = 3 ------------- P N
./ergasia2 inputFile.txt outputFile.txt 0 3	#P=0%
./ergasia2 inputFile.txt outputFile.txt 2 3	#P=2%
./ergasia2 inputFile.txt outputFile.txt 5 3	#P=5%
./ergasia2 inputFile.txt outputFile.txt 10 3	#P=10%
echo ' '
#----------- N = 5 ------------- P N
./ergasia2 inputFile.txt outputFile.txt 0 5	#P=0%
./ergasia2 inputFile.txt outputFile.txt 2 5	#P=2%
./ergasia2 inputFile.txt outputFile.txt 5 5	#P=5%
./ergasia2 inputFile.txt outputFile.txt 10 5	#P=10%
echo ' '
#----------- N = 11 ------------ P N
./ergasia2 inputFile.txt outputFile.txt 0 11	#P=0%
./ergasia2 inputFile.txt outputFile.txt 2 11	#P=2%
./ergasia2 inputFile.txt outputFile.txt 5 11	#P=5%
./ergasia2 inputFile.txt outputFile.txt 10 11	#P=10%
echo ' '
echo '(Se periptwsh pou den emfanizontai stoixismena, theste tab width=8)'
