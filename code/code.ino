#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80); // 80 numaralı port


const int ena = 14;
const int enb = 12;
const int in1 = 5;
const int in2 = 4;
const int in3 = 0;
const int in4 = 2;

int speedCar=450;  
// wifi kurulumu
char ssid[] ="";
char pass[] = "";
char HTML[] = " <!DOCTYPE html>  <head> <meta name=\'viewport\' content=\'width=device-width, initial-scale=1\'></head>  <style> html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}.button { background-color: #6df996; border: none;  color: white;  padding: 25px 25px; text-decoration: none;  font-size: 30px;  margin: 2px;  cursor: pointer; } .button2 {background-color: #9effba; } </style> <body>  <h1>RC Car - IOT</h1>  <button class=\'button\'><a href=\'ileri\'>ILERI</a></button> <br> <button class=\'button\' ><a href=\'sol\'>SOL</a></button>  <button class=\'button button2\' ><a href=\'dur\'>DUR</a></button>  <button class=\'button\'><a href=\'sag\'>SAG</a></button>  <br> <button class=\'button\'><a href=\'geri\'>GERI</a></button>  <h2> Hiz Miktari </h2>  <button class=\'button\'><a href=\'yavas\'>Yavas</a></button> <button class=\'button\'><a href=\'orta\'>Orta</a></button> <button class=\'button\'><a href=\'hizli\'>Hizli</a></button> </body></html>";

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

server.on("/yavas",yavas);
server.on("/orta",orta);
server.on("/hizli",hizli);
server.begin();
}

void loop(){
  server.handleClient(); // gelen taleplerin ele alınması
 
  
}
void yavas(){
  speedCar = 300;
  server.send(200,"text/html",HTML);
}
void orta(){
 speedCar = 600;
 server.send(200,"text/html",HTML);
}
void hizli(){
   speedCar = 1000;
   server.send(200,"text/html",HTML);
  
}
void ileri(){
  Serial.println("\nMotor ileri");
  server.send(200,"text/html",HTML);

   digitalWrite(in1, LOW);
   digitalWrite(in2, HIGH);
   analogWrite(ena, speedCar);

   digitalWrite(in3, HIGH);
   digitalWrite(in4, LOW);
   analogWrite(enb, speedCar);
  Serial.print("Motor hizi: ");
  Serial.print(speedCar);
}
void geri(){
  Serial.println("\nMotor geri");
  server.send(200,"text/html",HTML);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(ena, speedCar);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enb, speedCar);
  Serial.print("Motor hizi: ");
  Serial.print(speedCar);
}
void sag(){
  Serial.println("\nMotor sag");
  server.send(200,"text/html",HTML);

   digitalWrite(in1, HIGH);
   digitalWrite(in2, LOW);
   analogWrite(ena, speedCar);

   digitalWrite(in3, HIGH);
   digitalWrite(in4, LOW);
   analogWrite(enb, speedCar);
  Serial.print("Motor hizi: ");
  Serial.print(speedCar);
}
void sol(){
  Serial.println("\nMotor sol");
  server.send(200,"text/html",HTML);


  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(ena, speedCar);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enb, speedCar);
  Serial.print("Motor hizi: ");
  Serial.print(speedCar);
  
  }


void dur(){
  Serial.println("\nMotor dur");
  server.send(200,"text/html",HTML);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(ena, speedCar);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enb, speedCar);
  Serial.print("\nMotor hizi: ");
  Serial.print(speedCar);
}
