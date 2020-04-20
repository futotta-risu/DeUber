//
// Created by whiwho on 17/04/2020.
//

#ifndef GAME_MOTOR_FILES_H
#define GAME_MOTOR_FILES_H

#include <dirent.h>
#include <regex>
#include <functional>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace sp_str {
    using function_v_ss = std::function<void(const std::string&, const std::string&)> ;
    using functional_vector = std::vector<std::pair<std::string, function_v_ss > > ;
}
void file_rec(const std::string& path, const sp_str::functional_vector& codes);
json get_json(const std::string& path);

#endif //GAME_MOTOR_FILES_H
