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

int Cont,DeltaD,Soma,distancia;


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
   DeltaD = sonar.ping_cm();
   Soma += DeltaD;
   Cont++;

   if(Cont>=20){//Calculo media
      distancia = Soma/Cont;
      
      Soma = 0;
      Cont = 0;
     }
  
    if (distancia == 0){  
        pixels.clear();
        pixels.show();  //Exibe comando 
     }else{ 
        pixels.clear();         
        PiscaLed(0,0,5);
       }

  Serial.println(distancia);    
  delay(10);
}

void PiscaLed(int r, int g, int b){
  
  for (int i = 0; i <= distancia-1; i++){
        if ( i == distancia-1) pixels.setPixelColor(i, pixels.Color(50,50,50));

        else              pixels.setPixelColor(i, pixels.Color(r,g,b));
    
       pixels.show();//Exibe leds

  }
   
}
