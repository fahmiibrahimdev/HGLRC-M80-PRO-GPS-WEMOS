#include <SoftwareSerial.h>

int RXPin = D3;
int TXPin = D4;

int GPSBaud = 115200;
boolean newData = false;
float latitude, longitude;
int comma1, comma2, comma3, comma4, comma5, comma6;
String inputStringGPS, latitudeString, longitudeString;

SoftwareSerial gpsSerial(RXPin, TXPin);

void setup()
{
  Serial.begin(115200);
  gpsSerial.begin(GPSBaud);
}

void loop()
{
  while (gpsSerial.available()) 
  {
    char inputCharGPS = (char)gpsSerial.read();
    inputStringGPS += inputCharGPS;
    newData = true;
  }

  if (newData)
  {
    Serial.print("NMEA: ");
    Serial.println(inputStringGPS);
    comma1 = inputStringGPS.indexOf(",");
    comma2 = inputStringGPS.indexOf(",", comma1 + 1);
    comma3 = inputStringGPS.indexOf(",", comma2 + 1);
    comma4 = inputStringGPS.indexOf(",", comma3 + 1);
    comma5 = inputStringGPS.indexOf(",", comma4 + 1);
    comma6 = inputStringGPS.indexOf(",", comma5 + 1);
    
    latitudeString  = inputStringGPS.substring(comma2 + 1, comma3);
    longitudeString = inputStringGPS.substring(comma4 + 1, comma5);
    
    latitude = latitudeString.substring(0, 2).toFloat() + latitudeString.substring(2).toFloat() / 60.0;
    longitude = longitudeString.substring(0, 3).toFloat() + longitudeString.substring(3).toFloat() / 60.0;
    
    if (inputStringGPS.charAt(comma3 + 1) == 'S')
    {
      latitude *= -1.0;
    }

    if (inputStringGPS.charAt(comma6 + 1) == 'W')
    {
      longitude = -longitude;
    }
    
    Serial.print("Latitude: "); Serial.println(latitude, 6);
    Serial.print("Longitude: "); Serial.println(longitude, 6);
    Serial.print("Maps Link: http://maps.google.com/maps?q="); Serial.print(latitude, 6); Serial.print(","); Serial.print(longitude, 6); Serial.println("\n");
    inputStringGPS = "";
    newData = false;
  }

  delay(3000);
}
