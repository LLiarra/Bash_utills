COMPILE=gcc
FLAGS=-Wall -Wextra -Werror -std=c11 -g

SRC_CAT=s21_cat.c s21_util_cat.c s21_read_and_write.c ../common/s21_common.c

OBJ=$(SRC_CAT:.c=.o)

.PHONY: all clean

all: s21_cat test_cat

s21_cat: s21_cat.h $(OBJ)
	$(COMPILE) $(FLAGS) $(OBJ) -o s21_cat

test_cat: s21_cat
	chmod +x s21_test_cat.sh
	./s21_test_cat.sh

memory_test_cat: s21_cat
	chmod +x s21_memory_cat.sh
	./s21_memory_cat.sh

clean:
	rm -rf *.o s21_cat ../common/*.o
