#!/usr/bin/env bash
sshpass -p "raspberry" scp -r . pi@raspberrypi:~/openglpractice
sshpass -p "raspberry" ssh pi@raspberrypi \
  "cd ~/openglpractice; rm CMakeCache.txt; cmake . && make"
