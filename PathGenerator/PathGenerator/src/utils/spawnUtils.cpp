#include "spawnUtils.h"

int spawnParticle(float* particulesArray, genType spawnType, int particuleQuantity, int height, int width) {

    int radius = 400.0f;
    
    auto start = std::chrono::system_clock::now();

    genType type = middle_in_donut;
    
    for (int i = 0; i < particuleQuantity; i++) {

        int x = float(rand() % width);
        int y = float(rand() % height);

        if (spawnType == middle_in_circle) {

            while (powf(x - (width / 2), 2.0f) + powf(y - (height / 2), 2.0f) > powf(radius, 2.0f) || (x == width / 2 || y == height / 2)) {
                x = float(rand() % width);
                y = float(rand() % height);
            }

        }
        else if (spawnType == middle_in_square) {
            while (x < width / 2 - radius || x > width / 2 + radius || y < height / 2 - radius || y > height / 2 + radius) {
                x = float(rand() % width);
                y = float(rand() % height);
            }
        }
        else if (spawnType == middle_in_triangle) {
            while (!((y > height / 2 - 250) && 1.5 * (x - width / 2 + 500) > y && -1.5 * (x - width / 2 - 500) > y)) {
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