#version 410 core
layout(location = 0) in vec3 vertexPosition;    //renamed from earlier shaders
layout(location = 1) in vec3 vertexNormal;      //renamed from earlier shaders
layout(location = 2) in vec2 vertexUV;          //not used when we don't use textures

out vec3 fragmentPosition;
out vec3 normalTransposed;
out vec2 UV;      //for textures

uniform mat4 matrix;
uniform mat4 vmatrix;
uniform mat4 pmatrix;

void main() {
   fragmentPosition = vec3(matrix * vec4(vertexPosition, 1.0));    //1.0 because it is a point
   normalTransposed = mat3(transpose(inverse(matrix))) * vertexNormal;

   UV = vertexUV;      //for textures
   gl_Position = pmatrix * vmatrix * matrix * vec4(vertexPosition, 1.0);
}

//Using calculations in world space,
//https://learnopengl.com/Lighting/Basic-Lighting
//but could just as easy be done in camera space
//http://www.opengl-tutorial.org/beginners-tutorials/tutorial-8-basic-shading/
