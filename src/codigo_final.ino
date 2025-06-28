#include <Servo.h>

// 🌐 Pines ultrasónicos
const int pinUltraBoomFrente = 7;
const int pinEcoFrente = 6;
const int pinUltraBoomDerecha = 11;
const int pinEcoDerecha = 10;
const int pinUltraBoomIzquierda = 13;
const int pinEcoIzquierda = 12;

long ecoFrente, ecoDerecha, ecoIzquierda;
long distFantasmaF, distNinjaR, distNinjaL;

const int numLecturas = 5;
int cacheDerecha[numLecturas];
int cacheIzquierda[numLecturas];
long promedioDer, promedioIzq;

long peligroFrontal = 50;
long peligroDer = 35;
long peligroIzq = 35;

// 🎨 Color sensor vibes
#define pinColorS0 4
#define pinColorS1 A3
#define pinColorS2 A4
#define pinColorS3 A5
#define pinColorOUT 8

int rojoMin = 57, rojoMax = 160;
int verdeMin = 63, verdeMax = 230;
int azulMin = 53, azulMax = 198;

int pulsoRojo, pulsoVerde, pulsoAzul;
int nivelRojo, nivelVerde, nivelAzul;

unsigned long cronometroColor;
unsigned long pausaColor = 50;
bool tiempoParaColor = true;
int ordenColor = 0;
bool lecturaColorLista = false;
bool cazandoLinea = true;
int lineasCazadas = 0;
bool activadorCaza = true;
unsigned long tCazaActual;
unsigned long tCazaMax = 5000;
bool finalListo = true;
unsigned long tFinalAhora;
unsigned long tFinalMax = 3000;

// 🏎️ Motor DC
#define pinMotorA 2
#define pinMotorB 3
#define pinMotorVelocidad 5
const int motorVelMaxNormal = 230;
const int motorVelMaxGiro = 250;
int tiempoGiroTotal = 1800;
int retrocesoTime = 1400;
bool giraHorario = false;
bool primerGiro = true;
int distanciaFantasma = 7;

// 👀 Sensores infrarrojos diagonales
#define pinIRIzqDiag A1
#define pinIRDerDiag A2
bool alertaIzq = true;
bool alertaDer = true;
bool alertaDiagIzq = true;
bool alertaDiagDer = true;

// ⏱️ Temporizadores
unsigned long relojSensores;
unsigned long delaySensado = 100;
bool sensoresListos = true;
bool enGiro = false;

unsigned long relojGiro;
unsigned long delayGiro = 500;
bool okParaGirar = true;

// 🎯 Servo
Servo servoNeck;
int correccionDiagonal = 0;
int anguloDerecha = 120;
int anguloDerechaCorr = anguloDerecha - correccionDiagonal;
int anguloIzquierda = 70;
int anguloIzquierdaCorr = anguloIzquierda + correccionDiagonal;
int anguloDerechaSuave = 120;
int anguloIzquierdaSuave = 70;
int anguloCentro = 95;
bool giroPorDiagonal = false;

// 🔘 Botón de inicio
const int botonDespegue = A0;
int estadoBotonActual;
int estadoBotonPrevio = LOW;
unsigned long tiempoAntirebote = 0;
unsigned long antireboteDelay = 50;
bool sistemaEncendido = true;
bool sistemaAnterior = true;
bool arrancarProceso = false;

// 🌟 SETUP
void setup() {
  pinMode(botonDespegue, INPUT_PULLUP);

  pinMode(pinUltraBoomFrente, OUTPUT);
  pinMode(pinEcoFrente, INPUT);
  pinMode(pinUltraBoomDerecha, OUTPUT);
  pinMode(pinEcoDerecha, INPUT);
  pinMode(pinUltraBoomIzquierda, OUTPUT);
  pinMode(pinEcoIzquierda, INPUT);

  pinMode(pinColorS0, OUTPUT);
  pinMode(pinColorS1, OUTPUT);
  pinMode(pinColorS2, OUTPUT);
  pinMode(pinColorS3, OUTPUT);
  pinMode(pinColorOUT, INPUT);
  digitalWrite(pinColorS0, HIGH);
  digitalWrite(pinColorS1, LOW);

  pinMode(pinMotorA, OUTPUT);
  pinMode(pinMotorB, OUTPUT);
  pinMode(pinMotorVelocidad, OUTPUT);
  digitalWrite(pinMotorA, LOW);
  digitalWrite(pinMotorB, LOW);
  analogWrite(pinMotorVelocidad, 0);

  servoNeck.attach(9);
  servoNeck.write(anguloCentro);
  delay(1000);
}

// 🟢 Botón de arranque
void presionarBotonDespegue() {
  int lectura = digitalRead(botonDespegue);
  if (lectura != estadoBotonPrevio) {
    tiempoAntirebote = millis();
  }
  if ((millis() - tiempoAntirebote) > antireboteDelay) {
    if (lectura != estadoBotonActual) {
      estadoBotonActual = lectura;
      if (estadoBotonActual == LOW) {
        sistemaEncendido = !sistemaEncendido;
      }
    }
  }
  estadoBotonPrevio = lectura;
}

