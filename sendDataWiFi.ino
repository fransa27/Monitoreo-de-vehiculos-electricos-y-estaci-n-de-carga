#include <SoftwareSerial.h>
#define RX 2
#define TX 3

String AP = "movistar2,4GHZ_9BC4FE";       // AP NAME
String PASS = "TUiL5MMjCinm"; // AP PASSWORD
String API = "2MDS0Q7YP9XWJWFR";   // Write API KEY
String HOST = "api.thingspeak.com";
String PORT = "80";
String field1 = "field4";
String fieldTemperature = "field6";
String fieldVoltage = "field5";

float charge[]= {
  2.04, 4.41, 11.76, 6.88, 8.496, 11.9, 20.56, 10.77, 10.823, 10.68, 5.42, 8.79, 7.14, 3.52,
  14.85, 5.06, 7.35, 1.937, 2.24, 1.29, 4.93, 5.11
};

float dcVoltage[]= { 1.1,
0.0000,
0.0000,
0.0000,
3.7149,
5.3500,
5.8000,
5.8428,
5.4375,
0.0000,
4.3857,
5.8571,
2.4500,
5.6125,
3.7000,
4.1857,
5.0166,
3.7375,
3.8875,
5.2625,
3.8625,
5.4625,
5.4625,
5.7000,
3.4875,
2.7800,
3.1057,
3.1862,
3.1625,
3.1142,
6.1125,
1.8616,
1.8653,
1.8771,
1.8957,
1.8733,
};


/*float temperature[]={
  
};*/
int countTrueCommand;
int countTimeCommand; 
boolean found = false; 
float valSensor;
SoftwareSerial esp8266(RX,TX); 

void setup() {
  Serial.begin(115200);
  esp8266.begin(115200);
  sendCommand("AT",5,"OK");
  sendCommand("AT+CWMODE=1",5,"OK");
  sendCommand("AT+CWJAP=""+ AP +"",""+ PASS +""",20,"OK");
}

void loop() {
  /*int cantArrayCharrge = (sizeof(charge)/sizeof(charge[0]));
  for(int contador=0;contador<cantArrayCharrge;contador++){
  valSensor=charge[contador];
  String getData = "GET /update?api_key="+ API +"&"+ field1 +"="+String(valSensor);
  sendCommand("AT+CIPMUX=1",5,"OK");
  sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
  sendCommand("AT+CIPSEND=0," +String(getData.length()),4,">");
  esp8266.println(getData);delay(1500);countTrueCommand++;
  sendCommand("AT+CIPCLOSE=0",5,"OK");
  }*/
  int cantArrayVoltage = (sizeof(dcVoltage)/sizeof(dcVoltage[0]));
  for (int i=0;i<5138; i++){
    valSensor=dcVoltage[i];
    esp8266.println(valSensor);
    String getData = "GET /update?api_key="+ API +"&"+ "field5" +"="+String(valSensor);
    sendCommand("AT+CIPMUX=1",5,"OK");
    sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
    sendCommand("AT+CIPSEND=0," +String(getData.length()),4,">");
    esp8266.println(getData);delay(1500);countTrueCommand++;
    sendCommand("AT+CIPCLOSE=0",5,"OK");
    delay(10000);
  };

  /*int cantArrayTemperature = (sizeof(temperatureltage)/sizeof(temperaturege[0]));
  for (int j=0;j<cantArrayTemperature; j++){
    valSensor=charge[j];
    String getData = "GET /update?api_key="+ API +"&"+ fieldTemperature +"="+String(valSensor);
    sendCommand("AT+CIPMUX=1",5,"OK");
    sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
    sendCommand("AT+CIPSEND=0," +String(getData.length()),4,">");
    esp8266.println(getData);delay(1500);countTrueCommand++;
    sendCommand("AT+CIPCLOSE=0",5,"OK");
  };*/
  
}

void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    esp8266.println(command);//at+cipsend
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
    }

    countTimeCommand++;
  }

  if(found == true)
  {
    Serial.println("OYI");
    countTrueCommand++;
    countTimeCommand = 0;
  }

  if(found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }

  found = false;
 }
