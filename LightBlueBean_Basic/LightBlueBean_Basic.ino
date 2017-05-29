
String beanName = "LightBlueBean";
const uint8_t ledScratch = 1;
const uint8_t temperatureScratch = 2;
const uint8_t BatteryScratch = 3;
const uint8_t MotorScratch = 4;
void setup() {
    // Setup bean
    Bean.setBeanName(beanName);
    Bean.enableWakeOnConnect(true);
    // Reset the scratch data area 1.
    uint8_t resetLedBuffer[] = {0, 0, 0};
    Bean.setScratchData(ledScratch, resetLedBuffer, 3);
	uint8_t resetMotorBuffer[] = {0, 0, 0};
	Bean.setScratchData(MotorScratch, resetMotorBuffer, 3);
}
 
// the loop routine runs over and over again forever:
void loop() {
    bool connected = Bean.getConnectionState();
    if(connected) {
        // Write current temperature to a scratch data area.
        uint8_t temperatureBuffer[1];
                temperatureBuffer[0] = Bean.getTemperature();
        Bean.setScratchData(temperatureScratch, temperatureBuffer, 1);
        // Update LEDs

// Agregado ahorita
        uint8_t BatteryBuffer[1];
                BatteryBuffer[0] = Bean.getBatteryLevel();
        Bean.setScratchData(BatteryScatch, BatteryBuffer, 1);
// cerrado

        ScratchData receivedData = Bean.readScratchData(ledScratch);
        uint8_t redLed =   receivedData.data[0];
        uint8_t greenLed = receivedData.data[1];
        uint8_t blueLed =  receivedData.data[2];
        Bean.setLed(redLed, greenLed, blueLed);

// Agregado ahorita
 		ScratchData receivedData = Bean.readScratchData(MotorScratch);
        uint8_t Motor1 = receivedData.data[0];
        uint8_t Motor2 = receivedData.data[1];
        uint8_t Motor3 = receivedData.data[2];
        
// Cerrado    
	}
    else {
        // Turn LED off and put to sleep.
        Bean.setLed(0, 0, 0);
        Bean.sleep(0xFFFFFFFF);
    }
}