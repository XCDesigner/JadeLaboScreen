#!/bin/sh

#devicename=$(fdisk -l |grep "Disk" |grep "/dev/sd" |grep ":" |awk '{print $2}' |awk -F: '{print $1}')
#disklist=$(df -h | awk '{print $1}' | grep "/dev")

while true
do
	for i in `seq 1 50`
	do
		disk1="/dev/sda$i"
		disk2="/dev/sdb$i"
		#echo $disk1
		#echo $disk2

		mount -v $disk1 /mnt/exUDISK 2>/dev/null

		mount -v $disk2 /mnt/exUDISK 2>/dev/null
		
		
		
	done

	sleep 1

done
