/*
  PubNub sample client

  This sample client will use just the minimal-footprint raw PubNub
  interface where it is your responsibility to deal with the JSON encoding.

  It will just send a hello world message and retrieve one back, reporting
  its deeds on serial console.

  Circuit:
  * (Optional.) LED for reception indication.
  * (Optional.) LED for publish indication.

  created 23 October 2012
  by Petr Baudis

  https://github.com/pubnub/pubnub-api/tree/master/arduino
  This code is in the public domain.
  */

#include <SPI.h>
#include <WiFi.h>
#include <PubNub.h>

const int subLedPin = GREEN_LED;
const int pubLedPin = YELLOW_LED;
const int pubLedPin1 = RED_LED;
char count;

char pubkey[] = "pub-c-f5c67fc9-fdcf-412c-bd91-8c7db8b9de55";
char subkey[] = "sub-c-5b88d540-d6e3-11e5-8256-0619f8945a4f";
char channel[] = "hello_world";

// your network name also called SSID
char ssid[] = "ThanhLe";
// your network password
char password[] = "250508th@nh";

void setup()
{
        count = 0;
	pinMode(subLedPin, OUTPUT);
	pinMode(pubLedPin, OUTPUT);
        pinMode(pubLedPin1, OUTPUT);
	digitalWrite(subLedPin, LOW);
	digitalWrite(pubLedPin, LOW);
        digitalWrite(pubLedPin1, LOW);

	Serial.begin(115200);
	Serial.println("Serial set up");

	// attempt to connect to Wifi network:
	Serial.print("Attempting to connect to Network named: ");
	// print the network name (SSID);
	Serial.println(ssid); 
	// Connect to WPA/WPA2 network. Change this line if using open or WEP network:
	WiFi.begin(ssid, password);
	while ( WiFi.status() != WL_CONNECTED) {
		// print dots while we wait to connect
		Serial.print(".");
		delay(300);
	}

	Serial.println("\nYou're connected to the network");
	Serial.println("Waiting for an ip address");

	while (WiFi.localIP() == INADDR_NONE) {
		// print dots while we wait for an ip addresss
		Serial.print(".");
		delay(300);
	}

	Serial.println("\nIP Address obtained");
	// We are connected and have an IP address.
	// Print the WiFi status.
	printWifiStatus();

	PubNub.begin(pubkey, subkey);
	Serial.println("PubNub set up");
}

void flash(int ledPin)
{
	/* Flash LED three times. */
	for (int i = 0; i < 3; i++) {
		digitalWrite(ledPin, HIGH);
		delay(100);
		digitalWrite(ledPin, LOW);
		delay(100);
	}
}

void loop()
{
//	WiFiClient *client;
//
//	Serial.println("publishing a message");
//	client = PubNub.publish(channel, "\"\\\"Hello world!\\\" she said.\"");
//	if (!client) {
//		Serial.println("publishing error");
//		delay(1000);
//		return;
//	}
//	while (client->connected()) {
//		while (client->connected() && !client->available()) ; // wait
//		char c = client->read();
//		Serial.print(c);
//	}
//	client->stop();
//	Serial.println();
//	flash(pubLedPin);

//	Serial.println("waiting for a message (subscribe)");
	PubSubClient *pclient = PubNub.subscribe(channel);
	if (!pclient) {
		Serial.println("subscription error");
		delay(1000);
		return;
	}
	while (pclient->wait_for_data()) {
		char c = pclient->read();
                if(c == '1'){
                  Serial.print("Turn On Led");
                  digitalWrite(subLedPin, HIGH);
	          digitalWrite(pubLedPin, HIGH);
                  digitalWrite(pubLedPin1, HIGH);
                }
                if(c == '0'){
                  Serial.print("Turn Off Led");
                  digitalWrite(subLedPin, LOW);
	          digitalWrite(pubLedPin, LOW);
                  digitalWrite(pubLedPin1, LOW);
                }
	}
	pclient->stop();
	Serial.println();
//	flash(subLedPin);

//	Serial.println("retrieving message history");
//	client = PubNub.history(channel);
//	if (!client) {
//		Serial.println("history error");
//		delay(1000);
//		return;
//	}
//	while (client->connected()) {
//		while (client->connected() && !client->available()) ; // wait
//		char c = client->read();
//		Serial.print(c);
//	}
//	client->stop();
//	Serial.println();

	delay(100);
}

void printWifiStatus() {
	// print the SSID of the network you're attached to:
	Serial.print("SSID: ");
	Serial.println(WiFi.SSID());

	// print your WiFi IP address:
	IPAddress ip = WiFi.localIP();
	Serial.print("IP Address: ");
	Serial.println(ip);

	// print the received signal strength:
	long rssi = WiFi.RSSI();
	Serial.print("signal strength (RSSI):");
	Serial.print(rssi);
	Serial.println(" dBm");
}


