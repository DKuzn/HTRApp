// datasetitem.h
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

#ifndef HTRAPP_DATASETITEM_H
#define HTRAPP_DATASETITEM_H

#include <Eigen/Eigen>


typedef float Scalar;
typedef Eigen::RowVectorXf RowVector;


class DatasetItem {
public:
    DatasetItem(RowVector x_i, RowVector y_i);

    RowVector x;
    RowVector y;
};


#endif //HTRAPP_DATASETITEM_H
