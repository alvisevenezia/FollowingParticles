#version 460 core

out vec4 FragColor;

uniform vec4 ourColor = vec4(1.0f,0.0f,0.0f,1.0f);

void main(){

	FragColor = ourColor;

}