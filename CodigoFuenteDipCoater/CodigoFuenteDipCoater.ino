//PROYECTO DIP COATER

const int pinOnOff = 2;
const int PinEnable = 9;
const int PinPasos = 13;
const int PinDireccion = 12;
int contador = 0;
int direccion = HIGH;
int ndireccion = LOW;
int auxdireccion;
unsigned long velocidad=40000; //10 segundos
unsigned long distancia=4150;    
void setup() {
  pinMode(pinOnOff,INPUT); 
  pinMode(PinEnable,OUTPUT); 
  pinMode(PinPasos,OUTPUT); 
  pinMode(PinDireccion,OUTPUT);
  digitalWrite(PinDireccion,LOW);
}
void loop(){
  if(digitalRead(pinOnOff)==HIGH){
    digitalWrite(PinEnable,LOW);
    contador++;
    digitalWrite(PinPasos, HIGH);  
    delayMicroseconds(velocidad);
    digitalWrite(PinPasos, LOW);
    delayMicroseconds(velocidad*2);
    if(contador > distancia){
      digitalWrite(PinDireccion,direccion);
      auxdireccion = direccion;
      direccion = ndireccion;
      ndireccion = auxdireccion;
      contador=0;
    }
  }
  else{
    //digitalWrite(PinDireccion,LOW);
    digitalWrite(PinEnable,HIGH);
  }
}

