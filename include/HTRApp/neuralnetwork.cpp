#include "neuralnetwork.h"
#include <fstream>

NeuralNetwork::NeuralNetwork(std::vector<unsigned int> topology, Scalar learningRate) {
    this->topology = topology;
    this->learningRate = learningRate;
    for (unsigned int i = 0; i < topology.size(); i++) {
        if (i == topology.size() - 1)
            neuronLayers.push_back(new RowVector(topology[i]));
        else
            neuronLayers.push_back(new RowVector(topology[i] + 1));

        cacheLayers.push_back(new RowVector(neuronLayers.size()));
        deltas.push_back(new RowVector(neuronLayers.size()));

        if (i != topology.size() - 1) {
            neuronLayers.back()->coeffRef(topology[i]) = 1.0;
            cacheLayers.back()->coeffRef(topology[i]) = 1.0;
        }

        if (i > 0) {
            if (i != topology.size() - 1) {
                weights.push_back(new Matrix(topology[i - 1] + 1, topology[i] + 1));
                weights.back()->setRandom();
                weights.back()->col(topology[i]).setZero();
                weights.back()->coeffRef(topology[i - 1], topology[i]) = 1.0;
            } else {
                weights.push_back(new Matrix(topology[i - 1] + 1, topology[i]));
                weights.back()->setRandom();
            }
        }
    }
}

void NeuralNetwork::propagateForward(RowVector &input) {
    neuronLayers.front()->block(0, 0, 1, neuronLayers.front()->size() - 1) = input;

    for (unsigned int i = 1; i < topology.size(); i++) {
        (*neuronLayers[i]) = (*neuronLayers[i - 1]) * (*weights[i - 1]);
    }

    for (unsigned int i = 1; i < topology.size() - 1; i++) {
        neuronLayers[i]->block(0, 0, 1, topology[i]).unaryExpr(std::ptr_fun(activationFunction));
    }
}


void NeuralNetwork::calcErrors(RowVector &output) {
    (*deltas.back()) = output - (*neuronLayers.back());

    for (unsigned int i = topology.size() - 2; i > 0; i--) {
        (*deltas[i]) = (*deltas[i + 1]) * (weights[i]->transpose());
    }
}

void NeuralNetwork::updateWeights() {
    for (unsigned int i = 0; i < topology.size() - 1; i++) {
        if (i != topology.size() - 2) {
            for (unsigned int c = 0; c < weights[i]->cols() - 1; c++) {
                for (unsigned int r = 0; r < weights[i]->rows(); r++) {
                    weights[i]->coeffRef(r, c) += learningRate * deltas[i + 1]->coeffRef(c) *
                                                  activationFunctionDerivative(cacheLayers[i + 1]->coeffRef(c)) *
                                                  neuronLayers[i]->coeffRef(r);
                }
            }
        } else {
            for (unsigned int c = 0; c < weights[i]->cols(); c++) {
                for (unsigned int r = 0; r < weights[i]->rows(); r++) {
                    weights[i]->coeffRef(r, c) += learningRate * deltas[i + 1]->coeffRef(c) *
                                                  activationFunctionDerivative(cacheLayers[i + 1]->coeffRef(c)) *
                                                  neuronLayers[i]->coeffRef(r);
                }
            }
        }
    }
}

void NeuralNetwork::propagateBackward(RowVector &output) {
    calcErrors(output);
    updateWeights();
}

Scalar NeuralNetwork::activationFunction(Scalar x) {
    return tanhf(x);
}

Scalar NeuralNetwork::activationFunctionDerivative(Scalar x) {
    return 1 - tanhf(x) * tanhf(x);
}

void NeuralNetwork::train(std::vector<RowVector> input_data, std::vector<RowVector> output_data) {
    for (unsigned int i = 0; i < input_data.size(); i++) {
        propagateForward(input_data[i]);
        std::cout << "Expected output is : " << output_data[i] << std::endl;
        std::cout << "Output produced is : " << *neuronLayers.back() << std::endl;
        propagateBackward(output_data[i]);
        std::cout << "MSE : " << std::sqrt((*deltas.back()).dot((*deltas.back())) / deltas.back()->size()) << std::endl;
    }
}

RowVector NeuralNetwork::forward(RowVector &x) {
    propagateForward(x);
    RowVector out = *neuronLayers.back();
    return out;
}

void NeuralNetwork::saveWeights(const std::string &path) {
    std::ofstream file(path);
    const static Eigen::IOFormat CSVFormat(Eigen::StreamPrecision, Eigen::DontAlignCols, ",", "\n");

    if (file.is_open()) {
        for (Eigen::MatrixXf *i : weights) {
            file << i->format(CSVFormat);
            file << '\n';
            file << '\n';
        }
        file.close();
    }
}

void NeuralNetwork::loadWeights(const std::string &path) {
    std::setlocale(LC_NUMERIC, "en_US.UTF-8");
    std::ifstream file(path);
    std::string line;
    int length = weights.size();
    int matrix = 0;

    while (matrix < length) {

        int row = 0;
        int col;

        if (file.is_open()) {
            while (std::getline(file, line)) {
                char *ptr = (char *) line.c_str();
                int len = line.length();
                if (len == 0) {
                    matrix++;
                    row = 0;
                    continue;
                }

                col = 0;

                char *start = ptr;
                for (int i = 0; i < len; i++) {
                    if (ptr[i] == ',') {
                        weights[matrix]->coeffRef(row, col++) = std::atof(start);
                        start = ptr + i + 1;
                    }
                }
                weights[matrix]->coeffRef(row, col) = std::atof(start);
                row++;
            }
        }
    }
}
