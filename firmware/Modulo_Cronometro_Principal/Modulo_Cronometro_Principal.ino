#define buzer 45
int tempo_ms = 0;
int minuto_decimal = 0;
int minuto_unidade = 0;
int segundo_decimal = 0;
int segundo_unidade = 0;
int milissegundo_decimal = 0;

int segmentA1 = 52;
int segmentB1 = 50;
int segmentC1 = 40;
int segmentD1 = 48;
int segmentE1 = 38;
int segmentF1 = 42;
int segmentG1 = 44;

int segmentA2 = 8;
int segmentB2 = 9;
int segmentC2 = 2;
int segmentD2 = 3;
int segmentE2 = 4;
int segmentF2 = 5;
int segmentG2 = 6;

int segmentA3 = A11;
int segmentB3 = A10;
int segmentC3 = 32;
int segmentD3 = 46;
int segmentE3 = 30;
int segmentF3 = 36;
int segmentG3 = 34;

int segmentA4 = A7;
int segmentB4 = A6;
int segmentC4 = A13;
int segmentD4 = A12;
int segmentE4 = A15;
int segmentF4 = A5;
int segmentG4 = A4;

int segmentA5 = A3;
int segmentB5 = A2;
int segmentC5 = A9;
int segmentD5 = A8;
int segmentE5 = A14;
int segmentF5 = A0;
int segmentG5 = A1;

int tempo_inicial;
bool paused = false;
bool cronometro_iniciado = false;


