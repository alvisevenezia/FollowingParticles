#version 460 core

out vec4 FragColor;

uniform vec4 ourColor = vec4(0.42f,1.0f,0.25f,1.0f);

void main(){

	FragColor = ourColor;

}