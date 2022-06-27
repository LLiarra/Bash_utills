COMPILE=gcc
FLAGS=-Wall -Wextra -Werror -g

SRC_GREP=s21_grep.c s21_util_grep.c s21_grep_output.c ../common/s21_common.c

OBJ=$(SRC_GREP:.c=.o)

.PHONY: all clean

all: s21_grep test_grep

s21_grep: s21_grep.h $(OBJ)
		$(COMPILE) $(FLAGS) $(OBJ) -o s21_grep

test_grep: s21_grep
		chmod +x s21_test_grep.sh
		./s21_test_grep.sh

memory_test_grep: s21_grep
	chmod +x s21_memory_grep.sh
	./s21_memory_grep.sh

clean:
		rm -rf *.o s21_grep ../common/*.o
