#include "std_lib_facilities.h"
#include "Image.h"
#include "ImageFilter.h"
#include "MaskImageFilter.h"


void MaskImageFilter::setMask(const Image& i) {
	mask = &i;
}

const Image* MaskImageFilter::getMask(){
	return mask;
}

void MaskImageFilter::execute(const Image& i) {

	//Resize the output image
	(_output).resize(i.size());

	for (unsigned int t = 0; t < i.dim(4); ++t) {
		for (unsigned int c = 0; c < i.dim(3); ++c) {
			for (unsigned int z = 0; z < i.dim(2); ++z) {
				for (unsigned int y = 0; y < i.dim(1); ++y) {
					for (unsigned int x = 0; x < i.dim(0); ++x) {
						//set _output=0 where mask=0
						if ((*mask)(x, y, z, c, t) == 0)	(_output)(x, y, z, c, t) = 0;
						else (_output)(x, y, z, c, t) = i(x, y, z, c, t);
					}
				}
			}
		}
	}
}