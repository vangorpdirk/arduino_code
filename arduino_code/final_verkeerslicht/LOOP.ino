
void loop() {
  //Hier lees ik de waarde in voor het licht. Donker is in mijn bureau rond de 600. Licht zit iets boven de 950. Alles ertussen is om verschillen op te vangen.
  //De toestand verandert alleen als het of donker is, of helemaal licht. Daar kan uiteraard mee geschoven worden.(De opname is overigens overdag gemaakt bij vrij hoge
  //lichtintensiteit. 's Avonds kreeg ik meteen andere waarden.)
  lightState = analogRead(lightPin);
  if (lightState <= 600) afterDark = true;
  if (lightState >= 950) afterDark = false;
  Serial.println(lightState);

  //Beweging werkt bijna op dezelfde manier, maar de waarde is een beetje anders. En ik moet hier ook de lighState opnieuw meenemen, anders zou hij ook naar
  //een andere stand kunnen gaan.
  motionState = analogRead(motionPin);
  if (motionState <= 700 && lightState > 600) motionDetection = true;

  //Deze code is om de waarde van de voetgangersknop bij te houden. Druk je daarop, dan verandert de state en krijgt de voetganger dus voorrang. Hetzelfde geldt overigens voor de
  //web-melding. Daarover meer uitleg in de callback-methode.
  buttonState = digitalRead(pedestrianPin);
  if (buttonState == HIGH) pedestrianState = true;

  //Hier volgt iets langere code. Ik heb vier toestanden met if's geprogrammeerd. De timer is gebruikt om geen delays te moeten hebben. Bij een delay stopt het programma en kan
  //je geen andere inputs meer registereren. Op deze manier is dat probleem er niet.
  //  1.  Wanneer pedestrianCounter oneven is, dan krijgt een voetganger voorrang. Dat gebeurt met de drukknop, via een bewegingssensor of via de voetgangersmelding op het web.
  //      (later meer)
  //  2.  Wanneer het donker wordt, gaan de lichten in knipperstand.
  //  3.  Alarmfase = knipperende oranje lichten. Dit kan je alleen via de web bedienen. Een alarm mag niet automatisch uitgezet worden
  //      en dus kan niet aansluiten bij donker/licht. Overigens heb ik hier eens met een counter gewerkt ipv een boolean.
  //  4.  Tenslotte in elk ander geval, werken de verkeerslichten in normale stand. Wanneer er geen voetgangers zijn, blijft het rood voor hen.
  if (pedestrianState == true || motionDetection == true) {
    if (millis() - previousMillis <= trafficIntervals[j]) {
      trafficCombination(j);
    }
    else {
      previousMillis  = millis();
      if (j < 5) {
        j++;
        tone(buzzer, 150);
      }
      else {
        j = 4;
        pedestrianState = false;
        motionDetection = false;
        noTone(buzzer);
      }
    }
  }
  else if (afterDark == true) {
    if (millis() - previousMillis >= trafficIntervals[3]) {
      previousMillis = millis();
      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }
      allOff();
      setAndSendLamp(orangeLeds[0], ledState, "MySensor/orange");
      setAndSendLamp(orangeLeds[1], ledState, "MySensor/mainorange");
    }
  }
  else if (alarmCounter % 2 != 0) {
    if (millis() - previousMillis >= trafficIntervals[1]) {
      previousMillis = millis();
      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }
      allOff();
      setAndSendLamp(orangeLeds[0], ledState, "MySensor/orange");
      setAndSendLamp(orangeLeds[1], ledState, "MySensor/mainorange");
    }
  } else {
    if (millis() - previousMillis <= trafficIntervals[i]) {
      trafficCombination(i);
    }
    else {
      previousMillis = millis();
      if (i < 3) {
        i++;
      }
      else {
        i = 0;
      }
    }
  }

  //Voor de alarmfase en de voetgangersmelding moet ik ook nog subscriben op twee kanalen.
  if (!pubSubClient.connected()) {
    if (!pubSubClient.connect("dirk")) {
      Serial.print("connection to MQTT failed\n");
    }
    pubSubClient.subscribe("MySensor/flashing");
    pubSubClient.subscribe("MySensor/pedestrian");
  }

  pubSubClient.loop();
}
