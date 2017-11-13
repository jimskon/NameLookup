#MakeFile to build  the Sample US CENSUS Name Data 
# For CSC3004 Software Development

CC= g++

#For Optimization
#CFLAGS= -O2
#For debugging
CFLAGS= -std=c++14

RM= /bin/rm -f

all: namesdemo

NameEntry.o: NameEntry.cpp NameEntry.h
	$(CC) $(CFLAGS) NameEntry.cpp -c

NameMap.o: NameMap.cpp NameMap.h NameEntry.h
	$(CC) $(CFLAGS) NameMap.cpp -c

namesdemo.o: namesdemo.cpp NameEntry.h NameMap.h
	$(CC) $(CFLAGS) namesdemo.cpp -c

namesdemo: namesdemo.o NameEntry.o NameMap.o
	$(CC) $(CFLAGS) namesdemo.o NameEntry.o NameMap.o -o namesdemo

clean:
	rm -f *.o  namesdemo
