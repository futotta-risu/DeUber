
#include <time.h>
#include <cstdlib>

#define SDL_MAIN_HANDLED
#include "run_handler.h"


int main(int argc, char **argv){
    srand(time(NULL));
    run_handler launcher(true);

    return 0;
}
