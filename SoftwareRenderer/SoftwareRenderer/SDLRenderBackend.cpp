//
//  SDLRenderBackend.cpp
//  SoftwareRenderer
//
//  Created by Joseph Bennett on 12/11/16.
//  Copyright © 2016 Joseph Bennett. All rights reserved.
//

#include "SDLRenderBackend.hpp"

SDLRenderBackend::SDLRenderBackend(int width, int height) {
    mWidth = width;
    mHeight = height;
}

void SDLRenderBackend::startFrame() {
    resetClearColor();
    SDL_RenderClear(mRenderer);
}

void SDLRenderBackend::setPixel(int x, int y, unsigned short r, unsigned short g, unsigned short b, unsigned short a) {
    SDL_SetRenderDrawColor(mRenderer, r, g, b, a);
    SDL_RenderDrawPoint(mRenderer, x, y);
    resetClearColor();
}

void SDLRenderBackend::endFrame() {
    SDL_RenderPresent(mRenderer);
}

void SDLRenderBackend::resetClearColor() {
    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);
}

bool SDLRenderBackend::initialize() {
    bool success = true;
    
    mWindow = SDL_CreateWindow("Software Renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mWidth, mHeight, SDL_WINDOW_SHOWN);
    
    if (mWindow == NULL) {
        printf("Could not create window. SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {
        mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
        
        if (mRenderer == NULL) {
            printf("Could not create renderer. SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
    }
    
    
    return success;
}


void SDLRenderBackend::shutdown() {
    SDL_DestroyRenderer(mRenderer);
    mRenderer = nullptr;
    
    SDL_DestroyWindow(mWindow);
    mWindow = nullptr;
}

int SDLRenderBackend::width() {
    return mWidth;
}

int SDLRenderBackend::height() {
    return mHeight;
}
