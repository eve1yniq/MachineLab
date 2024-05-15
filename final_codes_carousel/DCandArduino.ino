#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

// Motor A connections
int enA = 9;
int in1 = 11;
int in2 = 10;

// Button and Relay connections
const int buttonPin = A2;  // The number of the pushbutton pin
const int relayPinAr = 2;    // Relay pin to control upper Arduino power
const int relayPinServos = 5;    // Relay pin to control upper Arduino power
int buttonState = 0;
int lastButtonState = 0;  // To store the previous state of the button

// Timer and duration control
unsigned long startTime = 0;
const unsigned long duration = 45000; // duration for which everything should be on (45 seconds)
bool isCarouselOn = false;
// Music player setup
#define SHIELD_RESET  -1
#define SHIELD_CS     7
#define SHIELD_DCS    6
#define CARDCS 4
#define DREQ 3

Adafruit_VS1053_FilePlayer musicPlayer = 
  Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

void setup() {
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(relayPinAr, OUTPUT);
  pinMode(relayPinServos, OUTPUT);

  // Start everything off
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(relayPinAr, HIGH);
  digitalWrite(relayPinServos, HIGH);
  
  if (!musicPlayer.begin()) {
    Serial.println("Couldn't find VS1053, do you have the right pins defined?");
    while (1);
  }
  Serial.println("VS1053 found");

  if (!SD.begin(CARDCS)) {
    Serial.println("SD failed, or not present");
    while (1);
  }

  printDirectory(SD.open("/"), 0);
  musicPlayer.setVolume(0, 0);
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH && lastButtonState == LOW && isCarouselOn == false) {
    // Start the timer and activate everything
    isCarouselOn = true;
    startTime = millis();
    carouselON();
    musicPlayer.startPlayingFile("/track001.mp3"); // Start playing music from the beginning
  }

  // Check if the timer has elapsed
  if (millis() - startTime >= duration) {
    isCarouselOn = false;
    carouselOFF();
    musicPlayer.stopPlaying(); // Stop the music completely
    startTime = millis() + duration; // Reset startTime to a future time to prevent reactivation
  }

  lastButtonState = buttonState; // Update the last button state
  delay(100);
}

void carouselON() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 100);
  digitalWrite(relayPinAr, LOW);// Turn on the relay, and thus the upper Arduino
  digitalWrite(relayPinServos, LOW);
}

void carouselOFF() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);
  digitalWrite(relayPinServos, HIGH);
  digitalWrite(relayPinAr, HIGH); // Turn off the relay, and thus the upper Arduino
}

void printDirectory(File dir, int numTabs) {
  while (true) {
    File entry = dir.openNextFile();
    if (!entry) break;
    for (uint8_t i=0; i<numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}
