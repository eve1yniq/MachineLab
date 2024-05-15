#include <Servo.h>
#include <Adafruit_NeoPixel.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
int pos = 90;

// Define parameters for Neopixel strip
#define PIN_STRIP     7 // Arduino pin connected to Neopixel Strip
#define NUM_PIXELS    65  // Number of pixels in Neopixel Strip
#define UPDATE_INTERVAL 100   // Time between gradient updates in milliseconds

// Create Neopixel object for strip
Adafruit_NeoPixel strip(NUM_PIXELS, PIN_STRIP, NEO_GRB + NEO_KHZ800);

unsigned long lastUpdate = 0; // Last update of color
int wavePosition = 0;         // Position of the wave in the strip
int colorPhase = 0;           // Color phase for continuous color update


unsigned long lastServoUpdate = 0;
int servoUpdateInterval = 15; // Interval between servo updates
bool movingUp = true; // Direction of servo movement


void setup() {
  Serial.begin(9600);
  servo1.attach(2);
  servo2.attach(4);
  servo3.attach(A3);
  servo4.attach(A2);

  strip.begin();
  strip.setBrightness(50); // Set brightness (adjust as needed)
  strip.show();            // Display the initialized state
}

void loop() {
  if (millis() - lastUpdate > UPDATE_INTERVAL) {
    updateWave();
    lastUpdate = millis();
  }

  updateServos(); // Update servos independently
}

void updateWave() {
  // Clear the strip before updating
  strip.clear();

  // Create a wave of yellow and purple
  for (int i = 0; i < strip.numPixels(); i++) {
    // Calculate distance from the wavePosition
    int distance = abs(wavePosition - i);

    if (distance % 20 < 10) {
      // Yellow color wave
      strip.setPixelColor(i, strip.Color(255, 215, 0)); // Yellow
    } else {
      // Purple color wave
      strip.setPixelColor(i, strip.Color(48, 20, 100)); // Purple
    }
  }

  strip.show(); // Display the updated Neopixel strip
  wavePosition = (wavePosition + 2) % strip.numPixels(); // Move the wave
}

void updateServos() {
  if (millis() - lastServoUpdate > servoUpdateInterval) {
    if (movingUp) {
      if (pos < 140) {
        pos += 1;
      } else {
        movingUp = false; // Change direction
      }
    } else {
      if (pos > 90) {
        pos -= 1;
      } else {
        movingUp = true; // Change direction
      }
    }

    // Update all servos to the new position
    servo1.write(pos);
    servo2.write(pos);
    servo3.write(pos);
    servo4.write(pos);

    lastServoUpdate = millis(); // Reset the last update time
  }
}


void updateGradient() {
  // Cycle through colors
  uint8_t r = (sin(colorPhase * 0.1) * 127 + 128);
  uint8_t g = (sin(colorPhase * 0.1 + 2) * 127 + 128);
  uint8_t b = (sin(colorPhase * 0.1 + 4) * 127 + 128);

  for (int i = 0; i < strip.numPixels(); i++) {
    float progress = (float)i / strip.numPixels();
    uint8_t calcR = r + progress * (255 - r);
    uint8_t calcG = g + progress * (255 - g);
    uint8_t calcB = b + progress * (255 - b);
    strip.setPixelColor(i, strip.Color(calcR, calcG, calcB));
  }

  strip.show(); // Display the updated Neopixel strip
  colorPhase++; // Increment color phase for continuous change
}


//#include <Servo.h>
//#include <Adafruit_NeoPixel.h>
//
//// Servo objects
//Servo servo1;
//Servo servo2;
//Servo servo3;
//Servo servo4;
//
//// Servo position variable
//int pos = 90;
//
//// NeoPixel Fader class
//class NeoPixelFader {
//  Adafruit_NeoPixel pixels;
//  int delayBetweenSteps;
//  unsigned long previousMillis = 0;
//  uint8_t currentIndex = 0;
//  bool direction = true; // true for incrementing, false for decrementing
//
//public:
//  NeoPixelFader(int pin, int numPixels, int delayBetween) : pixels(numPixels, pin, NEO_GRB + NEO_KHZ800) {
//    delayBetweenSteps = delayBetween;
//  }
//
//  void begin() {
//    pixels.begin();
//    pixels.clear();
//    pixels.show();
//  }
//
//  void update() {
//    unsigned long currentMillis = millis();
//    if (currentMillis - previousMillis >= delayBetweenSteps) {
//      // Update current pixel color
//      if (direction) {
//        pixels.setPixelColor(currentIndex, pixels.Color(255, 255, 102)); // Yellow
//      } else {
//        pixels.setPixelColor(currentIndex, 0); // Turn off
//      }
//      pixels.show();
//
//      // Adjust index and direction
//      if (direction) {
//        currentIndex++;
//        if (currentIndex >= pixels.numPixels()) {
//          currentIndex = pixels.numPixels() - 1; // Stay within bounds
//          direction = !direction; // Change direction
//        }
//      } else {
//        if (currentIndex == 0) {
//          direction = !direction; // Change direction
//        }
//        currentIndex--;
//      }
//
//      previousMillis = currentMillis;
//    }
//  }
//};
//
//// Initialize NeoPixelFader
//NeoPixelFader fader(7, 70, 250); // Pin 7, 65 pixels, 250 ms interval
//
//void setup() {
//  Serial.begin(9600);
//  servo1.attach(2);
//  servo2.attach(4);
//  servo3.attach(A3);
//  servo4.attach(A2);
//  fader.begin();
//}
//
//void loop() {
//  // Move servos smoothly
//  for (pos = 90; pos <= 140; pos += 1) {
//    servo1.write(pos);
//    servo2.write(pos);
//    servo3.write(pos);
//    servo4.write(pos);
//    fader.update(); // Update NeoPixel colors without delay
//    delay(15); // Short delay for servo movement
//  }
//  delay(200);
//  for (pos = 140; pos >= 90; pos -= 1) {
//    servo1.write(pos);
//    servo2.write(pos);
//    servo3.write(pos);
//    servo4.write(pos);
//    fader.update(); // Update NeoPixel colors without delay
//    delay(15); // Short delay for servo movement
//  }
//  delay(200);
//}
