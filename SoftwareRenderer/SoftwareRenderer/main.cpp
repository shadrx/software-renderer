//
//  main.cpp
//  SoftwareRenderer
//
//  Created by Joseph Bennett on 11/11/16.
//  Copyright © 2016 Joseph Bennett. All rights reserved.
//

#include <iostream>
#include <SDL2/sdl.h>
#include <stdio.h>
#include <string>
#include "SDLRenderBackend.hpp"
#include "Renderer.hpp"

const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 500;

void shutdownSDL();
void update();
void printSDLError(std::string message);
void drawLine(RenderBackend *renderBackend, int x1, int x2, int y1, int y2);


int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not initialiize SDL. SDL_Error: %s\n", SDL_GetError());
    }
    
    update();
    
    shutdownSDL();
    
    return 0;
}

void update() {
    RenderBackend *renderBackend = new SDLRenderBackend(SCREEN_WIDTH, SCREEN_HEIGHT);
    renderBackend->initialize();
    
    Renderer renderer = Renderer(renderBackend);
    
    SDL_Event event;
    bool running = true;
    
    glm::vec2 mousePosition;
    
    while(running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            
            if (event.type == SDL_MOUSEMOTION) {
                mousePosition.x = event.motion.x;
                mousePosition.y = event.motion.y;
            }
        }
        
        renderBackend->startFrame();

        renderer.fillTriangle(vec2(50, 50), vec2(50, 150), mousePosition);
    
        renderBackend->endFrame();
    }
    
    renderBackend->shutdown();
    free(renderBackend);
}

void shutdownSDL() {
    SDL_Quit();
}


void printSDLError(std::string message) {
    printf("%s, SDL_Error: %s\n", message.c_str(), SDL_GetError());
}
               
