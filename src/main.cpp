#include <gtkmm-3.0/gtkmm.h>
#include <window.hpp>

int main(int argc, char *argv[])
{
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
  auto refBuilder = Gtk::Builder::create();

  Window *MainWindow = nullptr;
  refBuilder->add_from_resource("/src/gui.glade");
  refBuilder->get_widget_derived("window_main", MainWindow);

  return app->run(*MainWindow);
}
