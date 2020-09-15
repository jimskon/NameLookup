#MakeFile to build and deploy the Sample US CENSUS Name Data using ajax
# For CSC3004 Software Development

user = skon
CC= g++

#For Optimization
#CFLAGS= -O2
#For debugging
CFLAGS= -std=c++14

RM= /bin/rm -f

all: namelookup PutCGI PutHTML

NameEntry.o: NameEntry.cpp NameEntry.h
	$(CC) $(CFLAGS) NameEntry.cpp -c

NameMap.o: NameMap.cpp NameMap.h NameEntry.h
	$(CC) $(CFLAGS) NameMap.cpp -c

namelookup.o: namelookup.cpp NameEntry.h NameMap.h
	$(CC) -c $(CFLAGS) namelookup.cpp 

namelookup: namelookup.o NameEntry.o NameMap.o
	$(CC) namelookup.o -o namelookup NameEntry.o NameMap.o -L/usr/local/lib -lcgicc

PutCGI: namelookup
	chmod 757 namelookup
	cp namelookup /usr/lib/cgi-bin/$(user)_namelookup.cgi 

	echo "Current contents of your cgi-bin directory: "
	ls -l /usr/lib/cgi-bin/

PutHTML:
	cp namelookup.html /var/www/html/class/softdev/$(user)/Names/
	cp namelookup.css /var/www/html/class/softdev/$(user)/Names/
	cp namelookup.js /var/www/html/class/softdev/$(user)/Names/
	echo "Current contents of your HTML directory: "
	ls -l /var/www/html/class/softdev/$(user)/Names/
clean:
	rm -f *.o  namelookup
