//Deze code kijkt of er een bericht komt via de kanalen waarop ingeschreven is. Of dus webbuttons. Ik heb twee buttons.
//  1.  Alarmfase: Is al eerder verduidelijkt. In geval van bijvoorbeeld een ongeval kan de operator de lichten vanop afstand laten knipperen. 
//  2.  Voetgangersmelding: Wanneer de operator bijvoorbeeld via de camera iemand ziet staan, kan hij voorrang geven aan die persoon. Later
//      zou ik die button bijvoorbeeld kunnen vervangen in een camera. Dus als die mensen registreert, gaat het 'WALK'-licht in voorrang. 

void callBackFunction(char* topic, byte * payload, unsigned int p_length) {
  if (payload[0] == '1') alarmCounter++;
  if (payload[0] == '0') pedestrianState = true;
}
