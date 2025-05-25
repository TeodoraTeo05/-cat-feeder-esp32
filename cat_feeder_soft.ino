#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>
#include <LiquidCrystal_I2C.h>

// Wi-Fi Access Point
const char* ssid = "CatFeeder_AP";
const char* password = "feedmypet";
WebServer server(80);

// Servos
Servo servoFood;
Servo servoWater;

// I2C LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pushbutton pins
#define BUTTON_FOOD 27
#define BUTTON_WATER 14
#define BUZZER_PIN 4

//Food function
void giveFood() {
  servoFood.write(90);
  delay(1000);
  servoFood.write(0);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Eat well,");
  lcd.setCursor(0, 1);
  lcd.print("my kittens");

  beepBuzzer(); 
}

//Water function
void giveWater() {
  servoWater.write(90);
  delay(1000);
  servoWater.write(0);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Drink well,");
  lcd.setCursor(0, 1);
  lcd.print("my kittens");

  beepBuzzer(); 
}

//Web server
void handleRoot() {
  String html = R"rawliteral(
    <html>
    <head>
      <title>Cat Feeder</title>
      <style>
        body { font-family: sans-serif; text-align: center; background: #f0f0f0; padding-top: 50px; }
        h1 { color: #333; }
        button {
          font-size: 1.5em;
          padding: 20px 40px;
          margin: 20px;
          background-color: #28a745;
          color: white;
          border: none;
          border-radius: 10px;
          width: 80%;
        }
        button:hover {
          background-color: #218838;
        }
      </style>
    </head>
    <body>
      <h1>Cat Feeder</h1>
      <form action='/food' method='GET'><button type='submit'>Give Food</button></form>
      <form action='/water' method='GET'><button type='submit'>Give Water</button></form>
    </body>
    </html>
  )rawliteral";
  server.send(200, "text/html", html);
}

void handleGiveFood() {
  giveFood();
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleGiveWater() {
  giveWater();
  server.sendHeader("Location", "/");
  server.send(303);
}

void beepBuzzer() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(300);
  digitalWrite(BUZZER_PIN, LOW);
}

void setup() {
  Serial.begin(115200);

  // LCD setup
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Cat Feeder Ready");

  // Servo setup
  servoFood.setPeriodHertz(50);
  servoFood.attach(16);
  servoWater.setPeriodHertz(50);
  servoWater.attach(17);

  // Button setup
  pinMode(BUTTON_FOOD, INPUT_PULLUP);
  pinMode(BUTTON_WATER, INPUT_PULLUP);

  // Wi-Fi AP
  WiFi.softAP(ssid, password);
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  // Web routes
  server.on("/", handleRoot);
  server.on("/food", handleGiveFood);
  server.on("/water", handleGiveWater);
  server.begin();

  //buzzer setup
  pinMode(BUZZER_PIN, OUTPUT);

}

void loop() {
  server.handleClient();

  if (digitalRead(BUTTON_FOOD) == LOW) {
    Serial.println("Physical button: GIVE FOOD");
    giveFood();
    delay(500);
  }

  if (digitalRead(BUTTON_WATER) == LOW) {
    Serial.println("Physical button: GIVE WATER");
    giveWater();
    delay(500);
  }
}