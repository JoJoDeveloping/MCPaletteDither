#version 450
layout(location=0) in vec2 pos;
layout(location=1) in vec2 uv_in;
uniform float blue;
smooth out vec3 incol;
void main() {
  gl_Position = vec4(pos, 0., 1.);
  incol=vec3(0.5*pos+vec2(0.5), blue);
}

