#pragma warning(default:4996)
#include "std_lib_facilities.h"
#include "Image.h"
#include "ImageIOBase.h"
#include "ImageIOFactory.h"
#include "ImageFilter.h"
#include "ThresholdImageFilter.h"
#include "StatisticsImageFilter.h"
#include "MaskImageFilter.h"
#include "ConvolutionImageFilter.h"
#include "ComplementImageFilter.h"

#include <memory>


int main() {
	cout << "This is the Image Processing Library of Maria Leousi\n";
	cout << "------------------------------------------------------\n" << "\n";
	cout << "Please enter input filename: \n";
	string iname;
	cin >> iname;

	try {
		unique_ptr<ImageIOBase> io = ImageIOFactory::getIO(iname);

		//handle the output filename
		string extension = iname.substr(iname.find('.'));
		int position = iname.find('.');
		string name = iname.substr(0, position);
		//read the input image
		Image image = io->read();

		
		//Threshold Image Filter
		ThresholdImageFilter threshFilter;
		threshFilter.setInput(image);
		int thresh=500;	//user-defined threshold value
		threshFilter.setThreshold(thresh);
		threshFilter.update();

		shared_ptr<Image> image_out_thresh = threshFilter.getOutput();
		string nameOUT_thresh = name + "_threshold" + to_string(thresh) + "_out" + extension;
		io = ImageIOFactory::getIO(nameOUT_thresh);
		io->write(*image_out_thresh);		

		
		//Statistics Image Filter
		StatisticsImageFilter statFilter;
		statFilter.setInput(image);
		statFilter.update();
		int maxValue = statFilter.getMaxIntensity();
		int minValue = statFilter.getMinIntensity();
		int meanValue = statFilter.getMeanIntensity();


		//Mask Image Filter
		MaskImageFilter maskFilter;
		maskFilter.setInput(image);
		maskFilter.setMask(*image_out_thresh);	//binary image obtained after the threshold application
		maskFilter.update();

		shared_ptr<Image> image_out_mask = maskFilter.getOutput();
		string nameOUT_mask = name + "_mask" + "_out" + extension;
		io = ImageIOFactory::getIO(nameOUT_mask);
		io->write(*image_out_mask);

		
		//Convolution Image Filter
		ConvolutionImageFilter convFilter;
		convFilter.setInput(image);
		int convolutionRadius = 5;	//user-defined kernel radius
		convFilter.setRadius(convolutionRadius);
		convFilter.update();

		shared_ptr<Image> image_out_conv = convFilter.getOutput();
		string nameOUT_conv = name + "_convolution" + to_string(convolutionRadius) + "_out" + extension;
		io = ImageIOFactory::getIO(nameOUT_conv);
		io->write(*image_out_conv);
		

		//Complement Image Filter
		ComplementImageFilter compFilter;
		compFilter.setInput(image);
		compFilter.update();

		shared_ptr<Image> image_out_comp = compFilter.getOutput();
		string nameÏUT_comp = name + "_complement" + "_out" + extension;
		io = ImageIOFactory::getIO(nameÏUT_comp);
		io->write(*image_out_comp);
	}

	catch (const char* exception) {
		cerr << "Error: " << exception << endl;
	}
}