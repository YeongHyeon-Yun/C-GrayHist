#if 0
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>
using namespace std;
using namespace cv;

void func(Mat& img)
{
	CV_Assert(img.type() == CV_8UC1);

	cout << "img is grayscale" << endl;
}

int main()
{
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);

	Mat img1 = imread("그럼됐네.bmp", IMREAD_GRAYSCALE);

	Mat img2(480, 640, CV_8UC1, Scalar(0));

	// img2 = img1;
	// img2 = img1.clone();
	img1.copyTo(img2);

	if (img1.empty()) {
		cout << " img1 can't open " << endl;
		return -1;
	}

	imshow("img1", img1);
	imshow("img2", img2);

	waitKey();
	destroyAllWindows();

	img2 = 10;

	imshow("img1", img1);
	imshow("img2", img2);

	waitKey();
	destroyAllWindows();

	Mat img3 = imread("그럼됐네.bmp", IMREAD_COLOR);
	Mat img4;

	cvtColor(img3, img4, COLOR_BGR2GRAY);

	func(img4);

	imshow("img3", img3);
	imshow("img4", img4);

	waitKey();
	destroyAllWindows();

	cout << " opencv version: " << CV_VERSION << endl;
	return 0;
}

#endif


#if 0
// 5.1.2 영상의 밝기
// dst(x, y) = src(x, y) + n
// n : 조절할 밝기 값( 양수 : 밝기 증가, 음수 : 밝기 감소 )
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>
using namespace std;
using namespace cv;
void brightness1();
void brightness2();
void brightness3();
void brightness4();

int main()
{
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);

	//brightness1();
	//brightness2();
	//brightness3();
	brightness4();
}

void brightness1()  // saturate_cast 가 자동으로 적용된다.
{
	Mat src = imread("그럼됐네.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << " Image load failed! " << endl;
		return;
	}

	Mat dst1 = src + 100;

	imshow("src", src);
	imshow("dst1", dst1);
	waitKey();
	destroyAllWindows();
}

void brightness2()
{
	Mat src = imread("그럼됐네.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << " Image load failed! " << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			dst.at<uchar>(j, i) = src.at<uchar>(j, i) + 100;
		}
	}

	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}
 // 밝기 제한을 함수로 직접 만들어 주기 (saturate_cast)
int cvt(int val) {
	return val > 255 ? 255 : val;
}

void brightness3()
{
	Mat src = imread("그럼됐네.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << " Image load failed! " << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			//dst.at<uchar>(j, i) = saturate_cast<uchar>(src.at<uchar>(j, i) + 150);  //밝기 제한 saturate_cast
			//dst.at<uchar>(j, i) = cvt(src.at<uchar>(j, i) + 150);
			dst.at<uchar>(j, i) = (src.at<uchar>(j, i) + 150) > 255 ? 255 : (src.at<uchar>(j, i) + 150);
		}
	}

	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}
void on_brightness(int pos, void* userdata)
{
	Mat src = *(Mat*)userdata;
	Mat dst = src + pos;

	imshow("dst", dst);
}

void brightness4()
{
	Mat src = imread("그럼됐네.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << " Image load failed! " << endl;
		return;
	}

	namedWindow("dst", WINDOW_NORMAL);
	createTrackbar("Brightness", "dst", 0, 100, on_brightness, (void*)&src);

	on_brightness(0, (void*)&src);

	waitKey();
	destroyAllWindows();
}


#endif


#if 0
#include <iostream>

int main()
{
	unsigned char a = 257;
	std::cout << "a: " << (int)a << std::endl;
	return 0;
}

#endif


#if 0
// dst(x, y) = saturate(s*src(X, y))
#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/core/utils/logger.hpp>
using namespace cv;
using namespace std;

void contrast1();

int main()
{
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);
	contrast1();
}
void contrast1()
{
	Mat src = imread("그럼됐네.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	float s = 2.f;
	Mat dst = s * src;

	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}
#endif


#if 0
#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/core/utils/logger.hpp>
using namespace cv;
using namespace std;

Mat calcGrayHist(const Mat& img);

int main()
{
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}
	Mat test;
	test = calcGrayHist(src);

	return 0;
}

