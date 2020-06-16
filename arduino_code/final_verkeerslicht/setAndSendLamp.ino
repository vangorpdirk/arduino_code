//Deze methode doet zoals ze zegt, zet de doorgegeven led aan of uit en stuurt tegelijk een bericht naar de web. 
//Dit werkt voor elke lamp waardoor ik nog maar één methode nodig heb.  

void setAndSendLamp(int led, int input, char message[20]) {
  digitalWrite(led, input);
  sprintf(ledAsString, "%1d", digitalRead(led));
  if (pubSubClient.connected()) {
    if (!pubSubClient.publish(message, ledAsString)) {
      Serial.print("cannot publish value\n");
    }
  }
}
