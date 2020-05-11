//
// Created by whiwho on 13/04/2020.
//

#ifndef DEUBER_MAP_SELECTOR_H
#define DEUBER_MAP_SELECTOR_H


#include <CWindow.h>
#include <component/CButton.h>
#include <dirent.h>
#include <component/CScrollPanel.h>

const unsigned int WIDTH_MS     =   600;
const unsigned int HEIGHT_MS    =   800;

class MapSelector : public CWindow{
private:

    static std::string *map_file;
public:

    MapSelector(std::string* map_file_t, const std::string& path) : CWindow("Map Selector"){
        set_size(WIDTH_MS, HEIGHT_MS);
        set_layout(new VerticalFlowLayout());
        auto *pann = new CScrollPanel;
        pann->set_size({400,500});
        auto *g_pan = new CPanel;
        std::string map_file_c_t;

        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir(path.c_str())) != nullptr) {
            while ((ent = readdir (dir)) != nullptr) {
                if(ent->d_name[0]=='.') continue;
                auto* but = new CButton(ent->d_name);
                but->set_minimum_size({200,50});
                but->set_size({200,50});
                map_file_c_t = ent->d_name;
                but->set_action_listener([map_file_t, map_file_c_t](CWindow *win){
                    *map_file_t = map_file_c_t;
                });
                but->set_window(this);
                g_pan->add(but);
            }
            closedir (dir);
        } else {
            /* could not open directory */
            perror ("No se ha podido abrir");
        }
        pann->set_panel(g_pan);
        this->add(pann);
        this->init_window();
    };
    ~MapSelector() = default;

};


#endif //DEUBER_MAP_SELECTOR_H
