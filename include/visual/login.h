//
// Created by lande on 17/05/2020.
//


#ifndef DEUBER_LOGIN_H
#define DEUBER_LOGIN_H

#include <CWindow.h>
#include <component/CButton.h>
#include <component/CTextBox.h>
#include <component/CLabel.h>
#include <windows.h>





using namespace std;


const unsigned int WIDTH_LOG     =   800;
const unsigned int HEIGHT_LOG    =   620;
const int WIDTH_AVI     =   500;
const  int HEIGHT_AVI    =   300;

extern int login_data;

class Login : public CWindow {
private:

    CPanel *login_panel = nullptr;
    CPanel *panelAviso=nullptr;
    CLabel *lblwelcome = nullptr;
    CLabel *lbluser = nullptr;
    CLabel *lblpass = nullptr;
    CLabel *lblAviso=nullptr;


public:

    CButton *btnLogIn = nullptr;
    CButton *btnregister = nullptr;
    CTextBox *usertxt = nullptr;
    CTextBox *password = nullptr;




    Login() : CWindow("Inicio Sesion") {
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
        login_panel->set_layout(new AbsoluteLayout());

        lblwelcome = new CLabel("Bienvenido a DeUber, Introduce tus datos para iniciar sesion");
        lblwelcome->set_size({700,80});
        lblwelcome->set_pos({50, 10});

        lbluser = new CLabel("Usuario:");
        lbluser->set_size({200, 80});
        lbluser->set_pos({15, 110});
        usertxt = new CTextBox();
        usertxt->set_size({600, 80});
        usertxt->set_pos({15, 210});

        lblpass = new CLabel("Contraseña:");
        lblpass->set_size({200, 80});
        lblpass->set_pos({15, 310});
        password = new CTextBox();
        password->set_size({600, 80});
        password->set_pos({15, 410});

        btnLogIn = new CButton("Iniciar Sesion");
        btnLogIn->set_size({300,80});
        btnLogIn->set_pos({75,510});
        btnLogIn->set_window(this);
        btnLogIn->set_action_listener([&](CWindow *win){
            const std::string& user = usertxt->get_text();
            const std::string& pass= password->get_text();
            if(user.compare("root") == 0 && pass.compare("1234") == 0){
                login_data = 1;
                dispose();
            }
        });

        btnregister = new CButton("Registrarse");
        btnregister->set_size({300,80});
        btnregister->set_pos({425,510});
        btnregister->set_window(this);
        btnregister->set_action_listener([&](CWindow *win){
           /*char buff[100];
           string mensaje = "hola mundo";
           sprintf_s(buff,"El mensage es : %s",mensaje.c_str());*/


            if((usertxt->get_text().compare("")==0) || (password->get_text().compare("")==0)){

               MessageBox(NULL,"Debes introducir los datos","ERROR",0 );





                login_panel->add(panelAviso);
            }

        });

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
