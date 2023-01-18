CC=g++
PROJECT=maze
SOURCES=./Model/maze.cc ./Model/parser.cc
HEADERS=./Model/maze.h ./Model/parser.h
OBJECTS=maze.o parser.o
OUTTESTSNAME=tests
REPORTNAME=Report
BUILDNAME=Build
TESTFILE=tests.cc
OUTDIRPATH=Build
ARCHIVENAME=MazeArchive
GCOV=-fprofile-arcs -ftest-coverage
CFLAGS=-Wall -Werror -Wextra -std=c++17

OS=$(shell uname -s)
ifeq ($(OS),Darwin)
	CHECKFLAGS=-lgtest
	OUTFILENAME=Maze.app
else
	CHECKFLAGS=-lgtest -lpthread -lrt -lm -lsubunit -ldl
	OUTFILENAME=Maze
endif

all: install gcov_report

install:
	@mkdir ./$(OUTDIRPATH)
	@cd ./$(OUTDIRPATH) && qmake ../Maze.pro
	@cd ./$(OUTDIRPATH) && make qmake_all
	@cd ./$(OUTDIRPATH) && make -j4

uninstall:
	@rm -rf ./$(OUTDIRPATH)

dist:
	@tar -czf $(ARCHIVENAME).tar.gz ./$(TESTFILE) ./Makefile ./Maze.pro ./Model/* ./Controller/* ./View/*

tests:
	@$(CC) -c $(SOURCES) $(TESTFILE)
	@$(CC) $(OBJECTS) $(TESTFILE:.cc=.o) $(CHECKFLAGS) -o $(OUTTESTSNAME)
	@./$(OUTTESTSNAME)

gcov_report:
	@$(CC) $(GCOV) $(SOURCES) $(TESTFILE) $(CHECKFLAGS) -o GcovReport
	@./GcovReport
	@lcov -t "GcovReport" -o GcovReport.info -c -d . --no-external
	@genhtml -o $(REPORTNAME) GcovReport.info

clean:
	@rm -rf ./*.o ./*.a ./a.out ./$(REPORTNAME) ./GcovReport.info ./$(OUTTESTSNAME) ./a.out.dSYM
	@rm -rf ./*.gcno ./*.gcda ./GcovReport ./GcovReport.info ../build-Maze-* ./$(BUILDNAME)
	@rm -rf ./$(OUTFILENAME) ./$(ARCHIVENAME).tar.gz
	@rm -rf ./$(BUILDNAME) ./$(OUTDIRPATH) ./$(ARCHIVENAME) ./.qtc_clangd ./*.gch ./*.pro.user ./.vscode

clang:
	clang-format -i ./$(TESTFILE) ./Controller/*.cc ./Controller/*.h ./Model/*.cc ./Model/*.h ./View/*.cc ./View/*.h

linter:
	clang-format -n ./$(TESTFILE) ./Controller/*.cc ./Controller/*.h ./Model/*.cc ./Model/*.h ./View/*.cc ./View/*.h

cppcheck:
	cppcheck --check-config --std=c++17 --language=c++ --enable=all --suppress=missingIncludeSystem ./$(TESTFILE) ./Controller/*.* ./Model/*.* ./View/*.c ./View/*.h

leaks:
	@$(CC) -c $(SOURCES) $(TESTFILE)
	@$(CC) $(OBJECTS) $(TESTFILE:.cc=.o) $(CHECKFLAGS) -o $(OUTTESTSNAME)
	CK_FORK=no leaks -atExit -- ./$(OUTTESTSNAME)
	@rm -rf ./*.o ./*.a ./$(OUTTESTSNAME)

valgrind:
	@$(CC) -c $(SOURCES) $(TESTFILE) -g
	@$(CC) $(OBJECTS) $(TESTFILE:.cc=.o) $(CHECKFLAGS) -o $(OUTTESTSNAME)
	CK_FORK=no valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=yes ./$(OUTTESTSNAME)
	@rm -rf ./*.o ./*.a ./$(OUTTESTSNAME)
