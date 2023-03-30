#pragma once
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	if (argc != 2) {
		cerr << "this program is designed to take in an image file as an argument, nothing else";
		return 1;
	}
	else {
		string filename = argv[1];
		Mat image = imread(filename, IMREAD_UNCHANGED);
		if (image.empty()) {
			cerr << "failed to load image " << filename << " try a different file\n";
			return 1;
		}
		cout << "Image " << filename << " has successfully been loaded\n the width of the image is: "
			<< image.cols << " \n The image height is: " << image.rows << "\n ";
		cout << "the number of channels is: " << image.channels() << "\n and the bits per pixel of the image is: " << (image.depth() * 8) / image.channels();
		char* data = new char[image.elemSize() * image.cols * image.rows];
		if (data == NULL) {
			return 1;
		}
			memcpy(data, image.data, image.elemSize() * image.cols * image.rows);
			delete[] data;
		return 0;
	}
}