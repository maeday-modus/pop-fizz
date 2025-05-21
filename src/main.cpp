
#include "app/application.h"
#include "app/gfx/renderer.h"

class MyApp : public fizz::Application
{
public:
    MyApp()
        : Application("C++ Physics Engine Demo", 800, 600)
    {
        fizz::Logger::LogINFO("Constructed MyApp!");
        fizz::Renderer::SetClearColor(0.1, 0.2, 0.2);
    }

};

int main()
{
    MyApp app;

    app.Run();

    // return 0; - IMPLICIT
}