Mat calcGrayHist(const Mat& img)
{
	CV_Assert(img.type() == CV_8UC1);

	Mat hist;
	int channels[] = { 0 };
	int dims = 1;
	const int histSize[] = { 256 };
	float graylevel[] = { 0, 256 };
	const float* ranges[] = { graylevel };
	calcHist(&img, 1, channels, noArray(), hist, dims, histSize, ranges);

	return hist;
}

#endif

#if 1
#include<iostream>
#include"opencv2/opencv.hpp"
#include"opencv2/core/utils/logger.hpp"
using namespace std;
using namespace cv;
Mat calcGrayHist(const Mat& img);
Mat getGrayHistImage(const Mat& hist);
void cameraman();
void cameraman1();
void cameraman2();
void histogram_stretching();

int main()
{
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);
	//cameraman();
	//cameraman1();
	//cameraman2();
	histogram_stretching();
	return 0;
}

void histogram_stretching()
{
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load falied!" << endl;
		return;
	}

	double gmin, gmax;
	minMaxLoc(src, &gmin, &gmax);

	Mat dst = (src - gmin) * 255 / (gmax - gmin);

	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));

	imshow("dst", dst);
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));

	waitKey();
	destroyAllWindows();
}

void cameraman2() {
	Mat src = imread("그럼됐네.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	float alpha = 2.f;
	Mat dst = src + (src - 128) * alpha;

	imshow("src", src);
	imshow("dst", dst);

	Mat histosrc1 = calcGrayHist(src);
	histosrc1 = getGrayHistImage(histosrc1);

	Mat histosrc = calcGrayHist(dst);
	histosrc = getGrayHistImage(histosrc);

	imshow("histosrc1", histosrc1);
	imshow("histosrc", histosrc);


	waitKey();
	destroyAllWindows();
}

void cameraman1() {
	Mat src1 = imread("그럼됐네.bmp", IMREAD_GRAYSCALE);
	if (src1.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	Mat src2 = src1 + 10; //밝기가 50만큼 밝아짐
	Mat histoimg1 = calcGrayHist(src1);
	histoimg1 = getGrayHistImage(histoimg1);
	Mat histoimg2 = calcGrayHist(src2);
	histoimg2 = getGrayHistImage(histoimg2);
	imshow("src1", src1);
	imshow("histoimg1", histoimg1);
	imshow("src2", src2);
	imshow("histoimg2", histoimg2);
	waitKey();
}

void cameraman() {
	Mat src = imread("그럼됐네.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	Mat test;
	test = calcGrayHist(src);
	Mat histoimg = getGrayHistImage(test);
	imshow("src", src);
	imshow("histo", histoimg);
	waitKey();
	destroyAllWindows();
}

Mat getGrayHistImage(const Mat& hist) {
	CV_Assert(hist.type() == CV_32FC1);
	CV_Assert(hist.size() == Size(1, 256));
	double histMax;
	minMaxLoc(hist, 0, &histMax);
	//min Max를 구해주는 것
	//머신러닝에서 minmaxscaler
	Mat imgHist(100, 256, CV_8UC1, Scalar(255));
	//imshow("imgHist", imgHist);
	waitKey();
	for (int i = 0; i < 256; i++) {
		line(imgHist, Point(i, 100),
			Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)), Scalar(0));
		// hist.at<float>(i, 0) rows는 256개 cols는 1개(0) => 0~1
		//* 100 0~1 => 0~100
		// / histMax
	}
	//imshow("imgHist", imgHist);
	//waitKey();
	return imgHist;
}

Mat calcGrayHist(const Mat& img)
{
	CV_Assert(img.type() == CV_8UC1);
	Mat hist;
	int channels[] = { 0 };
	int dims = 1;
	const int histSize[] = { 256 };
	float graylevel[] = { 0,256 };
	const float* ranges[] = { graylevel };
	calcHist(&img, 1, channels, noArray(), hist, dims, histSize, ranges);
	return hist;
}

#endif