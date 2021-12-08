#include <ESP8266WiFi.h> // Libreria de trabajo ESP8266
#include <ESPAsyncTCP.h> // Servidor TCP
#include <ESPAsyncWebServer.h> //Libreria de conexion y eleccion de IP
#include <FS.h> // Interconexion con pagina web
#include <Wire.h> // Conexion serial
int e;
int d;
int r;
const char* ssid = "Patty"; // Nombre de red
const char* password = "Patty99603879"; // Clave WiFi

const char* ssid_ap = "ssid"; // Nombre de red
const char* password_ap = "password"; // Clave WiFi

const char* ssid_movil = "Gare"; // Nombre de red
const char* password_movil = "3152Gare."; // Clave WiFi

AsyncWebServer server(443); // Elección de puerto de trabajo

const int Pin = 1; // Constante de activacion del sistema
String Estado;


String processor(const String& var)
{
  if(var == "ESTADO") // Activación
    {
     if(digitalRead(Pin)==1)
     {
      Estado= "Encendido";
     }
     else
     {
      Estado = "Apagado";
     }
    return Estado;
    }
  
} 





void setup(){
  pinMode(12, INPUT); // interruptor
  pinMode(13, INPUT);
  e=digitalRead(12); // lectura de interruptor
  d=digitalRead(13);
  // Inicializacion de conexion serial con arduino nano
  Serial.begin(9600); // velocidad de trabajo serial
  Wire.begin(); 
  if(!SPIFFS.begin()){
    Serial.println("Conexion Fallida"); // Señal de error auxiliar
    return;
  }
  
if(e==HIGH){//&&d==LOW){
  r=1;
IPAddress ip(192,168,0,15);     //Selección de IP en LAN
IPAddress gateway(192,168,0,1);   
IPAddress subnet(255,255,255,0);
  // Conexion WiFi
  WiFi.mode(WIFI_STA);
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);}

   /* if(e==LOW&&d==HIGH||e==HIGH&&d==HIGH){  
      r=1;
IPAddress ip(192,168,0,4); //Selección de IP en LAN de telefono movil
IPAddress gateway(192,168,148,100);
IPAddress subnet(255,255,255,0);
  // Conexion WiFi
  WiFi.mode(WIFI_STA);
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid_ap, password_ap);
    
    }*/

   else{  
    r=0;
IPAddress ip(192,168,148,139); //Selección de IP en LAN de telefono movil
IPAddress gateway(192,168,148,100);
IPAddress subnet(255,255,255,0);
  // Conexion WiFi
  WiFi.mode(WIFI_STA);
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid_movil, password_movil);
  
    
    }

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi..");
  }
  Serial.println(WiFi.localIP());

  
 Wire.beginTransmission(2);
  // Ruta de direccion de control via vinculo
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Llamada al archivo estilos para la estetica de la pagina en html
  server.on("/estilos.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/estilos.css", "text/css");
    
  });

  // Funcion de avanzar
  server.on("/Avanzar=ON", HTTP_GET, [](AsyncWebServerRequest *request){
      
    request->send(SPIFFS, "/index.html", String(), false, processor);
    
    
   Wire.beginTransmission(2);
   
 Wire.write('w'); // envia un byte
Serial.println("avanzar");
Wire.endTransmission(); // detoene la transmisión



  });

  // Funcion de retroceder
  server.on("/Retroceder=OFF", HTTP_GET, [](AsyncWebServerRequest *request){
      
    request->send(SPIFFS, "/index.html", String(), false, processor);
 
   Wire.beginTransmission(2);
 Wire.write('s'); // envia un byte
Serial.println("Retroceder");
Wire.endTransmission(); // detoene la transmisión

  });
  
  // Funcion de configuracion inicial
  server.on("/Configuracion_inicial=ON", HTTP_GET, [](AsyncWebServerRequest *request){
  
    request->send(SPIFFS, "/index.html", String(), false, processor);


  Wire.beginTransmission(2);
  
  Wire.write('g');
  Serial.println("configuracion inicial");
  Wire.endTransmission();
 
  
  });
// Funcion de detenerse
  server.on("/Detenerse=OFF", HTTP_GET, [](AsyncWebServerRequest *request){
    
    request->send(SPIFFS, "/index.html", String(), false, processor);
   Wire.beginTransmission(2);
  Wire.write('h');
  Serial.println("Detenerse");
  Wire.endTransmission();

  
  });

// Funcion de doblar a la izquierda
  server.on("/Doblar_Izquierda=ON", HTTP_GET, [](AsyncWebServerRequest *request){
    
     
    request->send(SPIFFS, "/index.html", String(), false, processor);

   Wire.beginTransmission(2);
  Wire.write('a');
  Serial.println("Izquierda");
  Wire.endTransmission();

  });

  // Funcion de doblar a la derecha
  server.on("/Doblar_Derecha=OFF", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);

   Wire.beginTransmission(2);
  Wire.write('d');
  Serial.println("Derecha");
  Wire.endTransmission();
 
  
  });


  

  server.begin();
}
void loop() {
} 
