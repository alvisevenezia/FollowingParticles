#version 460 core

out vec4 FragColor;

uniform vec4 ourColor = vec4(0.8f,0.49f,0.12f,1.0f);

void main(){

	FragColor = ourColor;

}