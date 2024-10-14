#include "Images.h"

Images::Images(std::vector<std::string>& filePath) 
{
    load_bmp(filePath);
}

void Images::show_slides() 
{
    SDL_Window *window = NULL;
    SDL_Surface *screen_surface = NULL;

    if (init(window, screen_surface)) {
        bool quit = false;
        SDL_Event e;        // Handles keyboard input.
        int idx = 0;        // Handles which index of picture.
        int num_img = (this->images).size();

        this->display_bmp(window, screen_surface, idx);
        while (!quit) {
            SDL_PollEvent(&e);
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN){
                switch (e.key.keysym.sym) {
                    case SDLK_RIGHT:
                        idx++;
                        idx = idx >  num_img-1 ?  num_img-1: idx;
                        this->display_bmp(window, screen_surface, idx);
                        break;
                    case SDLK_LEFT:
                        idx--;
                        idx = idx < 0 ? 0 : idx;        // if negative set it as 0.
                        this->display_bmp(window, screen_surface, idx);
                        break;
                }
            }
        }
    }
    close(window);
}

bool Images::init(SDL_Window *& window, SDL_Surface *& screen_surface) 
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize: %s\n", SDL_GetError());
        success = false;
    } else {
        window = SDL_CreateWindow("Slides", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 480, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            fprintf(stderr, "Window could not be created: %s\n", SDL_GetError());
            success = false;
        } else {
            screen_surface = SDL_GetWindowSurface(window);
            if (screen_surface == NULL) {
                SDL_DestroyWindow(window);
                success = false;
            }
        }
    }

    return success;
}

bool Images::add_bmp(std::string &img_path)
{
    bool success = true;
    SDL_Surface* image = SDL_LoadBMP(img_path.c_str());
    if (image == NULL) {
        success = false;
    }
    images.push_back(image);
    return success;
}

bool Images::load_bmp(std::vector<std::string> &img_paths) 
{
    int success = true;

    // Remove old bmp files.
    int n = (this->images).size();
    for (int i=0; i<n; i++) {
        SDL_FreeSurface((this->images)[i]);
        (this->images)[i] = NULL;
    }

    // Add new bmp files.
    int n2 = img_paths.size();
    (this->images).resize(n2);
    for (int i=0; i<n2; i++) {
        (this->images)[i] = SDL_LoadBMP(img_paths[i].c_str());
        if ((this->images)[i] == NULL) {
            success = false;
        }
    }

    return success;
}

void Images::display_bmp(SDL_Window *& window, SDL_Surface *& screen_surface, int idx) 
{
    if (idx >= 0 && idx < images.size()) {
        SDL_BlitSurface(this->images[idx], NULL, screen_surface, NULL);
        SDL_UpdateWindowSurface(window);
    }
}


void Images::close(SDL_Window *& window)
{
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}

Images::~Images() 
{
    int n = (this->images).size();
    for (int i=0; i<n; i++) {
        SDL_FreeSurface((this->images)[i]);
        (this->images)[i] = NULL;
    }
}