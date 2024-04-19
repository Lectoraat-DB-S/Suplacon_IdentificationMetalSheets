#ifndef PREP_IMAGE_H
#define PREP_IMAGE_H

#define ZOOM_FACTOR 0.25
#define MASK_SIZE 5
#define EMPHASIZE_FACTOR 2

#include "HalconCpp.h"

class PrepImage
{

private:
	HalconCpp::HImage image;

public:
	PrepImage(HalconCpp::HImage image);

	bool execute();
	void print();

	HalconCpp::HImage getImage() { return image; };
};

#endif

