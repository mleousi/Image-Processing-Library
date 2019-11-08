#pragma once
#include "std_lib_facilities.h"
#include "Image.h"
#include "ImageFilter.h"


class ConvolutionImageFilter :public ImageFilter {

private:
	typedef short T;
	T radius;
	int kernelX, kernelY;


protected:
	// Get functions for the radius of the kernel
	T getRadius() const;
	// Function that defines the kernel
	double** defineKernel();
	// Function tha calculates the average of a neighborhood
	Image& blur(const Image& i, T radius);

	// Override the execute function
	virtual void execute(const Image& i) override;

public:
	// Set functions for the radius of the kernel
	void setRadius(T r);
};

