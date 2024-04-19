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
	image = image.GrayRangeRect(MASK_SIZE, MASK_SIZE);

	Hlong width, height;
	image.GetImageSize(&width, &height);
	image = image.Emphasize(width, height, EMPHASIZE_FACTOR);

	image = image.InvertImage();

	return true;
};

void PrepImage::print()
{
	std::cout << "ZOOM: " << ZOOM_FACTOR << ", MASK: " << MASK_SIZE << ", EMPHASIZE: " << EMPHASIZE_FACTOR << "\n";
};




