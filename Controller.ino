const int Switch = 2;
const int x = A0;
const int y = A1;

const int thresholdLow = 300;
const int thresholdHigh = 700;

void setup() {
  Serial.begin(9600);
  pinMode(Switch, INPUT);
  pinMode(x, INPUT);
  pinMode(y, INPUT);
}

void loop() {
  int xData = analogRead(x);
  int yData = analogRead(y);
  int switchData = digitalRead(Switch);

  String output = "";

  if (xData < thresholdLow) {
    output += 's';
  } else if (xData > thresholdHigh) {
    output += 'w';
  }

  if (yData < thresholdLow) {
    output += 'a';
  } else if (yData > thresholdHigh) {
    output += 'd';
  }

  if (output.length() > 0) {
    Serial.println(output);
  }

  delay(100);
}
