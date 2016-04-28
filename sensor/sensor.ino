#define data 5
#define clock 4

int ledPin = 3;
int tempPin = 1;
int lightPin = 0;
const int buttonPin = 2;
int i = 0;
int tval, lval;
int buttonState = 0;
int lastState = 0;
bool ON;

void setup()
{
  pinMode(clock, OUTPUT); // make the clock pin an output
  pinMode(data , OUTPUT); // make the data pin an output
  
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  ON = false;
}
void loop()
{
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    // turn LED on:
    if (buttonState != lastState) ON = !ON;
  }
  lastState = buttonState;
  
  if (ON){
    tval = analogRead(tempPin);
    lval = analogRead(lightPin);
    float mv = (tval/1024.0)*5000; 
    float cel = mv/10;
    float farh = (cel*9)/5 + 32;
    int brightness = 100 * lval / 1023;
    
    analogWrite(ledPin, 255 - brightness);
    
    Serial.print("{\"status\" = \"on\" , ");
    Serial.print("\"temperature\" = ");
    Serial.print(cel);
    Serial.print(",");
    Serial.print("\"light\" = ");
    //Serial.print(brightness);
    Serial.print(lval);
    Serial.print("}");
    Serial.println();

    //show number in seveb=n segment
    int k = i%10;
    i++;
    sevenSegmentPrint(k);
  } else {
    
    Serial.println("{\"status\" = \"off\"}");
    analogWrite(ledPin,0);
    sevenSegmentPrint(-1);
  }
  delay(1000);
}




void sevenSegmentPrint(int num){
  switch (num){
    case 1 :
      shiftOut(data, clock, LSBFIRST, B10011110);
      break;
    case 2 :
      shiftOut(data, clock, LSBFIRST, B00100100);
      break;
    case 3 :
      shiftOut(data, clock, LSBFIRST, B00001100);
      break;
    case 4 :
      shiftOut(data, clock, LSBFIRST, B10011000);
      break;
    case 5 :
      shiftOut(data, clock, LSBFIRST, B01001000);
      break;
    case 6 :
      shiftOut(data, clock, LSBFIRST, B01000000);
      break;
    case 7 :
      shiftOut(data, clock, LSBFIRST, B00011110);
      break;
    case 8 :
      shiftOut(data, clock, LSBFIRST, B00000000);
      break;      
    case 9 :
      shiftOut(data, clock, LSBFIRST, B00011000);
      break;
    default :
      shiftOut(data, clock, LSBFIRST, B11111110);
  }
}
