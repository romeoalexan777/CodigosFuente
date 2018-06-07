/* Pin VCC  Arduino  ---- Pin VCC módulo HC-05
 * Pin 10 Arduino  ---- Pin TXD módulo HC-05
 * Pin 11 Arduino  ---- Pin RXD módulo HC-05
 * Pin GND Arduino ---- Pin GND modulo HC-05
 */
#include <SoftwareSerial.h>         // Librería SoftwareSerial para habilitar un segundo puerto serie vía software
SoftwareSerial SerialBT(10,11);     // Definición de pines RX y TX del Arduino conectados al Bluetooth
void setup(){
  pinMode(8, OUTPUT);    // Alimenta el módulo HC-05
  Serial.begin(9600);    // Inicializar  el puerto serie hardaware conectado al pc (Monitor serial)
  digitalWrite (8, HIGH);//Enciende el módulo HC-05
  Serial.println("Esperando comandos AT:");
  SerialBT.begin(9600);  // Inicializar el puerto serie software conectado al módulo Bluetooth HC-05 (Para Modo AT 2, encender con el boton presionado)
}
void loop(){
  if(SerialBT.available()){         // Si llega un dato desde el puerto serie software (Bluetooth HC-05) se envía a la computadora (monitor serial) 
    Serial.write(SerialBT.read());
  }
  if(Serial.available()){           // Si llega un dato desde la computadora(monitor serial) se envía al puerto serie software (Bluetooth HC-05)
    SerialBT.write(Serial.read());
  }
}

