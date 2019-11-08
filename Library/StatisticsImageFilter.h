#pragma once
#include "std_lib_facilities.h"
#include "Image.h"
#include "ImageFilter.h"


class StatisticsImageFilter : public ImageFilter {

private:
	typedef short T;
	T min;
	T max;
	T mean;

protected:
	// Override the execute function
	virtual void execute(const Image& i) override;

public:
	T getMinIntensity();
	T getMaxIntensity();
	T getMeanIntensity();
};