#version 460 core

#define PI 3.1415

layout(local_size_x = 32,local_size_y = 32, local_size_z = 1) in;

struct particle{
	vec2 pos;
	float angle;
};

layout(std430,binding = 1) buffer particulesBuffer{
	float particles[];
};

layout(std430,binding = 2)buffer mapBuffer{
	float map[];
};

uniform float seed,offsetAngle;
uniform int WIDTH,HEIGHT,snifSize,snifRange;

int localSeed;

//checks if new coordonate is on the map
int outOfBound(int x,int bound){

	if(x<0)return 0;
	if(x>=bound)return bound-1;
	return x;
}

//generate a random number
float random(){
	localSeed = (localSeed<<13) ^ localSeed;
	float rand = (1.0f - ((localSeed * (localSeed * localSeed * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
	return rand;
}

//this function count the number of particule in a zone
//the input is the coordonate of the zone
//the zone is a square
float snifZone(ivec2 coord){

	float count = 0.0f;
	int x,y;
	for(int i = 0;i<snifSize;i++){
		for(int j = 0;j<snifSize;j++){
			x = outOfBound(coord.x+i-snifSize/2,WIDTH);
			y = outOfBound(coord.y+j-snifSize/2,HEIGHT);
			count += map[y*WIDTH+x];
		}
	}
	return count;

}

//this funciton return a random angle between 0 and 2PI
float randomAngle(){
	return random()*2.0f*PI;
}


//this function return the angle to the most populated zone in front of the particule
//id is the id of the particule
//angle is the angle of the particule
float snif(int id,float angle){


	//get the coord of the particle
	ivec2 coord = ivec2(particles[id*3],particles[id*3+1]);
	
	//the first zone is on the front right of the particules at offsetAngle
	//the 2nd is in front
	//the 3rd is on the front left of the particules at offsetAngle
	//all zone are at a distance of snifRange
	
	//the first zone
	float zone1 = snifZone(coord+ivec2(snifRange*cos(angle+offsetAngle),snifRange*sin(angle+offsetAngle)));
	//the second zone
	float zone2 = snifZone(coord+ivec2(snifRange*cos(angle),snifRange*sin(angle)));
	//the third zone
	float zone3 = snifZone(coord+ivec2(snifRange*cos(angle-offsetAngle),snifRange*sin(angle-offsetAngle)));
	
	//return the angle of the most populated zone
	if(zone3>zone1 && zone3>zone2)return angle-offsetAngle;
	if(zone1>zone2 && zone1>zone3)return angle+offsetAngle;
	return angle;

	
}

void main(){

	localSeed = int(seed);
	
	//get the particule id
	int id = int(gl_GlobalInvocationID.x+gl_GlobalInvocationID.y*gl_NumWorkGroups.x*gl_WorkGroupSize.x);
	
	//get the particule coordonate
	vec2 coord = vec2(particles[id*3],particles[id*3+1]);
	
	//get the particule angle
	float angle = particles[id*3+2];
	
	//find the angle to the most populated zone
	float newAngle = snif(id,angle);

	//make the particule move
	coord.x = coord.x + cos(newAngle);
	coord.y = coord.y + sin(newAngle);
	
	//if particule goes ouside make it bounce

	if(coord.y<=0 || coord.y>=HEIGHT){
		
		newAngle = 2*PI - newAngle;
		
	}else if(coord.x<=0 || coord.x>=WIDTH){
		
		newAngle = PI - newAngle;
		
	}
	
	//set newAngle as the modulo of newAngle by 2pi
	newAngle = newAngle - 2*PI*floor(newAngle/(2*PI));

	//update the particule position and angle
	particles[id*3] = coord.x;
	particles[id*3+1] = coord.y;
	particles[id*3+2] = newAngle;
	
	//set the map value to 1
	map[int(coord.y)*WIDTH+int(coord.x)] = 1.0f;

}