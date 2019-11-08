#include "std_lib_facilities.h"
#include "PipImageIO.h"
#include "ImageIOBase.h"
#include <memory>
#define headerBytes 21


PIPImageIO::PIPImageIO(const string & filename)	//override constructor
	:ImageIOBase(filename)
{}

Image PIPImageIO::read() const {

	dimension dimensions = { 1,1,1,1,1 };	//initialize the dimensions to 1 each
	ifstream ifs{ filename, ios_base::binary };	//create a file stream made of binary info
	if (!ifs) throw "Cannot open the file.";

	while (ifs.good()) {
		//find the type
		char type;
		ifs.read(as_bytes(type), sizeof(char));
		if (int(type) != 2) throw "Wrong pixel type in PIP image";

		//find the dimensions
		int position = 0;
		for (int i; ifs.read(as_bytes(i), sizeof(int));) {	//read the first 4 bytes
			dimensions[position] = i;
			++position;
			if (position > 4) break;
		}

		Image image(dimensions);

		//find the image
		int pos = 0;
		for (short z; ifs.read(as_bytes(z), sizeof(short));) {	//sizeof(short)=2
			image.begin()[pos] = z;
			++pos;
			//check if image data is left out. 
			//according to the dimensions, if more voxels were found when reading the image data
			//throw an error
			if (pos > image.imageVoxels()) throw "PIP image is bigger than expected\n";
		}

		//check if image data is missing.
		//according to the dimensions, if lesser voxels were found when reading the image data
		//throw an error
		if (image.imageVoxels() > pos) throw "PIP image is incomplete\n";

		if (ifs.eof()) {
			ifs.close();
			Image& img = image;
			return img;
		}
	}

}

void PIPImageIO::write(Image& image) const {

	//write the output image
	ofstream ofs{ filename,ios_base::binary };
	// binary tells the stream not to try anything clever with the bytes
	if (!ofs) error("can't open output file ", filename);

	while (ofs.is_open()) {
		//save the type
		char type = 2;
		ofs.write(as_bytes(type), sizeof(char));

		//save the dimensions
		dimension dimensions = image.size();
		int d = 0;
		for (int j = 1; j < headerBytes; j += sizeof(int)) {	//since the size of the header is 21 bytes
			ofs.write(as_bytes(image.dim(d)), sizeof(int));
			++d;
		}

		//save the image
		for (int i = 0; i < image.imageVoxels(); ++i)
			ofs.write(as_bytes(image.begin()[i]), sizeof(short));

		ofs.close();
	}
}








