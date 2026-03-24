// ************* RemoteStartStop_PC ***************
// --------------------------------------------------------------------------
// REMOTE PC POWER START or STOP USING  ESP32 AND TELEGRAM BOT
// --------------------------------------------------------------------------
// Power ON or OFF PC buy sending message via Telegram App from anywhere
// Uses a ESP32 gadget to put the PC in sleep mode or turn-on using soft switching.
// ESP32 should have an active WiFi connection, and should be kept always on
// The PC should have the power supply connected, and not manually switched off.
// The ESP32 sends a  signal via opto-coupler to the PC soft-switch terminals to 
// either turn off or on.
// ESP32 receives the command to turn on/off through a Telegram message
// Multiple users can operate the PC power using their own Telegram app.
// Each user's Telegram id need to be included in this script.
// --------------------------------------------------------------------------
//
// ----------- REQUIRED INPUTS -----------------------------------------------
// 1. WiFi SSID and Password  for the ESP32. WiFi 5G does not work. Use 2G
// 2. Telegram Bot token from @BotFather
// 3. Telegram chat id  for each individual users. 
//    (More than one person can operate it. Everyone needs separate chat ids')
//
//  Replace these values in the script below with your own. 
//Here the values given are sample values and will not work for you.
//----------------------------------------------------------------------------

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
 
// --- 1. CONFIGURATION   (REPLACE WITH YOUR OWN VALUES) ---

// Replace with your Wi-Fi credentials
const char* WIFI_SSID = "Dr.paramesh 2G";
const char* WIFI_PASS = "xxxxxxxxxx";

// Replace with your Telegram Bot Token (from @BotFather)
#define BOT_TOKEN "1234567890:xxxxxxxpvY_q0S9oUt38qSeNYVXxxxxxxxx" 

// Replace with your personal Chat ID (from @myidbot) - CRUCIAL FOR SECURITY
#define CHAT_ID "9999999999"    //For single user

// List of allowed Telegram chat IDs  (FOR MULTIPLE USERS)
const  String allowed_ids[] = {
  "9999999999",
  "1111111111"
}; // your ID + friend's ID, just add new id with a , at the end (except the last line)
const int allowed_count = sizeof(allowed_ids)/sizeof(allowed_ids[0]);

bool isAllowed(const String& chat_id) {
  for (int i = 0; i < allowed_count; i++) {
    if (chat_id == allowed_ids[i]) return true;
  }
  return false;
}

// Define the pin connected to the Optocoupler (THE  OUTPUT PIN)
const int POWER_PIN = 23;  //Make sure this pin is used as output in ESP32 board
// Define the pin for the built-in LED (FOR VISUAL TESTING ONLY)
const int TEST_LED_PIN = 2;

// Time settings
const int BOT_REQUEST_DELAY = 1000; 
unsigned long lastTimeBotChecked;

// --- 2. BOT AND CLIENT OBJECTS ---
WiFiClientSecure client; 
UniversalTelegramBot bot(BOT_TOKEN, client);

// --- 3. FUNCTION DECLARATIONS ---
void setup_wifi();
void pulsePowerPin(int duration_ms);
void handleNewMessages(int numNewMessages);


// =========================================================
// --- 4. SETUP ---
// =========================================================

void setup() {
  Serial.begin(115200);
  Serial.println("--- ESP32 PC Power Controller  Starting ---");

  // Configure the power control pin (P23 / GPIO 23)
  pinMode(POWER_PIN, OUTPUT); 
  digitalWrite(POWER_PIN, LOW); 

  // Configure the TEST LED pin (GPIO 2)
  pinMode(TEST_LED_PIN, OUTPUT);
  digitalWrite(TEST_LED_PIN, LOW); // Start the LED off

  setup_wifi();
  client.setInsecure(); 
}


// =========================================================
// --- 5. LOOP ---
// =========================================================

