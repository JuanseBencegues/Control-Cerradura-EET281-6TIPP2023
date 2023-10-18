/*
 
Programa: Control de Acceso a Puertas con RC522
Autor:  Humberto Higinio
Facebook: https://www.facebook.com/humberto.higinio
Instagram: https://www.instagram.com/humberto.higinio/
Twitter: https://twitter.com/hhiginio
Canal de Youtube: https://www.youtube.com/user/HHSolis
Video Exclusivo para mi canal de Youtube
Todos los Derechos Reservados - 2019
Código de Dominio Público

 * 
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */


#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
#define RELAY 6 // Pin del Relay
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Crea la instancia MFRC522

 
void setup() 
{
  Serial.begin(9600);   // Inicializa la comunicacion serial
  SPI.begin();          // Inicializa el bus SPI
  mfrc522.PCD_Init();   // Inicializa el MFRC522
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);
  Serial.println("Ponga su Tarjeta para la lectura...");
  Serial.println();

}
void loop() 
{
  // Mirando para nuevas tarjeras
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Selecciona una de las tarjetas
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  // Muestra el UID sobre el Monitor Serial
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "50 AC DC A4") //Cambie aqui el UID de las tarjetas que usted desea dar acceso
  {
    Serial.println("Acceso Autorizado");
  digitalWrite(RELAY, HIGH);
  delay(3000);
  digitalWrite(RELAY,LOW);
  }
  else if  (content.substring(1) == "26 A7 EF F7")
  {
    Serial.println("Acceso Autorizado");
  digitalWrite(RELAY, HIGH);
  delay(3000);
  digitalWrite(RELAY,LOW);
  }
}
