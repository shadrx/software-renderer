//
//  Renderer.cpp
//  SoftwareRenderer
//
//  Created by Joseph Bennett on 12/11/16.
//  Copyright © 2016 Joseph Bennett. All rights reserved.
//

#include "Renderer.hpp"
#include <glm/gtx/norm.hpp>

Renderer::Renderer(RenderBackend *renderBackend) {
    mRenderBackend = renderBackend;
}

void Renderer::drawPoint(vec2 point) {
    mRenderBackend->setPixel(point.x, point.y, mCurrentColor.r, mCurrentColor.g, mCurrentColor.b, 0xFF);
}

void Renderer::drawLine(glm::vec2 a, glm::vec2 b) {
    drawLine(a.x, a.y, b.x, b.y);
}

void Renderer::drawLine(int x1, int y1, int x2, int y2) {
    bool steep = false;
    
    if (glm::abs(x1-x2)< glm::abs(y1-y2)) {
        std::swap(x1, y1);
        std::swap(x2, y2);
        steep = true;
    }
    
    if (x1>x2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }
    
    int deltaX = x2-x1;
    int deltaY = y2-y1;
    
    int deltaError = glm::abs(deltaY) * 2;
    int error = 0;
    
    int y = y1;
    for (int x=x1; x<=x2; x++) {
        if (steep) {
            drawPoint(vec2(y, x));
        } else {
            drawPoint(vec2(x, y));
        }
        
        error += deltaError;
        
        if (error > deltaX) {
            y += (y2 > y1 ? 1 : -1);
            error -= deltaX * 2;
        }
    }
    
}

void Renderer::fillTriangle(vec2 A, vec2 B, vec2 C) {
    int minX = min(min(A.x, B.x), C.x);
    int minY = min(min(A.y, B.y), C.y);
    
    int maxX = max(max(A.x, B.x), C.x);
    int maxY = max(max(A.y, B.y), C.y);
    
    // clamp to image dimensions
    minX = max(0, minX);
    minY = max(0, minY);
    maxX = min(mRenderBackend->width(), maxX);
    maxY = min(mRenderBackend->height(), maxY);
    
    vec2 boundingBoxMin = vec2(minX, minY);
    vec2 boundingBoxMax = vec2(maxX, maxY);
    
    
    vec3 u = vec3(B - A, 0);
    vec3 v = vec3(C - A, 0);

    
    for (int x = boundingBoxMin.x; x <= boundingBoxMax.x; x++) {
        for (int y = boundingBoxMin.y; y <= boundingBoxMax.y ; y++) {
            vec2 P = vec2(x, y);
            
            vec3 w = vec3(P - A, 0);
            
            vec3 vCrossW = cross(v, w);
            vec3 vCrossU = cross(v, u);
            
            // point to the right of vector AB.
            if (dot(vCrossW, vCrossU) < 0) continue;
            
            vec3 uCrossW = cross(u, w);
            vec3 uCrossV = cross(u, v);
            
            // point to the left of vector AC.
            if (dot(uCrossW, uCrossV) < 0) continue;
            
            float denominator = length(vCrossU);
            float r = length(vCrossW)/denominator;
            float t = length(uCrossW)/denominator;
            
            // test if point is actually in triangle
            if (r + t <= 1) {
                drawPoint(P);
            }
        }
    }
}

void fillTriangleInterpolation(vec2 v1, vec2 v2, vec2 v3, Renderer renderer) {
    if (v1.y == v2.y && v1.y == v3.y) {
        return;
    }
    
    
    if (v1.y > v2.y) std::swap(v1, v2);
    if (v1.y > v3.y) std::swap(v1, v3);
    if (v2.y > v3.y) std::swap(v2, v3);
    
    
    int totalRise = v3.y - v1.y;
    
    int segmentARun = (v3.x - v2.x);
    int segmentARise = (v3.y - v2.y);
    
    for (int y = v2.y; y <= v3.y; y++) {
        float am = (y - v2.y)/(segmentARise + 1);
        float bm = (y - v1.y)/totalRise;
        
        int ax = am * segmentARun + v2.x;
        int bx = bm * (v3.x - v1.x) + v1.x;
        
        renderer.setColor(vec3(255, 255, 0));
        vec2 a = vec2(ax, y);
        vec2 b = vec2(bx, y);
        renderer.drawLine(a, b);
    }
    
    
    int segmentBRun = (v2.x - v1.x);
    int segmentBRise = (v2.y - v1.y);
    
    for (int y = v1.y; y <= v2.y; y++) {
        float am = (y - v1.y)/(segmentBRise + 1);
        float bm = (y - v1.y)/totalRise;
        
        int ax = am * segmentBRun + v1.x;
        int bx = bm * (v3.x - v1.x) + v1.x;
        
        renderer.setColor(vec3(255, 255, 0));
        vec2 a = vec2(ax, y);
        vec2 b = vec2(bx, y);
        renderer.drawLine(a, b);
    }
}


void Renderer::setColor(vec3 color) {
    mCurrentColor = color;
}

void Renderer::drawMesh(Mesh mesh) {
    int width = mRenderBackend->width();
    int height = mRenderBackend->height();
    
    // step in blocks of 3 as a face is made up of 3 vertices
    for(int i = 0; i < mesh.mIndexBuffer.size(); i+=3) {
        for (int j = 0; j < 3; j++) {
            vec3 v1 = mesh.mVertexBuffer[mesh.mIndexBuffer[i + j]];
            vec3 v2 = mesh.mVertexBuffer[mesh.mIndexBuffer[i + ((j + 1) % 3)]];
            
            vec2 start = vec2(width - (v1.x + 1.) * width/2, (v1.y + 1.) * height/2);
            vec2 end = vec2((v2.x + 1.) * width/2, (v2.y + 1.) * height/2);
            
            drawLine(start, end);
        }
    }
}
