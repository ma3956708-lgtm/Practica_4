#include <Arduino.h>
#include <Wire.h>
#include <ESP32Servo.h>
#include <LiquidCrystal_I2C.h>

Servo servo;

#define SERVO_PIN 18
#define boton_1 32   // Botón para aumentar el ángulo
#define boton_2 33   // Botón para disminuir el ángulo

// Evalúa verdadero cuando el botón se presiona (conecta a GND)
#define PRESSED(x) (digitalRead(x) == LOW)

LiquidCrystal_I2C lcd(0x27, 16, 2);

int angulo = 180; // Variable que guarda los grados actuales (0 a 180)

void setup() {
    Serial.begin(115200);

    // Configuración de botones con resistencia pull-up interna
    pinMode(boton_1, INPUT_PULLUP);
    pinMode(boton_2, INPUT_PULLUP);

    // Inicializar Pantalla LCD
    lcd.init();
    lcd.backlight();

    // Inicializar Servo
    servo.attach(SERVO_PIN);
    servo.write(angulo);

    // Mostrar estado inicial en el LCD
    lcd.setCursor(0, 0);
    lcd.print("Angulo: ");
    lcd.print(angulo);
    lcd.print((char)223); // Símbolo °
}

void loop() {
    bool seMovio = false;

    // Botón 1: Incrementar ángulo
    if (PRESSED(boton_1)) {
        if (angulo < 180) {
            angulo += 15; // Incrementa de 15 en 15 grados (puedes cambiarlo a 1, 5, 10...)
            if (angulo > 180) angulo = 180;
            seMovio = true;
        }
        delay(200); // Pausa para evitar que tome múltiples pulsaciones seguidas
    }

    // Botón 2: Decrementar ángulo
    if (PRESSED(boton_2)) {
        if (angulo > 0) {
            angulo -= 15; // Decrementa de 15 en 15 grados
            if (angulo < 0) angulo = 0;
            seMovio = true;
        }
        delay(200); // Pausa anti-rebote
    }

    // Si cambió el ángulo, actualizamos el Servo y el LCD
    if (seMovio) {
        servo.write(angulo);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Angulo: ");
        lcd.print(angulo);
        lcd.print((char)223); // Símbolo °

        Serial.print("Angulo actual: ");
        Serial.println(angulo);
    }
}