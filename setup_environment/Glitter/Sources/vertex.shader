#version 150
in vec3 vert;
in vec3 normal;
in vec2 vertTexCoord;
in vec3 tangent;
in vec3 biTangent;
out vec2 fragTexCoord;

uniform mat4 view;
uniform mat4 proj;

void main() {
    // Pass the texture coordinate straight through to the fragment shader
    fragTexCoord = vertTexCoord;

    //gl_Position = proj * view * vec4(vert, 1.0);
    gl_Position = vec4(vert, 1.0);
}
