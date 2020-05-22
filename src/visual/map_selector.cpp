#include <visual/map_selector.h>
#include <plog/Log.h>
#include <maps/map.h>

void MapSelector::_set_default_window_properties(){
    set_size(WIDTH_MS, HEIGHT_MS);
    set_layout(new BorderLayout());
    set_resizable(false);
}

void MapSelector::_create_components(){
    map_files_scroll_pane = new CScrollPanel();
    map_files_panel = new CPanel();
    map_preview_panel = new CPanel();
    map_preview_txt = new CLabel();

    bottom_panel = new CPanel;
}

void MapSelector::_create_bottom_panel(){
    auto load_but = new CButton("Load");
    load_but->set_window(this);
    load_but->set_action_listener([&](CWindow *win){dispose();});
    load_but->set_minimum_size({250,50});
    bottom_panel->add(load_but);
    bottom_panel->set_minimum_size({620,50});
    bottom_panel->set_size(50,620);

    bottom_panel->set_layout(new VerticalFlowLayout(0,0));
}

void MapSelector::_load_components(){

    map_files_scroll_pane->set_minimum_size({350,500});
    map_files_panel->set_minimum_size({350,500});
    map_files_scroll_pane->set_panel(map_files_panel);
    map_files_panel->set_layout(new VerticalFlowLayout(0,0));

    map_preview_panel->add(map_preview_txt);
    map_preview_panel->set_minimum_size({250,500});

}

void MapSelector::_add_components(){
    this->add(map_files_scroll_pane, BorderLayout::CENTER);
    this->add(map_preview_panel, BorderLayout::EAST);
    this->add(bottom_panel, BorderLayout::SOUTH);
}

void MapSelector::_add_map_file_buttons(){
    // TODO Create function get_all_files_by_regex(path, regex) which returns a std::vector<std::string> with the files that satisfy the regex
    DIR *dir;
    struct dirent *ent;
    int i = 0;
    if ((dir = opendir(map_files_path.c_str())) != nullptr) {
        while ((ent = readdir (dir)) != nullptr) {
            if(ent->d_name[0]=='.') continue;
            map_files_panel->add(_create_map_file_button(ent->d_name, i++));
        }
        closedir (dir);
    } else PLOG_ERROR << "Could not load Map folder";
}

void _set_map_file_button_properties(CButton *btn, int i){
    int btn_color = 200+i*30;
    btn->set_minimum_size({350,50});
    btn->set_size({350,80});
    btn->set_border_size(0);
    btn->set_background(btn_color, btn_color,btn_color,255);
}

CButton* MapSelector::_create_map_file_button(const std::string& file_name, int i){
    auto but = new CButton(file_name);
    _set_map_file_button_properties(but,i%2);

    but->set_action_listener([&, file_name](CWindow *win){
        *map_file_ptr = file_name;
        Map temp_map;
        temp_map.read_map(file_name.c_str());
        int** map_cpy = temp_map.get_aval_map();

        map_preview_panel->clear();

        std::basic_string<char> temp_value;
        for(unsigned int i_height = 0; i_height < temp_map.get_height(); i_height++){
            for(unsigned int i_width = 0; i_width < temp_map.get_width(); i_width++)
                temp_value.push_back(map_cpy[i_height][i_width]+'0');
            auto lbl = new CLabel(temp_value);
            lbl->set_minimum_size({300,30});
            map_preview_panel->add(lbl);
            temp_value = "";
        }
        map_preview_txt->set_text(temp_value);

    });
    but->set_window(this);

    return but;
}