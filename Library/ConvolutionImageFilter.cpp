#include "std_lib_facilities.h"
#include "Image.h"
#include "ImageFilter.h"
#include "ConvolutionImageFilter.h"
#include <cmath>


ConvolutionImageFilter::T ConvolutionImageFilter::getRadius() const {
	//gets the radius of the kernel

	return radius;
}

void ConvolutionImageFilter::setRadius(T r) {
	//sets the radius of the kernel

	radius = r;
	defineKernel();
}

double** ConvolutionImageFilter::defineKernel() {
	//define a kernel of the given radius with its elements assigned to 1/(radius*radius)

	radius = getRadius();
	kernelX = radius / 2;
	kernelY = radius / 2;

	T sizeX = radius;
	T sizeY = radius;

	//dynamic allocation of a 2D array
	double** kernelMask = new double* [sizeY];
	for (int i = 0; i < sizeY; ++i)
		kernelMask[i] = new double[sizeX];

	for (int j = 0; j < radius; ++j) {
		for (int i = 0; i < radius; ++i) {
			kernelMask[i][j] = (1.0) / (pow(radius, 2));
		}
	}
	return kernelMask;
}


ConvolutionImageFilter::Image& ConvolutionImageFilter::blur(const Image& image, T radius) {
	//calculate an averaging within that radius around each voxel

	T sum = 0;
	this->setInput(image);
	double** convMask;
	convMask = defineKernel();

	for (unsigned int t = 0; t < image.dim(4); ++t) {
		for (unsigned int c = 0; c < image.dim(3); ++c) {
			for (unsigned int z = 0; z < image.dim(2); ++z) {
				for (unsigned int y = 0; y < image.dim(1); ++y) {
					for (unsigned int x = 0; x < image.dim(0); ++x) {
						sum = 0;
						for (int i = 0; i < radius; ++i) {	//loop inside the kernel
							for (int j = 0; j < radius; ++j) {
								//borders checking
								if ((y + i) > 0 || (y + i) < image.dim(1) || (x + j) > 0 || (x + j) < image.dim(0))
									sum = sum + image(x + i - 1, y + j - 1, z, c, t) * convMask[i][j];
							}
						}
						(_output)(x, y, z, c, t) = sum;
					}
				}
			}
		}
	}
	return _output;
}

void ConvolutionImageFilter::execute(const Image& i) {

	//Resize the output image
	(_output).resize(i.size());
	T convolutionRadius = getRadius();

	//if the radius is 0 or lower, the image remains unchanged
	if (convolutionRadius <= 0) {
		for (unsigned int t = 0; t < i.dim(4); ++t) {
			for (unsigned int c = 0; c < i.dim(3); ++c) {
				for (unsigned int z = 0; z < i.dim(2); ++z) {
					for (unsigned int y = 0; y < i.dim(1); ++y) {
						for (unsigned int x = 0; x < i.dim(0); ++x) {
							(_output)(x, y, z, c, t) = i(x, y, z, c, t);
						}
					}
				}
			}
		}
	}
	else {
		_output = blur(i, convolutionRadius);
	}
}