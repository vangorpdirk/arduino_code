//Deze twee methodes regelen de standen van de verschillende lichten. 
//  1.  Trafficcombination: dit zijn al de verschillende standen. Van 0 tem 3 zijn de standen voor de twee verkeerslichten. 
//      Case 4 en 5 zijn de standen voor het voetgangerslicht.
//  2.  TrafficRoutine: De routine heb ik nodig om de juiste lichten aan te zetten door de array te doorlopen. Gegevens worden 
//      ook meteen doorgestuurd naar de web.         

void trafficCombination(int combination) {
  switch (combination) {
    case 0:
      trafficRoutine(0, 2, 0);
      break;
    case 1:
      trafficRoutine(0, 1, 0);
      break;
    case 2:
      trafficRoutine(2, 0, 0);
      break;
    case 3:
      trafficRoutine(1, 0, 0);
      break;
    case 4:
      trafficRoutine(1, 1, 0);
      break;
    case 5:
      trafficRoutine(0, 0, 1);
      break;
  }
}

void trafficRoutine(int mainLight, int crossLight, int walkLight) {
  for (int k = 0; k < 3; k++) {
    if (k == mainLight)
      setAndSendLamp(mainRoadTrafficLight[k], HIGH, mainTrafficPubs[k]);
    else
      setAndSendLamp(mainRoadTrafficLight[k], LOW, mainTrafficPubs[k]);
  }
  for (int l = 0; l < 3; l++) {
    if (l == crossLight)
      setAndSendLamp(crossRoadTrafficLight[l], HIGH, crossTrafficPubs[l]);
    else
      setAndSendLamp(crossRoadTrafficLight[l], LOW, crossTrafficPubs[l]);
  }
  for (int m = 0; m < 2; m++) {
    if (m == walkLight)
      setAndSendLamp(walkTrafficLight[m], HIGH, walkTrafficPubs[m]);
    else
      setAndSendLamp(walkTrafficLight[m], LOW, walkTrafficPubs[m]);
  }
}
