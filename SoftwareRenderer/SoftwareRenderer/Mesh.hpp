//
//  Mesh.hpp
//  SoftwareRenderer
//
//  Created by Joseph Bennett on 12/11/16.
//  Copyright © 2016 Joseph Bennett. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

class Mesh {
public:
    Mesh();
    static Mesh fromOBJ(std::string filename);
    std::vector<glm::vec3> mVertexBuffer;
    std::vector<int> mIndexBuffer;

};

#endif /* Mesh_hpp */
