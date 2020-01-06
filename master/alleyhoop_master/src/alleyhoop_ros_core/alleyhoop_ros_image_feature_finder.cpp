#include "alleyhoop_ros_core/alleyhoop_ros_image_feature_finder.h"

#include <sstream>
#include <iostream>
#include <opencv2/opencv.hpp>

namespace AlleyHoopROS
{

    AlleyHoopImageFeatureFinder::AlleyHoopImageFeatureFinder(ros::NodeHandle* _nh)
	: AlleyHoopMVC::Model(), nh(*_nh)
    {
    }

    bool AlleyHoopImageFeatureFinder::update()
    {
        if (ros::ok())
        {
            return true;
        }

        std::cout << "program terminated" << std::endl;
        return false;
    }

    AlleyHoopROSUtils::AlleyHoopFeature* AlleyHoopImageFeatureFinder::findFeatures(cv_bridge::CvImagePtr imagePtr)
    {   
        using namespace cv;
        
        if(imagePtr == nullptr)
        {
            return new AlleyHoopROSUtils::AlleyHoopFeature();
        }

        Mat grayImage;

        int height = imagePtr->image.rows;
        int width = imagePtr->image.cols;

        cvtColor(imagePtr->image, grayImage, CV_BGR2GRAY);

        namedWindow("Display window", WINDOW_AUTOSIZE);
        imshow("Display window", imagePtr->image);

        namedWindow("Gray Image", WINDOW_AUTOSIZE);
        imshow("Gray Image", grayImage);
        cvWaitKey(0);
        grayImage.release();

        return new AlleyHoopROSUtils::AlleyHoopFeature();
    }

}