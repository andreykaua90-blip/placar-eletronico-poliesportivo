#define T1 9
#define T2 10
#define T3 11
#define T4 12

int segmentA1 = 2;
int segmentB1 = 3;
int segmentC1 = 4;
int segmentD1 = 5;
int segmentE1 = 6;
int segmentF1 = 7;
int segmentG1 = 8;
int ledPin = A0;

int count1 = 0;
int local_cont_T = 0;
int visitante_cont_T = 0;

void setup() {
    Serial.begin(9600);
    pinMode(segmentA1, OUTPUT);
    pinMode(segmentB1, OUTPUT);
    pinMode(segmentC1, OUTPUT);
    pinMode(segmentD1, OUTPUT);
    pinMode(segmentE1, OUTPUT);
    pinMode(segmentF1, OUTPUT);
    pinMode(segmentG1, OUTPUT);
    pinMode(T1, OUTPUT);
    pinMode(T2, OUTPUT);
    pinMode(T3, OUTPUT);
    pinMode(T4, OUTPUT);
    pinMode(ledPin, OUTPUT);

    digitalWrite(segmentA1, LOW);
    digitalWrite(segmentB1, LOW);
    digitalWrite(segmentC1, LOW);
    digitalWrite(segmentD1, LOW);
    digitalWrite(segmentE1, LOW);
    digitalWrite(segmentF1, LOW);
    digitalWrite(segmentG1, LOW);
    digitalWrite(T1, HIGH);
    digitalWrite(T2, HIGH);
    digitalWrite(T3, HIGH);
    digitalWrite(T4, HIGH);

    displayNumber(0, 1);
}

void displayNumber(int num, int display) {
    switch (num % 10) {
        case 0:
            digitalWrite(segmentA1, HIGH);
            digitalWrite(segmentB1, HIGH);
            digitalWrite(segmentC1, HIGH);
            digitalWrite(segmentD1, HIGH);
            digitalWrite(segmentE1, HIGH);
            digitalWrite(segmentF1, HIGH);
            digitalWrite(segmentG1, LOW);
            break;
        case 1:
            digitalWrite(segmentA1, LOW);
            digitalWrite(segmentB1, HIGH);
            digitalWrite(segmentC1, HIGH);
            digitalWrite(segmentD1, LOW);
            digitalWrite(segmentE1, LOW);
            digitalWrite(segmentF1, LOW);
            digitalWrite(segmentG1, LOW);
            break;
        case 2:
            digitalWrite(segmentA1, HIGH);
            digitalWrite(segmentB1, HIGH);
            digitalWrite(segmentC1, LOW);
            digitalWrite(segmentD1, HIGH);
            digitalWrite(segmentE1, HIGH);
            digitalWrite(segmentF1, LOW);
            digitalWrite(segmentG1, HIGH);
            break;
        case 3:
            digitalWrite(segmentA1, HIGH);
            digitalWrite(segmentB1, HIGH);
            digitalWrite(segmentC1, HIGH);
            digitalWrite(segmentD1, HIGH);
            digitalWrite(segmentE1, LOW);
            digitalWrite(segmentF1, LOW);
            digitalWrite(segmentG1, HIGH);
            break;
        case 4:
            digitalWrite(segmentA1, LOW);
            digitalWrite(segmentB1, HIGH);
            digitalWrite(segmentC1, HIGH);
            digitalWrite(segmentD1, LOW);
            digitalWrite(segmentE1, LOW);
            digitalWrite(segmentF1, HIGH);
            digitalWrite(segmentG1, HIGH);
            break;
        case 5:
            digitalWrite(segmentA1, HIGH);
            digitalWrite(segmentB1, LOW);
            digitalWrite(segmentC1, HIGH);
            digitalWrite(segmentD1, HIGH);
            digitalWrite(segmentE1, LOW);
            digitalWrite(segmentF1, HIGH);
            digitalWrite(segmentG1, HIGH);
            break;
        case 6:
            digitalWrite(segmentA1, HIGH);
            digitalWrite(segmentB1, LOW);
            digitalWrite(segmentC1, HIGH);
            digitalWrite(segmentD1, HIGH);
            digitalWrite(segmentE1, HIGH);
            digitalWrite(segmentF1, HIGH);
            digitalWrite(segmentG1, HIGH);
            break;
        case 7:
            digitalWrite(segmentA1, HIGH);
            digitalWrite(segmentB1, HIGH);
            digitalWrite(segmentC1, HIGH);
            digitalWrite(segmentD1, LOW);
            digitalWrite(segmentE1, LOW);
            digitalWrite(segmentF1, LOW);
            digitalWrite(segmentG1, LOW);
            break;
        case 8:
            digitalWrite(segmentA1, HIGH);
            digitalWrite(segmentB1, HIGH);
            digitalWrite(segmentC1, HIGH);
            digitalWrite(segmentD1, HIGH);
            digitalWrite(segmentE1, HIGH);
            digitalWrite(segmentF1, HIGH);
            digitalWrite(segmentG1, HIGH);
            break;
        case 9:
            digitalWrite(segmentA1, HIGH);
            digitalWrite(segmentB1, HIGH);
            digitalWrite(segmentC1, HIGH);
            digitalWrite(segmentD1, HIGH);
            digitalWrite(segmentE1, LOW);
            digitalWrite(segmentF1, HIGH);
            digitalWrite(segmentG1, HIGH);
            break;
        default:
            digitalWrite(segmentA1, LOW);
            digitalWrite(segmentB1, LOW);
            digitalWrite(segmentC1, LOW);
            digitalWrite(segmentD1, LOW);
            digitalWrite(segmentE1, LOW);
            digitalWrite(segmentF1, LOW);
            digitalWrite(segmentG1, LOW);
            break;
    }
}

