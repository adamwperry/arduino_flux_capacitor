#include <Adafruit_NeoPixel.h>
#define PIN 3       // input pin Neopixel is attached to
#define NUMPIXELS 4 // number of Neopixel in Ring

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int redColor = 255;
int greenColor = 255;
int blueColor = 0;

int buttonPushCounter = 0;
int colorButtonPushCounter = 0;

int arrSpeed[] = {1000, 500, 250, 100, 50, 25, 10};
int arrColors[11][3] = {
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
    {88, 89, 91}    //tn grey
};

void setup()
{
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);

  pixels.begin(); // Initializes the NeoPixel library.
}

void loop()
{
  if (digitalRead(2) == HIGH)
  {
    digitalWrite(13, HIGH);
    buttonPushCounter++;
    int len = sizeof(arrSpeed) / sizeof(arrSpeed[0]);
    if (buttonPushCounter > len)
    {
      buttonPushCounter = 0;
    }
  }
  else
  {
    digitalWrite(13, LOW);
  }

  if (digitalRead(4) == HIGH)
  {
    digitalWrite(13, HIGH);
    colorButtonPushCounter++;
    int len = sizeof(arrColors) / sizeof(arrColors[0]);
    if (colorButtonPushCounter > len)
    {
      colorButtonPushCounter = 0;
    }
  }
  else
  {
    digitalWrite(13, LOW);
  }

  pixels.show();
  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.clear();
    //pixels.setPixelColor(i, pixels.Color(redColor, greenColor, blueColor));

    pixels.setPixelColor(i, pixels.Color(arrColors[colorButtonPushCounter][0], arrColors[colorButtonPushCounter][1], arrColors[colorButtonPushCounter][2]));

    pixels.show();

    delay(arrSpeed[buttonPushCounter]); // Delay for a period of time (in milliseconds).

    if (i == NUMPIXELS)
    {
      i = 0;
    }
  }
}