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
    bool at_least_one_feature = false;

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

    //create hsv image
    Mat hsvImage;
    cvtColor(srcImage, hsvImage, CV_BGR2HSV);

    // get mask for color red
    Mat hsvMask1;
    inRange(hsvImage,
            Scalar(0, 70, 50), Scalar(10, 255, 255),
        hsvMask1);
    Mat hsvMask2;
    inRange(hsvImage,
            Scalar(170, 70, 50), Scalar(180, 255, 255),
        hsvMask2);
    Mat hsvMask = hsvMask1 | hsvMask2;

    //find contours
    std::vector<std::vector<Point> > contours;
    std::vector<Vec4i> hierarchy;
    findContours( hsvMask, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
   
    
    //get largest contour as feature
    if(contours.size() > 0)
    {
        at_least_one_feature = true;

        //get largest contour
        int cuurent_area = 0;
        int largest_area = 0;
        int largest_contour_index = 0;
        for( int i = 0; i< contours.size(); i++ )
        {
        
        double area = contourArea( contours[i] );  //  Find the area of contour

            if( area > largest_area )
            {
                largest_area = area;
                largest_contour_index = i;                   //Store the index of largest contour
            }
        }

        /// Draw contours
        Mat drawing = Mat::zeros( hsvMask.size(), CV_8UC3 );
        drawContours( drawing, contours,largest_contour_index, Scalar( 0, 255, 0 ), 2 );

        //get the bounding rect
        Rect bounding_rect = boundingRect( contours[largest_contour_index] );
        features.push_back(bounding_rect.x);
        features.push_back(bounding_rect.y);
        features.push_back(bounding_rect.width);
        features.push_back(bounding_rect.height);

        //show images
        //imshow("original image", srcImage);
        //imshow("hsv combined mask", hsvMask);
        //imshow("drawing", drawing);
        //waitKey(0);

        //release open cv images
        hsvMask.release();
        hsvMask1.release();
        hsvMask2.release();
        drawing.release();
    }

    //set result
    if(at_least_one_feature)
    {
        res.step = 4;
    }
    else
    {
        res.step = 0;
    }
    res.features = features;

    //release open cv images
    srcImage.release();
    hsvImage.release();

    return true;
}

//the ros service server
int main(int argc, char **argv)
{
    //print msg
    std::string service_name = "blob_feature_finder";
    std::cout << "feature finder server is starting with service name: "<< service_name << std::endl;
    
    //init ros
    ros::init(argc, argv, "blob_feature_finder_server");
    ros::NodeHandle nh;

    //init ros service and process incoming images
    ros::ServiceServer feature_finder_service = nh.advertiseService(service_name, findFeaturesOnImage);
    std::cout << "Ready to find features on image" << std::endl;
    ros::spin();

    return 0;
}
