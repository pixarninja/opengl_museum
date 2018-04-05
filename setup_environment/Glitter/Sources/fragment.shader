#version 330 core
uniform sampler2D tex; // texture
in vec2 fragTexCoord; // texture coord
out vec4 color; // output color of the pixel

void main() {
    color = texture(tex, fragTexCoord);
}