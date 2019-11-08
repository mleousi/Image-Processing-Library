#include "std_lib_facilities.h"
#include "MhdImageIO.h"
#include "ImageIOBase.h"


MHDImageIO::MHDImageIO(const string& filename)	//override constructor
	:ImageIOBase(filename)
{}

Image MHDImageIO::read() const {

	dimension dimensions = { 1,1,1,1,1 };	//initialize the dimensions to 1 each
	int ndim;
	string dims;
	string type;
	string datafile;
	stringstream ss;
	size_t position;

	ifstream ifs_text{ filename };
	string line;

	if (!ifs_text) throw "Cannot open the file.";

	while (ifs_text.good()) {

		while (getline(ifs_text, line)) {
			string findNdims = "NDims = ";
			string findDimsize = "DimSize = ";
			string findType = "ElementType = ";
			string findDatafile = "ElementDataFile = ";

			size_t pos;
			string x;

			//find the number of the dimensions
			if (line.find(findNdims) != std::string::npos) {
				pos = line.find(findNdims);
				x = line.substr(pos + findNdims.size());
				ndim = stoi(x);	//convert to int
			}

			//find the size of the dimensions
			else if (line.find(findDimsize) != std::string::npos) {
				pos = line.find(findDimsize);
				x = line.substr(pos + findDimsize.size());
				dims = x;

				string temp;
				ss << dims;
				int position = 0;
				//count the number of the dimensions found
				int count = 0;
				while (ss >> dims) ++count;
				//if that number differs from the expected one, throw an error
				if (count != 3) throw "Number of dimensions differs from the expected number.";

				stringstream stream(x);
				for (int i = 0; stream >> i; ) {
					dimensions[position] = i;
					++position;
				}
			}

			//find the type of the image file
			else if (line.find(findType) != std::string::npos) {
				pos = line.find(findType);
				x = line.substr(pos + findType.size());
				type = x;
				//if the image is not of type MET_SHORT throw an error
				if (type != "MET_SHORT") throw "Wrong image type.";
			}
			//find the name of the image file
			else if (line.find(findDatafile) != std::string::npos) {
				pos = line.find(findDatafile);
				x = line.substr(pos + findDatafile.size());
				datafile = x;
			}
		}
		ifs_text.close();
	}


	Image image(dimensions);
	ifstream ifs{ datafile, ios_base::binary };
	if (!ifs) error("Cannot open the file ", datafile);

	while (ifs.good()) {

		//find the image data
		int position = 0;
		for (short z; ifs.read(as_bytes(z), sizeof(short));) {
			image.begin()[position] = z;
			++position;
			//if (position > image.imageVoxels()) throw "MHD image is bigger than expected\n";
		}

		//if (image.imageVoxels() > position) throw ("MHD image is incomplete\n");

		if (ifs.eof()) {
			ifs.close();
			Image& img = image;
			return img;
		}
	}

}

void MHDImageIO::write(Image& image) const {
	//save the .mhd
	ofstream os(filename);
	string findNdims = "NDims = ";
	string findDimsize = "DimSize = ";
	string findType = "ElementType = ";
	string findDatafile = "ElementDataFile = ";

	int dims = image.nr_dims();
	dimension dimensions = image.size();
	int position = filename.find('.');
	string name = filename.substr(0, position);

	if (os.is_open()) {
		os << findNdims << dims << endl;

		os << findDimsize;
		for (int i = 0; i < dims; ++i) {
			os << " " << dimensions[i];
		}
		os << endl;

		os << findType << "MET_SHORT" << endl;

		os << findDatafile << name << ".raw" << endl;
	}
	os.close();

	//save the image(.raw)
	string rawFile = name + ".raw";

	ofstream ofs{ rawFile, ios_base::binary };
	if (ofs.is_open()) {
		int pos = 0;
		for (int i = 0; i < image.imageVoxels(); i += sizeof(short)) {
			ofs.write(as_bytes(image.begin()[pos]), sizeof(short));
			++pos;
		}
	}
	ofs.close();
}