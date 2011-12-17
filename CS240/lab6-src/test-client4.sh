#!/bin/bash

echo ======= Testing -users ======

if [ $# -ne 2 ]
then
  echo "Usage: `basename $0` client-prog port"
  exit 1
fi

CLIENT=$1
PORT=$2

# Kill server if needed
PID=`/usr/bin/ps | grep talk-ser | awk '{ print $1;}'`
kill -9 $PID >& /dev/null
PID=`/usr/bin/ps | grep tail | awk '{ print $1;}'`
kill -9 $PID >& /dev/null

#Start server in the background
echo Starting talk-server
rm password.txt
talk-server.org $PORT > talk-server.out &
sleep 6

# Create command
rm -f file
echo -quit > infile

echo > outfile

echo Add multiple clients
$CLIENT localhost $PORT superman clarkkent >> outfile < infile
$CLIENT localhost $PORT spiderman peterpark >> outfile < infile
$CLIENT localhost $PORT aquaman xyz >> outfile < infile
$CLIENT localhost $PORT mary poppins >> outfile < infile


# Create named pipes to talk to the running clients
rm -f fifo-cl1
rm -f fifo-cl2
rm -f fifo-cl3
mkfifo fifo-cl1
mkfifo fifo-cl2
mkfifo fifo-cl3

rm -f outfile1 outfile2 outfile3

sleep 6
echo Start client mary
tail -f fifo-cl3 | $CLIENT localhost $PORT mary poppins >> outfile3 &
sleep 6

echo Start client superman
tail -f fifo-cl1 | $CLIENT localhost $PORT superman clarkkent >> outfile1 &
sleep 6

echo Start client spiderman
tail -f fifo-cl2 | $CLIENT localhost $PORT spiderman peterpark >> outfile2 &
sleep 6

# Send commands to clients
echo -who > fifo-cl3
sleep 6
echo -quit > fifo-cl1
sleep 6
echo -quit > fifo-cl2
sleep 6
echo -quit > fifo-cl3
sleep 6


echo ======== Input ==========
cat infile
echo ======== Output superman ==========
cat outfile1
echo ======== Output spiderman ==========
cat outfile2
echo ======== Output mary ==========
cat outfile3

echo
echo ==========================

# Kill server

PID=`/usr/bin/ps | grep talk-ser | awk '{ print $1;}'`
kill -9 $PID >& /dev/null

PID=`/usr/bin/ps | grep tail | awk '{ print $1;}'`
kill -9 $PID >& /dev/null

echo Output compared will be marys output in outfile
echo
cp outfile1 outfile

