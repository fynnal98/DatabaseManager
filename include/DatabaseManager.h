#pragma once                 
#include <ArduinoJson.h>     
#include <Arduino.h>         
#include <LittleFS.h>

class DatabaseManager {
public:
    DatabaseManager();

    bool begin();
    bool load(const char* path);
    bool save(const char* path = nullptr);

    const char* getString(const char* key);
    int getInt(const char* key);
    float getFloat(const char* key);

    bool set(const char* key, const char* value);
    bool set(const char* key, int value);
    bool set(const char* key, float value);

private: 
    StaticJsonDocument<4096> m_doc;
    
    String m_path;
    bool m_loaded;

    JsonVariant resolvePath(const char* path);
    JsonVariant resolveParent(const char* path, String& lastKey);

};