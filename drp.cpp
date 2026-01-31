#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// ================= CONFIGURATIONS =================

// 1. Network Credentials
const char* ssid = "YOUR_WIFI_SSID";         // Replace with your WiFi Name
const char* password = "YOUR_WIFI_PASSWORD"; // Replace with your WiFi Password

// 2. Telegram Bot Credentials
#define BOT_TOKEN "YOUR_TELEGRAM_BOT_TOKEN"  // Get from BotFather
#define CHAT_ID "YOUR_TELEGRAM_CHAT_ID"      // Get from @userinfobot

// 3. Pin Definitions (Adjust based on your wiring)
#define TRIG_PIN 5      // Ultrasonic Trig
#define ECHO_PIN 18     // Ultrasonic Echo
#define BUZZER_PIN 19   // Speaker/Buzzer
#define VIB_MOTOR_PIN 21 // Vibration Motor
#define SOS_BUTTON_PIN 4 // SOS Button

// 4. Constants
const int OBSTACLE_THRESHOLD_CM = 50; // Distance to trigger alert (in cm)
const unsigned long BOT_MTBS = 1000;  // Mean time between scan messages

// ================= OBJECTS & VARIABLES =================

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

long duration;
int distance;
unsigned long lastTimeBotRan;
bool buttonState = false;

// ================= SETUP =================

void setup() {
  Serial.begin(115200);

  // Initialize Pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(VIB_MOTOR_PIN, OUTPUT);
  pinMode(SOS_BUTTON_PIN, INPUT_PULLUP); // Use Internal Pullup Resistor

  // Connect to WiFi
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  
  // Secure Client Setup for Telegram
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  
  // Startup Sound
  digitalWrite(BUZZER_PIN, HIGH);
  delay(200);
  digitalWrite(BUZZER_PIN, LOW);
}

// ================= MAIN LOOP =================

void loop() {
  
  // --- 1. OBSTACLE DETECTION LOGIC ---
  // Clear Trig
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  // Trigger Sensor
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Read Echo
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2; // Calculate distance in cm

  // --- 2. FEEDBACK SYSTEM (HAPTIC & AUDIO) ---
  if (distance > 0 && distance < OBSTACLE_THRESHOLD_CM) {
    // Obstacle Detected!
    Serial.print("Obstacle Detected: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Vibration ON
    digitalWrite(VIB_MOTOR_PIN, HIGH);
    
    // Buzzer Alert (Beep speed increases as object gets closer)
    digitalWrite(BUZZER_PIN, HIGH);
    delay(distance * 2); // Faster beeps for closer objects
    digitalWrite(BUZZER_PIN, LOW);
    delay(distance * 2);
    
  } else {
    // Path Clear
    digitalWrite(VIB_MOTOR_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }

  // --- 3. SOS BUTTON LOGIC ---
  // Check if button is pressed (LOW because of INPUT_PULLUP)
  if (digitalRead(SOS_BUTTON_PIN) == LOW) {
    Serial.println("SOS Button Pressed!");
    sendSOS();
    delay(2000); // Debounce delay to prevent multiple messages
  }
}

// ================= HELPER FUNCTIONS =================

void sendSOS() {
  // Beep to confirm button press
  digitalWrite(BUZZER_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN, LOW);
  delay(100);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.println("Sending Telegram SOS...");
  
  // Construct Message with Google Maps Link
  // Note: For real dynamic GPS, you would read latitude/longitude from a GPS module here.
  // Below is a placeholder or WiFi-based estimation.
  String message = "🚨 *EMERGENCY SOS* 🚨\n\n";
  message += "I need help! My smart stick detected an emergency.\n";
  message += "📍 *Current Location:* \n";
  message += "https://www.google.com/maps/search/?api=1&query=15.8281,78.0373"; // Replace with variable lat/long if GPS module attached
  
  if (bot.sendMessage(CHAT_ID, message, "Markdown")) {
    Serial.println("SOS Sent Successfully!");
  } else {
    Serial.println("Failed to send SOS.");
  }
}
