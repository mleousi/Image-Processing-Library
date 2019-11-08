#pragma once
#include "std_lib_facilities.h"
#include "Image.h"
#include "ImageFilter.h"


class ComplementImageFilter : public ImageFilter {
	typedef short T;

private:
	T max;

protected:
	// Override the execute function
	virtual void execute(const Image& i) override;

public:
	// Get functions for the maximun intesity value
	T getMaxIntensity();
};
