Ik heb gekozen voor een conflictvrij, slim verkeerslicht. Dat wil zeggen wanneer er voetgangers komen, springt het licht vanzelf op groen voor de voetgangers en zullen er geen auto's mogen rijden. Anders blijft het licht werken en zal het rood blijven voor de voetgangers. Ik heb een effectief kruispunt nagebootst door een verkeerslicht van de hoofdbaan te nemen en dan één van de kruisbaan. Het voetgangerslicht is een aparte set lichtjes. 

OUTPUT: 
	1. LEDS: De verkeerslichten zijn outputs. Alles ingesteld op de juiste pins, in dit geval in arrays. 
	2. BUZZER: Is in dit geval ook een output. Wanneer een voetganger groen krijgt, gaat ook de buzzer. 

INPUT: 
	1. Bewegingssensor: Eigenlijk een lichtmeter die dienst doet als bewegingssensor. 
	2. Lichtsensor: Deze doet dan weer dienst als lichtmeter. 's Nachts knipperen enkel de oranje lichten. 
	3. Drukknop: Voetgangers kunnen die induwen. 

WEERSTANDEN: 
	1. 220 Ohm: Alle leds en de piezo buzzer. Van die laatste ken ik de precieze waarden niet, maar de leds geeft 3,3V - 2V / 0.007A = 185 	Ohm. 
	2. 10 kOhm: Voor de twee lichtmeters. Op deze manier kan je de analoge waarden goed uitlezen.  

WEB: 
	U zal het in het filmpje zien, maar de web-applicatie geeft de actuele standen van het verkeerslicht. En er zijn ook twee inputmogelijkheden. 
	1. Alarm: De operator kan de lichten in alarm zetten. Dan knipperen de oranje lichten. 
	2. Voetganger: Stel de operator wil het voetgangerslicht eens testen, of later wil je op dit kanaal een slimme camera aansluiten.