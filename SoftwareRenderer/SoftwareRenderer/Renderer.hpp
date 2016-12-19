//
//  Renderer.hpp
//  SoftwareRenderer
//
//  Created by Joseph Bennett on 12/11/16.
//  Copyright © 2016 Joseph Bennett. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <stdio.h>
#include "RenderBackend.hpp"
#include <glm/glm.hpp>
#include "Mesh.hpp"

using namespace glm;

class Renderer {
public:
    Renderer(RenderBackend *renderBackend);
    void setColor(vec3 color);
    void drawPoint(vec2 point);
    void drawLine(vec2 a, vec2 b);
    void drawLine(int x1, int y1, int x2, int y2);
    void fillTriangle(vec2 v1, vec2 v2, vec2 v3);
    void drawMesh(Mesh mesh);
private:
    RenderBackend* mRenderBackend;
    vec3 mCurrentColor = vec3(255);
};

#endif /* Renderer_hpp */
