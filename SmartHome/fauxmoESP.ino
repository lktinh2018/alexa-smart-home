void initFauxmoESP() {
  fauxmo.createServer(true);
  
  fauxmo.enable(true);

  //Add virtual devices
  fauxmo.addDevice(DEVICE_1);
  fauxmo.addDevice(DEVICE_2);
  fauxmo.addDevice(DEVICE_3);
  fauxmo.addDevice("the screen backlight");

  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
    callback(device_id, device_name, state);
  });
  
}

void loopFauxmoESP() {
  fauxmo.handle();
}

void callback(uint8_t deviceID, const char * deviceName, bool state) {
  int pinNum;
  if(String(deviceName) == DEVICE_1) {
    pinNum = RELAY_PIN_1;
  } else if(String(deviceName) == DEVICE_2) {
      pinNum = RELAY_PIN_3;
  } else if(String(deviceName) == DEVICE_3) {
      pinNum = RELAY_PIN_4;
  } else if(String(deviceName) == "the screen backlight") {
      if(state)
        lcd.backlight();
      else
        lcd.noBacklight();
      return;
  } else if(String(deviceName) == "all devices") {
      digitalWrite(RELAY_PIN_1, state);
      digitalWrite(RELAY_PIN_3, state);
      digitalWrite(RELAY_PIN_4, state);
  
      //LCD
      lcd.clear();
      lcd.print("   All Devices");
      lcd.setCursor(7, 1);
      lcd.print(state ? "On" : "Off");
        
      //Debug
      debugln("");
      debug("All Devices ");
      debug(state ? "ON" : "OFF");
      debugln("");
      return;
  } 
  
  digitalWrite(pinNum, state);

  //Display status
  lcd.clear();
  lcd.print("Device " + String(deviceName));
  lcd.setCursor(7, 1);
  lcd.print(state ? "On" : "Off");
  debugln("");
  debug("Device ");
  debug(deviceName);
  debug(" state ");
  debug(state ? "ON" : "OFF");
  debugln("");
}
