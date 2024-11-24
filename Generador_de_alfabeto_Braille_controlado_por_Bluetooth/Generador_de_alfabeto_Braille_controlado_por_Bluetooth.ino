//Universidad de El Salvador
//Facultad de Ingenieria y arquitectura
//Arquitectura de computadoras - ARC115 - Ciclo II - 2024
//codigo fuente - Generador de alfabeto braille
//codigo diseñado por Jeyby Sabriska Castillo Ramirez
//revisado e implementado por Jose Raul Urquilla

//declaracion de librerias de entorno
#include <SoftwareSerial.h> // Incluimos la librería SoftwareSerial
//definicion de variables de entorno
// matriz de códigos Braille donde contenera la representacion de las letras en braille desde la letra a hasta la Z
//declaracion de variables de entorno
// Definición de los códigos Braille para las letras a-z 
int braille[27][6] = {
//{2,3,4,5,6,7}pines del arduino
//{1,2,3,4,5,6} puntos en el braille
  {1,0,0,0,0,0},  // a
  {1,1,0,0,0,0},  // b
  {1,0,0,1,0,0},  // c
  {1,0,0,1,1,0},  // d
  {1,0,0,0,1,0},  // e
  {1,1,0,1,0,0},  // f
  {1,1,0,1,1,0},  // g
  {1,1,0,0,1,0},  // h
  {0,1,0,1,0,0},  // i
  {0,1,0,1,1,0},  // j
  {1,0,1,0,0,0},  // k
  {1,1,1,0,0,0},  // l
  {1,0,1,1,0,0},  // m
  {1,0,1,1,1,0},  // n
  {1,0,1,0,1,0},  // o
  {1,1,1,1,0,0},  // p
  {1,1,1,1,1,0},  // q
  {1,1,1,0,1,0},  // r
  {0,1,1,1,0,0},  // s
  {0,1,1,1,1,0},  // t
  {1,0,1,0,0,1},  // u
  {1,1,1,0,0,1},  // v
  {0,1,0,1,1,1},  // w
  {1,0,1,1,0,1},  // x
  {1,0,1,1,1,1},  // y
  {1,0,1,0,1,1},  // z
};
//variable que determina el tiempo de uso configuracion del modulo HC-06
unsigned long Ret1 = 100;
//declaracion de pines a utilizar dentro del arduino
// Array de pines de Arduino para controlar los solenoides
int controlPins[6] = {2, 3, 4, 5, 6, 7};
// Pin para el botón
int buttonPin = 8;
//pines a utilizar para la comunicacion del bluetooth
SoftwareSerial BT(9,10); // Definimos los pines RX=9 y TX=10 del Arduino conectados al Bluetooth

//configuracion del arduino
void setup(){
  //configuramos la velocidad en baudios del puerto serie del modulo
  BT.begin(9600); // Inicializamos el puerto serie BT que hemos creado 
  // Configurar los pines de control como salidas
  for (int i = 0; i < 6; i++) {
    pinMode(controlPins[i], OUTPUT);
  }  
  // Configurar el pin 8 del arduino como entrada
  pinMode(buttonPin, INPUT);  
  // chequeo inicial de los solenoides
  for (int i = 0; i < 6; i++) {
    digitalWrite(controlPins[i], HIGH);
  }
  delay(1000);
  for (int i = 0; i < 6; i++) {
    digitalWrite(controlPins[i], LOW);
  }
  delay(500);
  //configuracion general para el modulo bluetooth
 //Comandos AT
  BT.print("AT+NAMEBraille2024"); //Comando AT: Modifique UES01 por un nombre de su elección
  delay(Ret1*10);
  BT.print("AT+PIN1234");   //Comando AT: Código de vinculación
  delay(Ret1*10);
  BT.print("AT+BAUD4");   //Comando AT: Velocidad de comunicación serial
  delay(Ret1*10);  
}

//subrutina general
void loop() {
  String Lectura;
  if(BT.available()) { // Si llega un dato por el puerto BT se a la variable del tipo string
   Lectura = BT.read();//capturamos el dato enviado al modulo bluetooth
   Lectura.trim(); // Eliminar espacios en blanco    
   //posteriormente se procesara cada letra encontrada en el string
   for (int i = 0; i < Lectura.length(); i++) {
      char letter = Lectura[i];
      int index = letter - 'a';      
      if (index >= 0 && index < 26) {
        // Mostrar la letra en los solenoides según el patrón de Braille
        for (int j = 0; j < 6; j++) {
          digitalWrite(controlPins[j], braille[index][j]);
        }        
        delay(1000); // Mantener la letra en los solenoides por 1 segundo        
        // Apagar todos los solenoides antes de la siguiente letra
        for (int j = 0; j < 6; j++) {
          digitalWrite(controlPins[j], LOW);
        }
        delay(500); // Pausa entre letras
      }
   } 
  }      
  // Verificar si el usuario presiono el boton de chequeo de los solenoides
  if (digitalRead(buttonPin) == LOW){
    //activar los solenoides de forma secuencial
     for(int i=0; i<=5; i++){
      digitalWrite(controlPins[i],HIGH);
      delay(1000);
      digitalWrite(controlPins[i],LOW);
     }
   }
}
