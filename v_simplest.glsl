#version 330

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec3 Camera_pos;



in vec3 vertex; 
in vec3 normal;
in vec2 texCoord0; 

out vec2 iTexCoord0; 
out vec3 camera;
out vec3 nc;
out vec3 position;

void main(void) { 

    gl_Position= P*V*M* vec4(vertex.xyz,1);
    nc = mat3(transpose(inverse(M))) * normal;
    //nc = normal;
    camera = Camera_pos;
    //position = vec3(gl_Position.xyz);
    position = vertex;    
    iTexCoord0 = texCoord0;
}
