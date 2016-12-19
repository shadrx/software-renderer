//
//  RenderBackend.hpp
//  SoftwareRenderer
//
//  Created by Joseph Bennett on 11/11/16.
//  Copyright © 2016 Joseph Bennett. All rights reserved.
//

#ifndef RenderBackend_hpp
#define RenderBackend_hpp

#include <stdio.h>


class RenderBackend {
public:
    virtual bool initialize()=0;
    virtual void startFrame()=0;
    virtual void setPixel(int x, int y, unsigned short r, unsigned short g, unsigned short b, unsigned short a)=0;
    virtual void endFrame()=0;
    virtual void shutdown()=0;
    
    virtual int width()=0;
    virtual int height()=0;
};

#endif /* RenderBackend_hpp */
