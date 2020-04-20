//
// Created by whiwho on 17/04/2020.
//

#ifndef GAME_MOTOR_G_CONSTANTS_H
#define GAME_MOTOR_G_CONSTANTS_H

#include <string>

namespace constants{

    extern const char* ASSET_REGEX_PNG;
    extern const char* ASSET_REGEX_LST;
    extern const char* ASSET_REGEX_STG;
    extern const char* ASSET_REGEX_PER;

    inline const char* get_default_file_regex(char* end_p){
        std::string new_file_regex = "(^(?!._).*\\."+ static_cast<std::string>(end_p)+"$)";
        return new_file_regex.c_str();
    }
}

#endif //GAME_MOTOR_G_CONSTANTS_H
