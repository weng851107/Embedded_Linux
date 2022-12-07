/*
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	// 獲取原圖
	Mat img = imread("/home/chicony/cvtest.jpeg", cv::IMREAD_ANYCOLOR);
	if (img.empty())
	{
		cout <<"無法讀取影象" <<endl;
		return 0;
	}

	int height = img.rows;
	int width = img.cols;

	// 縮小影象，比例為(0.3, 0.5)
	Size dsize = Size(round(0.3 * width), round(0.5 * height));
	Mat shrink;
	resize(img, shrink, dsize, 0, 0, INTER_AREA);

	// 放大影象，比例為(1.6, 1.2)
	float fx = 1.6;
	float fy = 1.2;
	Mat enlarge;
	resize(img, enlarge, Size(), fx, fy, INTER_CUBIC);

	// 儲存圖片
	imwrite("/home/chicony/cvtest_shrink.jpeg", shrink);
	imwrite("/home/chicony/cvtest_enlarge.jpeg", enlarge);

	while(1)
	{
		// 顯示
		imshow("src", img);
		imshow("shrink", shrink);
		imshow("enlarge", enlarge);
	}

	//waitKey(0);

	return 0;
}
*/
/*
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio.hpp>
using namespace cv;

int main()
{
	VideoCapture capture(0);
	VideoWriter writer("VideoTest.mp4", CV_FOURCC('H', '2', '6', '4'), 25.0, Size(640, 480));
	Mat frame;

	while (capture.isOpened())
	{
		capture >> frame;
		writer << frame;
		//imshow("video", frame);
		if (cvWaitKey(20) == 27){    // ESC
			break;
		}
	}

}
*/

#include <iostream>
using namespace std;

#include "opencv2/opencv.hpp"
using namespace cv;


int main()
{
    Mat srcImage = imread("/home/chicony/cat.jpeg", cv::IMREAD_ANYCOLOR); //logo图
	if (srcImage.empty())
	{
		cout << "無法讀取影象 srcImage" << endl;
		return 0;
	}
    Mat dstImage = imread("/home/chicony/cvtest.jpeg", cv::IMREAD_ANYCOLOR); //背景图
	if (dstImage.empty())
	{
		cout << "無法讀取影象 dstImage" << endl;
		return 0;
	}

    Mat imageROI = dstImage(Rect(250, 250, srcImage.cols, srcImage.rows)); //设置感兴趣区域
    Mat mask = imread("/home/chicony/cat.jpeg", 0); //加载掩膜（灰度图）
    srcImage.copyTo(imageROI, mask);    //将掩膜图复制到感兴趣区域

    // 儲存圖片
	imwrite("/home/chicony/cvtest_merge.jpeg", dstImage);
    //waitKey(0);

    return 0;
}