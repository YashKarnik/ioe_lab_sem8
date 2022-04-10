#include<Servo.h>
Servo Myservo;
int pos;

#include <DHT.h>
#include <DHT_U.h>

#define DHTType DHT11
#define tempHumidityPin 5
DHT dht(tempHumidityPin, DHTType);

#include <SoftwareSerial.h>
SoftwareSerial mySerial(12,13);

const int echoPin1 = 2; // Echo Pin of Ultrasonic Sensor1
const int pingPin1 = 3; // Trigger Pin of Ultrasonic Sensor1
int dled = 8; //dist led


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Starting Serial Communication
  mySerial.begin(9600);

  dht.begin();
  pinMode(pingPin1, OUTPUT); // initialising pin 3 as output
  pinMode(echoPin1, INPUT); // initialising pin 2 as input
  pinMode(A0, INPUT); // Smoke i/p
  pinMode(10, OUTPUT);
  pinMode(dled, OUTPUT);
  Myservo.attach(10);

}


void loop() {
  digitalWrite(dled, LOW);
  
  // put your main code here, to run repeatedly:
  long duration1, inches1, cm1,cmf,svf,tempf,gv;
  digitalWrite(pingPin1, LOW);
  delayMicroseconds(2);

  digitalWrite(pingPin1, HIGH);
  delayMicroseconds(10);

  digitalWrite(pingPin1, LOW);
 
  duration1 = pulseIn(echoPin1, HIGH);// using pulsin function to determine total time

  cm1 = microsecondsToCentimeters(duration1);// calling method
  cmf=floor(cm1%10);
  if(cmf<=3)
  {
    //Serial.println("High");
  digitalWrite(dled, HIGH);
  Serial.println("LED ON");
  Serial.print("Distance = ");
  Serial.println(cmf*10);
  }
  else
  {
    Serial.print("Distance = ");
    Serial.println(cmf*10);
    Serial.println("LED OFF");
  digitalWrite(dled, LOW);
   //Serial.println("low");
  }

  

/* Temp */
  // read temperature as Celsius
  int tempC = dht.readTemperature();
//  tempC = round(tempC);
//  Serial.println(tempC);

  // check if any reads failed
  if (isnan(tempC)) {
    Serial.println("Failed to read from DHT sensor.");
  } else {
    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.println("°C");
    
    if(tempC >= 29) {
      Serial.println("FAN ON");
      rotate();
    }
    else {
      Serial.println("FAN OFF");
    }
  }


/*gas sensor */
  int gasValue = analogRead(A0);
  gv = floor(gasValue%10);
  Serial.print("Smoke =");
  Serial.println(gv*10);
  Serial.println();
  if(gv>30)
  {
    digitalWrite(10, HIGH);
  }
  else
  {
    digitalWrite(10, LOW);  
  }

  mySerial.print('*');
  mySerial.print(cmf);
  mySerial.print(tempC);
  mySerial.print(gv);
  mySerial.println('#');
  delay(45000);
}


long microsecondsToCentimeters(long microseconds) // method to covert microsec to centimeters
{
   return microseconds / 29 / 2;
}


void rotate() {
  for(pos=0;pos<=1800;pos++){
  Myservo.write(pos);
  delay(15);
  }
}
