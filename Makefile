CC = gcc

SOL_FULL = solver_full
CFLAGS = -g -Wall -Wextra -std=c99
CPPFLAGS = -g -Wall -Wextra -Winline

SOL_HEADERS = direction.h solver.h move.h

SOL_EXECS = solver.c move.c

HEADERS = constants.h direction.h robot.h maze.h
EXECS = direction.cpp robot.cpp maze.cpp test.cpp


all: $(HEADERS) $(EXECS) maze_extras.cpp
	g++ $(CPPFLAGS) -o test $(EXECS) maze_extras.cpp -DEXTRAS -DTEST

# bare: $(HEADERS) $(EXECS)
# 	g++ $(CPPFLAGS) -o test $(EXECS)

# clean:
# 	rm -f test
