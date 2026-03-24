#  Remote PC Control Using ESP32 and Telegram

🔥 Just send Telegram message to turn off/on your computer from anywhere in the world! Build a simple ESP32 gadget!!  

---

## 🎥 Watch Full Tutorial  
👉 COMING SOON..<br>
<sub>Highly recommended before using the code</sub>

---

## 📥 Download Arduino IDE Code  
Click **Code → Download ZIP**

---

## 📁 Files
- **RemoteStartStop_PC** → Main project  
- **Test_ESP32_Blinking_Start** → Test ON signal (optional, recommended)  
- **Test_ESP32_Blinking_Stop** → Test OFF signal (optional)  

---

## ⚡ Quick Setup
1. Create Telegram bot (BotFather)  
2. Prepare hardware: ESP32 + Optocoupler (PC817) + resistor  
3. Connect ESP32 to PC/Mac via USB-C  
4. Install Arduino IDE + required libraries  
5. Add WiFi + BOT Token + Chat ID in `RemoteStartStop_PC`  
6. Test using `Test_ESP32_Blinking_Start`  
7. Upload `RemoteStartStop_PC` (one-time setup)  
8. Connect ESP32 + optocoupler to computer  
9. Send Telegram commands to control PC  

---

## 📲 Telegram Commands
- `/startpc` → Turn ON PC (500 ms signal)  
- `/shutdown` → Turn OFF PC (200 ms signal)  
- `/forceoff` → Force OFF (5000 ms signal)  

---

## ⚠️ Important
- Use relay/optocoupler — **DO NOT connect ESP32 directly to motherboard**  
- You may need to press ESP32 reset button while uploading (not needed on Mac)  
- Uploading code is required only once  
- Do NOT disconnect main power supply of the PC manually  
- WiFi must remain ON for remote control  

---

## 👍 Support

If this project helped you:

👉 Watch the full tutorial: COMING SOON  

And don’t forget to:
- 👍 Like the video  
- 💬 Comment your questions  
- 🔔 Subscribe for more ESP32 projects  
