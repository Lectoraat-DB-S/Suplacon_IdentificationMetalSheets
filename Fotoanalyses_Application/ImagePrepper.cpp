//Preprocessing image

#include "ImagePrepper.h"

using namespace HalconCpp;

ImagePrepper::ImagePrepper()
{
	//Do nothing
}

ImagePrepper::ImagePrepper(HImage image)
{
	this->image = image;
}

bool ImagePrepper::execute()
{
	image = image.ZoomImageFactor(ZOOM_FACTOR, ZOOM_FACTOR, "constant");
	image = image.GrayRangeRect(PREPPER_MASK_SIZE, PREPPER_MASK_SIZE);

	Hlong width, height;
	image.GetImageSize(&width, &height);
	image = image.Emphasize(width, height, EMPHASIZE_FACTOR);

	image = image.InvertImage();

	return true;
}

bool ImagePrepper::execute(HImage image)
{
	this->image = image;

	return execute();
}

void ImagePrepper::print()
{
	std::cout << "IMAGE_ZOOM: " << ZOOM_FACTOR << ", EMPHASIZE_FACTOR: " << EMPHASIZE_FACTOR << "\n";
}




