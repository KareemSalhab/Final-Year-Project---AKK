//
//  main.cpp
//  openCV
//
//  Created by Christine Baertl on 17.09.17.
//  Copyright © 2017 AhmadMoussa. All rights reserved.
//

#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/videoio/videoio.hpp"
#include "opencv2/imgcodecs/imgcodecs.hpp"
#include "zbar.h"

using namespace zbar;
using namespace std;
using namespace cv;


Mat getBarcode(Mat img){
    
    Mat imgout;
    
    // convert input matrix to grayscale
    cvtColor(img,imgout,CV_GRAY2RGB);
    
    int width = img.cols;
    int height = img.rows;
    uchar *raw = (uchar *)img.data;
    
    // wrap image data
    Image image(width, height, "Y800", raw, width * height);
    
    // scan the image for barcodes
    ImageScanner scanner;
    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);
    int n = scanner.scan(image);
    cout << "Barcode: " << n << endl;
    
    // extract results
    for(Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol)
    {
        vector<Point> vp;
        
        // do something useful with results
        cout << "decoded " << symbol->get_type_name()
             << " symbol \"" << symbol->get_data()
             << '"' << " " << endl;
        
        int n = symbol->get_location_size();
        
        for(int i=0;i<n;i++)
        {
            vp.push_back(Point(symbol->get_location_x(i),symbol->get_location_y(i)));
        }
        
        RotatedRect r = minAreaRect(vp);
        Point2f pts[4];
        r.points(pts);
        
        for(int i=0;i<4;i++)
        {
            line(imgout,pts[i],pts[(i+1)%4],Scalar(255,0,0),3);
        }
        cout<<"Angle: "<<r.angle<<endl;
    }
    
    return imgout;
}

int main(void) {
    
    // obtain image data
    // char file[256];
    // cin>>file;
    
    Mat img = imread("/Users/christinebaertl/Desktop/barcode11.jpg", 0);
    Mat imgout;
    
    //imgout = getBarcode(img);
    //imshow("imgout.jpg", imgout);
    //waitKey();
    
    /////////
    
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;
    
    Mat edges;
    namedWindow("edges",1);
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        
        //convert frame to grayscale
        cvtColor(frame, edges, COLOR_BGR2GRAY);
        edges = getBarcode(edges);
        //GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        //Canny(edges, edges, 0, 30, 3);
        imshow("edges.jpg", edges);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//    cout << "Hey" <<endl;
//
//    Mat image;
//    image = imread("/Users/christinebaertl/Desktop/barcode.jpg", CV_LOAD_IMAGE_GRAYSCALE);
//
//    if(! image.data )                              // Check for invalid input
//    {
//        cout <<  "Could not open or find the image" << std::endl ;
//        return -1;
//    }
//
//    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
//    imshow( "Display window", image );
//
//    waitKey(0);
//    return 0;



/////////////////////////////////////////////////////////////////////////////////////////////


//Mat imgx;
//Mat imgy;
//    Mat gradient;
//    Mat scaleAbs;
//    Mat blurred;
//    Mat thresholdDst;
//    Mat kernel;
//    Mat thresholdedImg;
//    Mat eroded;
//    Mat dilated;
//

//
//        Sobel(img, imgx, CV_32F, 1, 0, -1);
//        Sobel(img, imgy, CV_32F, 0, 1, -1);
//
//    subtract(imgx,imgy, gradient);
//    imshow("gradient.jpg",gradient);
//
//    convertScaleAbs(gradient,scaleAbs);
//    imshow("scaleAbs.jpg",scaleAbs);
//
//    blur(scaleAbs, blurred, Size(9,9), Point(-1,-1));
//    imshow("blurred.jpg",blurred);
//
//    double thresh = threshold(blurred, thresholdDst, 217, 255, THRESH_BINARY);
//    imshow("thresholdDst.jpg",thresholdDst);
//
//    kernel = getStructuringElement(MORPH_RECT, Size(21, 7));
//    morphologyEx(thresholdDst, thresholdedImg, MORPH_CLOSE, kernel, Point(-1,-1), 1, BORDER_CONSTANT,morphologyDefaultBorderValue());
//
//    imshow("thresholdedImg.jpg",thresholdedImg);
//
//    kernel = getStructuringElement(MORPH_RECT, Size(2, 2));
//    erode(thresholdedImg, eroded, kernel, Point(-1,-1), 25, BORDER_CONSTANT, morphologyDefaultBorderValue());
//    imshow("eroded.jpg", eroded);
//
//    dilate(eroded, dilated, kernel, Point(-1,-1), 25, BORDER_CONSTANT, morphologyDefaultBorderValue());
//    imshow("dilated.jpg", dilated);