void loop() {
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');

        if (input.equals("AU_FAL_LO")) {
            if (count1 < 19) {
                count1++;
            }
        } else if (input.equals("DI_FAL_LO")) {
            if (count1 > 0) {
                count1--;
            }
        } else if (input.equals("RESETAR")) {
            Serial.println("RESETAR\n");
            count1 = 0;
            digitalWrite(T1, HIGH);
            digitalWrite(T2, HIGH);
            digitalWrite(T3, HIGH);
            digitalWrite(T4, HIGH);
            local_cont_T = 0;
            visitante_cont_T = 0;
        }

        if (input.equals("AU_VISI")) { 
            if (visitante_cont_T < 2) { 
                visitante_cont_T++; 
            }
        } else if (input.equals("DI_VISI")) { 
            if (visitante_cont_T > 0) { 
                visitante_cont_T--; 
            }
        }

        if (input.equals("AU_LOCA")) { 
            if (local_cont_T < 2) { 
                local_cont_T++; 
            }
        } else if (input.equals("DI_LOCA")) { 
            if (local_cont_T > 0) { 
                local_cont_T--; 
            }
        }

        if (local_cont_T == 1) {
            digitalWrite(T1, LOW);
            digitalWrite(T2, HIGH);
        } else if (local_cont_T == 2) {
            digitalWrite(T1, LOW);
            digitalWrite(T2, LOW);
        } else {
            digitalWrite(T1, HIGH);
            digitalWrite(T2, HIGH);
        }

        if (visitante_cont_T == 1) {
            digitalWrite(T3, LOW);
            digitalWrite(T4, HIGH);
        } else if (visitante_cont_T == 2) {
            digitalWrite(T3, LOW);
            digitalWrite(T4, LOW);
        } else {
            digitalWrite(T3, HIGH);
            digitalWrite(T4, HIGH);
        }

        if (count1 >= 10) {
            digitalWrite(ledPin, HIGH);
        } else {
            digitalWrite(ledPin, LOW);
        }

        if (input.equals("AU_PONT_LO")){
            Serial.println("AU_PONT_LO\n");
        }
        if (input.equals("DI_PONT_LO")){
            Serial.println("DI_PONT_LO\n");
        }

        displayNumber(count1, 1);
    }
}