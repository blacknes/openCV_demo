#/*******************************************************************************
# * Author :          Nill_Rhoads
# * Email :           nillrhoads@gmail.com
# * Last modified :   2016-04-18 16:23
# * Filename :        CMakeLists.txt
# * Description :     
# * *****************************************************************************/

cmake_minimum_required(VERSION2.8)
project(DisplayImage)
find_package( OpenCV REQUIRED )
add_executable( DisplayImage DisplayImage.cpp )
target_link_libraries( DisplayImage ${OpenCV_LIBS} )
