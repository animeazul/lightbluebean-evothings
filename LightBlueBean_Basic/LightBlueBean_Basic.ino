
String beanName = "LightBlueBean";
int mot1i=9;
int mot1d=8;
int mot1e=7;
int mot2i=6;
int mot2d=4;
int mot2e=5;
int mot3i=1;
int mot3d=0;
int mot3e=2;

const uint8_t ledScratch = 1;
const uint8_t temperatureScratch = 2;
const uint8_t BatteryScratch = 3;
const uint8_t MotorScratch = 4;
void setup() {
   pinMode(mot1i, OUTPUT);
   pinMode(mot1d, OUTPUT);
   pinMode(mot2i, OUTPUT);
   pinMode(mot2d, OUTPUT);
   pinMode(mot3i, OUTPUT);
   pinMode(mot3d, OUTPUT);
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
        Bean.setScratchData(BatteryScratch, BatteryBuffer, 1);
// cerrado

        ScratchData receivedData = Bean.readScratchData(ledScratch);
        uint8_t redLed =   receivedData.data[0];
        uint8_t greenLed = receivedData.data[1];
        uint8_t blueLed =  receivedData.data[2];
        Bean.setLed(redLed, greenLed, blueLed);

// Agregado ahorita
 	ScratchData receivedData2 = Bean.readScratchData(MotorScratch);
        uint8_t Motor1 = receivedData2.data[0];
        uint8_t Motor2 = receivedData2.data[1];
        uint8_t Motor3 = receivedData2.data[2];
        analogWrite(mot1e, Motor1); 
        digitalWrite(mot1i,LOW);
        digitalWrite(mot1d,HIGH);
// Cerrado    
	}
    else {
        // Turn LED off and put to sleep.
        Bean.setLed(0, 0, 0);
        Bean.sleep(0xFFFFFFFF);
    }
}