// 🎯 Ultrasonido frontal
void escaneoFrente() {
  digitalWrite(pinUltraBoomFrente, LOW);
  delay(5);
  digitalWrite(pinUltraBoomFrente, HIGH);
  delay(10);
  digitalWrite(pinUltraBoomFrente, LOW);
  ecoFrente = pulseIn(pinEcoFrente, HIGH);
  distFantasmaF = (ecoFrente * 0.034) / 2;
}

// 🎯 Ultrasonido derecho
void escaneoDerecha() {
  digitalWrite(pinUltraBoomDerecha, LOW);
  delay(5);
  digitalWrite(pinUltraBoomDerecha, HIGH);
  delay(10);
  digitalWrite(pinUltraBoomDerecha, LOW);
  ecoDerecha = pulseIn(pinEcoDerecha, HIGH);
  distNinjaR = (ecoDerecha * 0.034) / 2;
}

// 🎯 Ultrasonido izquierdo
void escaneoIzquierda() {
  digitalWrite(pinUltraBoomIzquierda, LOW);
  delay(5);
  digitalWrite(pinUltraBoomIzquierda, HIGH);
  delay(10);
  digitalWrite(pinUltraBoomIzquierda, LOW);
  ecoIzquierda = pulseIn(pinEcoIzquierda, HIGH);
  distNinjaL = (ecoIzquierda * 0.034) / 2;
}

// 🔁 Filtro lateral
void filtroNinjaSide() {
  for (int i = 0; i < numLecturas; i++) {
    escaneoDerecha();
    cacheDerecha[i] = distNinjaR;
    delay(30);
  }
  promedioDer = 0;
  for (int i = 0; i < numLecturas; i++) {
    promedioDer += cacheDerecha[i];
  }
  promedioDer /= numLecturas;
  delay(30);
  for (int i = 0; i < numLecturas; i++) {
    escaneoIzquierda();
    cacheIzquierda[i] = distNinjaL;
    delay(30);
  }
  promedioIzq = 0;
  for (int i = 0; i < numLecturas; i++) {
    promedioIzq += cacheIzquierda[i];
  }
  promedioIzq /= numLecturas;
  delay(30);
}

// 👀 Check de obstáculos
void barridoObstaculos() {
  if (sensoresListos) {
    sensoresListos = false;
    relojSensores = millis();
  }
  if ((millis() - relojSensores) > delaySensado) {
    escaneoDerecha();
    escaneoIzquierda();
    alertaDiagDer = digitalRead(pinIRDerDiag);
    alertaDiagIzq = digitalRead(pinIRIzqDiag);
    escaneoFrente();
    if (distFantasmaF < peligroFrontal) {
      enGiro = true;
    } else if (!alertaDiagDer || !alertaDiagIzq) {
      giroPorDiagonal = true;
      enGiro = true;
    } else {
      enGiro = false;
    }
    sensoresListos = true;
  }
}

// 🧠 Decisión de giro
void elegirCaminoLibre() {
  if (okParaGirar) {
    okParaGirar = false;
    relojGiro = millis();
  }
  if ((millis() - relojGiro) > delayGiro) {
    if (primerGiro) {
      filtroNinjaSide();
      if (promedioDer > promedioIzq) {
        if (giroPorDiagonal) {
          girarCabeza(anguloDerechaCorr);
        } else {
          girarCabeza(anguloDerecha);
        }
                avanzar();
        delay(tiempoGiroTotal);
        giraHorario = true;
        enGiro = false;
        okParaGirar = true;
        giroPorDiagonal = false;
        primerGiro = false;
      } else if (promedioDer < promedioIzq) {
        if (giroPorDiagonal) {
          girarCabeza(anguloIzquierdaCorr);
        } else {
          girarCabeza(anguloIzquierda);
        }
        avanzar();
        delay(tiempoGiroTotal);
        giraHorario = false;
        enGiro = false;
        okParaGirar = true;
        giroPorDiagonal = false;
        primerGiro = false;
      }
    } else {
      filtroNinjaSide();
      if (giraHorario) {
        if (promedioDer > promedioIzq - distanciaFantasma) {
          girarCabeza(anguloDerechaCorr);
          avanzar();
          delay(tiempoGiroTotal);
          enGiro = false;
          okParaGirar = true;
          giroPorDiagonal = false;
        } else {
          girarCabeza(anguloIzquierdaCorr);
          avanzar();
          delay(tiempoGiroTotal);
          giraHorario = false;
          enGiro = false;
          okParaGirar = true;
          giroPorDiagonal = false;
        }
      } else {
        if (promedioDer - distanciaFantasma > promedioIzq) {
          girarCabeza(anguloDerechaCorr);
          avanzar();
          delay(tiempoGiroTotal);
          giraHorario = true;
          enGiro = false;
          okParaGirar = true;
          giroPorDiagonal = false;
        } else {
          girarCabeza(anguloIzquierdaCorr);
          avanzar();
          delay(tiempoGiroTotal);
          giraHorario = false;
          enGiro = false;
          okParaGirar = true;
          giroPorDiagonal = false;
        }
      }
    }
  } else {
    girarCabeza(anguloCentro);
    retroceder();
    delay(retrocesoTime);
    frenarTodo();
  }
}

