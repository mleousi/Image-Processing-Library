#include "std_lib_facilities.h"
#include "Image.h"
#include "ImageIOFactory.h"
#include "ImageIOBase.h"
#include "PipImageIO.h"
#include "MhdImageIO.h"



unique_ptr<ImageIOBase> ImageIOFactory::getIO(const string& filename) {

	string extension = filename.substr(filename.find('.'));	//get the file extension

	//if the file is a PIP, create a ImageIOBase pointer pointing to a PIP object
	if (extension == ".pip") {
		unique_ptr<ImageIOBase> baseObject(new PIPImageIO(filename));
		return baseObject;
	}

	//if the file is MHD, create a ImageIOBase pointer pointing to a MHD object
	else if (extension == ".mhd") {
		unique_ptr<ImageIOBase> baseObject(new MHDImageIO(filename));
		return baseObject;
	}

	//else create an ImageIOBase object pointing to null
	else {
		unique_ptr<ImageIOBase> baseObject = nullptr;
		return baseObject;
	}
}
