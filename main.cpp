#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "Your Wifi SSID";
const char *password = "Your Wifi Password";
String serverPath = "https://example.com/door-status"; // <-- replace with your server or server ip

const int relayPin = D5; // does not fire up on startup, other than no specific reason to use d5
const int ledBuiltIn = LED_BUILTIN;
HTTPClient http;
WiFiClientSecure client;

void setup()
{
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    pinMode(relayPin, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);

    while (WiFi.status() != WL_CONNECTED)
    {
        digitalWrite(ledBuiltIn, LOW);
        delay(1000);
        digitalWrite(ledBuiltIn, HIGH);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi");
    digitalWrite(ledBuiltIn, LOW);
}

void loop()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        client.setInsecure();
        client.connect(serverPath.c_str(), 443);

        http.begin(client, serverPath.c_str());
        int httpResponseCode = http.GET();
        Serial.println(httpResponseCode);

        if (httpResponseCode > 0)
        {
            if (http.getString() == "CLOSED")
            {
                // NOOP
            }
            else
            {
                digitalWrite(relayPin, HIGH);
                delay(1000);
                digitalWrite(relayPin, LOW);
            }
        }
        http.end();
    }
    delay(3000);
}
