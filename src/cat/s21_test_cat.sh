#!/bin/bash

SUCCESS=0
FAIL=0

allThreads=("" "-b" "-e" "-n" "-s" "-t")

two_path=("" "test_cat/test_cat.txt")
one_path="test_cat/test_cat.txt"

echo "START TEST: one flag..."
for (( i=0; i<6; i++ ))
do
for (( j=0; j<2; j++ ))
do
./s21_cat ${allThreads[i]} ${one_path} ${two_path[j]} > test_cat/out_s21_cat.txt
cat ${allThreads[i]} ${one_path} ${two_path[j]} > test_cat/out_cat.txt
result=$(diff test_cat/out_s21_cat.txt test_cat/out_cat.txt)
if [ -z "$result" ]
then
  SUCCESS=$(($SUCCESS + 1))
else
  FAIL=$(($FAIL + 1))
  echo "CASE FAIL: ${allThreads[i]} / ${two_path[j]}"
fi
done
done
echo "FINISH TEST: one flag..."
echo "SUCCESS: $SUCCESS"
echo "FAIL: $FAIL"
