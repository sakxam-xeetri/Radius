#pragma once
#include <WebServer.h>
#include "AudioManager.h"

class WebServerHandler {
public:
    WebServerHandler(AudioManager& audioMgr);
    void begin();
    void loop();

private:
    WebServer server;
    AudioManager& audio;
};
