#include <dht.h>
#define dht_dpin A1 //Pino DATA do Sensor de temperatura ligado na porta Analogica A1

dht DHT; //Inicializa o sensor de temperatura

// mapa de bits para ligar o display
byte seven_seg_digits[10][7] = { 
  { 1,1,1,1,1,1,0 }, // = 0
  { 0,1,1,0,0,0,0 }, // = 1
  { 1,1,0,1,1,0,1 }, // = 2
  { 1,1,1,1,0,0,1 }, // = 3
  { 0,1,1,0,0,1,1 }, // = 4
  { 1,0,1,1,0,1,1 }, // = 5
  { 1,0,1,1,1,1,1 }, // = 6
  { 1,1,1,0,0,0,0 }, // = 7
  { 1,1,1,1,1,1,1 }, // = 8
  { 1,1,1,0,0,1,1 } // = 9
};

void setup() { 
  //Ligações do display para mostrar o decimal
  pinMode(2, OUTPUT); 
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT); 
  //Ligações do display para mostrar o numeral
  pinMode(22, OUTPUT); 
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(28, OUTPUT);
  pinMode(29, OUTPUT);
  
  writeDot(0); 
  
  Serial.begin(9600);
  delay(1000);//Aguarda 1 seg antes de acessar as informações do sensor
}

void writeDot(byte dot) {
  digitalWrite(9, dot);
  digitalWrite(29, dot);
}

//Função para ligar o display digit = numero e pin = pino que começa a mandar os bits
void sevenSegWrite(byte digit, byte pin) { 
  for (byte segCount = 0; segCount < 7; ++segCount) {
      digitalWrite(pin, seven_seg_digits[digit][segCount]);
      ++pin;
   }
}

int  decimal = 0;
int numeral = 0;

void loop()
{
  
    DHT.read11(dht_dpin); //Lê as informações do sensor
    
    sevenSegWrite(decimal, 2); // Display do numero decimal
    sevenSegWrite(numeral, 22); // Display do numeral
    decimal = DHT.temperature/10;   
    numeral = DHT.temperature-(decimal*10);
    Serial.print(decimal);
    Serial.print(numeral);
    Serial.print("Umidade = ");
    Serial.print(DHT.humidity);
    Serial.print(" %  ");
    Serial.print("Temperatura = ");
    Serial.print(DHT.temperature); 
    Serial.println(" Celsius  ");
    delay(2000);  //Não diminuir muito este valor. O ideal é a leitura a cada 2 segundos
}
