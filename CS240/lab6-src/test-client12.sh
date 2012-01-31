#!/bin/bash

echo ======= Testing -users ======

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
echo -quit > infile

echo > outfile

echo Add multiple clients
$CLIENT localhost $PORT superman clarkkent >> outfile < infile
$CLIENT localhost $PORT spiderman peterpark >> outfile < infile
$CLIENT localhost $PORT aquaman xyz >> outfile < infile
$CLIENT localhost $PORT mary poppins >> outfile < infile

sleep 6

echo List registered users
echo -users > infile2
echo -quit >> infile2
cat infile
$CLIENT localhost $PORT mary wrongpassword >> outfile < infile2

sleep 6

echo ======== Input ==========
cat infile
echo
cat infile2
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

