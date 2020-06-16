/*Mijn adres van de vm. Overigens ziet de /etc/mosquitto/conf.d/custom.conf er als volgt uit: 
listener 1883

listener 8080
protocol websockets*/

const IP_ADDRESS = "192.168.0.192";
let client;

init();

function init() {
    client = new Paho.MQTT.Client(IP_ADDRESS, 8080, "web");
    client.onMessageArrived = onMessageArrived;
    client.onConnectionLost = onConnectionLost;
    client.connect({onSuccess: onConnect});
}

/*Hier schrijf ik me in op alle signalen van de arduino en ik zet het licht in de browser aan via de switchLight-methode.
Uitlezen kan via de message.destinationName.*/
function onMessageArrived(message) {
    switch(message.destinationName){
        case "MySensor/green":
        switchLight(message.payloadString,"green");
        break; 
        case "MySensor/orange":      
        switchLight(message.payloadString,"orange");
        break;
        case "MySensor/red":
        switchLight(message.payloadString,"red");
        break;
        case "MySensor/maingreen":
        switchOtherLight(message.payloadString,"green");
        break; 
        case "MySensor/mainorange":      
        switchOtherLight(message.payloadString,"orange");
        break;
        case "MySensor/mainred":
        switchOtherLight(message.payloadString,"red");
        break;
        case "MySensor/walkred":
        switchWalkLight(message.payloadString,"red");
        break;
        case "MySensor/walkgreen":
        switchWalkLight(message.payloadString,"green");
        break;
    }
}

function onConnect() {
    client.subscribe("MySensor/green");
    client.subscribe("MySensor/orange");
    client.subscribe("MySensor/red");
    client.subscribe("MySensor/maingreen");
    client.subscribe("MySensor/mainorange");    
    client.subscribe("MySensor/mainred");
    client.subscribe("MySensor/walkgreen"); 
    client.subscribe("MySensor/walkred");
}

function onConnectionLost(responseObject) {
    if (responseObject.errorCode !== 0) {
        alert("onConnectionLost:" + responseObject.errorMessage);
    }
}

/*Doorsturen van 1 als ik op Alarmfase duw. En ik stuur een 0 door als ik op Voetgangersmelding duw.*/
function flashOnOff() {
    message = new Paho.MQTT.Message("1");
    message.destinationName = "MySensor/flashing";
    client.send(message);
    console.log(message);
}

function pedestrian() {
    message = new Paho.MQTT.Message("0");
    message.destinationName = "MySensor/pedestrian";
    client.send(message);
    console.log(message);
}

function switchLight(number,light){
    if (number === "1") {
        document.getElementById(light).classList.add("get" + light);
    };
    if (number === "0") {
        document.getElementById(light).classList.remove("get"+light);
    };
}

function switchOtherLight(number,light){
    if (number === "1") {
        document.getElementById("main" + light).classList.add("get" + light);
    };
    if (number === "0") {
        document.getElementById("main"+light).classList.remove("get"+light);
    };
}

function switchWalkLight(number,light){
    if (number === "1") {
        document.getElementById("walk" + light).classList.add("get" + light);
    };
    if (number === "0") {
        document.getElementById("walk"+light).classList.remove("get"+light);
    };
}