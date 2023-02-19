#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

#include "config.h"

#define INTERPRETER_PIN GPIO_NUM_13

MPU6050 accelgyro;

void wifiConnect(const char* ssid, const char* password) {
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) { delay(100); }
}

void sendLineNotify(const char* host, const char* token, String message) {
  WiFiClientSecure client;  
  client.setInsecure();
  String query = String("message=") + String(message);
  String request = String("") +
               "POST /api/notify HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Authorization: Bearer " + token + "\r\n" +
               "Content-Length: " + String(query.length()) +  "\r\n" + 
               "Content-Type: application/x-www-form-urlencoded\r\n\r\n" +
                query + "\r\n";

  client.connect(host, 443);
  client.print(request);

  while (client.connected()) { if (client.readStringUntil('\n') == "\r") break; }
}

void wifiDisconnect(){
  WiFi.disconnect();
}

void setup() {
  Serial.begin(115200);
  Wire.begin(25, 26); // SDA = 25 SCL = 26 へ変更
  delay(1000);
  
  accelgyro.initialize();

  // 動体検知のパラメータ指定
  accelgyro.setIntMotionEnabled(true);
  accelgyro.setMotionDetectionDuration(60);
  accelgyro.setInterruptMode(HIGH);

  // 復帰用のpin指定
  esp_sleep_enable_ext0_wakeup(INTERPRETER_PIN, 0);
 
  // deepsleepからの復帰時処理
  if(esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0){
    wifiConnect(WIFI_SSID, WIFI_PASS);
    sendLineNotify(LINE_HOST, LINE_TOKEN, "動体検知しました。");
    wifiDisconnect();
  }

  esp_deep_sleep_start();
}

void loop() { }
