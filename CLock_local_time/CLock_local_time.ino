#include <ezTime.h>
#include <WiFi.h>

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

Timezone myTZ;
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
  }

  WiFi.begin("IceCube", "admin123");
    
  while (!Serial) {};
  waitForSync();

  Serial.println();

  // Provide official timezone names
  // https://en.wikipedia.org/wiki/List_of_tz_database_time_zones
  myTZ.setLocation(F("Asia/Dhaka"));
  Serial.print(F("Dhaka:     "));
  Serial.println(myTZ.dateTime());

  // Wait a little bit to not trigger DDoS protection on server
  // See https://github.com/ropg/ezTime#timezonedropnl
  delay(5000);
  Serial.println(myTZ.dateTime("g:i A"));
  Serial.println(myTZ.dateTime("jS F"));
  Serial.println(myTZ.dateTime());

    display.display();

}

void loop() {
  timeDate();
  //weatherStation();
  delay(delayTime);
}

void timeDate() {

  display.clearDisplay();
  
  display.setCursor(0,0);
  display.println(myTZ.dateTime("l Y"));
  display.println();  
 
  display.setTextSize(2);
  display.println(myTZ.dateTime("g:i A") + "\"");
    
  display.setTextSize(1);
  display.println();
  display.println(myTZ.dateTime("jS F"));

  display.setCursor(0, 55);
  display.print(bme.readTemperature() , 0);
  display.println("*C");

  display.setCursor(50, 55);
  display.print(bme.readHumidity(), 0);
  display.println("%");

 /* 
  *  display.setCursor(5, 55);
  display.print(bme.readPressure() / 100.0F , 0);
  display.println(" hPa");

  display.setCursor(64, 55);
  display.print(bme.readAltitude(SEALEVELPRESSURE_HPA),0);
  display.println(" m");
*/
  Serial.println();
  display.display();
}

void weatherStation() {
  display.clearDisplay();
  display.setCursor(10, 15);
  display.println("*Weather Station*");
  display.println("------------------");

  display.setCursor(0, 25);
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
