#include <Ultrasonic.h>

//os numeros dos pinos não precisam ser necessariamente estes

//pinos do motor A
#define IN1 2
#define IN2 3
#define PWMA 9

//pinos do motor B
#define IN3 4
#define IN4 5 
#define PWMB 10

//pino do sensor infravermelho;
#define SENSOR_BORDA 6

//pinos do sensor de proximidade
Ultrasonic ultrasonic(7,8);

#define DIAMETRO_RINGUE 77

int distancia;//distancia em cm que vai ser lida pelo sensor ultrassonico
int borda;//recebe o valor do sensor infravermelho para saber se o robo esta em cima da borda

//funcoes que serao utilizadas
void freia() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    analogWrite(PWMA, 0);

    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);
    analogWrite(PWMB, 0);
}

void vai_para_tras(int velocidade) {

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(PWMA, velocidade);

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(PWMB, velocidade);
}

void vai_para_frente(int velocidade) {

    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(PWMA, velocidade);

    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(PWMB, velocidade);
}

void procura(int velocidade) {

    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(PWMA, 128);

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(PWMB, 128);
}

void setup() {
    
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(PWMA, OUTPUT);

    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(PWMB, OUTPUT);

    pinMode(SENSOR_BORDA, INPUT);
    delay(5000);
}

void loop() {

    borda = digitalRead(SENSOR_BORDA);// lendo o valor do sensor infravermelho
    
    //caso o robo esteja em cima da linha
    if (borda) {
        freia();
        delay(500);

        vai_para_tras(128);
        delay(500);
    }

    distancia = ultrasonic.read();// lendo a distancia dos sensor ultrassonico
    //caso o robo inimigo esteja na frente do robo
    if (distancia < DIAMETRO_RINGUE) {
        vai_para_frente(200);
        while (distancia < DIAMETRO_RINGUE)
            distancia = ultrasonic.read();
    }

    //em outros casos o robo gira em torno do proprio eixo para procurar o robo inimigo
    procura(128);
}

