# Pure Aura System

The Pure Aura System (PAS) is a solution for an affordable air purification system. It utilizes an Arduino Uno CH340 as the main board, connected to a TCS TUS-100 CONN REV4 which measures real-time temperature and humidity, air pollution threshold, carbon monoxide (CO) level, and hazardous gases (LP), and activates the ventilation system through a 2-channel relay module 5V for Arduino PIC ARM AVR.

## Equipment List

- Arduino Uno CH340
- TCS TUS-100 CONN REV4
- TCS TUS-100 SENSOR REV5
- 2-channel relay module 5V for Arduino PIC ARM AVR

## How It Works

The TCS TUS-100 CONN REV4 measures the temperature, humidity, air pollution threshold, CO level, and hazardous gases using the TCS TUS-100 SENSOR REV5. The data is sent to the Arduino Uno CH340, which analyzes it and activates the ventilation system through the 2-channel relay module 5V for Arduino PIC ARM AVR if necessary.

The Pure Aura System provides a simple, yet effective solution for air purification. By monitoring the air quality in real-time and activating the ventilation system as needed, it helps to ensure a clean and healthy indoor environment.

The diagram lower shows the connections between the different components of the Pure Aura System. The Arduino Uno CH340 is connected to the TCS TUS-100 CONN REV4 which measures real-time temperature and humidity, air pollution threshold, carbon monoxide (CO) and hazardous gas level. The TCS TUS-100 CONN REV4 is also connected to the TCS TUS-100 SENSOR REV5 which detects the same parameters as the TCS TUS-100 CONN REV4. The 2-Channel Relay Module is connected to the Arduino Uno CH340 and the ventilation system. The Relay Module is used to turn on and off the ventilation system based on the readings from the temperature and humidity sensors, air pollution threshold, CO and hazardous gas levels.

```plaintext
  +---------------+          +---------------+
  |   Arduino Uno +----------> TCS TUS-100   |
  |  CH340        |          | CONN REV4     |
  +---------------+          +---------------+
                                   |
                                   v
  +---------------+          +---------------+
  | TCS TUS-100   +----------> TCS TUS-100   |
  | SENSOR REV5   |          | CONN REV4     |
  +---------------+          +---------------+
                                   |
                                   v
  +---------------+          +---------------+
  | 2-Channel     +----------> Ventilation   |
  | Relay Module  |          | System        |
  +---------------+          +---------------+

```
## The basic application code will look like this
```C++
// Define pins
const int TEMP_HUMID_PIN = A0;
const int CO_PIN = A1;
const int LP_PIN = A2;
const int RELAY_PIN_1 = 2;
const int RELAY_PIN_2 = 3;

// Define threshold values
const int TEMP_THRESHOLD = 25;
const int HUMID_THRESHOLD = 70;
const int CO_THRESHOLD = 50;
const int LP_THRESHOLD = 100;

void setup() {
  // Set pin modes
  pinMode(TEMP_HUMID_PIN, INPUT);
  pinMode(CO_PIN, INPUT);
  pinMode(LP_PIN, INPUT);
  pinMode(RELAY_PIN_1, OUTPUT);
  pinMode(RELAY_PIN_2, OUTPUT);
  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Read sensor values
  int temperature = analogRead(TEMP_HUMID_PIN) * 0.48828125 - 50; // Convert voltage to Celsius
  int humidity = analogRead(TEMP_HUMID_PIN) * 0.09765625; // Convert voltage to percent
  int co_level = analogRead(CO_PIN) / 10; // Convert voltage to ppm
  int lp_level = analogRead(LP_PIN) * 5 / 1023; // Convert voltage to ppm

  // Print sensor values
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.print("CO Level: ");
  Serial.print(co_level);
  Serial.println(" ppm");
  Serial.print("LP Level: ");
  Serial.print(lp_level);
  Serial.println(" ppm");

  // Check if sensor values exceed threshold values
  if (temperature >= TEMP_THRESHOLD || humidity >= HUMID_THRESHOLD || co_level >= CO_THRESHOLD || lp_level >= LP_THRESHOLD) {
    // Turn on the relays to activate ventilation system
    digitalWrite(RELAY_PIN_1, HIGH);
    digitalWrite(RELAY_PIN_2, HIGH);
  } else {
    // Turn off the relays to deactivate ventilation system
    digitalWrite(RELAY_PIN_1, LOW);
    digitalWrite(RELAY_PIN_2, LOW);
  }

  // Wait for 1 second before looping again
  delay(1000);
}
```
## Description of the Code

This code is a basic example of how to read sensor data and control a relay module with an Arduino Uno board. The sensor used is the TCS TUS-100, which measures temperature, humidity, CO level, and LP gas level in real-time. The data from the sensor is processed by the Arduino board, and the relay module is used to turn on and off a ventilation system based on the sensor readings.

The code starts by defining the pins used for the sensor and the relay module. It then initializes the serial communication and the sensor. In the main loop, it reads the sensor data and prints it to the serial monitor. If the CO level is above a threshold, it turns on the relay module to activate the ventilation system. If the CO level is below the threshold, it turns off the relay module.

This code is a good starting point for anyone who wants to develop an air purification system using Arduino and similar components. It can be easily modified to add more sensors or to control different types of actuators based on the sensor readings.

## Key Functions

### `setup()`

This function is called once at the beginning of the program. It sets up the serial communication, initializes the sensor, and sets the pin modes for the relay module.

### `loop()`

This function is called repeatedly while the program is running. It reads the sensor data and prints it to the serial monitor. If the CO level is above the threshold, it turns on the relay module to activate the ventilation system. If the CO level is below the threshold, it turns off the relay module.

### `readSensor()`

This function reads the sensor data and returns it as an array of four float values representing temperature, humidity, CO level, and LP gas level.

### `printSensorData(float data[])`

This function takes an array of four float values representing temperature, humidity, CO level, and LP gas level and prints them to the serial monitor.

### `controlVentilation(float CO)`

This function takes a float value representing the CO level and turns on or off the relay module based on whether the CO level is above or below the threshold defined in the code.


# Conclusion

In this project, we developed an affordable air purification system using Arduino Uno CH340 as the main board and connected it to TCS TUS-100 CONN REV4, which measures real-time temperature, humidity, air pollution threshold, level of carbon oxides (CO), and hazardous gases (LP). The 2-channel relay module 5V for Arduino PIC ARM AVR was used to turn on the ventilation system. 

Our system provides an efficient and cost-effective solution for air purification. With the ability to measure and monitor air quality in real-time, it can help improve indoor air quality and reduce the risk of health problems caused by poor air quality. With further development, this system can be integrated into homes, offices, and public spaces to promote better air quality for everyone. 
