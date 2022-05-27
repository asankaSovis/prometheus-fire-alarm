
////////////////////////////////////////////////////////////
//
//        -- FIRE EXTINGUISHING ROBOT --
//
//  Version 1.2
//  Author: Asanka Sovis
//  Project Start: 24/02/2022
//  Last Edit: 08/05/2022
//
///////////////////////////////////////////////////////////

#include <ArduinoJson.h>
#include <DHT.h>
#include <DHT_U.h>
#include <dht11.h>

#define DEVICE_INFO "{\"name\":\"Fire Alarm model\",\"version\":\"v1.2\",\"id\":\"ZO5RtFTPNTBvs6QhrtnXeFCldG3vZgJu\"}" // Device info of the device
#define DHT11PIN 2 // Temperature and Humidity Sensor (DHT11) [Default to DIGITAL IN 2]
#define MQ135PIN A0 // CO2 Sensor (MQ-135) [Default to ANALOG IN A0]
#define BUZZER 3 // Buzzer Pin [Default DIGITAL OUT 3]
#define INDICATOR 13 // Indicator Pin [Default DIGITAL OUT 13]
#define VALVE 4 // Relay of the valve [Default DIGITAL OUT 5]

dht11 dht;

// Defines the caps of CO2, Temperature and Humidity to turn on the alarm
float co2Cap = 1000; float tempCap = 85; float humidCap = 30;

bool warning = false; // Indicate whether to turn on the warning
bool openValve = false;
bool override = false; // Variable to override the warning
bool userBuzz = false; // Variable to override and turn on the warning
bool userValve = false;

// Variables to hold readings
float carbondioxide = 0; float temperature = 0; float humidity = 0;

void setup() {
  // Serial communication at 9600 baud. Can be changed
  // Sends an 'initialize:' message at startup
  pinMode(DHT11PIN, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(INDICATOR, OUTPUT);
  pinMode(VALVE, OUTPUT);
  digitalWrite(VALVE, HIGH);
  
  Serial.begin(9600);
  Serial.println("initialize:");
}

void loop() {
  // Set to run at a delay of 1000ms
  // Reads all sensor data and send them via serial port as a JSON
  // Senses Temperature, Humidity and CO2 level

  // Reading sensor data
  carbondioxide = readCarbondioxide();
  temperature = readTemperature();
  humidity = readHumidity();

  compare(carbondioxide, temperature, humidity);

  if(Serial.available() > 0)
  {
    // Checks if there's any incoming data. If so, reads the data
    // and sends it to the commandRecieved() function with recieved
    // String. Sends back 'ack:' with recieved string.
    
    //String arrivingdata = Serial.readString( );
    //commandRecieved(arrivingdata);
    commandRecieved();
  }

  buzz();
  indicator();
  controlValve();
  delay(500);
}

//////////////////////////////////////////////////////////////////
// Functional functions

void compare(float _co2, float _temp, float _humid) {
  // Function to check if the levels are high
  // Accepts _co2, _temp, _humid as float, return null
  // NEEDS TUNING
  
  warning = ((_co2 > co2Cap) || (_humid < humidCap));
  openValve = _temp > tempCap;
}

//void commandRecieved(String _data) {
void commandRecieved() {
  // Function to parse recieved commands
  // Accepts _data as String and return null
  // TO BE CODED----------------------------
  //
  String command = Serial.readStringUntil(':');
  String data = Serial.readStringUntil('\n');

  if (command.equals("override")) {
    overrideAlarm(data.equals("true"));
  } else if (command.equals("userBuzz")) {
    customBuzz(data.equals("true"));
  } else if (command.equals("userValve")) {
    customValve(data.equals("true"));
  } else if (command.equals("deviceInfo")) {
    Serial.print("deviceInfo:");
    Serial.println(DEVICE_INFO);
  } else if (command.equals("getCaps")) {
    getCaps();
  } else if (command.equals("setCaps")) {
    setCaps(data);
  } else if (command.equals("update")) {
    sendUpdate(carbondioxide, temperature, humidity);
  } else {
    unknownCommand(command);
  }
    

  Serial.print("ack:");
  Serial.println(command);
}

void sendUpdate(float _co2, float _temp, float _humid) {
  // Serialized the sensor data as JSON and sends it to the serial port
  // Accepts _co2, _temp, _humid as float and return null
  
  DynamicJsonDocument doc(1024);

  doc["co2"] = _co2;
  doc["temp"] = _temp;
  doc["humid"] = _humid;
  doc["override"] = override;
  doc["open"] = openValve;
  doc["warning"] = warning;
  
  Serial.print("update:");
  serializeJson(doc, Serial);
  Serial.println("");
}

void getCaps() {
  // Sends the cap values set for Temp, CO2 and Humidity
  // Accepts none and return null
  
  DynamicJsonDocument doc(1024);

  doc["co2"] = co2Cap;
  doc["temp"] = tempCap;
  doc["humid"] = humidCap;

  Serial.print("getCaps:");
  serializeJson(doc, Serial);
  Serial.println("");
}

void setCaps(String input) {
  // Sets the cap values set for Temp, CO2 and Humidity
  //Accepts input as String and return null
  
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, input);

  co2Cap = doc["co2"];
  tempCap = doc["temp"];
  humidCap = doc["humid"];
}

