// Define pin connections for sensors, LEDs, and buzzer
#define MQ A5 // Gas sensor connected to analog pin A5
#define RLED A4 // Red LED connected to pin A4
#define GLED A2 // Green LED connected to pin A2
#define BUZZER 4 // Buzzer connected to pin 4
#define BUTTON_PIN 8 // Button connected to pin 8


// Variable to track the alarm state (0: Off, 1: On)
int alarmState = 1;
unsigned long startTime = 0;
const unsigned long deactivationTime = 30000;

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
  
  // Configure pin modes
  pinMode(MQ, INPUT); // Set gas sensor as input
  pinMode(BUZZER, OUTPUT); // Set buzzer as output
  pinMode(RLED, OUTPUT); // Set red LED as output
  pinMode(GLED, OUTPUT); // Set green LED as output
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Set button as input
}

void loop() {
  // Read button state (1: Not pressed, 0: Pressed)
  int buttonstate = digitalRead(BUTTON_PIN);

  // Read the gas sensor value
  int LPG = analogRead(MQ);

  // Display sensor value in the Serial Monitor
  Serial.print("MQ: ");
  Serial.println(LPG);



  // Check if gas level exceeds the threshold (940mV,1000pm)
  if (LPG >= 940) {
    
  if (buttonstate == 0) {
    alarmState = 0;    // If button is pressed, it deactivates the alarm
    startTime = millis();  //notes the time of starting for the timer

  }
      digitalWrite(GLED, LOW); // Turn off the green LED
      delay(50);
      Alarm();

      if (alarmState ==0 && (millis() - startTime >= deactivationTime)){ // if the the time interval has passed the delaytime
        alarmState = 1;
      }

 
  } else {
    // Activates the alarm tate and turn off the red LED when gas levels are normal
    alarmState = 1;
    digitalWrite(RLED, LOW);
    delay(50);
    digitalWrite(GLED, HIGH); // Turn on the green LED to indicate safety

  }
}

// Function to blink the red LED
void Alarm() {
  digitalWrite(RLED, HIGH);
  if (alarmState == 1) {
  tone(BUZZER, 400); // Generate a 400 Hz tonea
    }
  delay(300);
  digitalWrite(RLED, LOW);
  noTone(BUZZER); // Stop the tone
  delay(300);
}

