# /home/class/csc3004/COPYME/setenv.gdb
# set environment variables to run a CGI program with gdb
#
# To debug a CGI program:
# Copy this file (setenv.gdb) to the same directory
#      with your source program.
# Start gdb.
# (gdb) source setenv.gdb
# Set a break point.
# (gdb) run <CGIInputFile

set environment REQUEST_METHOD POST
set environment CONTENT_TYPE application/x-www-form-urlencoded

# can be greater than actual size of input file
set environment CONTENT_LENGTH 100
