*/PROYECTO SPIN COATING
Conexiones de pines: --------------------------------------------------------------------
  Control velocidad******
      1 Arduino pin A0 <-> Potenciometro1 10K-control pin central
        2 Arduino pin 5V <-> Potenciometro1 10K-energia pin izquierdo
        3 Arduino pin GND <> Potenciometro1 10K-energia pin derecho
  Sensor velocidad*******
      1 Arduino pin 2 <--> Sensor-control cable amarillo    
        2 Arduino pin 5V <-> Sensor-energia cable rojo 
        3 Arduino pin GND <> Sensor-energia cable negro 
  LCD********************
      1 Arduino pin 3 <--> LCD-control pin Enable (E)
        2 Arduino pin 4 <--> LCD-control pin Register Select (RS) 
        3 Arduino pin 5 <--> LCD-datos pin DB4 
        4 Arduino pin 6 <--> LCD-datos pin DB5 
        5 Arduino pin 7 <--> LCD-datos pin DB6 
        6 Arduino pin 8 <--> LCD-datos pin DB7
        7 Arduino pin GND <> LCD-control pin read/write (RW)
        8 Arduino pin GND <> LCD-energy pin GND
        9 Arduino pin 5V <-> LCD-energy pin VCC 
        10Arduino pin 5V <-> LCD-energy pin anodo (A) 
        11Arduino pin GND <> LCD-energy pin catodo (K) 
        12LCD-control pin V0 <----> Potenciometro2 10K-control pin central
        13Arduino pin 5V <-> Potenciometro2 10K-energia pin izquierdo
        14Arduino pin GND <> Potenciometro2 10K-energia pin derecho
  ESC********************
      1 Arduino pin 10 <-> ESC-control cable blanco
        2 Arduino pin 5V <-> ESC-energia cable rojo 
        3 Arduino pin GND <> ESC-energia cable negro 
        4 ESC energia <----> Fuente 12v VCC
        5 ESC energia <----> Fuente 12v GND
        6 ESC control 1<---> Motor cable naranja
        7 ESC control 2<---> Motor cable blanco
        8 ESC control 3<---> Motor cable morado
 */

#include <LiquidCrystal.h>
#include <Servo.h>

volatile int cuentarotacion=0;
const int controlveloz=A0;
const int sensorveloz=2;
const int lcdE=3;
const int lcdRS=4;
const int lcdDB4=5;
const int lcdDB5=6;
const int lcdDB6=7;
const int lcdDB7=8;
LiquidCrystal LCD(lcdRS, lcdE, lcdDB4, lcdDB5, lcdDB6, lcdDB7);
Servo ESC;
const int motor=10;
int velocidad=0;

void setup(){                                   //Inicia la función de configuración (Ejecuta una vez)
  attachInterrupt(0,rotaciones,FALLING);
  ESC.attach(motor);                            //Establece el pin 10 del Arduino como señal de control para el ESC del motor
  armarEsc();                                   //Armar el ESC para que esté listo a recibir órdenes para girar el motor
  LCD.begin(16, 2);
  LCD.setCursor(0, 0);
  LCD.print("NANOLAB: Spin C.");
  LCD.setCursor(0, 1);
  LCD.print("RPM:    ");
}                                               //Finaliza la función de configuración

void loop(){                                    //Inicia la función repetitiva (Ejecuta infinitas veces)
 
  velocidad = analogRead(controlveloz);         //Leer el valor del potenciómetro
  velocidad = map(velocidad,0,1023,1100,2000);  //cambiando el valor del potenciómetro según la proporcionalidad de valores aceptados por la libreria servo

  
  ESC.writeMicroseconds(velocidad);             //Cambiar la velocidad del motor de acuerdo al valor del potenciómetro
  
  delay (999);
  LCD.setCursor(4, 1);
  LCD.print(cuentarotacion*30);
  LCD.print("    ");
  LCD.setCursor(9, 1);
  LCD.print("V:");
  LCD.print(velocidad-1100);
  LCD.print("   ");
  cuentarotacion=0;

}                                               //Finaliza la función repetitiva

void armarEsc(){                                //Inicia la función del armado del ESC
  ESC.writeMicroseconds(1000);                  //Establecer el ESC en 1000 para dar la señal de pulso de amplitud mínima y armar el controlador ESC
  delay(5000);                                  //Esperar 100 milisegundos
}                                               //Finaliza la función del armado del ESC

void rotaciones(){
  cuentarotacion++;
}
