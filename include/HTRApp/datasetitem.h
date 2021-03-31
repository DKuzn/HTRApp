#ifndef HTRAPP_DATASETITEM_H
#define HTRAPP_DATASETITEM_H
#include <eigen3/Eigen/Eigen>


typedef float Scalar;
typedef Eigen::RowVectorXf RowVector;


class DatasetItem {
public:
    DatasetItem(RowVector x_i, RowVector y_i);
    RowVector x;
    RowVector y;
};


#endif //HTRAPP_DATASETITEM_H
