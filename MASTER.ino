//THIS IS THE MAIN CODE WHICH ONLY CAN BE UPLOADED TO IOT BASED MICROCONTROLLERS
//SENDS ULTRASONIC DATA FROM MASTER ESP TO SLAVE ESP BOARD
//SENDS DATA OF DHT11 TEMPERATURE & HUMIDITY & DISTANCE VALUE TO BLYNK APP

/*
This code contains "ESP NOW COMMUNICATION" which is written by - RUI SANTOS
its also contains the "ULTRA SONIC RADAR" which is written by - Dejan Nedelkovski
to make radar graphics, user required a software called "PROCESSING". code for this graphics is 
written by - Dejan Nedelkovski & Jaycar Electronics
all the codes are later MODIFIED BY - Aslam to make the radar system wireless and also send the 
HC-SR04 and DHTt11 data to BLYNK application. using blynk app user can also controll wheels so
besically this code is for a moon rover demo project.
Modification DATE: 10-11-2023
*/
int forwardled = D1;
int backwardled = D2;
int leftled = D3;
int rightled = D4;

int forward;
int backward;
int right;
int left;
int speed;

const int trigPin = D8;
const int echoPin = D7;
long duration;
int distance;

//CONFIGS FOR MOTOR CONTROLL
int ena = D9; 
int enb = D10; 
int in1 = D11; 
int in2 = D12; 
int in3 = D13; 
int in4 = D14;

#include <ESP8266WiFi.h>
#include <espnow.h>

//BLYNK CONFIGS
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3StklvYjf"
#define BLYNK_TEMPLATE_NAME "DHT11"
#define BLYNK_AUTH_TOKEN "gdG0i0fnUt0xI0mVFtJ54kwxzp7Oelwc"
#include <DHT.h>
#include <BlynkSimpleEsp8266.h>


char auth[] = "gdG0i0fnUt0xI0mVFtJ54kwxzp7Oelwc";  
char ssid[] = "Aslam";   // Enter your WiFi SSID here
char pass[] = "aslam123";   // Enter your WiFi password here

#define DHTPIN D6  
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);

BLYNK_WRITE(V4) {
  forward = param.asInt();
  digitalWrite(forwardled,forward);
  //MOTOR FORWARD
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}


BLYNK_WRITE(V5) {
  backward = param.asInt();
  digitalWrite(backwardled,backward);
  //MOTOR BACKWARD
  digitalWrite(in1, LOW); 
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}


BLYNK_WRITE(V6) {
  right= param.asInt();
  digitalWrite(rightled,right); 
  //MOTOR RIGHT
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

BLYNK_WRITE(V7) {
  left = param.asInt();
  digitalWrite(leftled,left);
  //MOTOR LEFT
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

BLYNK_WRITE(V8) {
  speed = param.asInt();
  Serial.print("SLIDER VALUE: ");
  Serial.println(speed);
  //MOTOR SPEED
  analogWrite(ena, speed); 
  analogWrite(enb, speed);
}

// REPLACE WITH RECEIVER MAC Address
uint8_t broadcastAddress[] = {0xC4, 0x5B, 0xBE, 0x6F, 0xED, 0xF3};  //MAC ADDRESS OF MY ESP 8266 OR RECEIVER


// Must match the receiver structure
typedef struct struct_message {
  int a;  //ANGLE
  int d; //DISTANCE
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
 
  if (sendStatus == 0){
    //Serial.println("Delivery success");
  }
  else{
   // Serial.println("Delivery fail");
  }
}






void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 

  pinMode(forwardled,OUTPUT);        
  pinMode(backwardled,OUTPUT);
  pinMode(rightled,OUTPUT);
  pinMode(leftled,OUTPUT);
  
  //PIN MODES OF MOTOR 
  pinMode(ena, OUTPUT); 
  pinMode(enb, OUTPUT); 

  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  Blynk.begin(auth, ssid, pass);
  dht.begin(); 
  
//ESP NOW COMMUNICATION
  WiFi.mode(WIFI_STA); // Set device as a Wi-Fi Station

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
// Once ESPNow is successfully Init, we will register for Send CB to
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER); // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
// Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
 

}




void loop() {
    
  

  for(int i=15;i<=165;i++){
  
  Serial.print("FORWARD: ");
  Serial.println(forward);
  Serial.print("BACKWARD: ");
  Serial.println(backward);
  Serial.print("RIGHT: ");
  Serial.println(right);
  Serial.print("LEFT: ");
  Serial.println(left);
  Blynk.run();
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float Fahrenheit = ( temperature * 1.8 ) + 32;
  Blynk.virtualWrite(V1, temperature);   // Send temperature (CELCIUS) value to Blynk App
  Blynk.virtualWrite(V0, humidity);     // Send humidity value to Blynk App
  Blynk.virtualWrite(V2, Fahrenheit);  // send Fahrenheit value to Blynk App
  Blynk.virtualWrite(V3, distance);   // send distance value to Blynk App

    
  distance = calculateDistance();
  myData.d = distance;
  myData.a = i; 
  esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData)); // Send message via ESP-NOW
  
  }

  for(int i=165;i>15;i--){  
 
  Serial.print("FORWARD: ");
  Serial.println(forward);
  Serial.print("BACKWARD: ");
  Serial.println(backward);
  Serial.print("RIGHT: ");
  Serial.println(right);
  Serial.print("LEFT: ");
  Serial.println(left);
  Blynk.run();
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float Fahrenheit = ( temperature * 1.8 ) + 32;
  Blynk.virtualWrite(V1, temperature);   // Send temperature (CELCIUS) value to Blynk App
  Blynk.virtualWrite(V0, humidity);     // Send humidity value to Blynk App
  Blynk.virtualWrite(V2, Fahrenheit);  // send Fahrenheit value to Blynk App
  Blynk.virtualWrite(V3, distance);   // send distance value to Blynk App

    
  distance = calculateDistance();
  myData.d = distance;
  myData.a = i;
  esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData)); // Send message via ESP-NOW
    
  }


 

}



int calculateDistance(){ 
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  return distance;
}
