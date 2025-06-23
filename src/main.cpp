#include "of_window/ofApp.h"
#include "include/cef_app.h"
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
    CefMainArgs main_args(argc, argv);
    CefRefPtr<TestApp> app(new TestApp());
    int exit_code = CefExecuteProcess(main_args, app, nullptr);
    if (exit_code >= 0) {
        return exit_code;
    }

    CefSettings cefSettings;
    cefSettings.windowless_rendering_enabled = true;
    cefSettings.multi_threaded_message_loop = true;
    std::string appDir = fs::current_path().string();
    CefString(&cefSettings.cache_path).FromString(appDir + "/cache");
    CefString(&cefSettings.resources_dir_path).FromString(appDir);
    CefString(&cefSettings.locales_dir_path).FromString(appDir + "/locales");
    if(!CefInitialize(CefMainArgs(argc, argv), cefSettings, app.get(), nullptr)){
        return 404; //Like 404 error in HTML
    }

    ofGLWindowSettings ofSettings;
    ofSettings.setSize(1024, 768);
    ofSettings.windowMode = OF_WINDOW;
    auto window = ofCreateWindow(ofSettings);
    auto windowApp = std::make_shared<OfApp>();
    ofRunApp(window, windowApp);
    int exitCode = ofRunMainLoop();
    app = nullptr;
    CefShutdown();
    return exitCode;
}
