#/*******************************************************************************
#* Author :          Nill_Rhoads
#* Email :           nillrhoads@gmail.com
#* Last modified :   2016-04-21 13:32
#* Filename :        CMakeLists.txt
#* Description :     
#* *****************************************************************************/

cmake_minimum_required (VERSION 2.6)

PROJECT (TestCameraCapture)

# Requires OpenCV
FIND_PACKAGE( OpenCV REQUIRED )

SET(SRC
    TestCameraCapture.cpp
    ShowImage.cpp
    )

ADD_EXECUTABLE(${PROJECT_NAME} ${SRC})
TARGET_LINK_LIBRARIES( ${PROJECT_NAME}  ${OpenCV_LIBS} )

