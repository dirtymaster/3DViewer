FLAGS = g++ -g -std=c++17 -Wall -Wextra #-Werror
DATA = "In 3DViewer application you can load 3d objects and view them"

all: install test

install:
	cd View && qmake && make && make clean && rm Makefile
	mv View/3DViewer.app/Contents/MacOS/3DViewer .
	./3dViewer

uninstall:
	rm -rf View/3DViewer.app 3DViewer

reinstall: uninstall
	make install

dist:
	tar cfz 3DViewer.tgz 3DViewer.app

dvi:
	touch info.dvi
	@(echo $(DATA) >> info.dvi)

compile:
	$(FLAGS) Model/*.cpp Controller/*.cpp -lgtest

test: compile
	./a.out

gcov_report: gcov_report_build
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info

gcov_report_build: clean
	$(FLAGS) Model/*.cpp Controller/*.cpp -lgtest --coverage -o gcov_report
	./gcov_report
	lcov -t "./gcov_report" -o gcov_report.info -c -d .
	genhtml -o report gcov_report.info
	open ./report/index.html

leaks_check: compile
	CK_FORKS=no leaks -atExit -- ./a.out

style_check:
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py --extensions=cpp View/*.cpp View/*.h Controller/*.cpp \
	Controller/*.h Model/*.cpp Model/*.h

clean: uninstall
	rm -rf a.out* gcov_report* report CPPLINT.cfg 3DViewer.tgz 3DViewer.app info.dvi View/ui_View.h \
	build-3DViewer-Desktop_x86_darwin_generic_mach_o_64bit-Debug