// image.h
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

#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <opencv2/opencv.hpp>
#include <Eigen/Eigen>

typedef Eigen::RowVectorXf RowVector;

class Image {
public:
    Image();

    void open(QImage img);

    RowVector getVector();

private:
    static cv::Mat toMat(QImage img);

    static cv::Rect toSquare(cv::Rect bbox);

    static std::vector<int> calcPadding(const cv::Mat &img, const cv::Rect &bbox);

    RowVector vector;
};

#endif // IMAGE_H
