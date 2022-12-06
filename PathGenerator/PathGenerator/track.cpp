#include "track.h"

void writeMap(float* map,int width, int height){

    std::ofstream mapFileStream;
    mapFileStream.open("./map.csv");

    for (int id = 0; id < width * height; id++) {

        mapFileStream << map[id] << ",";
        if ((id + 1) % width == 0)mapFileStream << std::endl;

    }

    mapFileStream.close();

}

//this function save the map as a bmp image
void saveAsImg(float* map, int width, int height,int id) {


	system("mkdir img");

    FILE** fp = (FILE**)malloc(sizeof(FILE**));

	assert(fp != nullptr);
	//create var name for the file
	//id has to be a string
	char* fileName = (char*)malloc(sizeof(char*) * 20);
	sprintf_s(fileName,20, "./img/map%d.bmp", id);
	
	fopen_s(fp, fileName, "wb");
    
	unsigned char* img = (unsigned char*)malloc(width * height * 3);
	for (int i = 0; i < width * height; i++) {

		img[i * 3] = (unsigned char)(map[i] * 255);
		img[i * 3 + 1] = (unsigned char)0;
		img[i * 3 + 2] = (unsigned char)0;

	}

	unsigned char bmpfileheader[14] = { 'B','M',0,0,0,0,0,0,0,0,54,0,0,0 };
	unsigned char bmpinfoheader[40] = { 40,0,0,0,0,0,0,0,0,0,0,0,1,0,24,0 };

	int filesize = 54 + 3 * width * height;

	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);

	bmpinfoheader[4] = (unsigned char)(width);
	bmpinfoheader[5] = (unsigned char)(width >> 8);
	bmpinfoheader[6] = (unsigned char)(width >> 16);
	bmpinfoheader[7] = (unsigned char)(width >> 24);
	bmpinfoheader[8] = (unsigned char)(height);
	bmpinfoheader[9] = (unsigned char)(height >> 8);
	bmpinfoheader[10] = (unsigned char)(height >> 16);
	bmpinfoheader[11] = (unsigned char)(height >> 24);

	fwrite(bmpfileheader, 1, 14, *fp);
	fwrite(bmpinfoheader, 1, 40, *fp);
	fwrite(img, 1, width * height * 3, *fp);

	fclose(*fp);
}