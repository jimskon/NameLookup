#MakeFile to build and deploy the Sample US CENSUS Name Data using ajax
# For CSC3004 Software Development

# Put your user name below:
USER= skon

CC= g++

#For Optimization
#CFLAGS= -O2
#For debugging
CFLAGS= -std=c++11

RM= /bin/rm -f

all: namelookup PutCGI PutHTML

namelookup.o: namelookup.cpp
	$(CC) -c $(CFLAGS) namelookup.cpp 

namelookup: namelookup.o
	$(CC) namelookup.o -o namelookup -L/usr/local/lib -lcgicc

PutCGI: namelookup
	chmod 757 namelookup
	cp namelookup /usr/lib/cgi-bin/$(USER)_namelookup.cgi 

	echo "Current contents of your cgi-bin directory: "
	ls -l /usr/lib/cgi-bin/

PutHTML:
	cp namelookup.html /var/www/html/class/softdev/$(USER)/Names/
	cp namelookup.css /var/www/html/class/softdev/$(USER)/Names/
	cp namelookup.js /var/www/html/class/softdev/$(USER)/Names/

	echo "Current contents of your HTML directory: "
	ls -l /var/www/html/class/softdev/$(USER)/Names/
clean:
	rm -f *.o  namelookup
