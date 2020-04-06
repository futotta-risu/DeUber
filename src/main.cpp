#include <time.h>
#include <cstdlib>
#include <string>
#define SDL_MAIN_HANDLED
#include "run_handler.h"


int main(int argc, char* argv[]){
    bool visual = true;
    if(argc > 1){
        char* visual_style = argv[1];
        if(static_cast<std::string>(visual_style) == "visual")
            visual = true;
        else if(static_cast<std::string>(visual_style) == "non_visual")
            visual = false;
    }
    srand(time(nullptr));

    run_handler launcher(visual);
    return EXIT_SUCCESS;
}
