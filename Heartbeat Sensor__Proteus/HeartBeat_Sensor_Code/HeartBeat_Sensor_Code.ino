#include<LiquidCrystal.h>
#include<SoftwareSerial.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
SoftwareSerial mySerial(10,11);
// Variables
const int PulseWire = A0; // PulseSensor PURPLE WIRE connected to ANALOG PIN 0


void setup() {
 
Serial.begin(9600); // For Serial Monitor
 mySerial.begin(9600);
lcd.begin(16,2);
   lcd.print("HeartBeat Monitoring ");
  lcd.setCursor(0,2);
  lcd.print("System");
  delay(500);
 
}

 
void loop()
{
  
  int val = analogRead(PulseWire); 
  if(val > 0)
  {
    heartb();
  }
  else
  {
    lcd.clear();
    lcd.print("Sensor not  ");
    lcd.setCursor(0,2);
    lcd.print("connected");
    delay(10);
  }
}


void heartb()
{
  int  count = 0;
  int  time1  = 0;
  int reading  = 0;
  while (1)
  {
             reading = analogRead(PulseWire);
             if (reading>0)
             {
                     lcd.clear();
                    lcd.print("High Pulse");
                      delay(10);
                        count=count+1;
             }
             else
             {
                      lcd.clear();
                    lcd.print("Low Pulse");

                      delay(10);
                  
             }
             delay(600);
             time1=time1+600;
             
             if (time1>10000)
             {
                 count=15*count;
                 break;
             }
  }
     
        lcd.clear();
        lcd.print("Heart Rate");
         lcd.setCursor(0,2);
        lcd.print(count);
        delay(1000);
        if((count > 100 ) || (count  < 40 ))
        {
          SendMessage();
        }
           count=0;
        time1=0;
  }

void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(500);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+917995287103\"\r"); //7995287103 Replace x with mobile number
  delay(500);
  mySerial.println("Emeregency Condition");// The SMS text you want to send
  delay(500);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(500);
}
