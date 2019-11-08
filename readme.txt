Programming for Medical Imaging
Assignment 2: Image Processing Library
Maria Leousi
Student Number:6619525
08/11/2019

-----------------------------------
Image Processing Library

-----------------------------------

Implemented Filters:
	1)ThresholdImageFilter.h : applies a user-defined threshold to the input image.
	2)StatisticsImageFilter.h : calculates the minimun, maximum and mean intensity values of the input image.
	3)MaskImageFilter.h : applies a mask on the input image.
	4)ConvolutionImageFilter.h : convolves the input image with a 2D kernel.
	5)ComplementImageFilter.h : calculates the complement image of the input image.

-----------------------------------

Notes:
-In ImageIOBase.h/.cpp, I added a default constructor.

-In Image.cpp, I used the std::clamp function that clamps a variable to a predefined range.
-In Image.h/.cpp, I added a default contructor.
-In Image.h/.cpp, I added a function for computing the number of the voxels, imageVoxels().

-For a threshold application on the input image, change the value of the threshold variable in main.cpp, line 37.
-ConvolutionImagefilter.h/.cpp performes a 2D convolution of with the input image with a user-defined kernel
 (change the radius of the kernel in main.cpp, line 71).


