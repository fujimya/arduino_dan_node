#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

ESP8266WiFiMulti WiFiMulti;

//http
#define pushUrl "http://service.tangkal.com/Push.php?ref=https://palangpintu.firebaseio.com/&auth=Zs4pwkm5CilcGRWUwmO569xQhmYlADeHkrnYZdg2&path=/"

int pinInbuka = 16;
int pinIntutup = 5;

void setup() {
  pinMode(pinInbuka, INPUT);
  pinMode(pinIntutup, INPUT);
  Serial.begin(115200);
  int buka = digitalRead(pinInbuka);
  int tutup = digitalRead(pinIntutup);
  Serial.print("Buka : ");
  Serial.println(buka);
  Serial.print("Tutup : ");
  Serial.println(tutup);
  // put your setup code here, to run once:
  WiFiMulti.addAP("samsungxiaomi", "marcello5");
  while (WiFiMulti.run() != WL_CONNECTED) {
    digitalWrite(2, HIGH);
    delay(200);
    digitalWrite(2, LOW);
    delay(200);
    digitalWrite(2, HIGH);
    delay(200);
    digitalWrite(2, LOW);
    delay(200);
    digitalWrite(2, HIGH);
  }


}

//push data to firebare
void pushData(String ref, String path, String data)
{
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    ref += path;
    ref += "&data=";
    ref += data;
    HTTPClient http;
    http.begin(ref);
    int httpCode = http.GET();


    if (httpCode > 0) {

      if (httpCode == HTTP_CODE_OK)
      {

      }
    }
    else {
    }
    http.end();

  }
}

void loop() {
  // put your main code here, to run repeatedly:
  //  pushData(pushUrl, "rekam_data/palang", "tutup");
  int buka = digitalRead(pinInbuka);
  int tutup = digitalRead(pinIntutup);
  Serial.print("Buka : ");
  Serial.println(buka);
  Serial.print("Tutup : ");
  Serial.println(tutup);
  if(buka == 0){
    pushData(pushUrl, "rekam_data/palang", "buka");
  }
  if(tutup == 0){
     pushData(pushUrl, "rekam_data/palang", "tutup");
  }
  
  delay(50);

}
