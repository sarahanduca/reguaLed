// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>
#include <Adafruit_NeoPixel.h>


#define PIN       23 //pino de dados led
#define NUMPIXELS 25 //quantidade de leds

#define TRIGGER_PIN  26  
#define ECHO_PIN     27  
#define MAX_DISTANCE 25 

int Count,DistanciaSonar,DeltaD,Distancia;


NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() 
{
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.

  pixels.begin();//Inicia comunicaçao comled
  pixels.clear(); // manda apagar leds
  pixels.show();  //Exibe comando 

}

void loop(){
  //Serial.println(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
   DistanciaSonar = sonar.ping_cm();
   DeltaD += DistanciaSonar;
   Count++;

   if(Count>=50){//Calculo media
      Distancia = DeltaD/Count;
      
      DeltaD = 0;
      Count = 0;
     }
  
    if (Distancia == 0){  
        pixels.clear();
        pixels.show();  //Exibe comando 
     } else PiscaLed();
    

  Serial.println(Distancia);    
  //delay(5);
}

void PiscaLed(){
  pixels.clear();  
  for (int i = 0; i <= Distancia-1; i++){
        if ( i == Distancia-1) pixels.setPixelColor(i, pixels.Color(255,255,255));

        else              pixels.setPixelColor(i, pixels.Color(0,0,255));
    
       pixels.show();//Exibe leds

  }
   
}