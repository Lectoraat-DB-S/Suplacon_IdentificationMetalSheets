#ifndef IMAGEPREPPER_H
#define IMAGEPREPPER_H

//The following macros are used to configure the ImagePrepper class.
#define ZOOM_FACTOR 1 //Scale factor for the width and height of the input image.
#define PREPPER_MASK_SIZE 5 //Width and height of the filter mask
#define EMPHASIZE_FACTOR 2 //Intensity of contrast emphasis

#include "HalconCpp.h"

//This class is used to improve the visibility of digits on a given image.
class ImagePrepper
{
private:
	HalconCpp::HImage image;

public:
	ImagePrepper();
	ImagePrepper(HalconCpp::HImage image);

	bool execute();
	bool execute(HalconCpp::HImage image);
	void print();

	HalconCpp::HImage getImage() { return image; };
};

#endif