// 🖌️ Cabeza gira
void girarCabeza(int anguloDestino) {
  servoNeck.write(anguloDestino);
}

// 🛵 Movimiento
void avanzar() {
  analogWrite(pinMotorVelocidad, enGiro ? motorVelMaxGiro : motorVelMaxNormal);
  digitalWrite(pinMotorA, HIGH);
  digitalWrite(pinMotorB, LOW);
}

void retroceder() {
  analogWrite(pinMotorVelocidad, motorVelMaxNormal);
  digitalWrite(pinMotorA, LOW);
  digitalWrite(pinMotorB, HIGH);
}

void frenarTodo() {
  digitalWrite(pinMotorA, LOW);
  digitalWrite(pinMotorB, LOW);
}

// 🌈 Rutinas de color (simplificadas)
int getRedPW() {
  digitalWrite(pinColorS2, LOW);
  digitalWrite(pinColorS3, LOW);
  return pulseIn(pinColorOUT, LOW);
}

int getGreenPW() {
  digitalWrite(pinColorS2, HIGH);
  digitalWrite(pinColorS3, HIGH);
  return pulseIn(pinColorOUT, LOW);
}

int getBluePW() {
  digitalWrite(pinColorS2, LOW);
  digitalWrite(pinColorS3, HIGH);
  return pulseIn(pinColorOUT, LOW);
}

// 🎯 Detección de línea naranja
void analizarColor() {
  if (tiempoParaColor) {
    tiempoParaColor = false;
    cronometroColor = millis();
  }
  if ((millis() - cronometroColor) > pausaColor) {
    if (ordenColor == 0) {
      pulsoRojo = getRedPW();
      nivelRojo = map(pulsoRojo, rojoMin, rojoMax, 255, 0);
    } else if (ordenColor == 1) {
      pulsoVerde = getGreenPW();
      nivelVerde = map(pulsoVerde, verdeMin, verdeMax, 255, 0);
    } else if (ordenColor == 2) {
      pulsoAzul = getBluePW();
      nivelAzul = map(pulsoAzul, azulMin, azulMax, 255, 0);
    }
    tiempoParaColor = true;
    ordenColor++;
    if (ordenColor > 2) {
      lecturaColorLista = true;
      ordenColor = 0;
    }
  }
}

void detectarLinea() {
  if (cazandoLinea) {
    analizarColor();
    if (lecturaColorLista) {
      lecturaColorLista = false;
      if (nivelRojo >= 50 && nivelVerde < 50 && nivelVerde > -20 && nivelAzul < 50) {
        lineasCazadas++;
        cazandoLinea = false;
        activadorCaza = true;
      }
    }
  } else {
    if (activadorCaza) {
      activadorCaza = false;
      tCazaActual = millis();
    }
    if ((millis() - tCazaActual) > tCazaMax) {
      cazandoLinea = true;
    }
  }
}

void detenerTras3Vueltas() {
  if (lineasCazadas == 12) {
    if (finalListo) {
      finalListo = false;
      tFinalAhora = millis();
    }
    if ((millis() - tFinalAhora) > tFinalMax) {
      arrancarProceso = false;
      lineasCazadas = 0;
      finalListo = true;
    }
  }
}

// 🔄 LOOP PRINCIPAL
void loop() {
  if (!arrancarProceso) {
    frenarTodo();
    presionarBotonDespegue();
    if (sistemaEncendido != sistemaAnterior) {
      sistemaAnterior = sistemaEncendido;
      arrancarProceso = true;
      delay(500);
    }
  } else {
    detenerTras3Vueltas();
    detectarLinea();
    if (!enGiro) {
      barridoObstaculos();
      if (distNinjaL < peligroIzq) {
        girarCabeza(anguloDerechaSuave);
        avanzar();
      } else if (distNinjaR < peligroDer) {
        girarCabeza(anguloIzquierdaSuave);
        avanzar();
      } else if (distNinjaR > peligroDer && distNinjaL > peligroIzq) {
        girarCabeza(anguloCentro);
        avanzar();
      } else if (distNinjaR < peligroDer && distNinjaL < peligroIzq) {
        girarCabeza(anguloCentro);
        retroceder();
      }
    } else {
      elegirCaminoLibre();
    }
  }
}
 } 

    // tests
    //sonar_test();
    //IR_test();
    //sonarFilter();
    //check_colorLine();
    //detect_line();
}
        
