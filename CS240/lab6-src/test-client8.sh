#!/bin/bash

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
rm -f outfile
echo -quit > infile

echo > outfile

echo Add multiple clients
$CLIENT localhost $PORT superman clarkkent >> outfile < infile
$CLIENT localhost $PORT spiderman peterpark >> outfile < infile
$CLIENT localhost $PORT aquaman xyz >> outfile < infile
$CLIENT localhost $PORT mary poppins >> outfile < infile

sleep 6


# Create named pipes to talk to the running clients
rm -f fifo-cl1
rm -f fifo-cl2
rm -f fifo-cl3
mkfifo fifo-cl1
mkfifo fifo-cl2
mkfifo fifo-cl3

rm -f outfile1 outfile2 outfile3

echo Start client superman
tail -f fifo-cl1 | $CLIENT localhost $PORT superman clarkkent >> outfile1 &
sleep 3

echo Start client spiderman
tail -f fifo-cl2 | $CLIENT localhost $PORT spiderman peterpark >> outfile2 &
sleep 3

echo Start client mary
tail -f fifo-cl3 | $CLIENT localhost $PORT mary poppins >> outfile3 &
sleep 3

# Send commands to clients
echo -who > fifo-cl3
sleep 6
echo "Hello everybody. How is everybody there." > fifo-cl1
sleep 6
echo "How is the CS240 project going." > fifo-cl1
sleep 6
echo "Hi Peter. I am fine. Thanks." > fifo-cl3
sleep 6
echo "I am right now working on the project. It is awesome!" > fifo-cl3
sleep 6
echo "I hope to complete it soon." > fifo-cl3
sleep 6
echo "That is excelent Mary." > fifo-cl1
sleep 6
echo "Hi, this is spiderman. I have some questions about the project." > fifo-cl2
sleep 6
echo "Can anybody of you help me?." > fifo-cl2
sleep 6
echo "Yes. spiderman. I can help you." > fifo-cl3
sleep 6
echo "I will have to go now. See you later." > fifo-cl1
sleep 6
echo "Bye superman!" > fifo-cl3
sleep 6
echo "Bye!" > fifo-cl2
sleep 6
echo -quit > fifo-cl1
sleep 6
echo -who > fifo-cl3
sleep 6
echo -quit > fifo-cl2
sleep 6
echo -who > fifo-cl3
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
cp outfile3 outfile

