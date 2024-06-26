const int Switch1 = 2;
const int Switch2 = 3;
const int x1 = A0;
const int x2 = A1;
const int y1 = A2;
const int y2 = A3;

const int thresholdLow = 300;
const int thresholdHigh = 700;

unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
unsigned long debounceDelay = 50; 

unsigned long switchPressTime1 = 0;
unsigned long switchPressTime2 = 0;
unsigned long lastPrintTime1 = 0;
unsigned long lastPrintTime2 = 0;
const unsigned long pressThreshold = 2000; 
const unsigned long repeatInterval = 500; 

bool lastSwitchState1 = HIGH;
bool switchState1 = HIGH;
bool switchPressed1 = false;

bool lastSwitchState2 = HIGH;
bool switchState2 = HIGH;
bool switchPressed2 = false;

void setup() {
  Serial.begin(9600);
  pinMode(Switch1, INPUT_PULLUP);
  pinMode(Switch2, INPUT_PULLUP);
  pinMode(x1, INPUT);
  pinMode(y1, INPUT);
  pinMode(x2, INPUT);
  pinMode(y2, INPUT);
}

void loop() {
  int xData1 = analogRead(x1);
  int yData1 = analogRead(y1);
  int xData2 = analogRead(x2);
  int yData2 = analogRead(y2);

  int reading1 = digitalRead(Switch1);
  int reading2 = digitalRead(Switch2);

  if (reading1 != lastSwitchState1) {
    lastDebounceTime1 = millis();
  }

  if ((millis() - lastDebounceTime1) > debounceDelay) {
    if (reading1 != switchState1) {
      switchState1 = reading1;
      if (switchState1 == LOW) {
        switchPressed1 = true;
        switchPressTime1 = millis();
        lastPrintTime1 = 0;
        Serial.print("L");
      } else {
        switchPressed1 = false;
        switchPressTime1 = 0;
        lastPrintTime1 = 0;
      }
    }
  }

  lastSwitchState1 = reading1;

  if (reading2 != lastSwitchState2) {
    lastDebounceTime2 = millis();
  }

  if ((millis() - lastDebounceTime2) > debounceDelay) {
    if (reading2 != switchState2) {
      switchState2 = reading2;
      if (switchState2 == LOW) {
        switchPressed2 = true;
        switchPressTime2 = millis();
        lastPrintTime2 = 0;
        Serial.print("R");
      } else {
        switchPressed2 = false;
        switchPressTime2 = 0;
        lastPrintTime2 = 0;
      }
    }
  }

  lastSwitchState2 = reading2;

  String output = "";

  if (xData1 < thresholdLow) {
    output += 'w';
  } else if (xData1 > thresholdHigh) {
    output += 's';
  }

  if (yData1 < thresholdLow) {
    output += 'd';
  } else if (yData1 > thresholdHigh) {
    output += 'a';
  }

  if (switchPressed1 && (millis() - switchPressTime1) > pressThreshold) {
    if ((millis() - lastPrintTime1) > repeatInterval) {
      Serial.print("L");
      lastPrintTime1 = millis();
    }
  }

  if (xData2 < thresholdLow) {
    output += 'i';
  } else if (xData2 > thresholdHigh) {
    output += 'k';
  }

  if (yData2 < thresholdLow) {
    output += 'l';
  } else if (yData2 > thresholdHigh) {
    output += 'j';
  }

  if (switchPressed2 && (millis() - switchPressTime2) > pressThreshold) {
    if ((millis() - lastPrintTime2) > repeatInterval) {
      Serial.print("R");
      lastPrintTime2 = millis();
    }
  }

  if (output.length() > 0) {
    Serial.println(output);
  }

  delay(100);
}
