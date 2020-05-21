//
// Created by lande on 17/05/2020.
//


#ifndef DEUBER_LOGIN_H
#define DEUBER_LOGIN_H

#include <CWindow.h>
#include <component/CButton.h>
#include <component/CTextBox.h>
#include <component/CLabel.h>
#include <layout/FlowLayout.h>

#include <windows.h>

#include <database/dbManager.h>

using namespace std;


const unsigned int WIDTH_LOG     =   650;
const unsigned int HEIGHT_LOG    =   600;


extern int login_data;

class Login : public CWindow {
private:
    CLabel *lbluser, *lblpass;
    CButton *btnLogIn, *btnregister ;
    CTextBox *usertxt, *password ;

public:
    Login() : CWindow("DeUber Login") {
        set_default_window();
        load_components();
        this->init_window();
    };

    ~Login() {
        get_panel()->clear();
    };

    void set_default_window() {
        set_size(WIDTH_LOG, HEIGHT_LOG);
        set_layout(new VerticalFlowLayout());
        get_panel()->set_background(155,183,181,255);
    }

    void load_components() {


        lbluser = new CLabel("User");
        lbluser->set_size({200, 80});
        lbluser->get_font()->set_color({34,38,40});

        usertxt = new CTextBox();
        usertxt->set_size({600, 80});

        lblpass = new CLabel("Password");
        lblpass->set_size({200, 80});
        lblpass->get_font()->set_color({34,38,40});

        password = new CTextBox();
        password->set_size({600, 80});

        btnLogIn = new CButton("Login");
        btnLogIn->set_size({300,80});

        btnLogIn->set_window(this);
        btnLogIn->set_border_size(0);
        btnLogIn->set_action_listener([&](CWindow *win){
            std::string user = usertxt->get_text();
            std::string pass = password->get_text();
            if(user == "root" && pass == "1234"){
                login_data = 1;
                dispose();
            }
        });

        btnregister = new CButton("Sing Up");
        btnregister->set_size({300,80});

        btnregister->set_window(this);
        btnregister->set_border_size(0);
        btnregister->set_action_listener([&](CWindow *win){
            std::string user = usertxt->get_text();
            std::string pass = password->get_text();

            if(user.empty() || pass.empty()){
               MessageBox(nullptr,"Debes introducir los datos","ERROR",0 );
                return;
            }
            registro(user.c_str(),pass.c_str());
        });

        CPanel *bottom = new CPanel();
        bottom->set_layout(new FlowLayout(0,0));
        bottom->add(btnLogIn);
        bottom->add(btnregister);
        add(lbluser);
        add(usertxt);
        add(lblpass);
        add(password);
        add(bottom);
    }

};
#endif //DEUBER_LOGIN_H
