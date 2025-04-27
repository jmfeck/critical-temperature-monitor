// -------------------------------------------------------------------------------
// Critical Temperature Monitor
// University Project (2015/2016) - Proof of Concept
// Arduino Mega 2560 + Ethernet Shield + LCD Display
// -------------------------------------------------------------------------------

#include <SPI.h>
#include <Ethernet.h>
#include <LiquidCrystal.h>

// LCD pin configuration (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(33, 35, 37, 39, 41, 43);

// Button and LED pin definitions
const int ButtonPlus = 22;   // Button to increase the critical temperature
const int ButtonLess = 24;   // Button to decrease the critical temperature
const int ButtonOk = 26;     // Button to activate monitoring
const int LEDOk = 48;        // LED indicating monitoring active
const int LEDAlert = 46;     // LED indicating critical temperature alert

// Button states
int ButtonPlusState = 0;
int ButtonLessState = 0;
int ButtonOkState = LOW;
int ButtonOkPreviousState = LOW;
int ButtonOkReading;

// Debounce control
long LastDebounceTime = 0;
long DebounceDelay = 200;

// Ethernet settings
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "api.pushingbox.com";  // PushingBox API server
IPAddress ip(150, 162, 10, 109);       // Static IP fallback
EthernetClient client;

// Variables
String data;            // Data to send via HTTP GET
float tempData;         // Current temperature reading
float tempSet = 30.0;   // User-set temperature threshold
boolean Alert = false;  // Temperature above threshold
boolean Connection = false;

// -------------------------------------------------------------------------------
void setup() {
  pinMode(ButtonOk, INPUT);
  pinMode(ButtonPlus, INPUT);
  pinMode(ButtonLess, INPUT);
  pinMode(LEDAlert, OUTPUT);
  pinMode(LEDOk, OUTPUT);
  
  analogReference(INTERNAL1V1);
  lcd.begin(16, 2);
  Serial.begin(9600);

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP. Using static IP...");
    Ethernet.begin(mac, ip);
  }

  delay(1000);
}

// -------------------------------------------------------------------------------
void loop() {
  int Temp_ADC = analogRead(0);      // Read analog value from pin A0
  tempData = Temp_ADC * 0.105;        // Convert ADC reading to Celsius

  lcd.setCursor(0, 0);
  lcd.print("SetTemp:");
  lcd.setCursor(9, 0);
  lcd.print(tempSet, 2);
  lcd.setCursor(15, 0);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.setCursor(7, 1);
  lcd.print(tempData, 2);
  lcd.setCursor(15, 1);
  lcd.print("C");

  ButtonOkReading = digitalRead(ButtonOk);

  if (ButtonOkReading == HIGH && ButtonOkPreviousState == LOW && millis() - LastDebounceTime > DebounceDelay) {
    ButtonOkState = !ButtonOkState;  // Toggle OK state
    LastDebounceTime = millis();
  }

  if (ButtonOkState == HIGH) {
    if (tempData > tempSet) {
      Alert = true;
      digitalWrite(LEDAlert, HIGH);
      prepareRequest();
      Serial.println("Connecting...");

      if (client.connect(server, 80)) {
        sendRequest();
        Connection = true;
      } else {
        Serial.println("Connection failed.");
      }

      while (Connection) {
        if (client.available()) {
          char c = client.read();
          Serial.print(c);
        }
        if (!client.connected()) {
          Serial.println();
          Serial.println("Disconnecting.");
          Serial.print("Temperature Sent: ");
          Serial.println(tempData);
          client.stop();
          Connection = false;
          data = "";
        }
      }

      delay(5000);  // Wait 5 seconds before next alert
    } else {
      digitalWrite(LEDAlert, LOW);
    }
  } else {
    // Allow adjusting the threshold if monitoring is not active
    ButtonPlusState = digitalRead(ButtonPlus);
    ButtonLessState = digitalRead(ButtonLess);

    if (ButtonPlusState == HIGH) {
      if (tempSet < 99 && tempSet > -99) {
        tempSet += 0.25;
      }
      delay(200);
    }

    if (ButtonLessState == HIGH) {
      if (tempSet < 99 && tempSet > -99) {
        tempSet -= 0.25;
      }
      delay(200);
    }
  }

  digitalWrite(LEDOk, ButtonOkState);
  ButtonOkPreviousState = ButtonOkReading;
}

// -------------------------------------------------------------------------------
void prepareRequest() {
  data = "";
  data += "GET /pushingbox?devid=YOUR_DEVICE_ID&tempData=";
  data += tempData;
  data += "&tempSet=";
  data += tempSet;
  data += "&Alert=";
  data += Alert;
  data += " HTTP/1.1";
}

// -------------------------------------------------------------------------------
void sendRequest() {
  Serial.println("Connected");
  client.println(data);
  client.println("Host: api.pushingbox.com");
  client.println("Connection: close");
  client.println();
}