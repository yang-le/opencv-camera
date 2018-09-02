#include <opencv2/opencv.hpp>
#include <vector>

int main(int argc, char **argv)
{
    bool find = false;
    cv::Mat input;
    cv::VideoCapture cap;
    std::vector<cv::Point2f> corners;
    cv::Size pattern_size(atoi(argv[1]), atoi(argv[2]));

    if (argc > 3)
        cap.open(argv[3]);
    else
        cap.open(0);

    while (!find)
    {
        cap >> input;
        cv::namedWindow("input");
        cv::imshow("input", input);
        cv::waitKey(1);

        find = cv::findChessboardCorners(input, pattern_size, corners);

        if (find)
        {
            cv::Mat gray;
            cv::cvtColor(input, gray, CV_BGR2GRAY);
            cv::cornerSubPix(gray, corners, pattern_size, cv::Size(-1, -1),
                             cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
        }
        else
        {
            if (corners.size())
            {
                cv::drawChessboardCorners(input, pattern_size, corners, find);
                cv::imshow("input", input);
                cv::waitKey(500);
            }

            find = cv::findCirclesGrid(input, pattern_size, corners, cv::CALIB_CB_ASYMMETRIC_GRID);
            if (!find && corners.size())
            {
                cv::drawChessboardCorners(input, pattern_size, corners, find);
                cv::imshow("input", input);
                cv::waitKey(500);
            }
        }
    }

    cv::drawChessboardCorners(input, pattern_size, corners, find);
    cv::imshow("input", input);
    cv::waitKey(0);

    return 0;
}
