#include <WiFi101.h>
#include <PubSubClient.h>

//WIFI SETTINGS
char ssid[] = "Netwerk van vango";
char pass[] = "XXXXXXXXX";
WiFiClient client;
PubSubClient pubSubClient;

//Dit zijn de publicatiekanalen om informatie door te sturen naar de broker.
//Het bericht zal ingeladen worden in website. Volgorde zoals bij lichten: red = [0], orange = [1], green = [2]
char mainTrafficPubs[3][20] = {"MySensor/mainred", "MySensor/mainorange", "MySensor/maingreen"};
char crossTrafficPubs[3][20] = {"MySensor/red", "MySensor/orange", "MySensor/green"};
char walkTrafficPubs[3][20] = {"MySensor/walkred", "MySensor/walkgreen"};

//LedAsString: Ik heb ook nog een variabele nodig voor het wegschrijven naar de broker.
//Concreet wordt er een string voor het publicatiekanaal opgeladen in de char-array.
char ledAsString[20] = "";

//trafficLeds: Om het makkelijk te houden heb ik arrays in volgorde geprogrammeerd. red = [0], orange = [1], green = [2]
//De oranje lichten zitten ook in een aparte array, omdat ze ook in alarmfase moeten kunnen gaan. Dit zou ook anders kunnen.
const int mainRoadTrafficLight[] = {9, 10, 11};
const int crossRoadTrafficLight[] = {8, 7, 6};
const int orangeLeds[] = {7, 10};

//WALK: het voorrangslicht voor voetgangers is enkel rood en groen.
const int walkTrafficLight[] = {12, 13};

//Intervallen: Ik maak gebruik van verschillende intervallen. Ook weer in bepaalde volgorde, afhankelijk van de routine.
//Een gewone routine gaat van array 0 tot en met 2. De laatste twee arraywaarden zijn voor wanneer een voetganger over wil.
//Alles in millis. 
const long trafficIntervals[] = {4000, 1000, 4000, 1000, 3000, 5000};

//Timersettings: Deze variabelen worden alleen gebruikt voor de verandering van de verkeerslichten. Zo moet ik niet met een delay werken,
//maar kan ik alles van in het begin laten lopen.
//i voor het gewone verkeerslicht, j voor de intervals met de voetgangers.
int i = 0;
int j = 4;
unsigned long previousMillis = 0;

//buttonPress: De knop op het breadbord doet dienst als voetgangersknop. Denk aan een knop zoals aan de paal van een verkeerslicht voor voetgangers.
//Wanneer een voetganger op die knop duwt, zal hij voorrang krijgen en gaan de andere lichten op rood. De knop wordt overigens niet alleen aangestuurd
//via de fysieke button, maar ook via web. De state dient om het aantal drukken bij te houden. Da's handig voor de programmatie van het licht (zie verder).
int buttonState = 0;
int ledState = LOW;
const int pedestrianPin = A3;
int pedestrianState = false;

//lightmeter: Als het donker wordt dan zal het licht flikkeren. Daarvoor lees ik de waarde van de lightPin (lichtmeter) in.
//Ik wil natuurlijk niet bij elke loop een nieuwe waarde opnemen, dus tot ik de toestand (lightstate) zelf wijzig, zal het blijven flikkeren.
//Vandaar de state.
const int lightPin = A1;
int lightState = 0;
bool afterDark = false;

//Lightmeter 2: Eigenlijk een bewegingssensor. Wanneer er iemand voorbij komt en het dus even 'duister' wordt, dan verandert de motionDetection naar true;
const int motionPin = A2;
int motionState = 0;
bool motionDetection = false;

//buzzer: Wanneer een voetganger groen krijgt, gaat dat gepaard met de buzzer. 
const int buzzer = A0;

//alarmFase --> je kan het licht vanop afstand bedienen. Stel er is een ongeval gebeurd of er moet zwaar vervoer door, dan kan je alles in alarmstand zetten. 
//Knipperende oranje lichten. 
int alarmCounter = 0;
