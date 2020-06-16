//Deze code verklaart zichzelf volgens mij. Alle lampen af en doorsturen naar de web. 

void allOff() {
  for (int m = 0; m < 3; m++) {
    setAndSendLamp(mainRoadTrafficLight[m], LOW, mainTrafficPubs[m]);
    setAndSendLamp(crossRoadTrafficLight[m], LOW, crossTrafficPubs[m]);
    setAndSendLamp(walkTrafficLight[m != 2], LOW, walkTrafficPubs[m != 2]);
  }
}
