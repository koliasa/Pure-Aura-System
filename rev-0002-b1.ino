// Define pin numbers for TCS TUS-100 sensor
const int TUS_100_CONN_RX = 10;
const int TUS_100_CONN_TX = 11;

// Define pin numbers for 2-channel relay module
const int RELAY_MODULE_CH1 = 2;
const int RELAY_MODULE_CH2 = 3;

// Define thresholds for air pollution, CO, LP, temperature, humidity, NH3, CO2, H2S, CH4, CO, NO, NO2, NOx, and SO2
int air_pollution_threshold = 200;
int co_threshold = 100;
int lp_threshold = 50;
int temperature_threshold = 25;
int humidity_threshold = 50;
int nh3_threshold = 100;
int co2_threshold = 500;
int h2s_threshold = 20;
int ch4_threshold = 100;
int no_threshold = 50;
int no2_threshold = 20;
int nox_threshold = 30;
int so2_threshold = 20;

// Define sensitivity factors for each parameter
float air_pollution_sensitivity = 1.0;
float co_sensitivity = 1.0;
float lp_sensitivity = 1.0;
float temperature_sensitivity = 1.0;
float humidity_sensitivity = 1.0;
float nh3_sensitivity = 1.0;
float co2_sensitivity = 1.0;
float h2s_sensitivity = 1.0;
float ch4_sensitivity = 1.0;
float no_sensitivity = 1.0;
float no2_sensitivity = 1.0;
float nox_sensitivity = 1.0;
float so2_sensitivity = 1.0;

void setup() {
  // Initialize serial communication for TCS TUS-100 sensor
  Serial.begin(9600);
  Serial1.begin(9600);
  
  // Initialize pin modes for relay module
  pinMode(RELAY_MODULE_CH1, OUTPUT);
  pinMode(RELAY_MODULE_CH2, OUTPUT);
  
  // Turn off relay module
  digitalWrite(RELAY_MODULE_CH1, LOW);
  digitalWrite(RELAY_MODULE_CH2, LOW);
}

void loop() {
  // Read data from TCS TUS-100 sensor
  if (Serial1.available() > 0) {
    String sensor_data = Serial1.readStringUntil('\n');
    Serial.println(sensor_data);
    
    // Extract sensor values from string and apply sensitivity factors
    int air_pollution = (int)(getValue(sensor_data, ',', 0) * air_pollution_sensitivity);
    int co = (int)(getValue(sensor_data, ',', 1) * co_sensitivity);
    int lp = (int)(getValue(sensor_data, ',', 2) * lp_sensitivity);
    int temperature = (int)(getValue(sensor_data, ',', 3) * temperature_sensitivity);
    int humidity = (int)(getValue(sensor_data, ',', 4) * humidity_sensitivity);
    int nh3 = (int)(getValue(sensor_data, ',', 5) * nh3_sensitivity);
    int co2 = (int)(getValue(sensor_data, ',', 6) * co2_sensitivity);
    int h2s = (int)(getValue(sensor_data, ',', 7) * h2s_sensitivity);
    int ch4 = (int)(getValue(sensor_data, ',', 8) * ch4_sensitivity);
    int no = (int)(getValue(sensor_data, ',', 9) * no_sensitivity);
    int no2 = (int)(getValue(sensor_data, ',', 10) * no2_sensitivity);
    int nox = (int)(getValue(sensor_data, ',', 11) * nox_sensitivity);
    int so2 = (int)(getValue(sensor_data, ',', 12) * so2_sensitivity);

    // Check sensor values against thresholds and activate/deactivate relay module channels accordingly
    if (air_pollution > air_pollution_threshold) {
      digitalWrite(RELAY_MODULE_CH1, HIGH);
    } else {
      digitalWrite(RELAY_MODULE_CH1, LOW);
    }
    
    if (co > co_threshold) {
      digitalWrite(RELAY_MODULE_CH2, HIGH);
    } else {
      digitalWrite(RELAY_MODULE_CH2, LOW);
    }
  }
}

int getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for (int i=0; i<=maxIndex && found<=index; i++){
    if (data.charAt(i)==separator || i==maxIndex){
      found++;
      strIndex[0] = strIndex[1]+1;
      strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  return data.substring(strIndex[0], strIndex[1]).toInt();
}
