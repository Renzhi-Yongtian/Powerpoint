#ifndef Images_H
#define Images_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>

class Images{
    
public:
    Images(std::vector<std::string>& filePath);
    bool add_bmp(std::string &img_path);
    bool load_bmp(std::vector<std::string> &img_path);
    void show_slides();    // idx is the index of an image in the vector.
    ~Images();

private:
    std::vector<SDL_Surface*> images;
    static bool init(SDL_Window *& window, SDL_Surface *& screen_surface);
    void display_bmp(SDL_Window *& window, SDL_Surface *& screen_surface, int idx);
    void close(SDL_Window *& window);
};

#endif