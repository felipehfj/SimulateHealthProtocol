#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "includes.h"

AsyncWebServer server(80);

void printMessageHl7(const char *msg);
void printSingleLineMessage(const char *msg);
void printAllHl7();
void printAllVetChroma();
void printAllICheck();
void printAllUridoctor();
void printAllOther();

char charBuf[768];

void setup()
{
  WiFi.begin(ssid, password);
  Serial.begin(115200);
  

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    if(request->hasParam("messages")) {
      AsyncWebParameter* p = request->getParam("messages");
      String messageBlock = p->value();
      messageBlock.trim();
      messageBlock.replace("?messages=", "");


      /// VetChroma 
      if (messageBlock.equals("P01"))
      {
        printSingleLineMessage(MSG01);
      }
      else if (messageBlock.equals("P02"))
      {
        printSingleLineMessage(MSG02);
      }
      else if (messageBlock.equals("P03"))
      {
        printSingleLineMessage(MSG03);
      }
      else if (messageBlock.equals("P04"))
      {
        printSingleLineMessage(MSG04);
      }
      else if (messageBlock.equals("P05"))
      {
        printSingleLineMessage(MSG05);
      }
      else if (messageBlock.equals("P06"))
      {
        printSingleLineMessage(MSG06);
      }
      else if (messageBlock.equals("P07"))
      {
        printSingleLineMessage(MSG07);
      }
      else if (messageBlock.equals("P08"))
      {
        printSingleLineMessage(MSG08);
      }
      else if (messageBlock.equals("PALL"))
      {
        printAllVetChroma();
      }

      // HL7
      else if (messageBlock.equals("HVG1"))
      {
        printMessageHl7(MSGVG1);
      }
      else if (messageBlock.equals("H01"))
      {
        printMessageHl7(MSG09);
      }
      else if (messageBlock.equals("H02"))
      {
        printMessageHl7(MSG10);
      }
      else if (messageBlock.equals("H03"))
      {
        printMessageHl7(MMMXX);
      }
      else if (messageBlock.equals("HALL"))
      {
        printAllHl7();
      }

      // ICheck
      else if (messageBlock.equals("I01"))
      {
        printSingleLineMessage(MSG15);
      }
      else if (messageBlock.equals("I02"))
      {
        printSingleLineMessage(MSG16);
      }
      else if (messageBlock.equals("I03"))
      {
        printSingleLineMessage(MSG17);
      }
      else if (messageBlock.equals("IALL"))
      {
        printAllICheck();
      }

      // Uridoctor
      else if (messageBlock.equals("U01"))
      {
        printSingleLineMessage(MSG13);
      }
      else if (messageBlock.equals("U02"))
      {
        printSingleLineMessage(MSG14);
      }
      else if (messageBlock.equals("UALL"))
      {
        printAllUridoctor();
      }      
     
      // Other
      else if (messageBlock.equals("O01"))
      {
        printSingleLineMessage(MSG11);
      }
      else if (messageBlock.equals("O02"))
      {
        printSingleLineMessage(MSG12);
      }
      else if (messageBlock.equals("OALL"))
      {
        printAllOther();
      }
    }
    request->send_P(200, "text/html", html);    
  }); 


  server.begin();
}

void loop()
{
 
}

void printSingleLineMessage(const char *msg)
{
  Serial.write(msg);
  Serial.write(CARRIAGE_RETURN);
  Serial.write(LINE_FEED);
}

void printMessageHl7(const char *msg)
{
  Serial.write(START_OF_BLOCK);
  Serial.write(msg);
  Serial.write(END_OF_BLOCK);
  Serial.write(CARRIAGE_RETURN);
  Serial.write(LINE_FEED);
}

void printAllHl7()
{

  for (int i = 0; i < sizeof(HL7) / sizeof(HL7[0]); i++)
  {
    strcpy_P(charBuf, HL7[i]);
    printMessageHl7(charBuf);
  }
}

void printAllVetChroma()
{
  for (int i = 0; i < sizeof(VETCHROMA) / sizeof(VETCHROMA[0]); i++)
  {
    strcpy_P(charBuf, VETCHROMA[i]);
    printSingleLineMessage(charBuf);
  }
}
void printAllICheck()
{
  for (int i = 0; i < sizeof(ICHECKRALL) / sizeof(ICHECKRALL[0]); i++)
  {
    strcpy_P(charBuf, ICHECKRALL[i]);
    printSingleLineMessage(charBuf);
  }
}
void printAllUridoctor()
{
  for (int i = 0; i < sizeof(URIDOCTORALL) / sizeof(URIDOCTORALL[0]); i++)
  {
    strcpy_P(charBuf, URIDOCTORALL[i]);
    printSingleLineMessage(charBuf);
  }
}

void printAllOther()
{
  for (int i = 0; i < sizeof(OTHER) / sizeof(OTHER[0]); i++)
  {
    strcpy_P(charBuf, OTHER[i]);
    printSingleLineMessage(charBuf);
  }
}
