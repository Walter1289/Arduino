// Variables de tiempo
int horas = 0;
int minutos = 0;
int segundos = 0;
unsigned long tiempoAnterior = 0;

const int pulsador_inicio = 8;
const int pulsador_pausa = 9;
const int ledVerde = 6;
const int ledRojo = 7;

bool cronometroActivo = false;
bool estadoAnteriorInicio = false;
bool estadoAnteriorPausa = false;

void setup() {
  Serial.begin(9600);
  pinMode(pulsador_inicio, INPUT);
  pinMode(pulsador_pausa, INPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRojo, OUTPUT);

  digitalWrite(ledRojo, HIGH);  // Cronómetro empieza detenido
  digitalWrite(ledVerde, LOW);
}

void loop() {
  // Detectar botón de INICIO
  bool estadoInicio = digitalRead(pulsador_inicio);
  if (estadoInicio && !estadoAnteriorInicio) {
    // Reiniciar y activar cronómetro
    horas = 0;
    minutos = 0;
    segundos = 0;
    tiempoAnterior = millis();
    cronometroActivo = true;

    digitalWrite(ledRojo, LOW);
    digitalWrite(ledVerde, HIGH);
  }
  estadoAnteriorInicio = estadoInicio;

  // Detectar botón de PAUSA
  bool estadoPausa = digitalRead(pulsador_pausa);
  if (estadoPausa && !estadoAnteriorPausa) {
    cronometroActivo = !cronometroActivo;

    if (cronometroActivo) {
      tiempoAnterior = millis(); // reanuda sin salto
      digitalWrite(ledRojo, LOW);
      digitalWrite(ledVerde, HIGH);
    } else {
      digitalWrite(ledRojo, HIGH);
      digitalWrite(ledVerde, LOW);
    }
  }
  estadoAnteriorPausa = estadoPausa;

  // Lógica de tiempo
  if (cronometroActivo) {
    if (millis() - tiempoAnterior >= 1000) {
      tiempoAnterior += 1000;
      segundos++;

      if (segundos == 60) {
        segundos = 0;
        minutos++;
        if (minutos == 60) {
          minutos = 0;
          horas++;
        }
      }

      // Imprimir HH:MM:SS
      if (horas < 10) Serial.print("0");
      Serial.print(horas);
      Serial.print(":");
      if (minutos < 10) Serial.print("0");
      Serial.print(minutos);
      Serial.print(":");
      if (segundos < 10) Serial.print("0");
      Serial.println(segundos);
    }

    // Parpadeo del LED verde cada 500 ms
    if ((millis() / 500) % 2 == 0) {
      digitalWrite(ledVerde, HIGH);
    } else {
      digitalWrite(ledVerde, LOW);
    }
  }
}
