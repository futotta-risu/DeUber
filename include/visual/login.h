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

const unsigned int WIDTH_LOG     =   620;
const unsigned int HEIGHT_LOG    =   600;

extern int login_data;

class Login : public CWindow {
private:
    CPanel *bottom;
    CLabel *lbluser, *lblpass;
    CButton *btnLogIn, *btnregister;
    CTextBox *usertxt, *password;

    static bool _check_invalid_input(const std::string& user, const std::string& pass);

    static void _set_label_properties(CLabel* lbl);
    void _set_button_properties(CButton* btn);

    void _set_button_login_action();
    void _set_button_sing_up_action();

    void _set_default_window_properties();
    void _create_components();
    void _add_components();
    void _load_components();

public:

    Login() : CWindow("DeUber Login") {
        _set_default_window_properties();
        _create_components();
        _load_components();
        _add_components();
        this->init_window();
    };

    ~Login() {get_panel()->clear();};
};
#endif //DEUBER_LOGIN_H
