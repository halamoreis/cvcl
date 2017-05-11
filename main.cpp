//
// Created by hlm on 10/05/17.
//
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/ocl.hpp"
#include <iostream>
#include <unistd.h>


using namespace std;
using namespace cv;

int main(int argc, char *argv[]) {

/*
    Mat frame;
    Mat frame_gray;
    bool success, d = true;
    double fps;
    std::vector<Rect> faces;
    CascadeClassifier face_cascade;
//    VideoCapture v;
    string face_cascade_name = "/usr/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml";

    if(!face_cascade.load(face_cascade_name))
    {

        printf("--(!)Error loading\n");
        exit(1);

    }

    VideoCapture v(1);


    if(!v.isOpened())
    {

        cout << "Não encontrado\n";
        exit(1);

    }

    cout << "Deu certo!!! Beleza!!!" << endl;

    //v.set(CV_CAP_PROP_FPS, 10);
    fps = v.get(CV_CAP_PROP_FPS);
    cout << "Frames " << fps << endl;

    namedWindow("Video", CV_WINDOW_AUTOSIZE);


    while(d)
    {

        success = v.read(frame);

        if(!success)
        {

            cout << "Não foi lido\n";
            break;

        }

        cvtColor(frame, frame_gray, CV_BGR2GRAY);
        equalizeHist(frame_gray, frame_gray);
        face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30));
        //std::cout << "DETECT " << faces.size() << "faces" << std::endl;

        for( size_t i = 0; i < faces.size(); i++ )
        {

            rectangle(frame, faces[i], CV_RGB(0, 255,0), 2);
            //printf("%d %d %d %d\n", faces[i].x, faces[i].y, faces[i].height, faces[i].width);

        }

        imshow("Video", frame);

        if(waitKey(30) == 27)
        {

            cout << "Video desligado, saindo...\n";
            break;

        }

    }
*/

    namedWindow("Video", CV_WINDOW_AUTOSIZE);
    // initialization
    VideoCapture vcap(1);
    CascadeClassifier fd("/usr/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml");
    UMat frame, frameGray;
    vector<Rect> faces;


    cout << cv::ocl::haveOpenCL() << endl;
    if  ( ! cv::ocl::haveOpenCL ())
    {
        cout  <<  "OpenCL IS not avaiable ..."  <<  endl ;
        return 0;
    } else {
        cout  <<  "OpenCL BELEZA!"  <<  endl ;
    }

    for(int qntFaces = 50;qntFaces>0;qntFaces--){
        // processing loop
        vcap >> frame;
        cvtColor(frame, frameGray, CV_BGR2GRAY);
        equalizeHist(frameGray, frameGray);
        fd.detectMultiScale(frameGray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30));

        // draw rectangles …
        cv::Mat draw_img = frame.getMat(cv::ACCESS_WRITE);
        for( size_t i = 0; i < faces.size(); i++ )
        {

            cv::rectangle(draw_img, faces[i], CV_RGB(0, 255,0), 2);

//            rectangle(frame, faces[i], CV_RGB(0, 255,0), 2);
            //printf("%d %d %d %d\n", faces[i].x, faces[i].y, faces[i].height, faces[i].width);

        }

        // show image …
        imshow("Video", draw_img);

        if(waitKey(30) == 27)
        {

            cout << "Video desligado, saindo...\n";
            break;

        }

        draw_img.release();
        sleep(0.1);
    }

    return 0;
}
