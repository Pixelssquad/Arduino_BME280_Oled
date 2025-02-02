/***************************************************************************
Based on the Adafruit example, added support for oled
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_BME280 bme; // use I2C interface
Adafruit_Sensor *bme_temp = bme.getTemperatureSensor();
Adafruit_Sensor *bme_pressure = bme.getPressureSensor();
Adafruit_Sensor *bme_humidity = bme.getHumiditySensor();

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);

void setup() {
  Serial.begin(9600);
  Serial.println(F("BME280 Sensor event test"));

  if (!bme.begin()) {
    Serial.println(F("Could not find a valid BME280 sensor, check wiring!"));
    while (1) delay(10);
  }
  
  bme_temp->printSensorDetails();
  bme_pressure->printSensorDetails();
  bme_humidity->printSensorDetails();

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
   // init done
  display.display();
  delay(1000);
  display.clearDisplay();
  display.display();
  display.setTextSize(1.2);
  display.setTextColor(WHITE);
  delay(1000);
  display.display();

}

void loop() {
  sensors_event_t temp_event, pressure_event, humidity_event;
  bme_temp->getEvent(&temp_event);
  bme_pressure->getEvent(&pressure_event);
  bme_humidity->getEvent(&humidity_event);
     display.clearDisplay();
     display.setCursor(0,0);
     display.print(" Diegooz BME280 Test");
     display.setCursor(0,10);
     display.print("^^^^^^^^^^^^^^^^^^^^^");

  Serial.print(F("Temperature = "));
  Serial.print(temp_event.temperature);
  Serial.println(" *C");
     display.setCursor(0,30);
     display.print("Temp.: "); display.print(temp_event.temperature); display.println(" °C");
 
  Serial.print(F("Humidity = "));
  Serial.print(humidity_event.relative_humidity);
  Serial.println(" %");
     display.setCursor(0,40);
     display.print("Umidita': "); display.print(humidity_event.relative_humidity); display.println(" %");

  Serial.print(F("Pressure = "));
  Serial.print(pressure_event.pressure);
  Serial.println(" hPa");
      display.setCursor(0,50);
      display.print("Press.: "); display.print(pressure_event.pressure); display.println(" hPa");


  display.display();
  Serial.println();
  delay(1000);
    display.clearDisplay();
}