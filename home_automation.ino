int gasSensorPin = A5;
int distanceSensorPin = 13;
int echoPin = A4;
int temperatureSensorPin = 0;

void setup()
{
  // Gas Sensor
  pinMode(gasSensorPin, INPUT);

  // Distance Sensor
  pinMode(distanceSensorPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Temperature Sensor
  pinMode(tempPin, INPUT);

  Serial.begin(9600);
}

float getgasSensorPinReading()
{
  // https://create.arduino.cc/projecthub/Aritro/smoke-detection-using-mq-2-gas-sensor-79c54a
  int analogSensor = analogRead(gasSensorPin);
  return analogSensor;
}

float getDistanceSensorReading()
{
  // https://create.arduino.cc/projecthub/abdularbi17/ultrasonic-sensor-hc-sr04-with-arduino-tutorial-327ff6
  digitalWrite(distanceSensorPin, LOW);
  delayMicroseconds(2);
  digitalWrite(distanceSensorPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(distanceSensorPin, LOW);
  float duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;
  return distance;
}

float gettemperatureSensorReading()
{
  // https://www.tinkercad.com/things/i4VRaCal6PK-yashnakulharsh
  float temp = analogRead(temperatureSensorPin);
  temp = temp * 5.0;
  temp = temp / 1024.0;
  return (temp - 0.5) * 100;
}

void loop()
{
  Serial.print("Gas Sensor");
  Serial.println(getgasSensorPinReading());
  Serial.print("DIstance Sensor");
  Serial.println(getDistanceSensorReading());
  Serial.print("Temperature Sensor");
  Serial.println(gettemperatureSensorReading());
  delay(100);
}