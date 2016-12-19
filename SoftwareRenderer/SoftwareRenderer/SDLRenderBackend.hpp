//
//  SDLRenderBackend.hpp
//  SoftwareRenderer
//
//  Created by Joseph Bennett on 12/11/16.
//  Copyright © 2016 Joseph Bennett. All rights reserved.
//

#ifndef SDLRenderBackend_hpp
#define SDLRenderBackend_hpp

#include <stdio.h>
#include <SDL2/sdl.h>
#include "RenderBackend.hpp"

class SDLRenderBackend : public RenderBackend {
public:
    SDLRenderBackend(int width, int height);
    ~SDLRenderBackend();
    bool initialize();
    void startFrame();
    void setPixel(int x, int y, unsigned short r, unsigned short g, unsigned short b, unsigned short a);
    void endFrame();
    void shutdown();
    int width();
    int height();
private:
    int mWidth, mHeight;
    SDL_Window* mWindow = NULL;
    SDL_Renderer* mRenderer = NULL;
    void resetClearColor();
};

#endif /* SDLRenderBackend_hpp */
