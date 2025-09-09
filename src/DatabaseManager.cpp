#include "DatabaseManager.h"

// Konstruktor: hier reservieren wir Speicher für das JSON
DatabaseManager::DatabaseManager()
: m_doc(8192)   // 8192 Bytes RAM für JSON (anpassbar!)
{}

// load(): JSON-Text einlesen
bool DatabaseManager::load(const String& json) {
    auto err = deserializeJson(m_doc, json);
    return !err;  // true, wenn kein Fehler aufgetreten ist
}

// exportJson(): JSON wieder als String ausgeben
String DatabaseManager::exportJson() const {
    String out;
    serializeJson(m_doc, out);
    return out;
}
