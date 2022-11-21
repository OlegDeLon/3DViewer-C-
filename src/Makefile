CFLAGS = -std=c++17 -Wall -Wextra -Werror 
CFLAGS1 = -std=c++17
GFLAGS = -fprofile-arcs -ftest-coverage
LDFLAGS = -L. -lcheck -lgcov -lm

ifeq ($(shell lsb_release -si), Ubuntu)
LDFLAGS += -lsubunit 
endif


all: build

build: clean
	mkdir build
	cd build/; qmake ../3DViewer.pro
	make -C build/
	cd build/; rm -rf *.o *.cpp *.h Makefile

install: build
	mkdir $(HOME)/Desktop/3DViewer/
	cp -rf build/3DViewer.app $(HOME)/Desktop/3DViewer/

uninstall:
	rm -rf $(HOME)/Desktop/3DViewer/

dvi: info.pdf
	open info.pdf

info.pdf: info.tex
	texi2pdf info.tex --quiet -o info.pdf -c

dist: clean
	mkdir Dist
	tar --totals --create --verbose --file Dist/3DViewer.tar *

tests: clean
	g++ --coverage model.cpp test.cpp -o test -lstdc++ -lgtest -lgtest_main
	./test
	rm -rf *.o 

debug: clean
	g++ model.cpp debug.cpp -lgtest 
	rm -rf *.o 
	./a.out

gcov_report: 
	g++ --coverage model.cpp test.cpp -o test -lstdc++ -lgtest -lgtest_main
	./test
	lcov -t "test" --no-external -o test.info -c -d ./
	genhtml -o report test.info
	open ./report/index.html

check:
	cppcheck --language=c++ --suppress=missingIncludeSystem *.cpp *.h
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extensions=cpp *.cpp
	python3 ../materials/linters/cpplint.py --extensions=h *.h
	rm -rf CPPLINT.cfg


clean:
	rm -rf *.o *.a *.gcda *.gcno 3DViewer test 3DViewer.tar gcov_report build/ report/ test.info Dist/ *.out *.cfg
