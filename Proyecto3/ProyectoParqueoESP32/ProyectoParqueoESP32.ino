#define RXD2 16
#define TXD2 17
#include <WiFi.h>

byte pin[] = {26,27,14,12,32,33,25};   // pin 26,27,14,12,32,33,25 para a,b,c,d,e,f,g

//---------------------Credenciales de WiFi-----------------------

const char* ssid     = "CABELNET-CDBB70";
const char* password = "68CDBB70";
//------------------Servidor Web en puerto 80---------------------

WiFiServer server(80);

//---------------------VARIABLES GLOBALES-------------------------
int contconexion = 0;

String header; // Variable para guardar el HTTP request

//------------------------CODIGO HTML------------------------------
String paginaInicio = "<!DOCTYPE html>"
"<html lang='es'>"
"<head>"
"<title>Parqueo-Sotano 1</title>"
"<meta charset='utf-8'/>"
"<META HTTP-EQUIV='Refresh' CONTENT='1'>"
"<meta name='descripcion' content='Display de la cantidad de parqueos disponibles en el sotano 1'/>"
"<meta name='author' content='Juan Diego Villafuerte & Juan  Eliseo Lux'/>"
"<style>"
"* {"
"font-family: verdana;"
"text-align: center;"
"margin: auto;"
"}"
"</style>"
"</head>"
"<body>"
"<header>"       
"<h1 style='font-size: 50px; margin-top: 5%;'>Parqueos Disponibles</h1>"
"</header>"
"<section style='font-size: 50px; font-family: verdana;'>";

String paginaFin = "</section>"
"<img src='logo.jpg' alt='' style='display: block; width: 150px; margin: auto; padding: 55px 5%; float: left;'>"
"<footer style='display: block; background: black; color: gray; padding: 60px 20%; '>"
"<h3 style='text-align: left;'>Universidad del Valle de Guatemala</h3><br>"
"<h4 style='text-align: left;'>Creado por:</h4><br>"
"<h5 style='text-align: left;'>Juan Diego Villafuerte Pazos</h5>"
"<h6 style='text-align: left;'>juandiegovillafuertepazos@gmail.com</h5><br>"
"<h5 style='text-align: left;'>Juan Eliseo Lux Cajas</h5>"
"<h6 style='text-align: left;'>juaneliseolux240116@gmail.com</h5>"
"</footer>"
"</body>"
"</html>";


//---------------------------SETUP--------------------------------

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  
  pinMode(pin[0], OUTPUT);  //a
  pinMode(pin[1], OUTPUT);  //b
  pinMode(pin[2], OUTPUT);  //c
  pinMode(pin[3], OUTPUT);  //d
  pinMode(pin[4], OUTPUT);  //e
  pinMode(pin[5], OUTPUT);  //f
  pinMode(pin[6], OUTPUT);  //g
  // Conexión WIFI
  WiFi.begin(ssid, password);
  //Cuenta hasta 50 si no se puede conectar lo cancela
  while (WiFi.status() != WL_CONNECTED and contconexion <50) { 
    ++contconexion;
    delay(500);
    Serial.print(".");
  }
  if (contconexion <50) {
      //para usar con ip fija
      //IPAddress ip(192,168,1,180); 
      //IPAddress gateway(192,168,1,1); 
      //IPAddress subnet(255,255,255,0); 
      //WiFi.config(ip, gateway, subnet); 
      
      Serial.println("");
      Serial.println("WiFi conectado");
      Serial.println(WiFi.localIP());
      server.begin(); // iniciamos el servidor
  }
  else { 
      Serial.println("");
      Serial.println("Error de conexion");
  }  


}
//----------------------------LOOP----------------------------------
void loop() {
  String recibido = Serial2.readString();
  int num = recibido.toInt();
  
  WiFiClient client = server.available();   // Escucha a los clientes entrantes
  if (client) {                             // Si se conecta un nuevo cliente
    Serial.println("New Client.");          // 
    String currentLine = "";                //
    while (client.connected()) {            // loop mientras el cliente está conectado
      if (client.available()) {             // si hay bytes para leer desde el cliente
        char c = client.read();             // lee un byte
        Serial.write(c);                    // imprime ese byte en el monitor serial
        header += c;
        if (c == '\n') {                    // si el byte es un caracter de salto de linea
          // si la nueva linea está en blanco significa que es el fin del 
          // HTTP request del cliente, entonces respondemos:
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
                     
            // Muestra la página web
            client.println(paginaInicio + recibido + paginaFin);
            
            // la respuesta HTTP temina con una linea en blanco
            client.println();
            break;
          } else { // si tenemos una nueva linea limpiamos currentLine
            currentLine = "";
          }
        } 
      }
    }
    // Limpiamos la variable header
    header = "";
    // Cerramos la conexión
    client.stop();
  }

