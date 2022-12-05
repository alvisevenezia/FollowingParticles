#version 460 core

out vec4 FragColor;

uniform vec4 ourColor = vec4(0.7f,0.4f,0.5f,1.0f);

void main(){

	FragColor = ourColor;

}