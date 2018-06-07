/*CONEXION DE PINES
 * Pin 8  Arduino  ---- Pin VCC modulo HC-05
 * Pin 9  Arduino  ---- Pin KEY modulo HC-05
 * Pin 10 Arduino  ---- Pin TXD modulo HC-05
 * Pin 11 Arduino  ---- Pin RXD modulo HC-05
 * Pin GND Arduino ---- Pin GND modulo HC-05
 * COMANDOS AT
 * AT         ; Este comando sirve para comprobar la comunicación el modulo responderá OK
 * AT+NAME    ; El módulo responderá con su nombre
 * AT+PIN     ; El módulo responderá con su pin o clave 
 * AT+VERSION ; El módulo responderá con información de su versión
 * AT+BAUD    ; El módulo responderá con la velocidad de comunicación expresada en un número del 1 al 7 según las velocidades disponibles
 * AT+ROLE    ; El módulo responderá con su rol que puede ser 0=Esclavo o 1=Maestro
 * AT+NAMENuevoNombre ; Cambia el nombre del módulo a NuevoNombre
 * AT+PIN9510         ; Cambia el pin o clave del módulo a 9510
 * AT+ROLE1           ; Cambia el rol a esclavo
 * AT+ROLE0           ; Cambia el rol a maestro
 * AT+BAUD8           ; Cambia la velocidad de comunicación a 115200bps
 * VELOCIDADES DISPONIBLES PARA EL COMANDO AT+BAUD#
 *  #                  velocidad
 *  1 configura        1200bps
 *  2 configura        2400bps
 *  3 configura        4800bps
 *  4 configura        9600bps (Default)
 *  5 configura        19200bps
 *  6 configura        38400bps
 *  7 configura        57600bps
 *  8 configura        115200bps*/
#include <SoftwareSerial.h>         // Librería SoftwareSerial para habilitar un segundo puerto serie via software
SoftwareSerial SerialBT(10,11);     // Definición de pines RX y TX del Arduino conectados al Bluetooth
void setup(){
  pinMode(8, OUTPUT);    // Alimenta el módulo HC-05
  pinMode(9, OUTPUT);    // Envía señal HIGH para que el modulo entre en modo AT2 y pueda recibir comandos
  digitalWrite(9, HIGH); // Establecer señal HIGH antes de energizar el pin VCC del módulo HC-05
  delay (500) ;          // Pequeña pausa para garantizar el modo AT2
  Serial.begin(9600);    // Inicializar  el puerto serie hardware conectado al pc (Monitor serial)
  digitalWrite (8, HIGH);//Enciende el módulo HC-05
  Serial.println("Esperando comandos AT:");
  SerialBT.begin(57600);  // Inicializar el puerto serie software conectado al módulo Bluetooth HC-05 (Para Modo AT 2, encender con el boton presionado)
}
void loop(){
  if(SerialBT.available()){    // Si llega un dato desde el puerto serie software (Bluetooth HC-05) se envía a la computadora (monitor serial) 
    Serial.write(SerialBT.read());
  }
  if(Serial.available()){           // Si llega un dato desde la computadora(monitor serial) se envía al puerto serie software (Bluetooth HC-05)
    SerialBT.write(Serial.read());
  }
}

