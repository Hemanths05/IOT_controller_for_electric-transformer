#include <ESP8266WiFi.h>
#include <Servo.h>
#include <FirebaseESP8266.h>


#define WIFI_SSID "wifi" // your WiFi SSID
#define WIFI_PASSWORD "12345678" // WiFi PASSWORD

#define MOTOR_PIN 16 // Pin D0 for motor control
#define FIREBASE_HOST "transform-auto-default-rtdb.firebaseio.com" // change here
#define FIREBASE_AUTH "" // your private key

Servo myservo;
FirebaseData firebaseData;

void setup()
{
  myservo.attach(MOTOR_PIN);

  Serial.begin(9600);

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop()
{
  if (Firebase.getInt(firebaseData, "/MotorStatus"))
  {
    int motorStatus = firebaseData.intData();
    if (motorStatus == 1)
    {
      myservo.write(180); // Turn servo to 180 degrees
      Serial.println("Motor is ON (180 degrees)");
    }
    else
    {
      myservo.write(0); // Turn servo to 0 degrees
      Serial.println("Motor is OFF (0 degrees)");
    }
  }
  else
  {
    Serial.print("Error in getInt: ");
    Serial.println(firebaseData.errorReason());
  }

  delay(1000); // Add a delay for stability
}