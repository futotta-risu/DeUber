
#include <time.h>
#include <cstdlib>

#include "software_launcher.h"


int main(int argc, char **argv){
    srand(time(NULL));

    software_launcher launcher;


    launcher.main_launch();

    return 0;
}
