// Test_ESP32_blinking_Stop
// Stops ESP32 led blinking by setting LED_PIN to LOW

// Define the pin connected to the built-in LED.
// GPIO 2 usually corresponds to the blue LED near the Wi-Fi antenna.
const int LED_PIN = 2; 

void setup() {
  // Initialize the digital pin as an output.
  pinMode(LED_PIN, OUTPUT);
  
  // Start serial communication (for optional debugging check)
  Serial.begin(115200); 
  Serial.println("--- Blink Test Stop ---");

  // Turn the LED off (LOW voltage level)
  digitalWrite(LED_PIN, LOW);    
  Serial.println("LED OFF");
}

void loop() {
  // Nothing here — LED stays OFF
}
 