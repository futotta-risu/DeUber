//
// Created by whiwho on 13/04/2020.
//

#ifndef DEUBER_MAP_SELECTOR_H
#define DEUBER_MAP_SELECTOR_H


#include <CWindow.h>
#include <component/CButton.h>
#include <dirent.h>

const unsigned int WIDTH_MS     =   600;
const unsigned int HEIGHT_MS    =   800;

class MapSelector : public CWindow{
private:

    static std::string *map_file;
public:

    MapSelector(std::string* map_file_t, std::string path) : CWindow("Map Selector"){
        set_size(WIDTH_MS, HEIGHT_MS);
        set_layout(new VerticalFlowLayout());

        std::string map_file_c_t;

        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir(path.c_str())) != NULL) {
            while ((ent = readdir (dir)) != NULL) {
                if(ent->d_name[0]=='.') continue;
                CButton* but = new CButton(ent->d_name);
                but->set_minimum_size({200,50});
                but->set_size({200,50});
                map_file_c_t = ent->d_name;
                but->set_action_listener([map_file_t, map_file_c_t](CWindow *win){
                    *map_file_t = map_file_c_t;
                });
                but->set_window(this);
                this->add(but);
            }
            closedir (dir);
        } else {
            /* could not open directory */
            perror ("No se ha podido abrir");
        }

    };
    ~MapSelector() = default;

};


#endif //DEUBER_MAP_SELECTOR_H