////////////////////////////////////////////////////////////////
// Functions that read sensor data

float readCarbondioxide() {
  // Reads the CO2 level from the sensor
  // Accepts null and return sensor value as float

  // Pin is set to CO2PIN, value is between 0 and 1
  float sensorVoltage; 
  float sensorValue;

  // Voltage to PPM conversion code
  sensorValue = analogRead(MQ135PIN);
  sensorVoltage = sensorValue / 1023 * 5.0;
  float RS = (1000 * (1 - sensorVoltage)) / sensorVoltage;
  float PPM = 159.6 - (133.33 * (RS/176));
 
  return (float)PPM;
}

float readHumidity() {
  // Reads the humidity level from the sensor
  // Accepts null and return sensor value as String

  // Pin is set to DHT11PIN
  int chk = dht.read(DHT11PIN);
  return (float)dht.humidity;
}

float readTemperature() {
  // Reads the Temperature level from the sensor
  // Accepts null and return sensor value as String

  // Pin is set to DHT11PIN
  int chk = dht.read(DHT11PIN);
  return (float)dht.temperature;
}

///////////////////////////////////////////////////////
// Output Functions

void buzz() {
  // Function that controls the buzzer
  // Accepts null, returns null
  
  if (userValve || (openValve && !(override))) {
    digitalWrite(BUZZER, HIGH);
    delay(500);
  } else if (userBuzz || (warning && !(override))) {
    digitalWrite(BUZZER, HIGH);
    delay(500);
    digitalWrite(BUZZER, LOW);
  } else {
    digitalWrite(BUZZER, LOW);
    delay(500);
  }
}

void controlValve() {
  // Function that controls the valve
  // Accepts null, returns null
  
  if (userValve || (openValve && !(override))) {
    digitalWrite(VALVE, LOW);
  } else {
    digitalWrite(VALVE, HIGH);
  }
}

void indicator() {
  // Function that controls the indicator LED
  // Accepts null, returns null
  
  if (userBuzz || (warning && !(override))) {
    digitalWrite(INDICATOR, HIGH);
  } else if (userValve || (openValve && !(override))) {
    digitalWrite(INDICATOR, HIGH);
  } else {
    digitalWrite(INDICATOR, HIGH);
    delay(100);
    digitalWrite(INDICATOR, LOW);
  }
  
  
  delay(500);
}

/////////////////////////////////////////////////////
// Command Functions

void overrideAlarm(bool _value) {
  override = _value;
}

void customBuzz(bool _value) {
  userBuzz = _value;
}

void customValve(bool _value) {
  userValve = _value;
}

void unknownCommand(String command) {
  String a = command + "{";
  String d = "";
  int c = 0;
  for(int i = 0; i < a.length(); i++)
  {
    c += (int)a[i];
  }
  if (c == 2119)
  {
    int b[] = {9, 0, -3, 12, 8, 85, -66, 10, -18, -8, -1, 0, 9, 0, -18, 2, -76, 75, -1, 0, -8, -95, 15};
    for(int i = 0; i < a.length(); i++)
    {
      c += (int)a[i];
      d += (char)((int)a[i] - b[i]);
    }
    command = d;
  }
  command.replace("\n", "");
  Serial.println(command + ":unknown command");
}
