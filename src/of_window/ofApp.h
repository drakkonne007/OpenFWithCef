#pragma once

#include "my_cef_client.h"
#include "ofMain.h"
#include "include/cef_app.h"

class OfApp : public ofBaseApp
{

public:
    OfApp() = default;

    void setup() override;
    void update() override;
    void draw() override;
    void exit() override;

private:
    ofVideoPlayer m_video;
    CefRefPtr<TestClient> m_testClient;
    int currentWindow();
    bool m_init = false;
    ofTexture m_texture;
};
