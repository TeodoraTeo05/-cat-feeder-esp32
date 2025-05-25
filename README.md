# Cat Feeder ESP32

Acest proiect reprezintă un sistem automatizat de hrănire a pisicilor, realizat cu ajutorul unei plăci ESP32. Dispozitivul permite distribuirea hranei și a apei fie prin butoane fizice, fie printr-o interfață web accesibilă de pe orice telefon sau laptop conectat la rețeaua ESP32.

## Funcționalitate

- ESP32 creează o rețea Wi-Fi proprie denumită `CatFeeder_AP`.
- Utilizatorul se conectează la această rețea și accesează pagina web de control prin browser (ex: `http://192.168.4.1`).
- Interfața web conține două butoane:
  - **Give Food** – activează servomotorul pentru deschiderea compartimentului cu hrană.
  - **Give Water** – activează un alt servomotor pentru distribuirea apei.
- În paralel, sistemul permite declanșarea celor două funcții și prin două butoane fizice.
- Fiecare acțiune este confirmată prin:
  - un mesaj pe LCD (`Eat well, my kittens` sau `Drink well, my kittens`)
  - un sunet emis de buzzer.

## Componente hardware folosite

- ESP32 Development Board
- 2 x MicroServo SG90
- LCD 1602 cu interfață I2C
- Buzzer pasiv
- 2 x Butoane fizice (pushbutton)
- Cabluri jumper și breadboard

## Biblioteci utilizate

- `WiFi.h` – pentru crearea rețelei locale Wi-Fi (Access Point)
- `WebServer.h` – pentru implementarea interfeței web HTML
- `ESP32Servo.h` – pentru controlul precis al servomotoarelor
- `LiquidCrystal_I2C.h` – pentru afișajul LCD cu interfață I2C

Toate bibliotecile sunt compatibile cu platforma ESP32 și oferă o integrare facilă în cadrul Arduino IDE.

## Modul de funcționare

1. La pornire, LCD-ul afișează mesajul „Cat Feeder Ready”.
2. ESP32 inițializează rețeaua Wi-Fi și serverul web.
3. Atunci când se primește o cerere HTTP (`/food` sau `/water`) sau este apăsat un buton fizic:
   - Este activat servomotorul corespunzător.
   - Pe LCD este afișat mesajul relevant.
   - Buzzerul emite un semnal sonor scurt.

## Validare

Funcționalitățile au fost testate individual și în combinație:
- Interfața web a fost verificată pe telefon și PC.
- Butoanele fizice au fost testate cu `INPUT_PULLUP` și răspund corect.
- Servomotoarele se mișcă între poziția 0° și 90° cu un `delay` de 1s.
- Mesajele pe LCD și semnalul sonor sunt sincronizate corect.

---

## Demo video

https://youtu.be/CCG9btgEeA4

---


