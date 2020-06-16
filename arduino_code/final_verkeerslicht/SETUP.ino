//Outputs: de lichten. 
//Inputs: bewegingssensor (motionPin), voetgangersknop (pedestrianpin) en lichtsensor (lightPin). 
//Test of de wifi connecteert. 
//Dan de client opzetten. Ondermeer op juiste adres (in mijn geval de IP van m'n VM). 

void setup() {
  for (int x = 0; x < 3; x++) {
    pinMode(mainRoadTrafficLight[x], OUTPUT);
    pinMode(crossRoadTrafficLight[x], OUTPUT);
    pinMode(walkTrafficLight[x != 2], OUTPUT);
  }
  allOff();
  
  pinMode(lightPin, INPUT);
  pinMode(pedestrianPin, INPUT);
  pinMode(motionPin,INPUT); 

  //broker settings
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    delay(5000);
  }
  pubSubClient.setClient(client);
  pubSubClient.setServer("192.168.0.192", 1883);
  pubSubClient.setCallback(callBackFunction);
}
