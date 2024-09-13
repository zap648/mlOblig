#version 410 core
layout(location = 0) in vec4 positionIn;    // 1st attribute buffer = vertex positions
layout(location = 1) in vec4 colorIn;       // 2nd attribute buffer = colors
layout(location = 2) in vec2 aTexCoord;     // 3rd attribute buffer = texture coordinates

out vec4 color;                             //color sent to rest of pipeline
out vec2 TexCoord;                          // Texture coordinate sent to rest of pipeline

uniform mat4 pmatrix;                       //nye matriser 23/1
uniform mat4 vmatrix;                       //nye matriser 23/1
uniform mat4 matrix;                        //the matrix for the model

void main() {
    color = colorIn;                        // Passing on the vertex color
    TexCoord = aTexCoord;                   // Passing on the vertex texture coordinate
    gl_Position = pmatrix * vmatrix * matrix * positionIn; // Calculate the position of the model
}
