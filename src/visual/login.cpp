#include "visual/login.h"

int login_data = 0;

void Login::_set_default_window_properties() {
    set_size(WIDTH_LOG, HEIGHT_LOG);
    set_layout(new VerticalFlowLayout());
    set_resizable(false);
    get_panel()->set_background(155,183,181,255);
}

bool Login::_check_invalid_input(const std::string& user, const std::string& pass) {
    if (user.empty() || pass.empty())
        MessageBox(nullptr, "Empty fields detected", "ERROR", 0);
    else return false;

    return true;
}

void Login::_set_label_properties(CLabel* lbl){
    lbl->set_size({600, 80});
    lbl->set_alignment(CText::alignment_h::CENTER);
    lbl->set_alignment(CText::alignment_v::CENTER);
    lbl->get_font()->set_color({34,38,40});
    lbl->get_font()->set_size(60);
}

void Login::_set_button_properties(CButton* btn){
    btn->set_size({300,80});
    btn->get_font()->set_size(30);
    btn->set_window(this);
    btn->set_border_size(0);
}

void Login::_create_components(){
    lbluser = new CLabel("User");
    usertxt = new CTextBox();
    lblpass = new CLabel("Password");
    password = new CTextBox();
    btnLogIn = new CButton("Login");
    btnregister = new CButton("Sing Up");
    bottom = new CPanel();
}

void Login::_add_components(){
    bottom->add(btnLogIn);
    bottom->add(btnregister);
    add(lbluser);
    add(usertxt);
    add(lblpass);
    add(password);
    add(bottom);
}

void Login::_set_button_login_action(){
    btnLogIn->set_action_listener([&](CWindow *win){
        const char* user = usertxt->get_text().c_str();
        const char* pass = password->get_text().c_str();

        if(_check_invalid_input(user, pass)) return;
        try{
            if(DBManager::login_user(user, pass)){
                login_data = 1;
                dispose();
            }
        }catch(const std::exception& e){
            dispose();
        }
    });
}

void Login::_set_button_sing_up_action(){
    btnregister->set_action_listener([&](CWindow *win){
        const char *user = usertxt->get_text().c_str();
        const char *pass = password->get_text().c_str();

        if(_check_invalid_input(user, pass)) return;
        if(DBManager::is_user_registered(user)) {
            MessageBox(nullptr, "Username already taken", "ERROR", 0);
            return;
        }
        DBManager::sing_up_user(user,pass);
        MessageBox(nullptr, "User signed up :) ", "WELL DONE!", 0);
    });
}

void Login::_load_components() {

    _set_label_properties(lbluser);
    _set_label_properties(lblpass);

    usertxt->set_size({600, 80});
    password->set_size({600, 80});


    _set_button_properties(btnLogIn);
    _set_button_login_action();

    _set_button_properties(btnregister);
    _set_button_sing_up_action();

    bottom->set_layout(new FlowLayout(0,0));
}