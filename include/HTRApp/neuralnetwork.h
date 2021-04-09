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
