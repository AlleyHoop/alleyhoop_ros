#include "alleyhoop_ros_core/alleyhoop_ros_image_feature_finder.h"

#include <sstream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

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
        
        //ensure actual values where passed
        if(imagePtr == nullptr)
        {
            return nullptr;
        }

        if(imagePtr->image.empty())
        {
            std::cout << "image was empty" << std::endl;
            return nullptr;
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
        Mat blankImage(height, width, CV_8UC3, Scalar(0,0,0));

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

                // high contrast black and white
                Mat hsvThreshold;
                inRange(hsvImage,
                    Scalar(255, 255, 118),
                    Scalar(0, 0, 74),
                    hsvThreshold);

                //for each white point on the blankImage check add up the color from the original image
                /*std::vector<Point> points;
                cv::findNonZero(blankImage, points);

                //get average color
                for(std::vector<Point>::iterator pnt_iter = points.begin(); pnt_iter != points.end(); pnt_iter++)
                {
                    Scalar colour = drawing.at<Vec3b>(*pnt_iter);
                }*/

                imshow("thesh", hsvThreshold);
                imshow("detected circles", circleImage);

                circleImage.release();
                hsvThreshold.release();
            }
        }
        imshow("original image", imagePtr->image);
        waitKey(0);
        srcImage.release();
        grayImage.release();
        blankImage.release();
        hsvImage.release();
        return nullptr;
    }

}