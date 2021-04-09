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
