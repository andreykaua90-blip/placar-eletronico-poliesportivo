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

int count1 = 0;
int count2 = 0;

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

  displayNumber(0, 1);
  displayNumber(0, 2);
}

void displayNumber(int num, int display) {
  int segmentA, segmentB, segmentC, segmentD, segmentE, segmentF, segmentG;

  // Seleciona os pinos de acordo com o display
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

  // Desliga todos os segmentos
  digitalWrite(segmentA, LOW);
  digitalWrite(segmentB, LOW);
  digitalWrite(segmentC, LOW);
  digitalWrite(segmentD, LOW);
  digitalWrite(segmentE, LOW);
  digitalWrite(segmentF, LOW);
  digitalWrite(segmentG, LOW);

  // Controla os segmentos para exibir o número
  switch (num % 10) {
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

  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    
   if (input.equals("AU_SET")) {
      if (count2 < 9) {
        count2++;
      }
   }
    else if (input.equals("DI_SET")) {
      if (count2 > 0) {
        count2--;
      }
      }
    else if (input.equals("RESETAR")) {
      Serial.println("RESETAR\n");
      count2 = 0;
      count1 = 0;
    }

    if (input.equals("AU_FAL_VI")) {
      if (count1 < 19) {
        count1++;
      }
    } else if (input.equals("DI_FAL_VI")) {
      if (count1 > 0) {
        count1--;
      }
      }

      if (count1 >= 10) {
      digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

    displayNumber(count1, 1);  // Exibe o número no display 1
    displayNumber(count2, 2);  // Exibe o número no display 2

    if (input.equals("AU_PONT_VI")) {
      Serial.println("AU_PONT_VI\n");
    }
    else if (input.equals("DI_PONT_VI")) {
      Serial.println("DI_PONT_VI\n");
    }
  
}
   }
