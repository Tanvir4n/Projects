#include <LiquidCrystal_I2C.h>
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

int redLED = 2;
int greenLED = 3;
int buzzer = 9;
int relay = 7;
int sensor = A0;
float smokePercentage;
float remainingGas;
float tolerance = 30;

int switchPin = 12;  // Pin where the switch is connected
int switchState = 0;

int base_value = 399; // base value
int state; // state for blinking LED & buzzer without delay function

unsigned long previousMillis = 0; 
const long interval = 400; // interval for LED blinking & Buzzer sound (milliseconds)

void setup() {
    pinMode(switchPin, INPUT);
    pinMode(redLED, OUTPUT);
    pinMode(relay, OUTPUT);
    pinMode(greenLED, OUTPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(sensor, INPUT);
    Serial.begin(9600);
    lcd.init();              // Initialize LCD
    lcd.backlight();         // Turn on backlight
}

void loop() {
    switchState = digitalRead(switchPin);
    unsigned long currentMillis = millis();
    float MQ135SensorValues = analogRead(sensor);

    if (switchState == 1) {
        MQ135SensorValues *= 2; // Amplify sensor reading if switch is ON
    }

    Serial.print("Sensor Values: ");
    Serial.println(MQ135SensorValues);
    lcd.setCursor(0, 0);
    lcd.print("Smoke % :");

    remainingGas = 1023 - base_value + tolerance;
    smokePercentage = (MQ135SensorValues - base_value) / remainingGas;

    if (smokePercentage > 0) {
        Serial.print("Smoke percentage: ");
        Serial.println(smokePercentage * 100);
        lcd.setCursor(9, 0);
        lcd.print(smokePercentage * 100, 1); // Display smoke % with one decimal
        lcd.print("%");
    } else {
        lcd.setCursor(10, 0);
        lcd.print("-SAFE-");
    }

    if (MQ135SensorValues > (base_value + tolerance)) {
        digitalWrite(greenLED, LOW);
        digitalWrite(relay, LOW);
        lcd.setCursor(0, 1);
        lcd.print("Smoke Detected!!");
        Serial.println("Smoke Detected!!");

        if (currentMillis - previousMillis >= interval) {
            previousMillis = currentMillis;
            state = !state; // Toggle state
            digitalWrite(redLED, state);
            digitalWrite(buzzer, state);
        }
    } else {
        digitalWrite(redLED, LOW);
        digitalWrite(relay, HIGH);
        digitalWrite(greenLED, HIGH);
        digitalWrite(buzzer, LOW);
        lcd.setCursor(0, 1);
        lcd.print("Sensor Value:");
        lcd.setCursor(13, 1);
        lcd.print(MQ135SensorValues);
    }
    delay(500);
}
