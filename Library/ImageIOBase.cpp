#include "std_lib_facilities.h"
#include "Image.h"
#include "ImageIOBase.h"


ImageIOBase::ImageIOBase(const string& file)
	: filename(file)
{}

ImageIOBase:: ~ImageIOBase() {	//destructor
		
}

ImageIOBase::ImageIOBase()	//default contructor
	:filename("")
{}
