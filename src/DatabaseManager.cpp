#include "DatabaseManager.h"

DatabaseManager::DatabaseManager() : m_loaded(false) {}

// Dateisystem mounten
bool DatabaseManager::begin() {
    if (!LittleFS.begin()) {
        Serial.println("Failed to mount LittleFS");
        return false;
    }
    return true;
}

// JSON laden
bool DatabaseManager::load(const char* path) {
    if (!path) {
        Serial.println("No path provided for loading database");
        return false;
    }

    File file = LittleFS.open(path, "r");
    if (!file) {
        Serial.println("Failed to open database file for reading");
        return false;
    }

    DeserializationError error = deserializeJson(m_doc, file);
    file.close();

    if (error) {
        Serial.print("Failed to parse JSON: ");
        Serial.println(error.c_str());
        return false;
    }

    m_path = String(path);
    m_loaded = true;
    return true;
}

// JSON speichern
bool DatabaseManager::save(const char* path) {
    if (!m_loaded && path == nullptr) {
        Serial.println("No database loaded and no path provided for saving");
        return false;
    }

    const char* savePath = path ? path : m_path.c_str();
    File file = LittleFS.open(savePath, "w");
    if (!file) {
        Serial.println("Failed to open database file for writing");
        return false;
    }

    if (serializeJsonPretty(m_doc, file) == 0) { // Pretty für Lesbarkeit
        Serial.println("Failed to write JSON to file");
        file.close();
        return false;
    }

    file.close();
    return true;
}

// Hilfsfunktion: JSON-Pfad auflösen (für Getter)
JsonVariant DatabaseManager::resolvePath(const char* path) {
    JsonVariant current = m_doc;

    char buffer[128];
    strncpy(buffer, path, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    char* token = strtok(buffer, ".");
    while (token != nullptr) {
        current = current[token];
        token = strtok(nullptr, ".");
    }
    return current;
}

// Hilfsfunktion: Parent-Objekt + Key finden (für Setter)
JsonVariant DatabaseManager::resolveParent(const char* path, String& lastKey) {
    JsonVariant current = m_doc;

    char buffer[128];
    strncpy(buffer, path, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    char* token = strtok(buffer, ".");
    char* prev = token;

    token = strtok(nullptr, ".");
    while (token != nullptr) {
        current = current[prev];
        prev = token;
        token = strtok(nullptr, ".");
    }

    lastKey = prev;
    return current;
}

// Getter
float DatabaseManager::getFloat(const char* path) {
    return resolvePath(path) | 0.0f;
}

int DatabaseManager::getInt(const char* path) {
    return resolvePath(path) | 0;
}

const char* DatabaseManager::getString(const char* path) {
    return resolvePath(path) | "";
}

// Setter
bool DatabaseManager::set(const char* path, int value) {
    String lastKey;
    JsonVariant parent = resolveParent(path, lastKey);
    if (parent.isNull()) return false;

    parent[lastKey] = value;
    return true;
}

bool DatabaseManager::set(const char* path, float value) {
    String lastKey;
    JsonVariant parent = resolveParent(path, lastKey);
    if (parent.isNull()) return false;

    parent[lastKey] = value;
    return true;
}

bool DatabaseManager::set(const char* path, const char* value) {
    String lastKey;
    JsonVariant parent = resolveParent(path, lastKey);
    if (parent.isNull()) return false;

    parent[lastKey] = value;
    return true;
}
