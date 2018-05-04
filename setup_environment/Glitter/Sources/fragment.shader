#version 150 core
uniform sampler2D texture_diffuse1; // texture

in vec2 fragTexCoord; // texture coord

out vec4 color; // output color of the pixel

void main() {

    vec2 updatedTexCoord = vec2(fragTexCoord.x, fragTexCoord.y);
    color = texture(texture_diffuse1, updatedTexCoord);

}