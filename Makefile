#MakeFile to build and deploy the Sample US CENSUS Name Data using ajax
# For CSC3004 Software Development

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
	cp namelookup /usr/lib/cgi-bin/$(user)namelookup.cgi 

	echo "Current contents of your cgi-bin directory: "
	find /usr/lib/cgi-bin/ -type f -mmin -5 -ls	

PutHTML:
	cp namelookup.html /var/www/html/NameLookup/
	cp namelookup.css /var/www/html/NameLookup/
	cp namelookup.js /var/www/html/NameLookup/
	cp -r namedata /var/www/html/NameLookup/
	echo "Current contents of your HTML directory: "
	ls -l /var/www/html/NameLookup/
clean:
	rm -f *.o  namelookup
