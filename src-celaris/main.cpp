#include "webview/webview.h"

#include <iostream>

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE /*hInst*/, HINSTANCE /*hPrevInst*/,
                   LPSTR /*lpCmdLine*/, int /*nCmdShow*/)
{
#else
int main()
{
#endif
    try
    {
        webview::webview w(false, nullptr);
        w.set_title("Basic Example");
        w.set_size(800, 600, WEBVIEW_HINT_NONE);
        w.navigate("http://localhost:8080");
        w.run();
    }
    catch (const webview::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}