# Getting Started with Images

## Goal 
```
Read an image from file (using cv::imread)
Display an image in an OpenCV window (using cv::imshow)
Write an image to a file (using cv::imwrite)
```
## Obstacle
```
go to environment variable create a new parameter "OPENCV_SAMPLES_DATA_PATH"
add the location "...\sample\data" to your value
restart your IDE
you can run the sample data automatically.
```
## Explanation
```
This repository contains 

Now, let's analyze the main code. As a first step, we read the image "starry_night.jpg" from the OpenCV samples. In order to do so, a call to the cv::imread function loads the image using the file path specified by the first argument. The second argument is optional and specifies the format in which we want the image. This may be:

IMREAD_COLOR loads the image in the BGR 8-bit format. This is the default that is used here.
IMREAD_UNCHANGED loads the image as is (including the alpha channel if present)
IMREAD_GRAYSCALE loads the image as an intensity one
After reading in the image data will be stored in a cv::Mat object.
```
## Code examples
```
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;

std::string image_path = samples::findFile("OpenC.jpg");
    Mat img = imread(image_path, IMREAD_COLOR);

```
## if the image was loaded correctly
```
Then, the image is shown using a call to the cv::imshow function. The first argument is the title of the window and the second argument is the cv::Mat object that will be shown.

Because we want our window to be displayed until the user presses a key (otherwise the program would end far too quickly), we use the cv::waitKey function whose only parameter is just how long should it wait for a user input (measured in milliseconds). Zero means to wait forever. The return value is the key that was pressed.

if(img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
```
### Then, the image is shown using a call to the cv::imshow function
 imshow("Display window", img);
    int k = waitKey(0); // Wait for a keystroke in the window

### In the end, the image is written to a file if the pressed key was the "s"-key. For this the cv::imwrite function is called that has the file path and the cv::Mat object as an argument.
```
if(k == 's')
    {
        imwrite("OpenC.jpg", img);
    }
```
