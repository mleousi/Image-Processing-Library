#include "std_lib_facilities.h"
#include "Image.h"
#include "ImageFilter.h"
#include "ThresholdImageFilter.h"
#include <algorithm>
#include <numeric>


ThresholdImageFilter::ThresholdImageFilter() : _t(0) {}

ThresholdImageFilter::T ThresholdImageFilter::getThreshold() {
	return _t;
}

void ThresholdImageFilter::setThreshold(T threshold) {
	_t = threshold;
}

void ThresholdImageFilter::execute(const Image& i) {
	// Clear and resize the output
	(_output).resize(i.size());

	// Bring the threshold parameter within scope, so it can be given to
	// the lambda initializer
	const auto t = _t;

	// Do the thresholding with an std::transform, see Chapter 21
	transform(i.begin(), i.end(), (_output).begin(),
		[t](T value) { return value > t ? T(1) : T(0); }
	);
}
