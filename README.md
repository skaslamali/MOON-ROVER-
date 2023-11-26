# MOON-ROVER-
 This code contains "ESP NOW COMMUNICATION" which is written by - RUI SANTOS
 its also contains the "ULTRA SONIC RADAR" which is written by - Dejan Nedelkovski
 to make radar graphics, user required a software called "PROCESSING". 
 code for this graphics is written by - Dejan Nedelkovski & Jaycar Electronics
 all the codes are later MODIFIED BY - Sk Aslam Ali
 to make the radar system wireless and also send the 
 HC-SR04 and DHTt11 data to BLYNK application. using blynk app user can also controll wheels so
 besically this code is for a moon rover demo project.
#  Modification DATE: 10-11-2023
************************************************************************
************************************************************************
************************************************************************
# REQUIREMENTS:
1. one esp32(must) and one any esp microcontroller
2. hc-sr04 ultrasonic sensor
3. dht-11 temperature sensor
4. l298n motor driver
5. wheels

# TUTORIAL:
- installation - Arduino IDE, Processing 4 software
- libraries for arduino ide - esp8266WiFi.h, espnow.h, blynksimpleesp8266.h, dht11.h
- libraries for processing 4 - processing.serial.*, java.awt.event.KeyEvent, java.io.IOException
- install BLYNK application on your mobile

# UPLOAD CODE: 
1. upload the MASTER.INO to esp 32
2. upload SLAVE.INO to another esp board
3. run the RADAR GRAPHICS.PDE code in processing software

# CHANGES YOU HAVE TO DO:
- change the pins according to you
 - change the ssid and password
-  change the configs of blynk account 
-  change slave esp mac address
 - change these things in MASTER.INO
 - how to find MAC address of any esp board
 - https://randomnerdtutorials.com/get-change-esp32-esp8266-mac-address-arduino/#:~:text=You%20can%20set%20a%20custom,old%20and%20new%20MAC%20Address.

# CANTACT ME FOR MORE DETAILS - AA1397284@GMAIL.COM
