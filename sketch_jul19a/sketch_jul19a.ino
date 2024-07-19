#include <DHT.h>
#include <Wire.h>

// Définir les broches
#define DHTPIN 8
#define DHTTYPE DHT11  // ou DHT22
#define BLUE_LED 10
#define RED_LED 11
#define BUZZER_PIN 9

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // Lire les valeurs du capteur DHT
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Vérifier si les lectures sont valides
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Erreur de lecture du capteur DHT");
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BLUE_LED, LOW);
    tone(BUZZER_PIN, 1000); // Allumer le buzzer
  } else {
    Serial.print("Humidité: ");
    Serial.print(humidity);
    Serial.print("%  Température: ");
    Serial.print(temperature);
    Serial.println("°C");

    digitalWrite(RED_LED, LOW);
    digitalWrite(BLUE_LED, HIGH);
    noTone(BUZZER_PIN); // Éteindre le buzzer

    // Envoyer les données au port série pour le traitement Python
    Serial.print(humidity);
    Serial.print(",");
    Serial.print(temperature);
    Serial.print(",");
    Serial.println(millis()); // Temps actuel en millisecondes depuis le démarrage de l'Arduino
  }
  delay(2000); // Attendre 2 secondes entre chaque lecture
}
