// This #include statement was automatically added by the Particle IDE.
#include <google-maps-device-locator.h>

int reed = 2;
int vibe = 3;
int once = 0;
int readreed;
bool activate = false;
int vibes(String msg);
int text(String msg);
int activation(String msg);
double latitude = 0;
double longitude = 0;
double acc = 0;
String name = "";
GoogleMapsDeviceLocator locator;

void setup() 
{
   pinMode(reed, INPUT_PULLUP); 
   pinMode(vibe, OUTPUT);
   Particle.function("Vibes", vibes);
   Particle.variable("Activate", activate);
   Particle.variable("Latitude", latitude);
   Particle.variable("Longitude", longitude);
   Particle.variable("Accuracy", acc);
   Particle.variable("Reed Switch", readreed);
   Particle.function("Text", text);
   Particle.function("Activation", activation);
   // Scan for visible networks and publish to the cloud
  // Pass the returned location to be handled by the locationCallback() method
}

void loop() 
{
    locator.loop();
    readreed = digitalRead(reed);
    if(activate)
    {
        
        if (readreed == LOW && once == 0) //the magnet is on the switch
         {
             locator.withSubscribe(locationCallback).publishLocation();
             Particle.publish("Help");
             once = 1;
         }
         if (readreed == HIGH)
         {
             once = 0;
         }
    }
}

int vibes(String msg)
{
    if(activate)
    {
        if(msg == "1")
        {
            for(int i = 0; i < 3; i++)
            {
                digitalWrite(vibe, HIGH);
                delay(750);
                digitalWrite(vibe,LOW);
                delay(500);
                Particle.publish("Vibe");
            }
            
        }
    }
    
}

int text(String msg)
{
    if(activate)
    {
        locator.withSubscribe(locationCallback).publishLocation();
        Particle.publish("Help");
    }
}

int activation(String msg)
{
    if(msg == "1")
    {
        activate = true;
        return 1;
    }
    
    if(msg == "0")
    {
        activate = false;
        return 0;
    }
    return -1;
}


void locationCallback(float lat, float lon, float accuracy) {
  latitude = lat;
  longitude = lon;
  acc = accuracy;
}


