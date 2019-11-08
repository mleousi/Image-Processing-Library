#pragma once
#include "std_lib_facilities.h"
#include "ImageIOBase.h"
#include <memory>


class ImageIOFactory { 

public:
	static unique_ptr<ImageIOBase> getIO(const string& filename);
};