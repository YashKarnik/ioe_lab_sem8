#define BLYNK_TEMPLATE_ID "TMPLJ_3CHXUw"
#define BLYNK_DEVICE_NAME "Quickstart Device"
#define BLYNK_AUTH_TOKEN "bCJWXK62nds3JzigvFvmc-GaJhcdcND0"

#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>

#include 'sensors.h'

char auth[] = "bCJWXK62nds3JzigvFvmc-GaJhcdcND0";
BlynkTimer timer;

void GasLeakWarning()
{
    float gas = getgasSensorPinReading();
    String myStringe = "LEAK!";
    myString.concat(gas);
    Blynk.virtualWrite(V1, gas);
}

void TemperatureReading()
{
    float temp = gettemperatureSensorReading();
    Blynk.virtualWrite(V0, temp);
}

void setup()
{
    Serial.begin(9600);
    Blynk.begin(auth);

    timer.setInterval(1000L, GasLeakWarning);
    timer.setInterval(1000L, TemperatureReading);
}

void loop()
{
    Blynk.run();
    timer.run()
}
