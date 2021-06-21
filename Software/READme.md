The software is configured to use a secure MQTT-server. The initial version used an unsecured server so modifying to use an unsecured MQTT-server is possible.

Initially you need to configure the WiFi-settings of the device : just power on (plug into meter), there will be an accesspoint named smartmeter-p1. You can connect to it using the password Koenraad (my first name ;-) )
When connected to the accesspoint, go to 192.168.4.1 and there you can setup the device to connect to your wifi network and set your own device-name.
The LED will blink to indicate the accesspoint is up.

After your device has made a connection to you wifi-network, the led will stay lit. Then you can go to the web-site of the device.
There are three pages on the web-site : the data page where you can see the data from the meter. A setup page where you can further configure the device. And an about page.
You can access the setup-page by using the initial user and password : admin and smartmeter-p1.
On the page you can configure various settings. Those become active after saving and restarting the device. Settings are stored in EEPROM, so these are safe from power-loss.
You also can upload new firmware.

Please bear in mind that all web-trafic is unsecure (plain http). Passwords are NOT sent to your browser, but when changing passwords those are sent to the device in plain-text.
Another point to note : the meter uses the serial port of the ESP8266, so you can't connect the meter *and* upload software via USB. 
A final note : the P1-port needs to be activated by the provider, so plan ahead !

Enjoy.
