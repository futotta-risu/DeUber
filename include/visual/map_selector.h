#ifndef DEUBER_MAP_SELECTOR_H
#define DEUBER_MAP_SELECTOR_H


#include <CWindow.h>
#include <component/CButton.h>
#include <dirent.h>
#include <component/CScrollPanel.h>

#include <utility>

#include <component/CTextBox.h>

const unsigned int WIDTH_MS     =   600;
const unsigned int HEIGHT_MS    =   800;

class MapSelector : public CWindow{
private:

    CScrollPanel* map_files_scroll_pane = nullptr;
    CPanel* map_files_panel = nullptr;

    //CPanel* map_preview_panel = nullptr;
    //CTextBox* map_preview_txt = nullptr;


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
    };

    void set_default_window(){
        set_size(WIDTH_MS, HEIGHT_MS);
        set_layout(new VerticalFlowLayout());
    }

    void load_components(){
        map_files_scroll_pane = new CScrollPanel();
        map_files_scroll_pane->set_size({400,500});

        map_files_panel = new CPanel();
        map_files_scroll_pane->set_panel(map_files_panel);

        /*
        map_preview_panel = new CPanel();
        map_preview_panel->set_layout(new VerticalFlowLayout);
        map_preview_txt = new CTextBox();
        */

        this->add(map_files_scroll_pane);
        //this->add(map_preview_panel);
    }

    CButton* create_map_file_button(const std::string& file_name){
        auto but = new CButton(file_name);

        but->set_minimum_size({200,50});
        but->set_size({200,100});

        const std::string& map_file_c_t = file_name;
        //const char* temp_name = file_name.c_str();
        but->set_action_listener([&, map_file_c_t](CWindow *win){
            *map_file_ptr = map_file_c_t;
            /*
            Map temp_map;
            temp_map.read_map(temp_name);
            const std::string value0 = "0";
            const std::string value1 = "1";
            const std::string value2 = "2";

            for(unsigned int i_height = 0; i_height < temp_map.get_height(); i_height++){
                std::basic_string<char> temp_value = map_preview_txt->get_text();
                for(unsigned int i_width = 0; i_width < temp_map.get_width(); i_width++){
                    if(temp_map.get_aval_map()[i_height][i_width] == 0){
                        temp_value.push_back('0');
                        map_preview_txt->set_text(temp_value);
                    }else  if(temp_map.get_aval_map()[i_height][i_width] == 1){
                        temp_value.push_back('1');
                        map_preview_txt->set_text(temp_value);
                    }else{
                        temp_value.push_back('2');
                        map_preview_txt->set_text(temp_value);
                    }
                }
                temp_value.push_back('/');
                temp_value.push_back('n');
                map_preview_txt->set_text(temp_value);
            }
            map_preview_panel->add(map_preview_txt);
            */
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
