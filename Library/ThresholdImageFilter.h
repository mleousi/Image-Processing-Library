#pragma once
#include "std_lib_facilities.h"
#include "Image.h"
#include "ImageFilter.h"
#include <algorithm>
#include <numeric>

class ThresholdImageFilter : public ImageFilter {

	typedef short T;
public:
	// Constructor that initializes the threshold at 0
	ThresholdImageFilter();

	// Get and set functions for the threshold value
	T getThreshold();
	void setThreshold(T threshold);

protected:
	// Override the execute function
	virtual void execute(const Image& i) override;

private:
	// The threshold
	T _t;
};
