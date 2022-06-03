/***************************************************************************
  This is a library for the BME280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2650

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface. The device's I2C address is either 0x76 or 0x77.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
  See the LICENSE file for details.
 ***************************************************************************/


#include <Wire.h>                 // I2C
#include <Adafruit_GFX.h>         // OLED
#include <Adafruit_SSD1306.h>     // Graphic

#define OLED_RESET 4 // not used nicht genutzt bei diesem Display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

//Adafruit_SSD1306 display(OLED_RESET); Treiber vor Version1.2
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

unsigned long delayTime;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Wire.begin();
  display.display();
  delay(5000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(INVERSE);
  Serial.begin(115200);
    


  while (!Serial);   // time to get serial running
  Serial.println(F("BME280 test"));

  unsigned status;

  // default settings
  status = bme.begin(0x76);
  // You can also pass in a Wire library object like &Wire2
  // status = bme.begin(0x76, &Wire2)
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(), 16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }

  Serial.println("-- Default Test --");
  delayTime = 1000;

  Serial.println();
}


void loop() {
  
display.clearDisplay();
  
  printValues();
  delay(delayTime);
}


void printValues() {
  display.setCursor(10,5);
  display.println("*Weather Station*");
  display.println("------------------");

  display.setCursor(0,20);
  Serial.print("Temp = ");
  display.print("Temp = ");
  Serial.print(bme.readTemperature());
  display.print(bme.readTemperature());
  Serial.println("*C");
  display.println("*C");

  Serial.print("Press = ");
  display.print("Press = ");

  Serial.print(bme.readPressure() / 100.0F);
  display.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");
  display.println(" hPa");

  Serial.print("Altitude = ");
  display.print("Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  display.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");
  display.println(" m");

  Serial.print("Humidity = ");
  display.print("Humidity = ");
  Serial.print(bme.readHumidity());
  display.print(bme.readHumidity());
  Serial.println(" %");
  display.println(" %");

  Serial.println();
  display.display();
  
    //display.drawPixel(10, 10, SSD1306_WHITE);
     // display.startscrollright(0x00, 0x0F);
       // delay(2000);
 // display.stopscroll();
}
