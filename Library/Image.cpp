#include "std_lib_facilities.h"
#include "Image.h"
#include <iterator>
#include <numeric>
#include <algorithm>


//----------- Templates -----------
template <typename T>
T clamp(const T& n, const T& lower, const T& upper) {
	return std::max(lower, std::min(n, upper));
}


Image::Image(dimension dim) {					//constructor
	_dimensions = dim;
	_data = new T[imageVoxels()];
}

Image::Image(const Image& image) {				//copy contructor
	_dimensions = image._dimensions;
	_data = new T[image.imageVoxels()];
	for (int i = 0; i < imageVoxels(); ++i)	_data[i] = image.begin()[i];
}

Image::Image(Image&& image)						//move constructor
	:_dimensions({ 1,1,1,1,1 }), _data(nullptr)
{
	_data = image._data;
	_dimensions = image._dimensions;

	for (int i = 0; i < image.nr_dims(); ++i) {
		image._dimensions[i] = 1;
	}
	image._data = nullptr;
}


Image::Image() {								//default constructor 
	_dimensions = { 1,1,1,1,1 };
	//_data = nullptr;
}

Image::~Image() {								//destructor

	delete _data;
}

Image& Image::operator=(const Image& image) {	//copy assignment
	if (&image == this)	return *this;
	delete _data;

	_dimensions = image._dimensions;
	_data = new T[image.imageVoxels()];

	for (int i = 0; i < image.imageVoxels(); ++i) _data[i] = image.begin()[i];
	return *this;
}

Image& Image::operator=(Image&& image) {			//move assignment
	if (&image == this)	return *this;

	delete _data;

	_dimensions = image._dimensions;
	_data = image._data;

	for (int i = 0; i < image.nr_dims(); ++i) {
		image._dimensions[i] = 1;
	}
	image._data = nullptr;

	return *this;
}

Image::iterator Image::begin() {
	return _data;
}

Image::iterator Image::end() {
	return _data + imageVoxels();
}

Image::const_iterator Image::begin() const {
	return _data;
}

Image::const_iterator Image::end() const {
	return _data + imageVoxels();
}

Image::dimension Image::size() const {
	return _dimensions;
}

unsigned int Image::dim(unsigned int d) const {
	return _dimensions[d];
}

unsigned int Image::nr_dims() const {
	unsigned int count = 0;
	for (unsigned int i = 0; i < _dimensions.size() - 1; ++i) {
		if (Image::_dimensions[i] > 1)	++count;
	}
	return count;
}

void Image::resize(const dimension& d) {
	//create an empty image of the new size

	_dimensions = d;
	_data = new T[imageVoxels()];
}

Image::value_type Image::operator()(int x, int y, int z, int c, int t) const {
	//return the value of a voxel

	//check if position is outside the image range
	x = clamp(x, 0, _dimensions[0] - 1);	//clamp(x,lower,upper)
	y = clamp(y, 0, _dimensions[1] - 1);
	z = clamp(z, 0, _dimensions[2] - 1);
	c = clamp(c, 0, _dimensions[3] - 1);
	t = clamp(t, 0, _dimensions[4] - 1);

	int position = (t * _dimensions[0] * _dimensions[1] * _dimensions[2] * _dimensions[3]) +
		(c * _dimensions[0] * _dimensions[1] * _dimensions[2]) +
		(z * _dimensions[0] * _dimensions[1]) +
		(y * _dimensions[0]) +
		x;
	return _data[position];
}

Image::reference Image::operator()(int x, int y, int z, int c, int t) {

	//check if position is outside the image range
	x = clamp(x, 0, _dimensions[0] - 1);
	y = clamp(y, 0, _dimensions[1] - 1);
	z = clamp(z, 0, _dimensions[2] - 1);
	c = clamp(c, 0, _dimensions[3] - 1);
	t = clamp(t, 0, _dimensions[4] - 1);

	int position = (t * _dimensions[0] * _dimensions[1] * _dimensions[2] * _dimensions[3]) +
		(c * _dimensions[0] * _dimensions[1] * _dimensions[2]) +
		(z * _dimensions[0] * _dimensions[1]) +
		(y * _dimensions[0]) +
		x;
	return _data[position];
}

int Image::imageVoxels() const {
	//calculate the number of voxels in an image

	int num = 1;
	for (int i = 0; i < N_DIM; ++i) {
		num = num * Image::_dimensions[i];
	}
	return num;
}

