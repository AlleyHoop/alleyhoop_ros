//make sure to include ros
#include <ros/ros.h>

//libraries to process image
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

//import the service
#include "alleyhoop_ros_msgs/FindFeaturesOnImage.h"
#include <cv_bridge/cv_bridge.h>

//others
#include <iostream>
#include <vector>

using namespace cv;

//process image function
bool findFeaturesOnImage(alleyhoop_ros_msgs::FindFeaturesOnImage::Request &req,
                         alleyhoop_ros_msgs::FindFeaturesOnImage::Response &res)
{    
    //convert the image
    cv_bridge::CvImagePtr imagePtr = cv_bridge::toCvCopy(req.image, sensor_msgs::image_encodings::BGR8);

    //ensure actual values where passed
    if(imagePtr == nullptr)
    {
        std::cout << "image ptr was empty" << std::endl;
        return false;
    }

    if(imagePtr->image.empty())
    {
        std::cout << "image was empty" << std::endl;
        return false;
    }

    //to return data
    std::vector<uint32_t> features;

    //source image
    Mat srcImage = imagePtr->image.clone();
    int height = srcImage.rows;
    int width = srcImage.cols;

    //create grayscaled image
    Mat grayImage;
    cvtColor(srcImage, grayImage, CV_BGR2GRAY);
    medianBlur(grayImage, grayImage, 5);

    //create hsv image
    Mat hsvImage;
    cvtColor(srcImage, hsvImage, CV_BGR2HSV);

    //draw the circle on a black canvas
    Mat blankImage(height, width, CV_8UC1, Scalar(0,0,0));

    //find circles in image
    std::vector<Vec3f> circles;
    HoughCircles(grayImage, circles, HOUGH_GRADIENT, 1,
                grayImage.rows/8,  // change this value to detect circles with different distances to each other
                200, 100, 20, 50 // change the last two parameters
    );

    //identify features within found circles (traffic signs)
    if(circles.size() > 0)
    {
        for( size_t i = 0; i < circles.size(); i++ )
        {
            //get center and radius of circle
            Vec3i c = circles[i];
            Point center = Point(c[0], c[1]);
            int radius = c[2];

            //draw the circle on a black canvas
            Mat circleImage = blankImage.clone();
            circle( circleImage, center, radius, Scalar(255,255,255), CV_FILLED, 8, 0);

            // get mask for color red
            Mat hsvMask1;
            inRange(hsvImage,
                    Scalar(0, 70, 50), Scalar(10, 255, 255),
                hsvMask1);
            Mat hsvMask2;
            inRange(hsvImage,
                    Scalar(170, 70, 50), Scalar(180, 255, 255),
                hsvMask1);
            Mat hsvMask = hsvMask1 | hsvMask2;

            //resulting image
            Mat resImage;
            bitwise_and(circleImage, hsvMask, resImage);

            //for each white point on the blankImage check add up the color from the original image
            std::vector<Point> points;
            cv::findNonZero(resImage, points);

            //add the feature the center x , y , w, h means that every four elements is one feature
            if(points.size() > 100)
            {
                features.push_back(c[0]); //x
                features.push_back(c[1]); //y
                features.push_back(c[2]);  //w == r
                features.push_back(c[2]);  //h == r
            }

            //show images
            //imshow("hsv combined mask", hsvMask);
            //imshow("detected circles", circleImage);
            //imshow("bitwise and", resImage);
            //waitKey(0);

            //release open cv images
            circleImage.release();
            hsvMask.release();
            hsvMask1.release();
            hsvMask2.release();
            resImage.release();
        }
    }

    //set result
    res.step = 4;
    res.features = features;

    //release open cv images
    srcImage.release();
    grayImage.release();
    blankImage.release();
    hsvImage.release();

    return true;
}

//the ros service server
int main(int argc, char **argv)
{
    //print msg
    std::string service_name = "example_feature_finder";
    std::cout << "feature finder server is starting with service name: "<< service_name << std::endl;
    
    //init ros
    ros::init(argc, argv, "add_two_ints_server");
    ros::NodeHandle nh;

    //init ros service and process incoming images
    ros::ServiceServer feature_finder_service = nh.advertiseService(service_name, findFeaturesOnImage);
    std::cout << "Ready to find features on image" << std::endl;
    ros::spin();

    return 0;
}