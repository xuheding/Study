#!/bin/bash

for i in {1..254};do
	ping -c 2 -i 0.3 192.168.125.$i &> /dev/null
	if [ $? -eq 0 ];then
		echo "192.168.125.$i is up" 
	else 
		echo "192.168.125.$i is down"
	fi
done
