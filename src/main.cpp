#include <WiFi.h>
#include <FirebaseESP32.h>

const char* ssid = "B29";
const char* password = "68205713";

#define FIREBASE_HOST "smartparking-ff10b-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "j3mQDM9kiL0RyVYRcb89sxkmsxy50eleiS6nr5na"

const int irSensor1Pin = 2;
const int irSensor2Pin = 4;
const int irSensor3Pin = 5;

const int redLedPin1 = 12;
const int greenLedPin1 = 13;
const int redLedPin2 = 14;
const int greenLedPin2 = 15;
const int redLedPin3 = 16;
const int greenLedPin3 = 17;

void connectToWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void connectToFirebase() {
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  while (!Firebase.ready()) {
    Serial.println("Connecting to Firebase...");
    delay(500);
  }

  Serial.println("Connected to Firebase");
}

void readAndPublishSensorData() {
  int irSensor1Value = digitalRead(irSensor1Pin);
  int irSensor2Value = digitalRead(irSensor2Pin);
  int irSensor3Value = digitalRead(irSensor3Pin);

  Firebase.setInt("/irSensor1", irSensor1Value);
  Firebase.setInt("/irSensor2", irSensor2Value);
  Firebase.setInt("/irSensor3", irSensor3Value);
  
  // Control LEDs based on sensor values
  digitalWrite(redLedPin1, irSensor1Value);
  digitalWrite(greenLedPin1, !irSensor1Value);
  digitalWrite(redLedPin2, irSensor2Value);
  digitalWrite(greenLedPin2, !irSensor2Value);
  digitalWrite(redLedPin3, irSensor3Value);
  digitalWrite(greenLedPin3, !irSensor3Value);
}

void setup() {
  Serial.begin(115200);

  connectToWiFi();
  connectToFirebase();

  pinMode(irSensor1Pin, INPUT);
  pinMode(irSensor2Pin, INPUT);
  pinMode(irSensor3Pin, INPUT);
  
  pinMode(redLedPin1, OUTPUT);
  pinMode(greenLedPin1, OUTPUT);
  pinMode(redLedPin2, OUTPUT);
  pinMode(greenLedPin2, OUTPUT);
  pinMode(redLedPin3, OUTPUT);
  pinMode(greenLedPin3, OUTPUT);
}

void loop() {
  readAndPublishSensorData();

  delay(500); 
}
