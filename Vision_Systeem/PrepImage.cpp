//Preprocessing image

#include "PrepImage.h"

using namespace HalconCpp;

PrepImage::PrepImage(HImage image)
{
	this->image = image;
};

bool PrepImage::execute()
{
	image = image.ZoomImageFactor(ZOOM_FACTOR, ZOOM_FACTOR, "constant");
	image = image.Rgb1ToGray();
	image = image.GrayRangeRect(PREPPER_MASK_SIZE, PREPPER_MASK_SIZE);

	Hlong width, height;
	image.GetImageSize(&width, &height);
	image = image.Emphasize(width, height, EMPHASIZE_FACTOR);

	image = image.InvertImage();

	return true;
};

void PrepImage::print()
{
	std::cout << "IMAGE_ZOOM: " << ZOOM_FACTOR << ", EMPHASIZE_FACTOR: " << EMPHASIZE_FACTOR << "\n";
};




