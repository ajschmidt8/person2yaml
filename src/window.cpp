#include <window.hpp>

Window::Window(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &refGlade) : Gtk::Window(cobject), m_refGlade(refGlade)
{
  m_refGlade->get_widget("btn_save", m_Button_Save);
  m_refGlade->get_widget("btn_close", m_Button_Close);
  m_refGlade->get_widget("entry_name", m_Entry_Name);
  m_refGlade->get_widget("entry_age", m_Entry_Age);

  m_Button_Close->signal_clicked().connect(sigc::mem_fun(*this, &Window::on_button_close));
  m_Button_Save->signal_clicked().connect(sigc::mem_fun(*this, &Window::on_button_save));
};

Window::~Window() {}

void Window::on_button_close()
{
  hide();
}

void Window::on_button_save()
{
  myfile.open("output.yaml");
  myfile << "name: " << m_Entry_Name->get_text() << std::endl;
  myfile << "age: " << m_Entry_Age->get_text() << std::endl;
  myfile.close();
}

// References:
//  - https://gitlab.gnome.org/GNOME/gtkmm-documentation/-/tree/gtkmm-3-24/examples/book/builder/derived
//  - http://milindapro.blogspot.com/2012/10/create-gui-with-gtkmm-glade-with-gtkmm.html