//el html base
  if(num){
    switch(num){
      case 8:
      limpiar();
      ocho();
      break;

      case 7:
      limpiar();
      siete();
      break;

      case 6:
      limpiar();
      seis();
      break;

      case 5:
      limpiar();
      cinco();
      break;

      case 4:
      limpiar();
      cuatro();
      break;

      case 3:
      limpiar();
      tres();
      break;

      case 2:
      limpiar();
      dos();
      break;

      case 1:
      limpiar();
      uno();
      break;

      case 0:
      limpiar();
      cero();
      break;
    }
  }
}
void cero(){ 
digitalWrite(pin[0],HIGH);   //a
digitalWrite(pin[1],HIGH);  //b
digitalWrite(pin[2],HIGH);  //c
digitalWrite(pin[3],HIGH);   //d
digitalWrite(pin[4],HIGH);   //e
digitalWrite(pin[5],HIGH);   //f
digitalWrite(pin[6],LOW);   //g
}
void uno(){ 
digitalWrite(pin[0],LOW);   //a
digitalWrite(pin[1],HIGH);  //b
digitalWrite(pin[2],HIGH);  //c
digitalWrite(pin[3],LOW);   //d
digitalWrite(pin[4],LOW);   //e
digitalWrite(pin[5],LOW);   //f
digitalWrite(pin[6],LOW);   //g
}
void dos(){ 
digitalWrite(pin[0],HIGH);   //a
digitalWrite(pin[1],HIGH);  //b
digitalWrite(pin[2],LOW);  //c
digitalWrite(pin[3],HIGH);   //d
digitalWrite(pin[4],HIGH);   //e
digitalWrite(pin[5],LOW);   //f
digitalWrite(pin[6],HIGH);   //g
}
void tres(){ 
digitalWrite(pin[0],HIGH);   //a
digitalWrite(pin[1],HIGH);  //b
digitalWrite(pin[2],HIGH);  //c
digitalWrite(pin[3],HIGH);   //d
digitalWrite(pin[4],LOW);   //e
digitalWrite(pin[5],LOW);   //f
digitalWrite(pin[6],HIGH);   //g
}
void cuatro(){ 
digitalWrite(pin[0],LOW);   //a
digitalWrite(pin[1],HIGH);  //b-
digitalWrite(pin[2],HIGH);  //c-
digitalWrite(pin[3],LOW);   //d
digitalWrite(pin[4],LOW);   //e
digitalWrite(pin[5],HIGH);   //f-
digitalWrite(pin[6],HIGH);   //g-
}
void cinco(){ 
digitalWrite(pin[0],HIGH);   //a-
digitalWrite(pin[1],LOW);  //b
digitalWrite(pin[2],HIGH);  //c-
digitalWrite(pin[3],HIGH);   //d-
digitalWrite(pin[4],LOW);   //e
digitalWrite(pin[5],HIGH);   //f-
digitalWrite(pin[6],HIGH);   //g-
}
void seis(){ 
digitalWrite(pin[0],LOW);   //a
digitalWrite(pin[1],LOW);  //b
digitalWrite(pin[2],HIGH);  //c-
digitalWrite(pin[3],HIGH);   //d-
digitalWrite(pin[4],HIGH);   //e-
digitalWrite(pin[5],HIGH);   //f-
digitalWrite(pin[6],HIGH);   //g-
}
void siete(){ 
digitalWrite(pin[0],HIGH);   //a-
digitalWrite(pin[1],HIGH);  //b-
digitalWrite(pin[2],HIGH);  //c-
digitalWrite(pin[3],LOW);   //d
digitalWrite(pin[4],LOW);   //e
digitalWrite(pin[5],LOW);   //f
digitalWrite(pin[6],LOW);   //g
}
void ocho(){ 
digitalWrite(pin[0],HIGH);   //a
digitalWrite(pin[1],HIGH);  //b
digitalWrite(pin[2],HIGH);  //c
digitalWrite(pin[3],HIGH);   //d
digitalWrite(pin[4],HIGH);   //e
digitalWrite(pin[5],HIGH);   //f
digitalWrite(pin[6],HIGH);   //g
}
void limpiar(){ 
digitalWrite(pin[0],LOW);   //a
digitalWrite(pin[1],LOW);  //b
digitalWrite(pin[2],LOW);  //c
digitalWrite(pin[3],LOW);   //d
digitalWrite(pin[4],LOW);   //e
digitalWrite(pin[5],LOW);   //f
digitalWrite(pin[6],LOW);   //g
}
