#!/bin/bash

SUCCESS=0
FAIL=0

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
grep ${allPatterns[j]} ${allThreads[i]} test_grep/test.txt ${path[k]} > test_grep/out_grep.txt
./s21_grep ${allPatterns[j]} ${allThreads[i]} test_grep/test.txt ${path[k]} > test_grep/out_s21_grep.txt
result=$(diff test_grep/out_grep.txt test_grep/out_s21_grep.txt)
if [ -z "$result" ]
then
  SUCCESS=$(($SUCCESS + 1))
else
  FAIL=$(($FAIL + 1))
  echo "CASE FAIL: ${allPatterns[j]}/ ${allThreads[i]}/${path[k]}"
fi
done
done
done

for (( k=0; k<2; k++ ))
do
grep -e "Della" -e "look" test_grep/test.txt ${path[k]} > test_grep/out_grep.txt
./s21_grep -e "Della" -e "look" test_grep/test.txt ${path[k]} > test_grep/out_s21_grep.txt
result=$(diff test_grep/out_grep.txt test_grep/out_s21_grep.txt)
if [ -z "$result" ]
then
  SUCCESS=$(($SUCCESS + 1))
else
  FAIL=$(($FAIL + 1))
  echo $result
fi
done

for (( k=0; k<2; k++ ))
do
grep -f  test_grep/patterns.txt test_grep/test.txt ${path[k]} > test_grep/out_grep.txt
./s21_grep -f test_grep/patterns.txt test_grep/test.txt ${path[k]} > test_grep/out_s21_grep.txt
result=$(diff test_grep/out_grep.txt test_grep/out_s21_grep.txt)
if [ -z "$result" ]
then
  SUCCESS=$(($SUCCESS + 1))
else
  FAIL=$(($FAIL + 1))
  echo $result
fi
done
echo "FINISH TEST: one flag..."
echo "SUCCESS: $SUCCESS"
echo "FAIL: $FAIL"
echo "START TEST: two flags..."

#one or more path, two flags
for (( i=0; i<7; i++ ))
do
for (( j=i+1; j<8; j++))
do
for (( l=0; l<3; l++ )) 
do
for (( k=0; k<2; k++ ))
do
grep ${allPatterns[l]} ${allThreads[i]} ${allThreads[j]} test_grep/test.txt ${path[k]} > test_grep/out_grep.txt
./s21_grep ${allPatterns[l]} ${allThreads[i]} ${allThreads[j]} test_grep/test.txt ${path[k]} > test_grep/out_s21_grep.txt
result=$(diff test_grep/out_grep.txt test_grep/out_s21_grep.txt)
if [ -z "$result" ]
then
  SUCCESS=$(($SUCCESS + 1))
else
  FAIL=$(($FAIL + 1))
  echo "CASE FAIL: ${allPatterns[l]}/ ${allThreads[i]}/${allThreads[j]}/${path[k]}"
fi
done
done
done
done

for (( i=1; i<8; i++ ))
do
for (( k=0; k<2; k++ ))
do
grep -e "Della" -e "look" ${allThreads[i]} test_grep/test.txt ${path[k]} > test_grep/out_grep.txt
./s21_grep -e "Della" -e "look" ${allThreads[i]} test_grep/test.txt ${path[k]} > test_grep/out_s21_grep.txt
result=$(diff test_grep/out_grep.txt test_grep/out_s21_grep.txt)
if [ -z "$result" ]
then
  SUCCESS=$(($SUCCESS + 1))
else
  FAIL=$(($FAIL + 1))
  echo "CASE FAIL: ${allThreads[i]}/${path[k]}"
fi
done
done

for (( i=1; i<8; i++ ))
do
for (( k=0; k<2; k++ ))
do
grep -f test_grep/patterns.txt test_grep/test.txt ${path[k]} > test_grep/out_grep.txt
./s21_grep -f test_grep/patterns.txt test_grep/test.txt ${path[k]} > test_grep/out_s21_grep.txt
result=$(diff test_grep/out_grep.txt test_grep/out_s21_grep.txt)
if [ -z "$result" ]
then
  SUCCESS=$(($SUCCESS + 1))
else
  FAIL=$(($FAIL + 1))
  echo "CASE FAIL: ${allThreads[i]}/${path[k]}"
fi
done
done

echo "FINISH TEST: two flags..."
echo "SUCCESS: $SUCCESS"
echo "FAIL: $FAIL"