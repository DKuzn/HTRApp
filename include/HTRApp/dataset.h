// dataset.h
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

#ifndef HTRAPP_DATASET_H
#define HTRAPP_DATASET_H

#include <string>
#include <vector>
#include <Eigen/Eigen>
#include "datasetitem.h"


class Dataset {
public:
    explicit Dataset(std::string &path);

    DatasetItem operator[](int index);

    std::vector<RowVector> x_vector;
    std::vector<RowVector> y_vector;

private:
    static std::vector<DatasetItem> loadCsv(std::string &path);

    static RowVector toOneHot(Scalar y);

    std::vector<DatasetItem> data;
};


#endif //HTRAPP_DATASET_H
