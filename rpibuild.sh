#!/usr/bin/env bash
rsync -vrtl --delete --exclude=Makefile --exclude=openglpractice --exclude=CMakeCache.txt --exclude=CMakeFiles --rsh="/usr/bin/sshpass -p \"raspberry\" ssh" ./ pi@raspberrypi:~/openglpractice/
sshpass -p "raspberry" ssh pi@raspberrypi \
  "cd ~/openglpractice; cmake . && make"
