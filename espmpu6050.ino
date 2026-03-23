#include <WiFi.h>
#include <WebSocketsServer.h>
#include <MPU6050_tockn.h>
#include <Wire.h>

const char* ssid = "name";
const char* password = "pass";

IPAddress local_IP(192, 168, 1, 222);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WebSocketsServer webSocket = WebSocketsServer(81);
MPU6050 mpu6050(Wire);
unsigned long lastMsg = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  WiFi.config(local_IP, gateway, subnet);
  WiFi.begin(ssid, password);
  
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  webSocket.begin();
}

void loop() {
  webSocket.loop();
  mpu6050.update();

  unsigned long now = millis();
  if (now - lastMsg > 30) {
    float x = mpu6050.getAngleX();
    float y = mpu6050.getAngleY();
    float z = mpu6050.getAngleZ();

    String msg = String(x, 2) + "," + String(y, 2) + "," + String(z, 2);
    
    Serial.println(msg);
    webSocket.broadcastTXT(msg);
    
    lastMsg = now;
  }
}
