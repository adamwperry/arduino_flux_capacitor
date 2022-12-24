#include <ezButton.h>
#include <Adafruit_NeoPixel.h>
#define PIN 3       // input pin Neopixel is attached to
#define NUMPIXELS 4 // number of Neopixel in Ring

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

ezButton button(5);
ezButton button2(4);

int redColor = 255;
int greenColor = 255;
int blueColor = 0;

int buttonPushCounter = 0;
int colorButtonPushCounter = 0;
bool isRainbow = false;

int arrColors[12][3] = {
  {255, 255, 255},
  {216, 81, 22},  //btf - orange
  {228, 128, 29}, //btf - orange 2
  {240, 168, 26}, //btf - yellow
  {247, 220, 17}, //btf - yellow 2
  {45, 156, 206}, //btf - blue
  {0, 0, 255},    //blue
  {65, 40, 141},  //purple
  {0, 133, 41},   //green
  {255, 130, 0},  //tn orange
  {88, 89, 91},   //tn grey
  {255, 0, 0},    //red
};



int i = 0;

unsigned long patternInterval = 1000 ; // time between steps in the pattern
unsigned long lastUpdate = 0 ; // for millis() when last update occoured
unsigned long intervals [] = {1000, 500, 250, 100, 50, 25, 10}; // speed for each pattern

void setup()
{
  Serial.begin(9600);

  button.setDebounceTime(50);

  pinMode(13, OUTPUT);
  pinMode(5, INPUT);
  pinMode(4, INPUT);

  pixels.begin(); // Initializes the NeoPixel library.
}

void loop()
{
  button.loop();
  button2.loop();

  if (button.isPressed()) {
    buttonPushCounter++;
    int len = sizeof(intervals) / sizeof(intervals[0]);
    if (buttonPushCounter == len)
    {
      isRainbow = true;
    }
    else if (buttonPushCounter > len)
    {
      isRainbow = false;
      buttonPushCounter = 0;
    }
    patternInterval = intervals[buttonPushCounter];
  }

  if (button2.isPressed()) {
    colorButtonPushCounter++;
    int len = sizeof(arrColors) / sizeof(arrColors[0]);
    if (colorButtonPushCounter >= len)
    {
      colorButtonPushCounter = 0;
    }
  }

  if (millis() - lastUpdate > patternInterval) updatePattern();
}


void updatePattern() {
  if (isRainbow)
  {
    rainbow();
    return;
  }
  pixels.clear();
  pixels.setPixelColor(i, pixels.Color(arrColors[colorButtonPushCounter][0], arrColors[colorButtonPushCounter][1], arrColors[colorButtonPushCounter][2]));
  pixels.show();
  i++;
  if (i == NUMPIXELS)
  {
    i = 0;
  }

  lastUpdate = millis();
}

// These two functions below for the rainbow effect were found on several arduino forum post.
void rainbow() { 
  static uint16_t j = 0;
  for (int i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, Wheel((i + j) & 255));
  }
  pixels.show();
  j++;
  if (j >= 256) j = 0;
  lastUpdate = millis();
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}