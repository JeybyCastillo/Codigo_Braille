// Definición de los códigos Braille para las letras a-z 
int braille[26][6] = {
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

// Array de pines de Arduino para controlar los LEDs
int controlPins[6] = {2, 3, 4, 5, 6, 7};

// Pin para el botón
int buttonPin = 8;

void setup() {
  Serial.begin(9600);
  
  // Configurar los pines de control como salidas
  for (int i = 0; i < 6; i++) {
    pinMode(controlPins[i], OUTPUT);
  }
  
  // Configurar el pin del botón como entrada
  pinMode(buttonPin, INPUT);
  
  // Comprobar que los LEDs funcionan
  for (int i = 0; i < 6; i++) {
    digitalWrite(controlPins[i], HIGH);
  }
  delay(1000);
  for (int i = 0; i < 6; i++) {
    digitalWrite(controlPins[i], LOW);
  }
  delay(500);
}

void loop() {
  // Si hay datos disponibles en el monitor serial
  if (Serial.available() > 0) {
    String word = Serial.readStringUntil('\n'); // Leer la palabra enviada
    word.trim(); // Eliminar espacios en blanco
    
    // Procesar cada letra de la palabra
    for (int i = 0; i < word.length(); i++) {
      char letter = word[i];
      int index = letter - 'a';
      
      if (index >= 0 && index < 26) {
        // Mostrar la letra en LEDs según el patrón de Braille
        for (int j = 0; j < 6; j++) {
          digitalWrite(controlPins[j], braille[index][j]);
        }
        
        delay(1000); // Mantener la letra en pantalla por 1 segundo
        
        // Apagar todos los LEDs antes de la siguiente letra
        for (int j = 0; j < 6; j++) {
          digitalWrite(controlPins[j], LOW);
        }
        delay(500); // Pausa entre letras
      }
    }
  }
  
  // Verificar el estado del botón para chequear LEDs
  if (digitalRead(buttonPin) == LOW) {
    //activar los solenoides uno a uno
    //Serial.println("Estado de los solenoides:");
//    for (int i = 0; i < 6; i++) {
//      Serial.print("Solenoide ");
//      Serial.print(i + 1);
//      Serial.print(": ");
//      Serial.println(digitalRead(controlPins[i]) == HIGH ? "Activo" : "Inactivo");
//    }
//    delay(500); // Evitar lecturas múltiples en una sola pulsación
     for(int i=0; i<=5; i++){
      digitalWrite(controlPins[i],HIGH);
      delay(1000);
      digitalWrite(controlPins[i],LOW);
     }
  }
}
