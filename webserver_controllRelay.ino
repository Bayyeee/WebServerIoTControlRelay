#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char *ssid = "Haji";
const char *password = "hajikadap123";

const int relayPin1 = 4;
const int relayPin2 = 5;

AsyncWebServer server(80);

void setup() {
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);

  digitalWrite(relayPin1, HIGH);  // Matikan relay awalnya
  digitalWrite(relayPin2, HIGH);  // Matikan relay awalnya

  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Tampilkan alamat IP web server di Serial Monitor
  Serial.print("Connected to WiFi. IP address: ");
  Serial.println(WiFi.localIP());


  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    String html = "<html><body>";
    html += "<h1>Control Relays</h1>";

    // Tombol untuk mengontrol relay individu
    html += "<button style='background-color: green; color: white'><a href='/relay1/on' style='color: white; text-decoration: none'>Relay 1 On</a></button>";
    html += "<button style='background-color: red; color: white'><a href='/relay1/off' style='color: white; text-decoration: none'>Relay 1 Off</a></button>";
    html += "<br>";
    html += "<button style='background-color: blue; color: white'><a href='/relay2/on' style='color: white; text-decoration: none'>Relay 2 On</a></button>";
    html += "<button style='background-color: orange; color: white'><a href='/relay2/off' style='color: white; text-decoration: none'>Relay 2 Off</a></button>";

    // Tombol untuk mengontrol semua relay bersamaan
    html += "<br>";
    html += "<button style='background-color: purple; color: white'><a href='/all/on' style='color: white; text-decoration: none'>Turn All On</a></button>";
    html += "<button style='background-color: brown; color: white'><a href='/all/off' style='color: white; text-decoration: none'>Turn All Off</a></button>";

    html += "</body></html>";
    request->send(200, "text/html", html);
  });

  // server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
  //   String html = "<html><body>";
  //   html += "<h1>Control Relays</h1>";

  //   // Mengganti tautan dengan tombol dan memberikan warna
  //   html += "<button style='background-color: green; color: white'><a href='/relay1/on' style='color: white; text-decoration: none'>Relay 1 On</a></button>";
  //   html += "<button style='background-color: red; color: white'><a href='/relay1/off' style='color: white; text-decoration: none'>Relay 1 Off</a></button>";
  //   html += "<br>";  // Baris baru
  //   html += "<button style='background-color: blue; color: white'><a href='/relay2/on' style='color: white; text-decoration: none'>Relay 2 On</a></button>";
  //   html += "<button style='background-color: orange; color: white'><a href='/relay2/off' style='color: white; text-decoration: none'>Relay 2 Off</a></button>";

  //   html += "</body></html>";
  //   request->send(200, "text/html", html);
  // });

  server.on("/relay1/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    digitalWrite(relayPin1, LOW);
    String message = "Relay 1 is ON";
    String response = "<html><body><script>alert('" + message + "'); window.history.back();</script></body></html>";
    request->send(200, "text/html", response);
  });

  server.on("/relay1/off", HTTP_GET, [](AsyncWebServerRequest *request) {
    digitalWrite(relayPin1, HIGH);
    String message = "Relay 1 is OFF";
    String response = "<html><body><script>alert('" + message + "'); window.history.back();</script></body></html>";
    request->send(200, "text/html", response);
  });

  server.on("/relay2/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    digitalWrite(relayPin2, LOW);
    String message = "Relay 2 is ON";
    String response = "<html><body><script>alert('" + message + "'); window.history.back();</script></body></html>";
    request->send(200, "text/html", response);
  });

  server.on("/relay2/off", HTTP_GET, [](AsyncWebServerRequest *request) {
    digitalWrite(relayPin2, HIGH);
    String message = "Relay 2 is OFF";
    String response = "<html><body><script>alert('" + message + "'); window.history.back();</script></body></html>";
    request->send(200, "text/html", response);
  });

  server.on("/all/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    digitalWrite(relayPin1, LOW);
    digitalWrite(relayPin2, LOW);
    String message = "All Relays are ON";
    String response = "<html><body><script>alert('" + message + "'); window.history.back();</script></body></html>";
    request->send(200, "text/html", response);
  });

  server.on("/all/off", HTTP_GET, [](AsyncWebServerRequest *request) {
    digitalWrite(relayPin1, HIGH);
    digitalWrite(relayPin2, HIGH);
    String message = "All Relays are OFF";
    String response = "<html><body><script>alert('" + message + "'); window.history.back();</script></body></html>";
    request->send(200, "text/html", response);
  });

  server.begin();
}

void loop() {
  // Tidak ada yang perlu dilakukan di loop
}
