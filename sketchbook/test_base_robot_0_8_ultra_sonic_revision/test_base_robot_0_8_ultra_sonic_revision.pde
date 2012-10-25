//hier maak ik duidelijk welke namen ik geef aan pinnen, en aan variabelen.
int E2 = 6;
int M2 = 7;
int E1 = 5;
int M1 = 4;

int sensorValue ;
int sensorValue2 ;
int sensorValue3 ;
int pot1 = A5;
int sensorINFRA = A0;
int sensorLDR2 = A3;

#include "URMSerial.h"
//wat soor type meeting.
#define DISTANCE 1
URMSerial urm;

void setup()
//hier maak ik duidelijk wat de functie van de pinnen is die
//ik ga gebruiken, of ze een output of een input zijn.
//hier begin ik ook een verbinding met de computer, zo kan ik dan
//makkelijk foutjes op sporen in variabelen. en variabele parameters instellen.

{
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(pot1, INPUT);
  pinMode(sensorINFRA, INPUT);
  pinMode(sensorLDR2, INPUT);
  Serial.begin(9600);
  urm.begin(2,3,9600);
  
}

void loop()
{
  int getMeasurement(int mode)
  
  
  Serial.println(getMeasurement(DISTANCE));  // Output measurement
  delay(1000);
}

  switch(urm.requestMeasurementOrTimeout(mode, sensorValue2))
  
  {
  case DISTANCE: // Double check the reading we recieve is of DISTANCE type
    Serial.println(value); // Fetch the distance in centimeters from the URM37
    return value;
    break;

  }
  
  //lees variable van de pot.
  sensorValue = analogRead(pot1);
  //zet 0-1023 om in 0-255.
  sensorValue = map(sensorValue, 0, 1023, 0, 255);
  
  //lees sensor 2 en map deze naar 0-255
  sensorValue2 = DISTANCE;
  
  
  // lees sensor 3 en map deze naar 0-255
  //op dit moment is sensorLDR een variable weerstand om concept te testen.
  sensorValue3 = analogRead(sensorLDR2);
  sensorValue3 = map(sensorValue3, 1023, 0, 0, 255);
        
  
  //kijkt of de sensor in de buurt is van een object.
  if (sensorValue2 <= 180)
  {
  
        //het eerste wat gebeurt is een stukje terug rijden.
        digitalWrite(M1, LOW);
        //en met welke snelheid dit gebeurt.
        analogWrite(E1, sensorValue);
        //dan gebeurt dit voor x seconden lang.
        delay(1000);
        //daarna word de motor uit gezet.
        digitalWrite(M1, LOW);
        analogWrite(E1, 0);
        delay(100);
        //vervolgens worden de wielen bij gedraaid, volgens de
        //waarneming van sensorLDR2
       
        if (sensorValue3 < 112 )
        {
          //hier word naar links gestuurt als de linker sensor
         //minder licht opvangt
          digitalWrite(M2, HIGH);
          analogWrite(E2, 255);
          
          delay(100);
          // een kleine tik voor het tandwiel probleem.
          digitalWrite(M2, LOW);
          analogWrite(E2, 0);
          // en terug na tik.
          delay(100);
          
          digitalWrite(M2, HIGH);
          analogWrite(E2, 255);
          //de motor aan anders heeft het geen zin he.
          digitalWrite(M1, HIGH);
          analogWrite(E1, 200);
          delay(1000);
        }
         
          else if(sensorValue3 > 132)
        {
          //naar rechts gestuurd, als de linker sensor minder
         // belicht is.
          digitalWrite(M2, LOW);
          analogWrite(E2, 255);
          
          delay(100);
          // een kleine tik voor het tandwiel probleem.
          digitalWrite(M2, HIGH);
          analogWrite(E2, 0);
          // en terug na tik.
          delay(100);
          
          digitalWrite(M2, LOW);
          analogWrite(E2, 255);
          
          //ook hier moet de motor draaien, anderS heeft het geen zin he.
          digitalWrite(M1, HIGH);
          analogWrite(E1, 200);
          delay(1000);
        }
        
        
  }
   
   //vervolgens het stuur recht zetten en door rijden.
    else if (sensorValue2 >= 180
    )
    {
      //zet het stuur mechanisme uit, anders blijft het constant aan blijkbaar :S
      digitalWrite(M2, HIGH);  
      //signaal word uitgezet. dat word weer gegeven met een 0.
      analogWrite(E2, 0);
       
       //laat de motor gewoon door draaien als er geen obstakel is gevonden.
       digitalWrite(M1,HIGH);
       analogWrite(E1, sensorValue);
      
    }   
     
}
