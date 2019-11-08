#include "std_lib_facilities.h"
#include "Image.h"
#include "ImageFilter.h"
#include "StatisticsImageFilter.h"
#include <algorithm>
#include <numeric>


StatisticsImageFilter::T StatisticsImageFilter::getMinIntensity() {
	//computes the min value of the image (function of std)

	T minValue = *min_element(getInput().begin(), getInput().end());
	return minValue;
}

StatisticsImageFilter::T StatisticsImageFilter::getMaxIntensity() {
	//computes the max value of the image (function of std)

	T maxValue = *max_element(getInput().begin(), getInput().end());
	return maxValue;
}

StatisticsImageFilter::T StatisticsImageFilter::getMeanIntensity() {
	//computes the mean value of the image

	T meanValue = (accumulate(getInput().begin(), getInput().end(), 0)) / ((double)getInput().imageVoxels());
	return meanValue;
}

void StatisticsImageFilter::execute(const Image& i) {
	min = getMinIntensity();
	max = getMaxIntensity();
	mean = getMeanIntensity();
}