void setup() {
  Serial.begin(9600);
  pinMode(buzer, OUTPUT);
  Serial.println("ai");

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

  pinMode(segmentA3, OUTPUT);
  pinMode(segmentB3, OUTPUT);
  pinMode(segmentC3, OUTPUT);
  pinMode(segmentD3, OUTPUT);
  pinMode(segmentE3, OUTPUT);
  pinMode(segmentF3, OUTPUT);
  pinMode(segmentG3, OUTPUT);

  pinMode(segmentA3, OUTPUT);
  pinMode(segmentB3, OUTPUT);
  pinMode(segmentC3, OUTPUT);
  pinMode(segmentD3, OUTPUT);
  pinMode(segmentE3, OUTPUT);
  pinMode(segmentF3, OUTPUT);
  pinMode(segmentG3, OUTPUT);

  pinMode(segmentA4, OUTPUT);
  pinMode(segmentB4, OUTPUT);
  pinMode(segmentC4, OUTPUT);
  pinMode(segmentD4, OUTPUT);
  pinMode(segmentE4, OUTPUT);
  pinMode(segmentF4, OUTPUT);
  pinMode(segmentG4, OUTPUT);

  pinMode(segmentA5, OUTPUT);
  pinMode(segmentB5, OUTPUT);
  pinMode(segmentC5, OUTPUT);
  pinMode(segmentD5, OUTPUT);
  pinMode(segmentE5, OUTPUT);
  pinMode(segmentF5, OUTPUT);
  pinMode(segmentG5, OUTPUT);

  displayNumber(0, 1); // Inicializa o primeiro display no número zero
  displayNumber(0, 2); // Inicializa o segundo display no número zero
  displayNumber(0, 3); // Inicializa o primeiro display no número zero
  displayNumber(0, 4); // Inicializa o primeiro display no número zero
  displayNumber(0, 5); // Inicializa o primeiro display no número zero
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
  } if (display == 2) {
    segmentA = segmentA2;
    segmentB = segmentB2;
    segmentC = segmentC2;
    segmentD = segmentD2;
    segmentE = segmentE2;
    segmentF = segmentF2;
    segmentG = segmentG1;
  } if (display == 3) {
    segmentA = segmentA3;
    segmentB = segmentB3;
    segmentC = segmentC3;
    segmentD = segmentD3;
    segmentE = segmentE3;
    segmentF = segmentF3;
    segmentG = segmentG3;
  } if (display == 4) {
    segmentA = segmentA4;
    segmentB = segmentB4;
    segmentC = segmentC4;
    segmentD = segmentD4;
    segmentE = segmentE4;
    segmentF = segmentF4;
    segmentG = segmentG4;
  } else {
    segmentA = segmentA5;
    segmentB = segmentB5;
    segmentC = segmentC5;
    segmentD = segmentD5;
    segmentE = segmentE5;
    segmentF = segmentF5;
    segmentG = segmentG5;
  }

  // Desliga todos os segmentos primeiro
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
    if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    if (input.toInt() > 0) {
      tempo_inicial = input.toInt();
      cronometro_iniciado = true;
      paused = false;
    }
  }
  
  while (cronometro_iniciado) {
    if (Serial.available() > 0) {
      String input = Serial.readStringUntil('\n');
      
      if (input.equalsIgnoreCase("Crescente")) {
        tempo_ms = 0;
    while (tempo_ms <= tempo_inicial * 600) { // Contagem ajustada para 100 ms

    if (Serial.available() > 0) {
        String command = Serial.readStringUntil('\n');
        if (command.equalsIgnoreCase("RESETAR")) {
          displayNumber(0, 1);
          displayNumber(0, 2);
          displayNumber(0, 3);
          displayNumber(0, 4);
          displayNumber(0, 5);
          digitalWrite(buzer, LOW);
          cronometro_iniciado = false;
          return;
        } else if (command.equalsIgnoreCase("PAUSAR")) {
          paused = !paused;
        }
      }
      if (paused) continue;

      milissegundo_decimal = (tempo_ms % 10); // Milissegundos (0 a 9)
      segundo_unidade = (tempo_ms / 10) % 10; // Unidade de segundos (0 a 9)
      segundo_decimal = (tempo_ms / 100) % 6; // Parte decimal de segundos (0 a 5)
      minuto_unidade = (tempo_ms / 600) % 10; // Unidade de minutos (0 a 9)
      minuto_decimal = (tempo_ms / 6000);     // Parte decimal de minutos (0 a 9)

      displayNumber(minuto_decimal, 5);
      displayNumber(minuto_unidade, 4);
      displayNumber(segundo_decimal, 3);
      displayNumber(segundo_unidade, 2);
      displayNumber(milissegundo_decimal, 1);

      Serial.print(minuto_decimal);
      Serial.print(minuto_unidade);
      Serial.print(":");
      Serial.print(segundo_decimal);
      Serial.print(segundo_unidade);
      Serial.print(":");
      Serial.println(milissegundo_decimal);

      delay(100); // Intervalo de 100 ms
      tempo_ms++;
    }
    digitalWrite(buzer, HIGH);
    delay(3000);
    digitalWrite(buzer, LOW);
    cronometro_iniciado = false;

  }
    

      if (input.equalsIgnoreCase("Decrescente")) {
      tempo_ms = tempo_inicial * 600;
    while (tempo_ms >= 0) {

      if (Serial.available() > 0) {
        String command = Serial.readStringUntil('\n');
        if (command.equalsIgnoreCase("RESETAR")) {
          displayNumber(0, 1);
          displayNumber(0, 2);
          displayNumber(0, 3);
          displayNumber(0, 4);
          displayNumber(0, 5);
          digitalWrite(buzer, LOW);
          cronometro_iniciado = false;
          return;
        } else if (command.equalsIgnoreCase("PAUSAR")) {
          paused = !paused;
        }
      }
      if (paused) continue;

      milissegundo_decimal = (tempo_ms % 10); // Milissegundos (0 a 9)
      segundo_unidade = (tempo_ms / 10) % 10; // Unidade de segundos (0 a 9)
      segundo_decimal = (tempo_ms / 100) % 6; // Parte decimal de segundos (0 a 5)
      minuto_unidade = (tempo_ms / 600) % 10; // Unidade de minutos (0 a 9)
      minuto_decimal = (tempo_ms / 6000);     // Parte decimal de minutos (0 a 9)

      displayNumber(minuto_decimal, 5);
      displayNumber(minuto_unidade, 4);
      displayNumber(segundo_decimal, 3);
      displayNumber(segundo_unidade, 2);
      displayNumber(milissegundo_decimal, 1);

      Serial.print(minuto_decimal);
      Serial.print(minuto_unidade);
      Serial.print(":");
      Serial.print(segundo_decimal);
      Serial.print(segundo_unidade);
      Serial.print(":");
      Serial.println(milissegundo_decimal);

      delay(100); // Intervalo de 100 ms
      tempo_ms--;
    }
    digitalWrite(buzer, HIGH);
    delay(3000);
    digitalWrite(buzer, LOW);
    cronometro_iniciado = false;
    return;
      }
      }
    }
  }