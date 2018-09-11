# Copyright[2017]<Chaoyi Yang> [legalcpoyright]
# Name: Chaoyi Yang
# Student ID: 1465947
# UW Email: yangc22@uw.edu

CXX = g++
OBJS = Vector.o ex11.o
EXE  = ex11
HEADERS = Vector.h
CPPFLAGS = -Wall -g -std=c++11

# default target
$(EXE): $(OBJS)
	$(CXX) $(CPPFLAGS) -o $(EXE) $(OBJS)

# source files
%.o: %.cc $(HEADERS)
	$(CXX) $(CPPFLAGS) -c $<

# phony target - remove generated files and backups
clean:
	rm -rf $(EXE) *.o *~ *.dSYM
