#version 410 core
layout(std140) uniform;

void main() {
    gl_FragDepth = gl_FragCoord.z;

}
