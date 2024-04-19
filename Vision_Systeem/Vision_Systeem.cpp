// Vision_Systeem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

#include <iostream>
#include "HalconCpp.h"

using HalconCpp::HImage;
using HalconCpp::HRegion;
using HalconCpp::HTuple;

int main()
{
	//Laad de foto in
	HImage img{ "Fotos_Plaatcodes/2.jpg" };

	//Werkende code -> 'Verwachte Area: 2652682'
	HRegion region = img.Threshold(0, 122);
	HRegion connectedRegions = region.Connection();
	HTuple area = connectedRegions.Area();
	std::cout << "Verwachte Area: " << area.L() << '\n'; 
}

