#version 460 core

layout (location = 0) in vec4 aPos;

uniform int HEIGHT,WIDTH;

void main(){

	gl_Position = vec4((aPos.x -WIDTH/2) / (WIDTH/2),(aPos.y-HEIGHT/2)/(HEIGHT/2),0.0f,1.0f);

}