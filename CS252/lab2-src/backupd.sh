#!/bin/bash

# checks that 4 arguments are passed
if [ $# -ne 4 ]
then
	echo "Usage: backupd.sh dir backupdir interval-secs max-backups"
	exit 65 
fi

pwd=$PWD

# storing the argument in variables 
directory=$1
backup=$2
interval=$3
max=$4

# stores times that files were 'last modified' 
ls -lR $directory > ls-lR.last

# backs up directory to backup
timestamp=$(date +"%Y-%m-%d-%H-%M-%S")

# the date for the notification email
propDate=$(date +"%m %d, %Y at %H:%M")

# copies the directory to a backup directory
cp -r $directory "$backup/$timestamp" 

# constructs a message and emails it to the user
# contains: date backup was made, and the path to it
echo > tmp-message
echo "Hello $USER," >> tmp-message
echo >> tmp-message
echo "A backup of $directory was made on $propDate."  >> tmp-message
echo "You can find it here: $backup/$timestamp ." >> tmp-message
echo >> tmp-message
/usr/bin/mailx -s "mail-hello" $USER < tmp-message 


# change to the backups directory, checks if the amount of backups 
# created exceeds the max, if it does, delete the oldest
cd ${backup}
currdirs=$(ls -l $2 | grep ^d | wc -l | tr -s " " | tr -d " ")

while [ ${currdirs} -gt $max ]
do
	# find the oldest directory and delete it
	oldest=$(ls -1t|tail -1)
	rm -rf $oldest	

	let "currdirs = currdirs - 1"
done

# change back to the directory where the script exists
cd $pwd	


# loop that sleeps for appropriate amount of seconds, checks
# if there is any modified data, and backs up if there is
while [ "1" ] 
do
	sleep $interval
	ls -lR $directory > ls-lR.new
	
	# checks if any modifications have been made to the diretory
	difference=$(diff ls-lR.new ls-lR.last)

	# if there are changes, make another backup and send another email
	if [ ${#difference} -ne 0 ]
	then
		# get current time (for folder and for email)
		_timestamp=$(date +"%Y-%m-%d-%H-%M-%S")
		_propDate=$(date +"%m %d, %Y at %H:%M")

	    # make a backup
		cp -r $directory "$backup/$_timestamp"
		
		# construct email and send to user
		echo > tmp-message
		echo "Hello $USER," >> tmp-message
		echo >> tmp-message
		echo "A backup of $directory was made on $_propDate." >> tmp-message
		echo "You can find it here: $backup/$_timestamp ." >> tmp-message
		echo >> tmp-message
		/usr/bin/mailx -s "mail-hello" $USER < tmp-message 

		# move curr state of directory as the new one to compare with
		mv ls-lR.new ls-lR.last
		
		# changes to backup directory, checks if the amount of backups 
		# created exceeds the max, if it does, delete the oldest
		cd ${backup}
		currdirs=$(ls -l $2 | grep ^d | wc -l | tr -s " " | tr -d " ")

		if [ ${currdirs} -gt $max ]
		then
			# find the oldest directory and delete it
			oldest=$(ls -1t|tail -1)
			rm -rf $oldest	
		fi

		# change back to the directory where the script exists
		cd $pwd	
	fi
done
