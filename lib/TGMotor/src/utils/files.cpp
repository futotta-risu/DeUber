//
// Created by whiwho on 17/04/2020.
//

#include <fstream>
#include "utils/files.h"

void file_rec(const std::string& path, const sp_str::functional_vector& codes){
    DIR *dir;
    struct dirent *ent;
    // TODO Set an error here

    if ((dir = opendir(path.c_str())) == nullptr) return;

    while ((ent = readdir (dir)) != nullptr) {
        if(strcmp(ent->d_name,".")==0 || strcmp(ent->d_name,"..")==0) continue;

        if(ent->d_type == DT_DIR) file_rec(path+ent->d_name+"/", codes);
        else if(ent->d_type == DT_REG){
            std::string file_name = ent->d_name;
            if(file_name.length() < 4) continue;
            for(unsigned short i = 0; i < 4; i++) file_name.pop_back();
            for(auto& code : codes)
                if(std::regex_match(static_cast<std::string>(ent->d_name), std::regex(code.first)))
            code.second(file_name, path+ent->d_name);
        }
    }
    closedir(dir);
}

json get_json(const std::string& path){
    std::ifstream f_file(path);
    // TODO Throw Error
    if(!f_file.is_open()) return nullptr;

    json data_json;
    f_file >> data_json;
    f_file.close();
    return data_json;
}