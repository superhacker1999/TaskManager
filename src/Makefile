LIB_FLAG=-l sqlite3
CC=g++
FLAGS=
SRC=model/taskmanager.cc 
# view/interface.cc

clean:
	rm -rf mngr

test: clean
	$(CC) $(FLAGS) $(SRC) $(LIB_FLAG) -o mngr
	./mngr $(DB_PATH)