void loop() {
  if (millis() > lastTimeBotChecked + BOT_REQUEST_DELAY) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    
    while(numNewMessages) {
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    
    lastTimeBotChecked = millis();
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi disconnected. Reconnecting...");
    setup_wifi();
  }
}


// =========================================================
// --- 6. HELPER FUNCTIONS ---
// =========================================================

void setup_wifi() {
  Serial.print("Connecting to WiFi: ");
  Serial.println(WIFI_SSID);
  
  // Clear any persistent Wi-Fi settings for a fresh start
  WiFi.disconnect(true); 
  WiFi.mode(WIFI_STA);
  
  // --- Check 1: Hidden SSID ---
  // If your Wi-Fi network name (SSID) is NOT broadcasted, uncomment the line below.
  // WiFi.begin(WIFI_SSID, WIFI_PASS, 0, NULL, true); // true = isHidden
  // Otherwise, use the standard command:
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  
  int attempts = 0;
  // NOTE: Increased timeout attempts for slower networks (30 attempts = 15 seconds)
  while (WiFi.status() != WL_CONNECTED && attempts < 30) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected successfully.");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.print("\nFailed to connect. Wi-Fi Status Code: ");
    Serial.println(WiFi.status()); // THIS IS THE CRUCIAL DIAGNOSTIC OUTPUT
  }
}

// Simulates a momentary button press 
void pulsePowerPin(int duration_ms) {
  // 1. Press the button (close the switch) AND turn on the test LED
  digitalWrite(POWER_PIN, HIGH); 
  digitalWrite(TEST_LED_PIN, HIGH); // TEMPORARY TEST LINE

  Serial.print("Pulsing HIGH for ");
  Serial.print(duration_ms);
  Serial.println("ms...");

  // 2. Hold the press
  delay(duration_ms);            

  // 3. Release the button (open the switch) AND turn off the test LED
  digitalWrite(POWER_PIN, LOW);  
  digitalWrite(TEST_LED_PIN, LOW); // TEMPORARY TEST LINE
}

// Processes incoming Telegram messages (logic remains the same)
void handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;
    
    Serial.print("Received message: ");
    Serial.println(text);
    
    // Temporary for debugging
    //Serial.print("Received message: ");
    //Serial.println(message.text);
    //Serial.print("Sender chat_id: ");
    //Serial.println(message.chat_id);

    if (!isAllowed(chat_id)) {
      Serial.println("Unauthorized message received. Ignoring.");
      bot.sendMessage(chat_id, "Access Denied: You are not an authorized user for this device.", "");
      continue; 
    }  

    //if (chat_id != CHAT_ID) {
      //Serial.println("Unauthorized message received. Ignoring.");
      //bot.sendMessage(chat_id, "Access Denied: You are not an authorized user for this device.", "");
      //continue; 
    //}
    
    if (text == "/startpc") {
      bot.sendMessage(chat_id, "✅ REMOTE PC: Power ON pulse (500ms).", "");
      pulsePowerPin(500); 
    } 
    else if (text == "/shutdown") {
      bot.sendMessage(chat_id, "⏸️ REMOTE PC: Graceful Shutdown pulse (200ms).", "");
      pulsePowerPin(200); 
    }
    else if (text == "/forceoff") {
      bot.sendMessage(chat_id, "🛑 REMOTE PC: HARD SHUTDOWN pulse (5000ms).", "");
      pulsePowerPin(5000); 
    }
    else if (text == "/status") {
      String message = "ESP32 Ready to receive commands! IP: " + WiFi.localIP().toString();
      message += "\nCommands: /startpc, /shutdown, /forceoff";
      bot.sendMessage(chat_id, message, "");
    }
    else if (text == "/start" || text == "/help") {
      bot.sendMessage(chat_id, "Welcome to Remote PC. Send /status or a command to test the pulse.", "");
    }
    else if (text == "/clear") {
        bot.sendMessage(chat_id, "Message history cleared.", "");
    }
  }
}
