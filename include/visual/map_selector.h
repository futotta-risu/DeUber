#ifndef DEUBER_MAP_SELECTOR_H
#define DEUBER_MAP_SELECTOR_H


#include <CWindow.h>
#include <component/CButton.h>
#include <dirent.h>
#include <component/CScrollPanel.h>
#include<string.h>

#include <utility>

#include <component/CTextBox.h>
#include <component/CLabel.h>

const unsigned int WIDTH_MS     =   600;
const unsigned int HEIGHT_MS    =   800;

class MapSelector : public CWindow{
private:

    CScrollPanel* map_files_scroll_pane = nullptr;
    CPanel* map_files_panel = nullptr;
    CPanel* bottom_panel = nullptr;

    CPanel* map_preview_panel = nullptr;
    CLabel* map_preview_txt = nullptr;


    std::string *map_file_ptr = nullptr;
    std::string map_files_path;
public:

    MapSelector(std::string* map_file_t, std::string map_files_path_t) : CWindow("Map Selector"),
    map_file_ptr{map_file_t}, map_files_path{std::move(map_files_path_t)}{
        set_default_window();
        load_components();
        add_map_file_buttons();

        this->init_window();
    };
    ~MapSelector(){
        delete map_files_scroll_pane;
        delete bottom_panel;
        delete map_preview_panel;
    };

    void set_default_window(){
        set_size(WIDTH_MS, HEIGHT_MS);
        set_layout(new BorderLayout());
    }

    void load_components(){
        map_files_scroll_pane = new CScrollPanel();
        map_files_scroll_pane->set_size({400,500});

        map_files_panel = new CPanel();
        map_files_scroll_pane->set_panel(map_files_panel);

        map_preview_panel = new CPanel();
        map_preview_panel->set_layout(new VerticalFlowLayout);
        map_preview_txt = new CLabel();

        bottom_panel = new CPanel;
        auto load_but = new CButton("Cargar");
        load_but->set_window(this);
        load_but->set_action_listener([&](CWindow *win){
            dispose();
        });
        map_preview_panel->add(map_preview_txt);
        this->add(map_files_scroll_pane, BorderLayout::CENTER);
        this->add(map_preview_panel, BorderLayout::EAST);
        bottom_panel->add(load_but);
        this->add(bottom_panel, BorderLayout::SOUTH);
    }

    CButton* create_map_file_button(const std::string& file_name){
        auto but = new CButton(file_name);

        but->set_minimum_size({200,50});
        but->set_size({200,100});

        char* temp_name = new char[file_name.size() + 1];
        std::copy(file_name.begin(), file_name.end(), temp_name);
        temp_name[file_name.size()] = '\0';
        but->set_action_listener([&, temp_name](CWindow *win){
            *map_file_ptr = temp_name;

            Map temp_map;
            temp_map.read_map(temp_name);
            int** map_cpy = temp_map.get_aval_map();

            map_preview_panel->clear();

            std::basic_string<char> temp_value;
            for(unsigned int i_height = 0; i_height < temp_map.get_height(); i_height++){
                for(unsigned int i_width = 0; i_width < temp_map.get_width(); i_width++)
                    temp_value.push_back(map_cpy[i_height][i_width]+'0');
                map_preview_panel->add(new CLabel(temp_value));
                temp_value = "";
            }
            std::cout << "Valor " << temp_value << std::endl;
            map_preview_txt->set_text(temp_value);

        });
        but->set_window(this);

        return but;
    }

    void add_map_file_buttons(){
        // TODO Create function get_all_files_by_regex(path, regex) which returns a std::vector<std::string> with the files that satisfy the regex
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir(map_files_path.c_str())) != nullptr) {
            while ((ent = readdir (dir)) != nullptr) {
                if(ent->d_name[0]=='.') continue;
                map_files_panel->add(create_map_file_button(ent->d_name));
            }
            closedir (dir);
        } else PLOG_ERROR << "Could not load Map folder";


    }


};


#endif //DEUBER_MAP_SELECTOR_H
