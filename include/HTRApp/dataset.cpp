#include "dataset.h"
#include <fstream>
#include <iostream>


Dataset::Dataset(std::string &path) {
    data = loadCsv(path);
}

std::vector<DatasetItem> Dataset::loadCsv(std::string &path) {
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