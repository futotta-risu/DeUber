
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include "software_launcher.h"


int main(int argc, char **argv){
    srand(time(NULL));
    printf("Hola1");
    
    software_launcher launcher;
    launcher.main_launch();

    return 0;
}
