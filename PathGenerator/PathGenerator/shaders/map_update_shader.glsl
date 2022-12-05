#version 460 core

layout(local_size_x = 10,local_size_y = 10, local_size_z = 1) in;

layout(std430,binding = 2)buffer mapBuffer{
	float map[];
};

uniform int frameRate;

void main(){

	//get the id of the particule
	uint id = gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;
	
	//decrease the map value by 0.1f and make sure it stays positiv
	map[id] -= 0.1f;
	if(map[id] < 0.0f)map[id] = 0.0f;

}