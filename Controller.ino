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

  if (xData < thresholdLow) {
    Serial.print('A');
  } else if (xData > thresholdHigh) {
    Serial.print('D');
  } else if (yData < thresholdLow) {
    Serial.print('W');
  } else if (yData > thresholdHigh) {
    Serial.print('S');
  } else if (switchData == LOW) {
    Serial.print('R');
  }

  delay(100);
}
