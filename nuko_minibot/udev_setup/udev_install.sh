#!/bin/bash

# STM32 Base
echo  'KERNEL=="ttyUSB*", ATTRS{idVendor}=="1a86", ATTRS{idProduct}=="7523", MODE:="666", SYMLINK+="stm32base"' >/etc/udev/rules.d/stm32base.rules 

# YDLIDAR
echo  'KERNEL=="ttyUSB*", ATTRS{serial}=="0001", ATTRS{idVendor}=="10c4", ATTRS{idProduct}=="ea60", MODE:="0666", GROUP:="dialout",  SYMLINK+="ydlidar"' >/etc/udev/rules.d/ydlidar.rules

echo  'KERNEL=="ttyACM*", ATTRS{serial}=="0001", ATTRS{idVendor}=="0483", ATTRS{idProduct}=="5740", MODE:="0666", GROUP:="dialout",  SYMLINK+="ydlidar"' >/etc/udev/rules.d/ydlidar-V2.rules

echo  'KERNEL=="ttyUSB*", ATTRS{serial}=="0001", ATTRS{idVendor}=="067b", ATTRS{idProduct}=="2303", MODE:="0666", GROUP:="dialout",  SYMLINK+="ydlidar"' >/etc/udev/rules.d/ydlidar-2303.rules

service udev reload
sleep 2
service udev restart

