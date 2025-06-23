#include "my_cef_client.h"
#include "include/cef_thread.h"

TestClient::TestClient(int width, int height) : m_width(width), m_height(height)
{
    m_pixels.allocate(m_width, m_height, OF_PIXELS_BGRA);
    m_pixels.set(0);
}

CefRefPtr<CefBrowser> TestClient::getBrowser()
{
    return m_browser;
}

CefRefPtr<CefRenderHandler> TestClient::GetRenderHandler()
{
    return this;
}

void TestClient::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect)
{
    (void)browser;
    rect = CefRect(0, 0, m_width, m_height);
}

void TestClient::OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList &dirtyRects, const void *buffer, int width, int height)
{
    (void)browser;
    (void)dirtyRects;
    if(type == cef_paint_element_type_t::PET_POPUP){
        return;
    }
    std::lock_guard<std::mutex> lock(m_textureMutex);
    if (width != m_width || height != m_height) {
        m_width = width;
        m_height = height;
        m_pixels.clear();
        m_pixels.allocate(m_width, m_height, OF_PIXELS_BGRA);
    }
    memcpy(m_pixels.getData(),buffer, m_width * m_height * 4);
    m_isNeedRefresh.store(true);
}

void TestClient::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
    if(!m_browser){
        m_browser = browser;
        m_browserId = browser->GetIdentifier();
    }
    m_browserCount++;
}

bool TestClient::DoClose(CefRefPtr<CefBrowser> browser)
{
    if(m_browserId == browser->GetIdentifier()){
        m_isClosing = true;
    }
    return false;
}

void TestClient::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
    if(m_browserId == browser->GetIdentifier()){
        m_browser = nullptr;
    }
    if(--m_browserCount == 0){
        CefQuitMessageLoop();
    }
}

CefRefPtr<CefLifeSpanHandler> TestClient::GetLifeSpanHandler()
{
    return this;
}
