// image.cpp
//
// Copyright 2021 Дмитрий Кузнецов
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "image.h"
#include <opencv2/opencv.hpp>
#include <QImage>
#include <utility>

Image::Image() {
    vector.setZero(784);
}

void Image::open(QImage img) {
    cv::Mat mat = toMat(std::move(img));
    cv::resize(mat, mat, cv::Size(28, 28));
    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 28; j++) {
            vector(i + j) = mat.at<int>(i, j);
        }
    }
}

cv::Mat Image::toMat(QImage img) {
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
        bbox = toSquare(bbox);
        try {
            cv::Mat crop(bin, bbox);
            return crop;
        }
        catch (const cv::Exception &e) {
            std::vector<int> paddings = calcPadding(bin, bbox);
            if (bbox.x < 0) {
                bbox.x = 0;
            }
            if (bbox.y < 0) {
                bbox.y = 0;
            }
            cv::copyMakeBorder(bin, bin, paddings[0], paddings[1], paddings[2], paddings[3], 0);
            cv::Mat crop(bin, bbox);
            return crop;
        }
    } else {
        return bin;
    }
}

cv::Rect Image::toSquare(cv::Rect bbox) {
    int x, y, w, h;
    x = bbox.x;
    y = bbox.y;
    w = bbox.width;
    h = bbox.height;
    if (w > h) {
        int s = (w - h) / 2;
        y = y - s;
        h = w;
    } else if (h > w) {
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

std::vector<int> Image::calcPadding(const cv::Mat &img, const cv::Rect &bbox) {
    int x, y, w, h, imgW, imgH, top, bottom, left, right;
    x = bbox.x;
    y = bbox.y;
    w = bbox.width;
    h = bbox.height;
    imgW = img.cols;
    imgH = img.rows;
    top = -y;
    bottom = h - (imgH - y);
    left = -x;
    right = w - (imgW - x);
    std::vector<int> paddings = {top, bottom, left, right};
    for (int i = 0; i < 4; i++) {
        if (paddings[i] < 0) {
            paddings[i] = 0;
        }
    }
    return paddings;
}

RowVector Image::getVector() {
    return vector;
}
