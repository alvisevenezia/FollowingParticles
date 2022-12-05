#version 460 core

layout(local_size_x = 10,local_size_y = 10, local_size_z = 1) in;

layout(std430,binding = 2)buffer mapBuffer{
	float map[];
};

uniform float decayRate;

void main(){

	uint locationIndex = gl_LocalInvocationID.z * gl_WorkGroupSize.x * gl_WorkGroupSize.y + (gl_LocalInvocationID.y -1) * gl_WorkGroupSize.x + gl_LocalInvocationID.x;
	uint i = locationIndex+(gl_WorkGroupSize.x*gl_WorkGroupSize.y*gl_WorkGroupID.x);
	
	float newMapValue = map[i] - decayRate;

	map[i] = newMapValue <= 0.09f? 0.0f:newMapValue;
}