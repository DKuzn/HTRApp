// neuralnetwork.h
// Based on https://www.geeksforgeeks.org/ml-neural-network-implementation-in-c-from-scratch/
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

#ifndef HTRAPP_NEURALNETWORK_H
#define HTRAPP_NEURALNETWORK_H

#include <Eigen/Eigen>
#include <iostream>
#include <vector>

typedef float Scalar;
typedef Eigen::MatrixXf Matrix;
typedef Eigen::RowVectorXf RowVector;


class NeuralNetwork {
public:
    explicit NeuralNetwork(std::vector<unsigned int> topology, Scalar learningRate = Scalar(0.005));

    void propagateForward(RowVector &input);

    void propagateBackward(RowVector &output);

    void calcErrors(RowVector &output);

    void updateWeights();

    static Scalar activationFunction(Scalar x);

    static Scalar activationFunctionDerivative(Scalar x);

    void train(std::vector<RowVector> input_data, std::vector<RowVector> output_data);

    RowVector forward(RowVector &x);

    void saveWeights(const std::string &path);

    void loadWeights(const std::string &path);

    std::vector<RowVector *> neuronLayers;
    std::vector<RowVector *> cacheLayers;
    std::vector<RowVector *> deltas;
    std::vector<Matrix *> weights;
    std::vector<unsigned int> topology;
    Scalar learningRate;
};


#endif //HTRAPP_NEURALNETWORK_H
