#include <gtkmm.h>

int main(int argc, char const *argv[])
{
	auto app=Gtk::Application::create();
	Gtk::Window janela;
	janela.set_title("Campo minado Jardel e Micaelli");
	janela.set_default_size(400,400);


	return app->run(janela);
}