#include "CampoMinado.cpp"
#include <gtkmm/application.h>

int main(int argc, char const *argv[])
{
    auto app = Gtk::Application::create();

    CampoMinado campoMinado;
    return app->run(campoMinado);
}
