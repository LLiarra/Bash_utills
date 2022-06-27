#!/bin/bash

allThreads=("" "-b" "-e" "-n" "-s" "-t")

two_path=("" "test_cat/test_cat.txt")
one_path="test_cat/test_cat.txt"

for (( i=0; i<6; i++ ))
do
for (( j=0; j<2; j++ ))
do
valgrind --leak-check=full ./s21_cat ${allThreads[i]} ${one_path} ${two_path[j]}
done
done