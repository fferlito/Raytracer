#include "raytracer.h"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Introduction to Computer Graphics - Raytracer\n\n";

    if (argc < 2 || argc > 3)
    {
        cerr << "Usage: " << argv[0] << "in-file [out-file.png]\n";
        return 1;
    }

    Raytracer raytracer;

    // read the scene
    if (!raytracer.readScene(argv[1]))
    {
        cerr << "Error: reading scene from " << argv[1] <<
            " failed - no output generated.\n";
        return 1;
    }

    // determine output name
    string ofname;
    if (argc >= 3)
    {
        ofname = argv[2];   // use the provided name
    }
    else
    {
        ofname = argv[1];   // replace .json with .png
        ofname.erase(ofname.begin() + ofname.find_last_of('.'), ofname.end());
        ofname += ".png";
    }

    raytracer.renderToFile(ofname);

    return 0;
}
