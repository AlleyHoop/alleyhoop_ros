#include "alleyhoop_ros_core/alleyhoop_ros_image_feature_finder.h"

#include <sstream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

namespace AlleyHoopROS
{
    bool AlleyHoopImageFeatureFinder::verboseDisplay = false;
    bool AlleyHoopImageFeatureFinder::verboseLog = false;

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

    std::list<AlleyHoopROSUtils::AlleyHoopFeature*> AlleyHoopImageFeatureFinder::findFeatures(cv_bridge::CvImagePtr imagePtr)
    {   
        using namespace cv;
        std::list<AlleyHoopROSUtils::AlleyHoopFeature*> features;
        
        //ensure actual values where passed
        if(imagePtr == nullptr)
        {
            return features;
        }

        if(imagePtr->image.empty())
        {
            std::cout << "image was empty" << std::endl;
            return features;
        }

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

        //identify features within found circles
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

                //add the feature (TODO, actually decide the feature and make features usefull for the controller)
                if(points.size() > 100)
                    features.push_back(new AlleyHoopROSUtils::AlleyHoopFeature(AlleyHoopROSUtils::FeatureTypes::SpecificObject));

                //show images
                if(verboseDisplay)
                {
                    imshow("hsv combined mask", hsvMask);
                    imshow("detected circles", circleImage);
                    imshow("bitwise and", resImage);
                    waitKey(0);
                }

                //release open cv images
                circleImage.release();
                hsvMask.release();
                hsvMask1.release();
                hsvMask2.release();
                resImage.release();
            }
        }

        //release open cv images
        srcImage.release();
        grayImage.release();
        blankImage.release();
        hsvImage.release();
        return features;
    }

}