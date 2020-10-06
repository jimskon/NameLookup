#MakeFile to build and deploy the Sample US CENSUS Name Data using ajax
# For CSC3004 Software Development

user = skon

all:  PutHTML


PutHTML:
	cp webfun.html /var/www/html/class/softdev/$(user)/webfun/
	cp webfun.css /var/www/html/class/softdev/$(user)/webfun/
	cp webfun.js /var/www/html/class/softdev/$(user)/webfun/
	cp words.txt /var/www/html/class/softdev/$(user)/webfun/
	echo "Current contents of your HTML directory: "
	ls -l /var/www/html/class/softdev/$(user)/webfun/
clean:
	rm -f *.o  webfun
