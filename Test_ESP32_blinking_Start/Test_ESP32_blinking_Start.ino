//Test_ESP32_blinking_Start
// Starts led blinking on ESP32 board. Off/on duration adjustable

// Define the pin connected to the built-in LED.
// GPIO 2 usually corresponds to the blue LED near the USB port.
const int LED_PIN = 2; 

void setup() {
  // Initialize the digital pin as an output.
  pinMode(LED_PIN, OUTPUT);
  
  // Start serial communication (for optional debugging check)
  Serial.begin(115200); 
  Serial.println("--- Blink Test Start ---");
}

void loop() {
    
  // Turn the LED on (Set LED-PIN to HIGH)
  digitalWrite(LED_PIN, HIGH);    
  //Serial.println("LED ON"); //Optional, better to avoid
  //Remain on for 1000 milliseconds
  delay(1000); // Wait for 1 second in ON state, change to any value

  // Turn the LED off (Set LED_PIN to LOW)
  digitalWrite(LED_PIN, LOW);   
  //Serial.println("LED OFF"); //Optional, better to avoid
  //Remain off for 500 mili-second
  delay(500); // Wait for 0.5 second in OFF state, change to any value
              
}
 