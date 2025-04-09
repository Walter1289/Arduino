// C++ code
//
int pinsPWM[3];
int pinPot = 0;

void inicializar(){
  pinsPWM[0]=3;
  pinsPWM[1]=6;
  pinsPWM[2]=9;

}
void setup()
{
  inicializar();
  Serial.begin(9600);
  for (int i = 0; i<3; i++){
    pinMode(pinsPWM[i], OUTPUT);
  }
}

void loop() {
  int valor = analogRead(pinPot);

  // Encender LEDs de forma secuencial según el valor del potenciómetro
  if (valor < 341) {
    // Apagar todos
    for (int i = 0; i < 3; i++) {
      digitalWrite(pinsPWM[i], LOW);
    }
  } else if (valor < 682) {
    // Encender 1 LED
    digitalWrite(pinsPWM[0], HIGH);
    digitalWrite(pinsPWM[1], LOW);
    digitalWrite(pinsPWM[2], LOW);
  } else if (valor < 850) {
    // Encender 2 LEDs
    digitalWrite(pinsPWM[0], HIGH);
    digitalWrite(pinsPWM[1], HIGH);
    digitalWrite(pinsPWM[2], LOW);
  } else {
    // Encender los 3 LEDs
    for (int i = 0; i < 3; i++) {
      digitalWrite(pinsPWM[i], HIGH);
    }
  }
   Serial.println(valor);
  delay(100);
}