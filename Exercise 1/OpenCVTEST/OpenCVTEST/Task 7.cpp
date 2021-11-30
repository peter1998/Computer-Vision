#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
using namespace std;
using namespace cv;
int DELAY_CAPTION = 1500;
int DELAY_BLUR = 100;
int MAX_KERNEL_LENGTH = 20;
Mat src, src_gray;
Mat dst, detected_edges;
char window_name[] = "Exersize 1. Task 7.";
int lowThreshold = 13;
const int max_lowThreshold = 100;
const int ratio_var = 3;
const int kernel_size = 3;
int display_caption(const char* caption);
int display_dst(int delay);
int threshold_value = 60;
int threshold_type = 0;
int const max_value = 255;
int const max_type = 4;
int const max_binary_value = 255;
const char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
const char* trackbar_value = "Value";

void display_image();
void TaskTwo();
void TaskThree();
void TaskFour();
void TaskFive();
void TaskSix();


static void CannyThreshold(int, void*)
{
	blur(src_gray, detected_edges, Size(3, 3));
	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * ratio_var, kernel_size);
	dst = Scalar::all(0);
	src.copyTo(dst, detected_edges);
	imshow(window_name, dst);
}



static void Threshold_Demo(int, void*)
{
	threshold(src_gray, dst, threshold_value, max_binary_value, threshold_type);
	imshow(window_name, dst);
}



int main()
{
	 display_image();
	std::string image_path = samples::findFile("OpenC.jpg");
	src = imread(image_path, IMREAD_COLOR);
	if (src.empty())
	{
		std::cout << "Could not read the image: " << image_path << std::endl;
		return 1;
	}



	imshow("Original", src);



	dst = src.clone();



	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
	{
		GaussianBlur(src, dst, Size(i, i), 0, 0);
		if (display_dst(DELAY_BLUR) != 0)
		{
			return 0;
		}
	}



	dst.create(dst.size(), dst.type());
	cvtColor(dst, src_gray, COLOR_BGR2GRAY);
	namedWindow(window_name, WINDOW_AUTOSIZE);
	createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);
	CannyThreshold(0, 0);



	cvtColor(dst, src_gray, COLOR_BGR2GRAY); // Convert the image to Gray
	namedWindow(window_name, WINDOW_AUTOSIZE); // Create a window to display results
	createTrackbar(trackbar_type,
		window_name, &threshold_type,
		max_type, Threshold_Demo); // Create a Trackbar to choose type of Threshold
	createTrackbar(trackbar_value,
		window_name, &threshold_value,
		max_value, Threshold_Demo); // Create a Trackbar to choose Threshold value
	Threshold_Demo(0, 0); // Call the function to initialize



	int k = waitKey(0); // Wait for a keystroke in the window
	return 0;
}

 void display_image() {
	std::string image_path = samples::findFile("OpenC.jpg");
	Mat img = imread(image_path, IMREAD_COLOR);
	if (img.empty())
	{
		std::cout << "Could not read the image: " << image_path << std::endl;
		
	}
	imshow("Display window", img);
	int k = waitKey(0); // Wait for a keystroke in the window
	if (k == 's')
	{
		imwrite("OpenC.jpg", img);
	}
	
}



int display_caption(const char* caption)
{
	dst = Mat::zeros(src.size(), src.type());
	putText(dst, caption,
		Point(src.cols / 4, src.rows / 2),
		FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));
	return display_dst(DELAY_CAPTION);
}



int display_dst(int delay)
{
	imshow(window_name, dst);
	int c = waitKey(delay);
	if (c >= 0) { return -1; }
	return 0;
}