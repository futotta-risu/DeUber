#ifndef DEUBER_MAP_SELECTOR_H
#define DEUBER_MAP_SELECTOR_H

#include <dirent.h>
#include <string.h>
#include <iostream>

#include <CWindow.h>
#include <component/CButton.h>
#include <component/CScrollPanel.h>
#include <component/CTextBox.h>
#include <component/CLabel.h>

const unsigned int WIDTH_MS     =   620;
const unsigned int HEIGHT_MS    =   550;

class MapSelector : public CWindow{
private:

    CScrollPanel* map_files_scroll_pane = nullptr;
    CPanel *map_files_panel, *bottom_panel;
    CPanel* map_preview_panel = nullptr;
    CLabel* map_preview_txt = nullptr;

    std::string *map_file_ptr = nullptr;
    std::string map_files_path;

    void _set_default_window_properties();
    void _create_components();
    void _create_bottom_panel();
    void _load_components();
    void _add_components();

    void _add_map_file_buttons();
    CButton* _create_map_file_button(const std::string& file_name, int i);

public:

    MapSelector(std::string* map_file_t, std::string map_files_path_t) : CWindow("Map Selector"),
    map_file_ptr{map_file_t}, map_files_path{std::move(map_files_path_t)}{
        _set_default_window_properties();
        _create_components();
        _create_bottom_panel();
        _load_components();
        _add_components();

        _add_map_file_buttons();

        this->init_window();
    };
    ~MapSelector(){
        delete map_files_scroll_pane;
        delete bottom_panel;
        delete map_preview_panel;
    };










};


#endif //DEUBER_MAP_SELECTOR_H
