#include "WebServerHandler.h"
#include <LittleFS.h>

WebServerHandler::WebServerHandler(AudioManager& audioMgr) : server(80), audio(audioMgr) {
}

void WebServerHandler::begin() {
    if(!LittleFS.begin(true)){
        Serial.println("LittleFS Mount Failed. Make sure to upload filesystem image first.");
        return;
    }
    
    // Serve HTML
    server.on("/", HTTP_GET, [this]() {
        File file = LittleFS.open("/index.html", "r");
        if (!file) {
            server.send(500, "text/plain", "index.html not found. Did you upload LittleFS?");
            return;
        }
        server.streamFile(file, "text/html");
        file.close();
    });

    // Serve CSS
    server.on("/style.css", HTTP_GET, [this]() {
        File file = LittleFS.open("/style.css", "r");
        if (!file) {
            server.send(404, "text/plain", "File not found");
            return;
        }
        server.streamFile(file, "text/css");
        file.close();
    });
    
    // Serve JS
    server.on("/script.js", HTTP_GET, [this]() {
        File file = LittleFS.open("/script.js", "r");
        if (!file) {
            server.send(404, "text/plain", "File not found");
            return;
        }
        server.streamFile(file, "application/javascript");
        file.close();
    });

    // API to play audio stream
    server.on("/api/play", HTTP_POST, [this]() {
        if (server.hasArg("url")) {
            String url = server.arg("url");
            audio.playStream(url.c_str());
            server.send(200, "application/json", "{\"status\":\"playing\"}");
        } else {
            server.send(400, "application/json", "{\"error\":\"url parameter missing\"}");
        }
    });

    // API to stop audio stream
    server.on("/api/stop", HTTP_POST, [this]() {
        audio.stop();
        server.send(200, "application/json", "{\"status\":\"stopped\"}");
    });

    // API to set volume
    server.on("/api/volume", HTTP_POST, [this]() {
        if (server.hasArg("level")) {
            int level = server.arg("level").toInt();
            audio.setVolume(level);
            server.send(200, "application/json", "{\"status\":\"success\"}");
        } else {
            server.send(400, "application/json", "{\"error\":\"level parameter missing\"}");
        }
    });

    // API to get device status
    server.on("/api/status", HTTP_GET, [this]() {
        String json = "{";
        json += "\"playing\":" + String(audio.isPlaying() ? "true" : "false") + ",";
        json += "\"volume\":" + String(audio.getVolume()) + ",";
        json += "\"url\":\"" + audio.getCurrentStation() + "\"";
        json += "}";
        server.send(200, "application/json", json);
    });

    server.begin();
    Serial.println("HTTP WebServer started");
}

void WebServerHandler::loop() {
    // Non-blocking handler
    server.handleClient();
}
