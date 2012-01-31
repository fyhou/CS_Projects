#!/bin/bash

if [ $# -ne 2 ]
then
  echo "Usage: `basename $0` client-prog port"
  exit 1
fi

CLIENT=$1
PORT=$2

# Kill server
echo
echo Killing Server
PID=`/usr/bin/ps | grep talk-ser | awk '{ print $1;}'`
kill -9 $PID >& /dev/null

#Start server in the background
rm password.txt
talk-server.org $PORT > talk-server.out &
sleep 6

# Create command
rm -f outfile
echo > infile
echo -help >> infile
echo >> infile
echo -quit >> infile

echo ======== Input ==========
cat infile

echo Running client
$CLIENT localhost $PORT peter parker > outfile < infile

echo
echo ======== Output ==========

cat outfile

echo
echo ==========================

# Kill server
echo
echo Killing Server
PID=`/usr/bin/ps | grep talk-ser | awk '{ print $1;}'`
kill -9 $PID >& /dev/null

echo Output compared will be in outfile
echo

