#include <iostream>
#include <string>
#include <vector>
#include "Images.h"

using namespace std;

int main(int argc, char* argv[]) 
{

    if (argc < 2) {
        fprintf(stderr, "Invalid argument.\n");
        return EXIT_FAILURE;
    }
    
    vector<string> filepath;
    
    for (int i=1; i < argc; i++) {
        string temp = argv[i];
        filepath.push_back(temp);
        cerr << "File " << i << ": " << temp << endl;
    }
    cerr << endl;

    Images slide(filepath);
    slide.show_slides();
    return EXIT_SUCCESS;
}