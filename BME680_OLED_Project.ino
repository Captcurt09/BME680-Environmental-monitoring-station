#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BME680.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_BME680 bme;

void setup() {
  Serial.begin(115200);

  Wire.begin(21, 22);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED Failed");
    while (1);
  }

  if (!bme.begin(0x77)) {
    Serial.println("BME680 Failed");
    while (1);
  }

  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setGasHeater(320, 150);
}

void loop() {

  if (!bme.performReading()) {
    Serial.println("Reading Failed");
    return;
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  float tempF = (bme.temperature * 9.0 / 5.0) + 32.0;

  display.setCursor(0,0);
  display.print("Temp: ");
  display.print(tempF, 1);
  display.println(" F");

  display.print("Hum: ");
  display.print(bme.humidity);
  display.println("%");

  display.print("Pres:");
  display.print(bme.pressure / 100.0);
  display.println("hPa");

  display.print("Gas: ");
  display.print(bme.gas_resistance / 1000.0);
  display.println("K");

  display.display();

  delay(2000);
}