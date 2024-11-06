#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "includes.h"

AsyncWebServer server(80);

void printMessagePrc(const char *msg);
void printMessageHl7(const char *msg);
void printMessageOther(const char *msg);
void printAllHl7();
void printAllPrc();
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
      if (messageBlock.equals("P01"))
      {
        printMessagePrc(MSG01);
      }
      else if (messageBlock.equals("P02"))
      {
        printMessagePrc(MSG02);
      }
      else if (messageBlock.equals("P03"))
      {
        printMessagePrc(MSG03);
      }
      else if (messageBlock.equals("P04"))
      {
        printMessagePrc(MSG04);
      }
      else if (messageBlock.equals("P05"))
      {
        printMessagePrc(MSG05);
      }
      else if (messageBlock.equals("P06"))
      {
        printMessagePrc(MSG06);
      }
      else if (messageBlock.equals("P07"))
      {
        printMessagePrc(MSG07);
      }
      else if (messageBlock.equals("P08"))
      {
        printMessagePrc(MSG08);
      }
      else if (messageBlock.equals("PALL"))
      {
        printAllPrc();
      }
      else if (messageBlock.equals("H01"))
      {
        printMessageHl7(MSG09);
      }
      else if (messageBlock.equals("H02"))
      {
        printMessageHl7(MSG10);
      }
      else if (messageBlock.equals("HALL"))
      {
        printAllHl7();
      }     
      else if (messageBlock.equals("O01"))
      {
        printMessageOther(MSG11);
      }
      else if (messageBlock.equals("O02"))
      {
        printMessageOther(MSG12);
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

void printMessagePrc(const char *msg)
{

  Serial.write(msg);
  Serial.write(CARRIAGE_RETURN);
  Serial.write(LINE_FEED);
}

void printMessageOther(const char *msg)
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

void printAllPrc()
{
  for (int i = 0; i < sizeof(PRC) / sizeof(PRC[0]); i++)
  {
    strcpy_P(charBuf, PRC[i]);
    printMessagePrc(charBuf);
  }
}

void printAllOther()
{
  for (int i = 0; i < sizeof(OTHER) / sizeof(OTHER[0]); i++)
  {
    strcpy_P(charBuf, OTHER[i]);
    printMessageOther(charBuf);
  }
}
