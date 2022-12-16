#include "spawnUtils.h"

int spawnParticle(float* particulesArray, genType spawnType, int particuleQuantity, int height, int width) {

    int radius = 400.0f;

    auto start = std::chrono::system_clock::now();

    if (spawnType == middle_in_circle)  spawnParticule_in_circle(particulesArray, 0, particuleQuantity, width / 2, height / 2, 250);
    else if (spawnType == multiple_circle) {

        //spawn particule in for circle of 1/4 of the population
        spawnParticule_in_circle(particulesArray, 0, particuleQuantity / 4, width / 4, height / 4, 200);
        spawnParticule_in_circle(particulesArray, particuleQuantity / 4, particuleQuantity / 4, width / 4, 3 * height / 4, 200);
        spawnParticule_in_circle(particulesArray, particuleQuantity / 2, particuleQuantity / 4, 3 * width / 4, 3 * height / 4, 200);
        spawnParticule_in_circle(particulesArray, 3 * particuleQuantity / 4, particuleQuantity / 4, 3 * width / 4, height / 4, 200);
    }

    else if (spawnType == middle_in_triangle) spawnParticule_in_triangle(particulesArray, 0, particuleQuantity, width / 2, height / 2, 250);
    else {

        for (int i = 0; i < particuleQuantity; i++) {

            int x = float(rand() % width);
            int y = float(rand() % height);


            if (spawnType == middle_in_square) {
                while (x < width / 2 - radius || x > width / 2 + radius || y < height / 2 - radius || y > height / 2 + radius) {
                    x = float(rand() % width);
                    y = float(rand() % height);
                }
            }
            else if (spawnType == middle_in_donut) {

                while (powf(x - (width / 2), 2.0f) + powf(y - (height / 2), 2.0f) > powf(radius, 2.0f) || (x == width / 2 || y == height / 2)
                    ||
                    powf(x - (width / 2), 2.0f) + powf(y - (height / 2), 2.0f) < powf((radius - 100), 2.0f) || (x == width / 2 || y == height / 2)) {
                    x = float(rand() % width);
                    y = float(rand() % height);
                }

            }


            particulesArray[i * 3] = x;
            particulesArray[i * 3 + 1] = y;

            //generate random angle betwenn 0 and 2pi
            float angle = float(rand() % 628) / 100.0f;

            particulesArray[i * 3 + 2] = angle;

        }



        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);

        std::cout << "elapsed time: " << elapsed_seconds.count() << "s"
            << std::endl;

        return 0;
    }
}

int spawnParticule_in_circle(float* particulesArray, int arrayIndex, int particuleQuantity, int x, int y, int radius) {

	for (int i = 0; i < particuleQuantity; i++) {

        int coordX = x + float(rand() % (radius*2)) - radius;
        int coordY = y + float(rand() % (radius*2)) - radius;

        while (powf(coordX - (x), 2.0f) + powf(coordY - (y), 2.0f) > powf(radius, 2.0f)) {
            
            coordX = x + float(rand() % (radius * 2)) - radius;
            coordY = y + float(rand() % (radius * 2)) - radius;
        
        }
        

        particulesArray[arrayIndex + i * 3] = coordX;
		particulesArray[arrayIndex + i * 3 + 1] = coordY;

		//generate random angle betwenn 0 and 2pi
		float angle = float(rand() % 628) / 100.0f;

		particulesArray[arrayIndex + i * 3 + 2] = angle;

	}

	return 0;
}

int spawnParticule_in_triangle(float* particulesArray, int arrayIndex, int particuleQuantity, int x, int y, int height) {

    for (int i = 0; i < particuleQuantity; i++) {

        int coordX = x + float(rand() % (height * 2)) - height;
        int coordY = y + float(rand() % (height * 2)) - height;

		while (coordY <= y - height / 2 && coordY > 1.5*coordX ) {

            coordX = x + float(rand() % (height * 2)) - height;
            coordY = y + float(rand() % (height * 2)) - height;

        }


        particulesArray[arrayIndex + i * 3] = coordX;
        particulesArray[arrayIndex + i * 3 + 1] = coordY;

        //generate random angle betwenn 0 and 2pi
        float angle = float(rand() % 628) / 100.0f;

        particulesArray[arrayIndex + i * 3 + 2] = angle;

    }

    return 0;
    
}