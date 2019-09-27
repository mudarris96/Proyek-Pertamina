/// wiring
// out = pin A0
// vcc = Pin 5V
//GND = pin GND

int const TEMP6000_PIN = A0;
int const AREF = 5.0;       // set for 5.0 or 3.3 depending on voltage of uC
//===============================================================================
//  Initialization
//===============================================================================
void setup() {
  Serial.begin(9600);    // Initialize serial comm
}
//===============================================================================
//  Main
//===============================================================================
void loop() {

// The math is broken out into steps to make it easier to follow.
float sensor_value = analogRead(TEMP6000_PIN); // Get raw sensor reading
float volts = sensor_value * AREF / 1024.0;    // Convert reading to voltage
float amps = volts / 10000.0;             // Convert to amps across 10K resistor
float microamps = amps * 1000000.0;             // Convert amps to microamps
float lux = microamps * 2.0;                  // 2 microamps = 1 lux

// All the math above can also be replaced with the following formula 
// assuming AREF is 5.0 volts.

    // float lux = sensor_value * 0.9765625;

Serial.print ("Raw ADC data: ");
Serial.print (sensor_value);
Serial.print ("  Volts: ");
Serial.print (volts);
Serial.print ("  Lux: ");
Serial.println (lux);

delay(1000);  // Take reading every second
}
