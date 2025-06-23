#include "ofApp.h"
#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3.h>
#include <X11/Xlib.h>
#include <GLFW/glfw3native.h>

int OfApp::currentWindow()
{
    auto window = dynamic_cast<ofAppGLFWWindow*>(ofGetWindowPtr());
    if (!window) {
        ofLogError() << "Not using GLFW";
        return 0;
    }
    GLFWwindow* glfwWin = window->getGLFWWindow();
    return glfwGetX11Window(glfwWin);
}

void OfApp::setup()
{
    m_video.load("defaultVideo.mp4");
    ofSetVerticalSync(true);
    m_video.setLoopState(OF_LOOP_NORMAL);
    m_video.play();
    int window = currentWindow();
    if(window == 0){
        ofLogError()<<"Error enable window";
    }
    CefWindowInfo windInfo;
    windInfo.SetAsWindowless(static_cast<CefWindowHandle>(window));
    m_testClient = new TestClient(ofGetWidth(), ofGetHeight() / 2);
    CefBrowserSettings browserSettings;
    browserSettings.windowless_frame_rate = 60;
    CefBrowserHost::CreateBrowser(windInfo,m_testClient.get(),
                                  CefString("file:////home/drakkonne/openFrameworks/apps/myApps/DanyaOfWithCef/bin/site/index.html"), browserSettings,nullptr,nullptr);
}

void OfApp::update()
{
    if(m_testClient && m_testClient->m_isNeedRefresh.load() && m_testClient->m_textureMutex.try_lock()){
        m_texture.clear();
        m_texture.allocate(m_testClient->m_pixels);
        m_texture.loadData(m_testClient->m_pixels);
        m_testClient->m_isNeedRefresh.store(false);
        m_init = true;
        m_testClient->m_textureMutex.unlock();
    }
    m_video.update();
}

void OfApp::draw()
{
    if(m_init){
        m_texture.draw(0,0,ofGetWidth(), ofGetHeight() / 2);
    }
    m_video.draw(0, ofGetHeight() / 2, ofGetWidth(), ofGetHeight() /2 );
}

void OfApp::exit()
{
    if (m_testClient && m_testClient->getBrowser()) {
        m_testClient->getBrowser()->GetHost()->CloseBrowser(true);
        m_testClient = nullptr;
    }
}
