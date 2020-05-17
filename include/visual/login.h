//
// Created by lande on 17/05/2020.
//

#ifndef DEUBER_LOGIN_H
#define DEUBER_LOGIN_H

#include <CWindow.h>
#include <component/CButton.h>
#include <component/CTextBox.h>
#include <component/CLabel.h>
using namespace std;

const unsigned int WIDTH_LOG     =   600;
const unsigned int HEIGHT_LOG    =   800;

class Login : public CWindow {
private:

    CPanel *login_panel = nullptr;
    CLabel *lblwelcome = nullptr;
    CTextBox *usertxt = nullptr;
    CTextBox *password = nullptr;
    CLabel *lbluser = nullptr;
    CLabel *lblpass = nullptr;
    CButton *btnLogIn = nullptr;
    CButton *btnregister = nullptr;

public:

    Login() : CWindow("") {
        set_default_window();
        load_components();
        this->init_window();
    };

    ~Login() {
        delete login_panel;
    };


    void set_default_window() {
        set_size(WIDTH_LOG, HEIGHT_LOG);
        set_layout(new AbsoluteLayout());
    }

    void load_components() {
        login_panel = new CPanel();
        login_panel->set_size(HEIGHT_LOG, WIDTH_LOG);
        usertxt = new CTextBox();
        password = new CTextBox();
        lblwelcome = new CLabel("Bienvenido a DeUber, Introduce tus datos para iniciar sesion");
        lbluser = new CLabel("Usuario:");
        lblpass = new CLabel("Contraseña:");
        btnLogIn = new CButton("Iniciar Sesion");
        btnregister = new CButton("Registrarse");

        login_panel->add(lblwelcome);
        login_panel->add(lbluser);
        login_panel->add(usertxt);
        login_panel->add(lblpass);
        login_panel->add(password);
        login_panel->add(btnLogIn);
        login_panel->add(btnregister);

        this->add(login_panel);

    }

};
#endif //DEUBER_LOGIN_H
