#pragma once                 // sorgt dafür, dass die Datei nur 1x eingebunden wird
#include <ArduinoJson.h>     // wir nutzen ArduinoJson zum Parsen
#include <Arduino.h>         // für den Datentyp "String"

class DatabaseManager {
public:
    DatabaseManager();              // Konstruktor

    // JSON laden (z. B. aus NVS oder String)
    bool load(const String& json);

    // JSON wieder als String exportieren (z. B. zurück zur GUI schicken)
    String exportJson() const;

private:
    // JSON-Speicher (hier liegt die geparste Database)
    DynamicJsonDocument m_doc;
};
