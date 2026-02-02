# DRP
Design Realisation Project
# Smart Blind Stick with Telegram SOS & Navigation  

A **Smart Blind Stick** project designed to assist visually impaired individuals using an **ESP32 module**, **ultrasonic sensors**, **haptic feedback**, **speakers for navigation**, and **Telegram Bot integration** for emergency SOS with live location sharing. The device is **rechargeable** and portable, providing real-time navigation assistance and safety alerts.  

---

## 🚀 Features  

- **Obstacle Detection**: Ultrasonic sensors detect obstacles in the path.  
- **Haptic Feedback**: Vibrations alert the user about nearby obstacles.  
- **Voice Guidance**: Speaker provides real-time navigation and safety warnings.  
- **Telegram Bot Integration**: Sends emergency SOS with live GPS location to predefined contacts.  
- **Rechargeable**: Powered by a rechargeable battery for portability.  
- **Compact & Lightweight**: Easy to carry, designed for daily use.  

---

## 🛠️ Components Used  

- **ESP32 Development Board**  
- **HC-SR04 Ultrasonic Sensor(s)** (for obstacle detection)  
- **Vibration Motor / Haptic Feedback Sensor**  
- **Mini Speaker / Buzzer** (for audio guidance)  
- **Rechargeable Battery Pack (Li-ion / Li-Po)** with charging circuit  
- **Switches & Buttons** (for power & SOS trigger)  
- **Optional**: GPS Module (if precise live location is needed)  

---

## 🔧 System Architecture  

1. **Obstacle Detection**  
   - Ultrasonic sensors measure the distance of obstacles.  
   - If within threshold, ESP32 triggers vibration and audio alerts.  

2. **Navigation Assistance**  
   - ESP32 communicates with speaker to give voice alerts (e.g., “Obstacle ahead at 1 meter”).  

3. **Emergency SOS**  
   - On SOS button press, ESP32 sends a message via Telegram Bot.  
   - Live GPS location is attached (via GPS module or ESP32’s WiFi-assisted geolocation).  

4. **Power Management**  
   - Rechargeable battery powers the stick.  
   - Charging handled via USB or battery management system.  

---

## 📱 Telegram Bot Setup  

1. Open **Telegram** and search for **BotFather**.  
2. Create a new bot using `/newbot`.  
3. Copy the **API Token**.  
4. Replace it in your ESP32 code under `TELEGRAM_BOT_TOKEN`.  
5. Get your **Chat ID** using [@userinfobot](https://t.me/userinfobot).  
6. Add Chat ID in ESP32 code to receive SOS alerts.  

---

## ⚡ Circuit Connections  

- **Ultrasonic Sensor** → ESP32 (Trigger & Echo pins)  
- **Vibration Motor** → ESP32 GPIO + Transistor driver circuit  
- **Speaker** → ESP32 DAC/PWM Pin  
- **SOS Button** → ESP32 GPIO (Input, Pull-up)  
- **Battery Pack** → ESP32 VIN (through charging circuit)  

---



