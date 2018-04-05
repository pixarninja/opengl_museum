#version 330
in vec3 vert;
in vec2 vertTexCoord;
out vec2 fragTexCoord;

void main() {
    // Pass the texture coordinate straight through to the fragment shader
    fragTexCoord = vertTexCoord;

    gl_Position = vec4(vert, 1);
}
