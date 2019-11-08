#pragma once
#include "std_lib_facilities.h"
#include "Image.h"


class ImageIOFactory;

class ImageIOBase :public Image {

private:

	ImageIOBase(const ImageIOBase&) = delete;	//delete copy constructor
	ImageIOBase& operator=(const ImageIOBase&) = delete;	//delete assignment operator

	static constexpr int N_DIM{ 5 };

	friend class ImageIOFactory;

protected:
	ImageIOBase(const string& filename);	//constructor
	const string& filename;

public:

	virtual ~ImageIOBase();		//destructor

	ImageIOBase();	//default constructor

	virtual Image read() const = 0;
	virtual void write(Image& image) const = 0;

};