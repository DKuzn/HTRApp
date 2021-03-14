#ifndef HTRAPP_DATASET_H
#define HTRAPP_DATASET_H
#include <string>
#include <vector>
#include <Eigen/Eigen>
#include "datasetitem.h"


class Dataset {
public:
    explicit Dataset(std::string& path);
    DatasetItem operator[](int index);
    std::vector<DatasetItem> data;

private:
    static std::vector<DatasetItem> loadCsv(std::string& path);
    static RowVector toOneHot(Scalar y);
};


#endif //HTRAPP_DATASET_H
