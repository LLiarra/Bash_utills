#!/bin/bash

allThreads=("" "-i" "-v" "-c" "-l" "-n" "-h" "-o")
path=("" "test_grep/test.txt")

allPatterns=("Della" "look" "she")

# one or more path, one flag
echo "START TEST: one flag..."
for (( i=0; i<8; i++ )) 
do
for (( j=0; j<3; j++ )) 
do
for (( k=0; k<2; k++ ))
do
valgrind --leak-check=full ./s21_grep ${allPatterns[j]} ${allThreads[i]} test_grep/test.txt ${path[k]} > test_grep/out_s21_grep.txt
done
done
done

for (( k=0; k<2; k++ ))
do
valgrind --leak-check=full ./s21_grep -e "Della" -e "look" test_grep/test.txt ${path[k]} > test_grep/out_s21_grep.txt
done

for (( k=0; k<2; k++ ))
do
valgrind --leak-check=full ./s21_grep -f test_grep/patterns.txt test_grep/test.txt ${path[k]} > test_grep/out_s21_grep.txt
done

#two flags
for (( i=0; i<7; i++ ))
do
for (( j=i+1; j<8; j++))
do
for (( l=0; l<3; l++ )) 
do
for (( k=0; k<2; k++ ))
do
valgrind --leak-check=full ./s21_grep ${allPatterns[l]} ${allThreads[i]} ${allThreads[j]} test_grep/test.txt ${path[k]} > test_grep/out_s21_grep.txt
done
done
done
done

for (( i=1; i<8; i++ ))
do
for (( k=0; k<2; k++ ))
do
valgrind --leak-check=full ./s21_grep -e "Della" -e "look" ${allThreads[i]} test_grep/test.txt ${path[k]} > test_grep/out_s21_grep.txt
done
done

for (( i=1; i<8; i++ ))
do
for (( k=0; k<2; k++ ))
do
valgrind --leak-check=full ./s21_grep -f test_grep/patterns.txt test_grep/test.txt ${path[k]} > test_grep/out_s21_grep.txt
done
done