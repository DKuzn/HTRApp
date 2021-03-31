#include "image.h"
#include <opencv2/opencv.hpp>
#include <QImage>
#include <utility>

Image::Image()
{
    vector.setZero(784);
}

void Image::open(QImage img) {
    cv::Mat mat = to_mat(std::move(img));
    cv::resize(mat, mat, cv::Size(28, 28));
    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 28; j++) {
            vector(i + j) = mat.at<int>(i, j);
        }
    }
}

cv::Mat Image::to_mat(QImage img) {
    cv::Mat mat(img.height(), img.width(), CV_8UC4, img.bits(), img.bytesPerLine());
    cv::cvtColor(mat, mat, cv::COLOR_BGRA2GRAY);
    cv::Mat bin;
    cv::threshold(mat, bin, 200, 255, cv::THRESH_BINARY_INV);
    std::vector<std::vector<cv::Point>> cntr;
    std::vector<cv::Vec4i> hier;
    cv::findContours(bin, cntr, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    std::vector<cv::Point> cntrs = {};
    for (unsigned long i = 0; i < cntr.size() - 1; i++) {
        cntrs.insert(cntrs.end(), cntr[i].begin(), cntr[i].end());
    }
    std::vector<cv::Point> appr;
    if (!cntrs.empty()) {
        cv::approxPolyDP(cntrs, appr, 3, true);
        cv::Rect bbox = cv::boundingRect(appr);
        bbox = to_square(bbox);
        cv::Mat crop(bin, bbox);
        return crop;
    } else {
        return bin;
    }
}

cv::Rect Image::to_square(cv::Rect bbox) {
    int x, y, w, h;
    x = bbox.x;
    y = bbox.y;
    w = bbox.width;
    h = bbox.height;
    if (w > h) {
        int s = (w - h) / 2;
        y = y - s;
        h = w;
    }
    else if (h > w) {
        int s = (h - w) / 2;
        x = x - s;
        w = h;
    }
    bbox.x = x - 5;
    bbox.y = y - 5;
    bbox.width = w + 10;
    bbox.height = h + 10;
    return bbox;
}

RowVector Image::getVector() {
    return vector;
}
