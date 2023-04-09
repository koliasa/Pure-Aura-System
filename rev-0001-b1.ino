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
