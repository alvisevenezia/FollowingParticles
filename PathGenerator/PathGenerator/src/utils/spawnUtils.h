#pragma once
#include <random>
#include <chrono>
#include <ctime>
#include <iostream>

enum genType {

	random,
	middle_in_circle,
	middle_in_square,
	middle_in_triangle,
	middle_in_donut,
	multiple_circle
	
};

int spawnParticle(float* particulesArray, genType spawnType, int particuleQuantity, int height, int width);

int spawnParticule_in_circle(float* particulesArray,int arrayIndex, int particuleQuantity, int x, int y, int radius);

int spawnParticule_in_triangle(float* particulesArray, int arrayIndex, int particuleQuantity, int x, int y, int height);