#include "datasetitem.h"
#include <utility>


DatasetItem::DatasetItem(RowVector x_i, RowVector y_i) {
    x = std::move(x_i);
    y = std::move(y_i);
}