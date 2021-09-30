#include <SPI.h>  //Para comuniacion con SD usando Tiva
#include <SD.h>

// Variables a usar dentro de la libreria
Sd2Card card;
SdVolume volume;
SdFile root;

const int chipSelect = 12; //SPI PIN
String archivo;            //variable en la q ira la palabra

File dataFile; //Variable para tener acceso a la informacion a los txt
//------------------------------------------------------------------------------------------------------------------------------------------------
void setup() {

  Serial.begin(9600);       //inicio comunicacion serial
  while (!Serial) {         //espero a q se establezca
    ;
  }
  SPI.setModule(0);         //Indespensable declarar el SPI a usar en TIVA C
  delay(2500);              //Tiempo para abrir la terminal serial
  Serial.print("\nInicializando tarjeta SD...\n");
  pinMode(12, OUTPUT);    // ChipSelect como salida

//Se inicializa la comunicacion con la SD, obtencion de datos, no acceder a la informacion, si no a sus propiedades
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {                 //Lo inicio en configuración de obtencion de datos
    Serial.println("Inicializacion de la SD fallida");

    return;
  } else {
    Serial.println("La tarjeta SD esta conectada.");
  }

  if (!volume.init(card)) {       //Se inicia a corde a los formatos permitidos
    Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    return;
  }

  menu();
 
}
//------------------------------------------------------------------------------------------------------------------------------------------------
void loop() {
//Siempre que se envie algo por comunicacion serial, lo almacene en string palabra
  while (Serial.available()) {  //Confirmando que la comunicación Serial esté disponible para hacer la lectura del mensaje
    delay(10);                  //para dar estabilidad al programa
    char c = Serial.read();     //lee el caracter turno
    archivo += c;               //sumando el contenido de la variable c en la variable mensaje (inserta caracter a la variable)
  }
//ARCHIVO 1------------------------------------------------------------------------------------
  if (archivo == "SHELBY\n"){
    Serial.println();
    //Se ingresa al archivo
    dataFile = SD.open("SHELBY.txt");  //creo un espacio en la memoria para guardar la info del txt abierto para leer
    //Se imprime el dato obtenido
    if (dataFile) {                           //si no esta vacio/existe el archivo imprimo lo leido
      while (dataFile.available()) {
        Serial.write(dataFile.read());
      }
      //Reinicio de configuracion
      dataFile.close();                       //cierro la comunicacion para que posterior a ello se pueda abrir para leer/escribir
      Serial.println();
      menu();
    }
    else {                                    //si no se puede abrir un archivo con el nombre declarado
      Serial.println("error al abrir SHELBY.txt");
      menu();
    }
//ARCHIVO 2------------------------------------------------------------------------------------
  } else if (archivo == "IRONMAN\n"){
    Serial.println();
    dataFile = SD.open("IRONMAN.txt");  //creo un espacio en la memoria para guardar la info del txt abierto para leer
    if (dataFile) {                           //si no esta vacio/existe el archivo imprimo lo leido
      while (dataFile.available()) {
        Serial.write(dataFile.read());
      }
      dataFile.close();                       //cierro la comunicacion para que posterior a ello se pueda abrir para leer/escribir
      Serial.println();
      menu();
    }
    else {                                    //si no se puede abrir un archivo con el nombre declarado
      Serial.println("error al abrir IRONMAN.txt");
      menu();
    }
//ARCHIVO 3------------------------------------------------------------------------------------
  } else if (archivo == "VIKINGS\n"){
    Serial.println();
    dataFile = SD.open("VIKINGS.txt");  //creo un espacio en la memoria para guardar la info del txt abierto para leer
    if (dataFile) {                           //si no esta vacio/existe el archivo imprimo lo leido
      while (dataFile.available()) {
        Serial.write(dataFile.read());
      }
      dataFile.close();                       //cierro la comunicacion para que posterior a ello se pueda abrir para leer/escribir
      Serial.println();
      menu();
    }
    else {                                    //si no se puede abrir un archivo con el nombre declarado
      Serial.println("error al abrir VIKINGS.txt");
      menu();
    }
//ARCHIVO 4------------------------------------------------------------------------------------
  } else if (archivo == "AVENGERS\n"){
    Serial.println();
    dataFile = SD.open("AVENGERS.txt");  //creo un espacio en la memoria para guardar la info del txt abierto para leer
    if (dataFile) {                           //si no esta vacio/existe el archivo imprimo lo leido
      while (dataFile.available()) {
        Serial.write(dataFile.read());
      }
      dataFile.close();                       //cierro la comunicacion para que posterior a ello se pueda abrir para leer/escribir
      Serial.println();
      menu();
    }
    else {                                    //si no se puede abrir un archivo con el nombre declarado
      Serial.println("error al abrir AVENGERS.txt");
      menu();
    }
//SIEMPRE QUE SEA DISTINTO DE UN CARACTER VACIO, NULO.
  } else if (archivo != "") {
    Serial.println("\n*************No es opcion valida*************");
  }

  archivo = ""; //Me aseguro de no repetir la seleccion

}
//------------------------------------------------------------------------------------------------------------------------------------------------
//FUNCION
void menu(void) {
  //SE CONFIGURA PARA NUEVAMENTE INICIAR EL MENU
  Serial.println("\nDocumentos encontrados en la SD: ");
  root.openRoot(volume);              //accedo a las propiedades de cada documento
  root.ls(LS_R);                       //la imprimo en el orden de datos que quiero
  delay(1000);                        //espero a que aparezcan
  root.close();                       //cierro la configuracion de obtencion de datos

//lECTURA DE ARCIVOS EN SD
  if (!SD.begin(chipSelect)) {        //Inicio la comunicacion a la SD pero en config. de lectura/escritura
    return;
  }
  Serial.println("Tajerta SD inicializada.");

}
