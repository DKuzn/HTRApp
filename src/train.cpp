#include "neuralnetwork.h"
#include "dataset.h"
#include <iostream>

int main() {
    std::string path = "../train.csv";
    Dataset ds = Dataset(path);
    std::vector<unsigned int> topology = {784, 120, 10};
    NeuralNetwork net = NeuralNetwork(topology, 0.0001);
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 42000; i++) {
            net.train({ds[i].x}, {ds[i].y});
        }
        net.saveWeights("../HTRApp/net_weights.csv");
    }
}

