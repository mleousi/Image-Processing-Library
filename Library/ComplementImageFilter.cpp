#include "std_lib_facilities.h"
#include "Image.h"
#include "ImageFilter.h"
#include "ComplementImageFilter.h"
#include <numeric>


ComplementImageFilter::T ComplementImageFilter::getMaxIntensity() {
	//compute the max intensity value of the image (function of std)
	
	T maxValue = *max_element(getInput().begin(), getInput().end());
	return maxValue;
}

void ComplementImageFilter::execute(const Image& i) {

	this->setInput(i);
	max = this->getMaxIntensity();

	//Resize the output image
	(_output).resize(i.size());

	for (unsigned int t = 0; t < i.dim(4); ++t) {
		for (unsigned int c = 0; c < i.dim(3); ++c) {
			for (unsigned int z = 0; z < i.dim(2); ++z) {
				for (unsigned int y = 0; y < i.dim(1); ++y) {
					for (unsigned int x = 0; x < i.dim(0); ++x) {
						(_output)(x, y, z, c, t) = max - i(x, y, z, c, t);
					}
				}
			}
		}
	}
}