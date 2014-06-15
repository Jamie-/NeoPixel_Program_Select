#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal.h>
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Sets LCD's pins
int a = 0;
int b = 1;
int c = 2;
int d = 3;
int e = 4;
int f = 5;
int g = 6;
int h = 7;
int i = 8;
int j = 9;
int k = 10;
int l = 11;
int m = 12;
int n = 13;
int o = 14;
int p = 15;
int z;

const int enter_p = 10;
const int up_p = 9;
const int down_p = 8;

int up = 0;
int down = 0;
int enter = 0;
int scrl = 1;

int current = 0;

void setup() {
  pinMode(enter_p, INPUT);
  pinMode(up_p, INPUT);
  pinMode(down_p, INPUT);
  lcd.begin(16, 2); // Sets LCD size
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Menu:");
  enter = digitalRead(enter_p);
  write_to_lcd();
  if (enter == HIGH) {
    switch (scrl) {
      case 1:
        beach_ball();
        break;
      case 2:
        ldr_to_light();
        break;
      case 3:
        set_colour();
        break;
      case 4:
        blank();
        break;
      default:
        lcd.print(" Error! "+scrl);
        break;    
    }
  }
  delay(100);
}

void beach_ball() {
  while (digitalRead(enter_p) == HIGH) { delay(1); }
  do {
//strip.setPixelColor(i,   r,   g,   b);
  strip.setPixelColor(a, 255, 000, 000);
  strip.setPixelColor(b, 255, 070, 000);
  strip.setPixelColor(c, 255, 180, 000);
  strip.setPixelColor(d, 245, 255, 000);
  strip.setPixelColor(e, 155, 255, 015);
  strip.setPixelColor(f, 050, 255, 015);
  strip.setPixelColor(g, 000, 255, 000);
  strip.setPixelColor(h, 000, 255, 150);
  strip.setPixelColor(i, 000, 255, 255);
  strip.setPixelColor(j, 000, 200, 255);
  strip.setPixelColor(k, 000,  80, 255);
  strip.setPixelColor(l, 000, 000, 255);
  strip.setPixelColor(m, 100, 000, 255);
  strip.setPixelColor(n, 200, 000, 255);
  strip.setPixelColor(o, 255, 000, 255);
  strip.setPixelColor(p, 255, 000, 100);
  strip.setBrightness(16);
  strip.show();
  delay(50);
  rotate();
  enter = digitalRead(enter_p);
  } while (enter == LOW);
  for (z = 0; z < 16; z++) {
    strip.setPixelColor(z, 0, 0, 0);
  }
  strip.show();
  while (digitalRead(enter_p) == HIGH) { delay(1); }
}

void rotate() {
  int extra = a;
  a = b;
  b = c;
  c = d;
  d = e;
  e = f;
  f = g;
  g = h;
  h = i;
  i = j;
  j = k;
  k = l;
  l = m;
  m = n;
  n = o;
  o = p;
  p = extra;
} 

void write_to_lcd() {
  up = digitalRead(up_p);
  down = digitalRead(down_p);
  if (up == HIGH) { // Increments menu option for up button (and loops)
    scrl = scrl + 1;
    if (scrl == 5) { scrl = 1; }
    while (digitalRead(up_p) == HIGH) { delay(1); }
  }
  if (down == HIGH) { // Decrements menu option for down button (and loops)
    scrl = scrl - 1;
    if (scrl == 0) { scrl = 4; }
    while (digitalRead(down_p) == HIGH) { delay(1); }
  }
  
  lcd.setCursor(0, 1);
  switch (scrl) {
    case 1:
      lcd.print("< Rainbow Ball >");
      break;
      
    case 2:
      lcd.print("< LDR to Light >");
      break;
      
    case 3:
      lcd.print("< Set Colour   >");
      break;
      
    case 4:
      lcd.print("< Blank LEDs   >");
      break;
      
    default:
      lcd.print(" Error! ");
      break;  
  }
}

void set_colour() {
  while (digitalRead(enter_p) == HIGH) { delay(1); }
  int red = 0;
  int green = 0;
  int blue = 0;
  lcd.setCursor(0, 0);
  lcd.print("Red?            ");
  get_value();
  red = current;
  lcd.setCursor(0, 0);
  lcd.print("Green?          ");
  get_value();
  green = current;
  lcd.setCursor(0, 0);
  lcd.print("Blue?           ");
  get_value();
  blue = current;
  
  for (z = 0; z < 16; z++) {
    strip.setPixelColor(z, red, green, blue);
  }
  strip.setBrightness(16);
  strip.show();
}

void get_value() {
  current = 0;
  lcd.setCursor(0, 1);
  lcd.print("                ");
  delay(1);
  lcd.setCursor(0, 1);
  lcd.print(current);
  do {
    up = digitalRead(up_p);
    down = digitalRead(down_p);
    
    if (up == HIGH) { // Increments menu option for up button (and loops)
      current = current + 10;
      if (current == 250) { current = 0; }
      while (digitalRead(up_p) == HIGH) { delay(1); }
    }
    if (down == HIGH) { // Decrements menu option for down button (and loops)
      current = current - 10;
      if (current == -10) { current = 250; }
      while (digitalRead(down_p) == HIGH) { delay(1); }
    }
    
    lcd.setCursor(0, 1);
    lcd.print("                ");
    delay(1);
    lcd.setCursor(0, 1);
    lcd.print(current);
    enter = digitalRead(enter_p);
    delay(10);
  } while (enter == LOW);
  while (digitalRead(enter_p) == HIGH) { delay(1); }
}

void blank() {
  for (z = 0; z < 16; z++) {
    strip.setPixelColor(z, 0, 0, 0);
  }
  strip.show();
}

void ldr_to_light() {
  while (digitalRead(enter_p) == HIGH) { delay(1); }
  int ldr;
  do {
    ldr = analogRead(A0);
    strip.setBrightness(ldr / 20);
    strip.show();
    enter = digitalRead(enter_p);
  } while (enter == LOW);
  while (digitalRead(enter_p) == HIGH) { delay(1); }
}

