#ifndef IMAGEPREPPER_H
#define IMAGEPREPPER_H

#define ZOOM_FACTOR 0.25
#define PREPPER_MASK_SIZE 5
#define EMPHASIZE_FACTOR 2

#include "HalconCpp.h"

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

