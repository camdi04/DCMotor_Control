#include <BluetoothSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <ThingSpeak.h>
#define MOTOR_PIN1  12
#define MOTOR_PIN2  13
#define LED1_PIN  5
#define LED2_PIN  18
#define LED3_PIN  19

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
unsigned long myChannekNumber = 2128168;
const char * myWriteApiKey = "YBLC0YVKE8UHVZLS";

//empresa HORUS SMART CONTROL 
const char* ssid = "MCA-ITACA";            //Enter SSID
const char* password = "Itaca#900418160";  //Enter Password
WiFiClient client;
int E=0;

// Definición de pines LCD
LiquidCrystal_I2C lcd(0x27, 16,2);
// Variables de tiempo
unsigned int lastRequestTime = 0;
const unsigned int requestInterval = 100; // Intervalo de tiempo para recibir peticiones en milisegundos
BluetoothSerial SerialBT;
void setup() { 
  // Configurar los pines como salida
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);

  // Configurar la pantalla LCD
  lcd.begin();    
  lcd.backlight();

   // Todos los LEDs apagados al inicio
  digitalWrite(MOTOR_PIN1, LOW);
  digitalWrite(MOTOR_PIN2, LOW);
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(LED3_PIN, LOW);
  WiFi.begin(ssid,password);
  
  Serial.begin(115200);
  SerialBT.begin("ESP32"); //Bluetooth device name
  Serial.println("now you can pair it with bluetooth!");// CONEXION ESTABLECIDA
  lcd.print(" !Hola A Todos!");
  lcd.setCursor(0,1);
  lcd.print("Control De Motor");
  ThingSpeak.begin(client);
}
// CONFIGURACION--------
//---------------------------------------------------------------------------------
//------------------------------------------------------------------------------------


//LCD----------------------- SE IMPRIME
void loop() {
  if (Serial.available()) {
    lastRequestTime = millis(); // Actualizar el tiempo de la última petición
    char cmd = Serial.read();
    readpakeg(cmd);
  }
  //--------------------------------------------------------------------------------
//BLUETOOTH-----------------------
// Todo se muestra en el monitor serie
  if (SerialBT.available()) {
    lastRequestTime = millis(); // Actualizar el tiempo de la última petición
    char cmd = SerialBT.read();
    readpakeg(cmd);
  }
  
  if(E==3){
    if (Serial.available()) {
    lastRequestTime = millis(); // Actualizar el tiempo de la última petición
    char cmd = Serial.read();
    readpakeg(cmd);
    }else RL();
  
  }
}
String readpakeg(char code){
  switch (code){
      case '0': // Detenido
        E=0;
        NLR();   
        lcd.clear();
        lcd.print("Detenido");
        envio_de_datos(1,E);
        break;
        
      case '1': // Gira a la derecha
        E=1;
        R();
        lcd.clear();
        lcd.print("Girando a la");
        lcd.setCursor(0, 1);
        lcd.print("derecha");
        envio_de_datos(1,E);
        break;

        case '2': // Gira a la izquierda
        E=2;
        L();
        lcd.clear();
        lcd.print("Girando a la");
        lcd.setCursor(0, 1);
        lcd.print("izquierda");
        envio_de_datos(1,E);
        break;

        case '3': // Gira a ambos sentidos
        lcd.clear();
        lcd.print("Ambos Sentidos");
        E=3;
        envio_de_datos(1,E);
        break;
    }
}

//LO QUE EJECUTA EL ESP32

void NLR(){
  Serial.println("Detenido");
  digitalWrite(LED1_PIN, LOW);
        digitalWrite(LED2_PIN, LOW);
        digitalWrite(LED3_PIN, LOW);
        digitalWrite(MOTOR_PIN2, LOW);
        digitalWrite(MOTOR_PIN1, LOW);     
}

void R(){
  digitalWrite(LED1_PIN, HIGH);
        digitalWrite(LED2_PIN, LOW);
        digitalWrite(LED3_PIN, LOW);
        digitalWrite(MOTOR_PIN2, LOW);
        digitalWrite(MOTOR_PIN1, LOW); 
        delay(1000);
        Serial.println("derecha");
        digitalWrite(MOTOR_PIN1, HIGH);
}

void L(){
  digitalWrite(LED1_PIN, LOW);
        digitalWrite(LED2_PIN, HIGH);
        digitalWrite(LED3_PIN, LOW);
        digitalWrite(MOTOR_PIN2, LOW);
        digitalWrite(MOTOR_PIN1, LOW); 
        delay(1000);
        Serial.println("izquierda");
        digitalWrite(MOTOR_PIN2, HIGH);
}

void RL(){
  Serial.println("Ambos Sentidos");
  digitalWrite(LED1_PIN, LOW);
        digitalWrite(LED2_PIN, LOW);
        digitalWrite(LED3_PIN, HIGH);
        digitalWrite(MOTOR_PIN1, LOW);
        digitalWrite(MOTOR_PIN2, LOW); 
        delay(1000);
        digitalWrite(MOTOR_PIN1, HIGH);
        Serial.println("derecha");
        lcd.setCursor(0, 1);
        lcd.print("derecha         ");
        delay(5000);
        
        digitalWrite(MOTOR_PIN1, LOW);
        delay(1000);
        digitalWrite(MOTOR_PIN2, HIGH);
        Serial.println("izquierda");
        lcd.setCursor(0, 1);
        lcd.print("izquierda");
        delay(5000);
}

String envio_de_datos(int a,int e){
  int x = ThingSpeak.writeField(myChannekNumber,a,e,myWriteApiKey);
   if(x == 200){
      lcd.print("channel update successful");
    }else{
      lcd.print("http error code: "+ String(x));
    }
    String z= String(x);
    return z;
  }
