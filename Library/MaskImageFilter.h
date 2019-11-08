#pragma once
#include "std_lib_facilities.h"
#include "Image.h"
#include "ImageFilter.h"


class MaskImageFilter : public ImageFilter {
private:
	typedef short T;
	const Image* mask;

protected:
	// Override the execute function
	virtual void execute(const Image& i) override;

public:
	// Set and get functions for the binary image mask
	void setMask(const Image& i);
	const Image* getMask();
};