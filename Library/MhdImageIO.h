#pragma once
#include "std_lib_facilities.h"
#include "ImageIOBase.h"


class MHDImageIO : public ImageIOBase {

private:
	static constexpr int N_DIM{ 5 };

	friend class ImageIOFactory;	//used for accesing the filename

protected:
	MHDImageIO(const string& filename);

public:

	Image read() const override;
	void write(Image& image) const override;
	~MHDImageIO() {};
};
