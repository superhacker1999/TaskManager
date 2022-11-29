.PHONY: clean build test all
LIB_FLAG=-l sqlite3
CC=gcc
FLAGS=-Wall -Werror -Wextra -lstdc++ -std=c++17
SRCS=controller/controller.cc model/dbhandler/dbhandler.cc model/parser/parser.cc model/taskmanager/taskmanager.cc view/interface.cc
DB_PATH=../todo.db

all: test

build: clean
	$(CC) $(FLAGS) $(LIB_FLAG) $(SRCS) -o mngr

debug: clean
	$(CC) $(FLAGS) -g $(LIB_FLAG) $(SRCS) -o mngr

test:	build
	./mngr $(DB_PATH)