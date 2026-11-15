int segmentA1 = 2;
int segmentB1 = 3;
int segmentC1 = 4;
int segmentD1 = 5;
int segmentE1 = 6;
int segmentF1 = 8;
int segmentG1 = 7;

int segmentA2 = 9;
int segmentB2 = 10;
int segmentC2 = 11;
int segmentD2 = 12;
int segmentE2 = 13;
int segmentF2 = A5;
int segmentG2 = A4;

int ledPin = A0;

int buttonPinIncrement = A2;
int buttonPinDecrement = A1;
int buttonPinReset = A3;

int count = 0;

void setup() {
  Serial.begin(9600);

  pinMode(segmentA1, OUTPUT);
  pinMode(segmentB1, OUTPUT);
  pinMode(segmentC1, OUTPUT);
  pinMode(segmentD1, OUTPUT);
  pinMode(segmentE1, OUTPUT);
  pinMode(segmentF1, OUTPUT);
  pinMode(segmentG1, OUTPUT);

  pinMode(segmentA2, OUTPUT);
  pinMode(segmentB2, OUTPUT);
  pinMode(segmentC2, OUTPUT);
  pinMode(segmentD2, OUTPUT);
  pinMode(segmentE2, OUTPUT);
  pinMode(segmentF2, OUTPUT);
  pinMode(segmentG2, OUTPUT);

  pinMode(ledPin, OUTPUT);
  
  pinMode(buttonPinIncrement, INPUT_PULLUP);
  pinMode(buttonPinDecrement, INPUT_PULLUP);
  pinMode(buttonPinReset, INPUT_PULLUP);

  displayNumber(0, 1);
  displayNumber(0, 2);
}

void displayNumber(int num, int display) {
  int segmentA, segmentB, segmentC, segmentD, segmentE, segmentF, segmentG;

  if (display == 1) {
    segmentA = segmentA1;
    segmentB = segmentB1;
    segmentC = segmentC1;
    segmentD = segmentD1;
    segmentE = segmentE1;
    segmentF = segmentF1;
    segmentG = segmentG1;
  } else {
    segmentA = segmentA2;
    segmentB = segmentB2;
    segmentC = segmentC2;
    segmentD = segmentD2;
    segmentE = segmentE2;
    segmentF = segmentF2;
    segmentG = segmentG2;
  }

  digitalWrite(segmentA, LOW);
  digitalWrite(segmentB, LOW);
  digitalWrite(segmentC, LOW);
  digitalWrite(segmentD, LOW);
  digitalWrite(segmentE, LOW);
  digitalWrite(segmentF, LOW);
  digitalWrite(segmentG, LOW);

  switch (num) {
    case 0:
      digitalWrite(segmentA, HIGH);
      digitalWrite(segmentB, HIGH);
      digitalWrite(segmentC, HIGH);
      digitalWrite(segmentD, HIGH);
      digitalWrite(segmentE, HIGH);
      digitalWrite(segmentF, HIGH);
      digitalWrite(segmentG, LOW);
      break;
    case 1:
      digitalWrite(segmentA, LOW);
      digitalWrite(segmentB, HIGH);
      digitalWrite(segmentC, HIGH);
      digitalWrite(segmentD, LOW);
      digitalWrite(segmentE, LOW);
      digitalWrite(segmentF, LOW);
      digitalWrite(segmentG, LOW);
      break;
    case 2:
      digitalWrite(segmentA, HIGH);
      digitalWrite(segmentB, HIGH);
      digitalWrite(segmentC, LOW);
      digitalWrite(segmentD, HIGH);
      digitalWrite(segmentE, HIGH);
      digitalWrite(segmentF, LOW);
      digitalWrite(segmentG, HIGH);
      break;
    case 3:
      digitalWrite(segmentA, HIGH);
      digitalWrite(segmentB, HIGH);
      digitalWrite(segmentC, HIGH);
      digitalWrite(segmentD, HIGH);
      digitalWrite(segmentE, LOW);
      digitalWrite(segmentF, LOW);
      digitalWrite(segmentG, HIGH);
      break;
    case 4:
      digitalWrite(segmentA, LOW);
      digitalWrite(segmentB, HIGH);
      digitalWrite(segmentC, HIGH);
      digitalWrite(segmentD, LOW);
      digitalWrite(segmentE, LOW);
      digitalWrite(segmentF, HIGH);
      digitalWrite(segmentG, HIGH);
      break;
    case 5:
      digitalWrite(segmentA, HIGH);
      digitalWrite(segmentB, LOW);
      digitalWrite(segmentC, HIGH);
      digitalWrite(segmentD, HIGH);
      digitalWrite(segmentE, LOW);
      digitalWrite(segmentF, HIGH);
      digitalWrite(segmentG, HIGH);
      break;
    case 6:
      digitalWrite(segmentA, HIGH);
      digitalWrite(segmentB, LOW);
      digitalWrite(segmentC, HIGH);
      digitalWrite(segmentD, HIGH);
      digitalWrite(segmentE, HIGH);
      digitalWrite(segmentF, HIGH);
      digitalWrite(segmentG, HIGH);
      break;
    case 7:
      digitalWrite(segmentA, HIGH);
      digitalWrite(segmentB, HIGH);
      digitalWrite(segmentC, HIGH);
      digitalWrite(segmentD, LOW);
      digitalWrite(segmentE, LOW);
      digitalWrite(segmentF, LOW);
      digitalWrite(segmentG, LOW);
      break;
    case 8:
      digitalWrite(segmentA, HIGH);
      digitalWrite(segmentB, HIGH);
      digitalWrite(segmentC, HIGH);
      digitalWrite(segmentD, HIGH);
      digitalWrite(segmentE, HIGH);
      digitalWrite(segmentF, HIGH);
      digitalWrite(segmentG, HIGH);
      break;
    case 9:
      digitalWrite(segmentA, HIGH);
      digitalWrite(segmentB, HIGH);
      digitalWrite(segmentC, HIGH);
      digitalWrite(segmentD, HIGH);
      digitalWrite(segmentE, LOW);
      digitalWrite(segmentF, HIGH);
      digitalWrite(segmentG, HIGH);
      break;
    default:
      digitalWrite(segmentA, LOW);
      digitalWrite(segmentB, LOW);
      digitalWrite(segmentC, LOW);
      digitalWrite(segmentD, LOW);
      digitalWrite(segmentE, LOW);
      digitalWrite(segmentF, LOW);
      digitalWrite(segmentG, LOW);
      break;
  }
}

void loop() {
  
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n'); // Ler até a nova linha

    if (command.equals("AU_PONT_LO")) { // Aumentar
      if (count < 199) {
        count++;
      }
    } else if (command.equals("DI_PONT_LO")) { // Diminuir
      if (count > 0) {
        count--;
      }
    } else if (command.equals("RESETAR")) { // Resetar
      count = 0;
    }

    updateDisplay();
  }
  
  if (count >= 100) {
    digitalWrite(ledPin, HIGH);
   // displayNumber(0, 2); // Apagar o segundo display ao atingir 100
  } else {
    digitalWrite(ledPin, LOW);
    displayNumber(count % 10, 2); // Mostrar unidade se count < 100
  }
}

void updateDisplay() {
  if (count <= 99) {
  int tens = count / 10;
  int units = count % 10;
  displayNumber(tens, 1);
  displayNumber(units, 2);
  Serial.println(count);
  }
  
  if (count >= 100){
  int tens = (count / 10) % 10;
  int units = count % 10;
  displayNumber(tens, 1);
  displayNumber(units, 2);
  Serial.println(count);
    
  }
}
