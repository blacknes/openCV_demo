/*******************************************************************************
 * Author :          Nill_Rhoads
 * Email :           nillrhoads@gmail.com
 * Last modified :   2016-04-21 13:37
 * Filename :        TestCameraCapture.cpp
 * Description :     
 * *****************************************************************************/

#include <iostream>
#include <opencv2/opencv.hpp>
#include "ShowImage.hpp"

const int DESIRED_CAMERA_WIDTH = 640;
const int DESIRED_CAMERA_HEIGHT = 480;

const int NUM_STICK_FIGURE_ITERATIONS = 40; // Sets how long the stick figure face should be shown for skin detection.

const char *windowName = "Cartoonifier";   // Name shown in the GUI window.


// Set to true if you want to see line drawings instead of paintings.
bool m_sketchMode = false;
// Set to true if you want to change the skin color of the character to an alien color.
bool m_alienMode = false;
// Set to true if you want an evil "bad" character instead of a "good" character.
bool m_evilMode = false;
// Set to true if you want to see many windows created, showing various debug info. Set to 0 otherwise.
bool m_debugMode = false;

using namespace std;
using namespace cv;

int m_stickFigureIterations = 0;  // Draws a stick figure outline for where the user's face should be.

#if !defined VK_ESCAPE
    #define VK_ESCAPE 0x1B      // Escape character (27)
#endif


void onKeypress(char key)
{
    switch (key) {
    case 's':
        m_sketchMode = !m_sketchMode;
        cout << "Sketch / Paint mode: " << m_sketchMode << endl;
        break;
    case 'a':
        m_alienMode = !m_alienMode;
        cout << "Alien / Human mode: " << m_alienMode << endl;
        // Display a stick figure outline when alien skin is enabled,
        // so the user puts their face in the correct place.
        if (m_alienMode) {
            m_stickFigureIterations = NUM_STICK_FIGURE_ITERATIONS;
        }
        break;
    case 'e':
        m_evilMode = !m_evilMode;
        cout << "Evil / Good mode: " << m_evilMode << endl;
        break;
    case 'd':
        m_debugMode = !m_debugMode;
        cout << "Debug mode: " << m_debugMode << endl;
        break;
    }
}

void initWebcam(VideoCapture &videoCapture, int cameraNumber)
{
    // Get access to the default camera.
    try {   // Surround the OpenCV call by a try/catch block so we can give a useful error message!
        videoCapture.open(cameraNumber);
    } catch (cv::Exception &e) {}
    if ( !videoCapture.isOpened() ) {
        cerr << "ERROR: Could not access the camera!" << endl;
        exit(1);
    }
    cout << "Loaded camera " << cameraNumber << "." << endl;
}


int main(int argc, char *argv[])
{

    cout << "start Camera Capture" << endl;

    int cameraNumber = 0;   // Change this if you want to use a different camera device.
    if (argc > 1) {
        cameraNumber = atoi(argv[1]);
    }

    // Get access to the camera.
    VideoCapture camera;
    initWebcam(camera, cameraNumber);

    // Try to set the camera resolution. Note that this only works for some cameras on
    // some computers and only for some drivers, so don't rely on it to work!
    camera.set(CV_CAP_PROP_FRAME_WIDTH, DESIRED_CAMERA_WIDTH);
    camera.set(CV_CAP_PROP_FRAME_HEIGHT, DESIRED_CAMERA_HEIGHT);

	

     // Create a GUI window for display on the screen.
    namedWindow(windowName); // Resizable window, might not work on Windows.

    // Run forever, until the user hits Escape to "break" out of this loop.
    while (true) {

        // Grab the next camera frame. Note that you can't modify camera frames.
        Mat cameraFrame;
        camera >> cameraFrame;
        if( cameraFrame.empty() ) {
            cerr << "ERROR: Couldn't grab the next camera frame." << endl;
            exit(1);
        }

        Mat displayedFrame = Mat(cameraFrame.size(), CV_8UC3);

        // Use debug type 2 (for desktop) if debug mode is enabled.
        int debugType = 0;
        if (m_debugMode)
            debugType = 2;

        // Run the cartoonifier filter using the selected mode.
        cartoonifyImage(cameraFrame, displayedFrame, m_sketchMode, m_alienMode, m_evilMode, debugType);

	imshow(windowName, displayedFrame);

	 char keypress = waitKey(20);  // This is needed if you want to see anything!
        if (keypress == VK_ESCAPE) {   // Escape Key
            // Quit the program!
            break;
        }
        // Process any other keypresses.
        if (keypress > 0) {
            onKeypress(keypress);
        }

    }

    return 0;
}
