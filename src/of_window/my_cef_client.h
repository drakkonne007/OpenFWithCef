#pragma once
#include "include/cef_app.h"
#include <ofPixels.h>
#include <ofTexture.h>
#include <thread>

class TestApp : public CefApp
{
    IMPLEMENT_REFCOUNTING(TestApp);
};

class TestClient : public CefClient, public CefRenderHandler, public CefLifeSpanHandler
{
    IMPLEMENT_REFCOUNTING(TestClient);

public:
    TestClient(int width, int height);

    std::mutex m_textureMutex;
    ofPixels m_pixels;
    std::atomic_bool m_isNeedRefresh = false;

    CefRefPtr<CefBrowser> getBrowser();
    CefRefPtr<CefRenderHandler> GetRenderHandler() override;
    void GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect) override;
    void OnPaint(CefRefPtr<CefBrowser> browser,PaintElementType type,const RectList& dirtyRects,
                 const void* buffer,int w, int h) override;
    void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
    bool DoClose(CefRefPtr<CefBrowser> browser) override;
    void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;
    CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override;

private:
    CefRefPtr<CefBrowser> m_browser;
    int m_browserId = -1;  // invalid value
    int m_browserCount = 0;
    bool m_isClosing = false;
    int m_width = 0;
    int m_height = 0;
};
