# smartmeter-p1-v1
Readout of a Flemish smartmeter via the P1 port and publish it to MQTT.
The meter uses the DSMR v5 protocol, so probably recent Dutch meters can be read out.

## Software

The software is intended to run on an ESP8266 device.
This version is made with the Arduino IDE.
The software is based on https://github.com/neographikal/P1-Meter-ESP8266-MQTT and others.

## Hardware

I made a motherboard containing a Wemos D1 mini R2 and the hardware to connect to the P1 port of the energy-meter. Later I swapped the mini R2 with a mini Pro, because the poor WiFi signal at my meter. So both can be used.

## Risk

Both software and hardware are running fine at my home. Using any of this is at your own risk.
