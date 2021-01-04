#include <gtkmm-3.0/gtkmm.h>
#include <iostream>
#include <fstream>

class Window : public Gtk::Window
{
public:
  Window(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &refGlade);
  virtual ~Window();

protected:
  void on_button_save();
  void on_button_close();

  Gtk::Entry *m_Entry_Name;
  Gtk::SpinButton *m_Entry_Age;
  Gtk::Button *m_Button_Close;
  Gtk::Button *m_Button_Save;
  std::ofstream myfile;

  Glib::RefPtr<Gtk::Builder> m_refGlade;
};
