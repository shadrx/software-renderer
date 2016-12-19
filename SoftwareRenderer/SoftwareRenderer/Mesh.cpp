//
//  Mesh.cpp
//  SoftwareRenderer
//
//  Created by Joseph Bennett on 12/11/16.
//  Copyright © 2016 Joseph Bennett. All rights reserved.
//

#include "Mesh.hpp"
#include <fstream>
#include <sstream> 
#include <iostream>
#include <stdexcept>

Mesh::Mesh() {
    
}

Mesh Mesh::fromOBJ(std::string filename) {
    Mesh mesh = Mesh();
    
    std::ifstream input;
   
    input.open(filename);
    
    if (!input.is_open()) {
        // there are better ways to do this but I just want to get something rendering!
        std::cerr << "Could not read file: " << filename;
        throw std::runtime_error("Could not read OBJ file: " + filename);
    }
        
    std::string line;
    while(std::getline(input, line)) {
        std::istringstream lineStream(line);
        
        std::string mode;
        lineStream >> mode;
        
        if (mode == "v") {
            glm::vec3 vertex;
            lineStream >> vertex.x >> vertex.y >> vertex.z;
            mesh.mVertexBuffer.push_back(vertex);
        } else if (mode == "f") {
            while (lineStream.good()) {
                int vertexIndex, n, t;
                lineStream >> vertexIndex;
                lineStream.ignore(1);
                lineStream >> n;
                lineStream.ignore(1);
                lineStream >> t;
                
                vertexIndex -= 1; // subtract one as OBJ files start indexing from 1.
                
                mesh.mIndexBuffer.push_back(vertexIndex);
            }
        } else {
            if (mode != "#") {
                std::cout << "Unknown/Unsupported OBJ mode: " << mode << "\n";
            }
        }
    }

    return mesh;
}
