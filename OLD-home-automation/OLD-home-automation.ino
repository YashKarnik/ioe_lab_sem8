#include <DHT.h>
#include <DHT_U.h>

#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04
#define distanceLed 4

#define smokePin A0
#define smokeLed 6
#define smokeThreshold 15

#define DHTType DHT11
#define tempHumidityPin 5
DHT dht(tempHumidityPin, DHTType);

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(distanceLed, OUTPUT);

  pinMode(smokePin, INPUT);
  pinMode(smokeLed, OUTPUT);

  dht.begin(); // initialize the sensor
  
  Serial.begin(9600); // Serial Communication is starting with 9600 of baudrate speed
}

void loop() {
  digitalWrite(distanceLed, LOW);
  measureDistance();

  digitalWrite(smokeLed, LOW);
  measureSmoke();
  
  measureTempHumidity();
  
  Serial.println();
  delay(2000);
}

void measureDistance() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if(distance < 5) {
    digitalWrite(distanceLed, HIGH);
  }
}

void measureTempHumidity() {
  // read humidity
  float humi  = dht.readHumidity();
  // read temperature as Celsius
  float tempC = dht.readTemperature();
  // read temperature as Fahrenheit
  float tempF = dht.readTemperature(true);

  // check if any reads failed
  if (isnan(humi) || isnan(tempC) || isnan(tempF)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Humidity: ");
    Serial.print(humi);
    Serial.print("%");

    Serial.print("  |  "); 

    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.print("°C ~ ");
    Serial.print(tempF);
    Serial.println("°F");
  }
}

void measureSmoke() {
  int analogSensor = analogRead(smokePin);

  Serial.print("Smoke: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor > smokeThreshold) {
    digitalWrite(smokeLed, HIGH); 
  }
}

// Reference articles
// DHT11: https://arduinogetstarted.com/tutorials/arduino-temperature-humidity-sensor
// MQ-2: https://create.arduino.cc/projecthub/Aritro/smoke-detection-using-mq-2-gas-sensor-79c54a
// LED: https://create.arduino.cc/projecthub/rowan07/make-a-simple-led-circuit-ce8308
// HC-SR04: https://create.arduino.cc/projecthub/abdularbi17/ultrasonic-sensor-hc-sr04-with-arduino-tutorial-327ff6
