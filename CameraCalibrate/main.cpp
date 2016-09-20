
#include<iostream> 
#include<iomanip>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include"CameraCalibrator.h"

using namespace cv;
using namespace std;

int main()
{
	cv::namedWindow("Image");
	cv::Mat image;
	std::vector<std::string> filelist;

	// generate list of chessboard image filename
	for (int i = 1; i <= 20; i++) {

		std::stringstream str;
		str << "../chessboards/chessboard" << std::setw(2) << std::setfill('0') << i << ".jpg";
		std::cout << str.str() << std::endl;

		filelist.push_back(str.str());
		image = cv::imread(str.str(), 0);
		cv::imshow("Image", image);

		cv::waitKey(100);
	}

	// Create calibrator object
	CameraCalibrator cameraCalibrator;
	// add the corners from the chessboard
	// 添加棋盘的方块数
	cv::Size boardSize(6, 4);
	// filenames of chessboard image， 添加图片文件list
	// size of chessboard 棋盘尺寸，具体来说是几行几列
	cameraCalibrator.addChessboardPoints(filelist,	boardSize);	
	// calibrate the camera
	//	cameraCalibrator.setCalibrationFlag(true,true);
	cameraCalibrator.calibrate(image.size());

	// Image Undistortion
	image = cv::imread(filelist[6]);
	cv::Mat uImage = cameraCalibrator.remap(image);

	// display camera matrix
	cv::Mat cameraMatrix = cameraCalibrator.getCameraMatrix();
	std::cout << " Camera intrinsic: " << cameraMatrix.rows << "x" << cameraMatrix.cols << std::endl;
	std::cout << cameraMatrix.at<double>(0, 0) << " " << cameraMatrix.at<double>(0, 1) << " " << cameraMatrix.at<double>(0, 2) << std::endl;
	std::cout << cameraMatrix.at<double>(1, 0) << " " << cameraMatrix.at<double>(1, 1) << " " << cameraMatrix.at<double>(1, 2) << std::endl;
	std::cout << cameraMatrix.at<double>(2, 0) << " " << cameraMatrix.at<double>(2, 1) << " " << cameraMatrix.at<double>(2, 2) << std::endl;

	imshow("Original Image", image);
	imshow("Undistorted Image", uImage);

	cv::waitKey();
	return 0;

}

