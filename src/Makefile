SRCS = s21_matrix_oop.cc	
OBJS = ${SRCS:.cc=.o}
CC = g++
CFLAGS = -Wall -Werror -Wextra

all: s21_matrix_oop.a

s21_matrix_oop.a:
	${CC} ${CFLAGS} -c ${SRCS}
	ar rcs s21_matrix_oop.a s21_*.o
	ranlib s21_matrix_oop.a

test: unit_test

unit_test: s21_matrix_oop.a
	${CC} ${CFLAGS} -std=c++17 s21_matrix_oop_test.cc s21_matrix_oop.a -lgtest -lgtest_main -pthread -o test
	./test

gcov_report: s21_matrix_oop.a
	@g++ --coverage s21_matrix_oop_test.cc -lgtest ${SRCS} -o unit-test
	@./unit-test
	@lcov -t "test" -o test.info --no-external -c -d .
	@genhtml -o report test.info

clean:
	@rm -rf *.{a,o,dSYM,out,info,gcno,gcda} test unit-test gcov_report report 3main leaks

checks: cppcheck leaks style

style:
	cp ../materials/linters/.clang-format ../src
	clang-format -n *.cc *.h

cppcheck:
	cppcheck *.cc

leaks: s21_matrix_oop_test.cc
	leaks --atExit -- ./test

install_brew:
	cd ~
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov

install_valgrind:
	brew install --HEAD LouisBrunner/valgrind/valgrind

install_cpch:
	brew install cppcheck
