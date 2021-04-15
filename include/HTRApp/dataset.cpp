// dataset.cpp
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

#include "dataset.h"
#include <fstream>
#include <iostream>


Dataset::Dataset(std::string &path) {
    data = loadCsv(path);
    for (const DatasetItem &i : data) {
        x_vector.push_back(i.x);
        y_vector.push_back(i.y);
    }
}

std::vector<DatasetItem> Dataset::loadCsv(std::string &path) {
    std::setlocale(LC_NUMERIC, "en_US.UTF-8");
    std::ifstream file(path);
    std::string line;

    std::vector<DatasetItem> temp = {};

    int col;
    RowVector img(784);
    img.setOnes();
    Scalar y;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            char *ptr = (char *) line.c_str();
            int len = line.length();

            col = 0;

            char *start = ptr;
            for (int i = 0; i < len; i++) {
                if (ptr[i] == ',') {
                    if (col == 0) {
                        y = std::atof(start);
                        start = ptr + i + 1;
                        col++;
                    } else {
                        img(col++ - 1) = std::atof(start);
                        start = ptr + i + 1;
                    }
                }
            }
            img(col - 1) = std::atof(start);
            temp.emplace_back(img / 255.0, toOneHot(y));
        }
    }
    return temp;
}

RowVector Dataset::toOneHot(Scalar y) {
    RowVector oneHot(10);
    oneHot.setZero();
    oneHot.coeffRef(y) = 1;
    return oneHot;
}

DatasetItem Dataset::operator[](int index) {
    return data[index];
}