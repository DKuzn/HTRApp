#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <opencv2/opencv.hpp>
#include <Eigen/Eigen>

typedef Eigen::RowVectorXf RowVector;

class Image
{
public:
    Image();
    void open(QImage img);
    RowVector getVector();

private:
    static cv::Mat to_mat(QImage img);
    static cv::Rect to_square(cv::Rect bbox);
    static std::vector<int> calcPadding(const cv::Mat& img, const cv::Rect& bbox);
    RowVector vector;
};

#endif // IMAGE_H
