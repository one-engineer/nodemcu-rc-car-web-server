#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80); // 80 numaralı port

// wifi kurulumu
const int ena = 14;
const int enb = 12;
const int in1 = 5;
const int in2 = 4;
const int in3 = 0;
const int in4 = 2;

int speedCar = 1000;  

char ssid[] = "****";
char pass[] = "****";
char HTML[] = "<!DOCTYPE html> <head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}.button { background-color: #6df996; border: none; color: white; padding: 25px 25px;text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}.button2 {background-color: #9effba;}</style> </head> <body> <h1>WifiArac</h1> <button class=\"button\"><a href=\"ileri\">Go</a></button> <br> <button class=\"button\" ><a href=\"sol\">Left</a></button> <button class=\"button button2\" ><a href=\"dur\">Stop</a></button> <button class=\"button\"><a href=\"sag\">Right</a></button> <br> <button class=\"button\"><a href=\"geri\">Back</a></button> <h2> Kontrol et </h2> </body></html>"; // --> Simple HTML page

void handleRoot() {
  server.send(200,"text / html", HTML);
   
}

void setup() {

  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  Serial.begin(115200);
  WiFi.begin(ssid, pass); // wifi bağlantısı için
  Serial.println("");
  Serial.print("Bağlanıyor . ");
  while ( WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  server.on("/", handleRoot);// işleyici işlevini yolla ve ilişkilendirme
  server.on("/other",[] (){
  server.send(200, "text/html"," Other URL");
  });
  server.begin(); //Server başladı
  Serial.print("Server bekliyor, acik ");
  Serial.print(WiFi.localIP());
  Serial.println(" tarayıcıda");
  server.on("/", handleRoot);
server.on("/ileri",ileri);
server.on("/sol",sol);
server.on("/sag",sag);
server.on("/geri",geri);
server.on("/dur",dur);
server.begin();
}

void loop(){
  server.handleClient(); // gelen taleplerin ele alınması
 
  
}

void ileri(){
  Serial.println("Motor ileri");
  server.send(200,"text/html",HTML);

   digitalWrite(in1, LOW);
   digitalWrite(in2, HIGH);
   analogWrite(ena, speedCar);

   digitalWrite(in3, HIGH);
   digitalWrite(in4, LOW);
   analogWrite(enb, speedCar);
 
}
void geri(){
  Serial.println("Motor geri");
  server.send(200,"text/html",HTML);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(ena, speedCar);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enb, speedCar);
}
void sag(){
  Serial.println("Motor sag");
  server.send(200,"text/html",HTML);

   digitalWrite(in1, HIGH);
   digitalWrite(in2, LOW);
   analogWrite(ena, speedCar);

   digitalWrite(in3, HIGH);
   digitalWrite(in4, LOW);
   analogWrite(enb, speedCar);
}
void sol(){
  Serial.println("Motor sol");
  server.send(200,"text/html",HTML);


  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(ena, speedCar);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enb, speedCar);
  }


void dur(){
  Serial.println("Motor dur");
  server.send(200,"text/html",HTML);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(ena, speedCar);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enb, speedCar);
}
