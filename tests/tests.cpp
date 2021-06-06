// tests.cpp
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

#include <iostream>
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "neuralnetwork.h"
#include "dataset.h"

NeuralNetwork getNet() {
    std::vector<unsigned int> topology = {784, 120, 10};
    NeuralNetwork net = NeuralNetwork(topology);
    return net;
}

TEST_CASE("Neural network weights interaction", "[net_weights]") {
    NeuralNetwork net = getNet();

    SECTION("Getting weights matrices") {
        CHECK_NOTHROW(net.getWeights());
    }
    SECTION("Save weights") {
        CHECK_NOTHROW(net.saveWeights("weights.csv"));
    }
    SECTION("Load weights for right path") {
        CHECK_NOTHROW(net.loadWeights("weights.csv"));
    }
    SECTION("Load weights for wrong path") {
        CHECK_THROWS(net.loadWeights("notweights.csv"));
    }
}

TEST_CASE("Neural network forwarding", "[forwarding]") {
    RowVector right_input = RowVector(784);
    RowVector wrong_input = RowVector(10);
    NeuralNetwork net = getNet();

    SECTION("Forwarding with right input data") {
        CHECK_NOTHROW(net.forward(right_input));
    }
    SECTION("Forwarding with wrong input data") {
        CHECK_THROWS(net.forward(wrong_input));
    }
}

TEST_CASE("Network training", "[training]") {
    std::string path = "./train.csv";
    Dataset ds = Dataset(path);
    NeuralNetwork net = getNet();

    SECTION("Dataset indexation operator") {
        CHECK(typeid(ds[0]) == typeid(DatasetItem));
    }
    SECTION("Weights updating after train step") {
        Matrix source_weight = *net.getWeights()[1];
        net.train({ds[0].x}, {ds[0].y});
        Matrix updated_weight = *net.getWeights()[1];
        CHECK(source_weight != updated_weight);
    }
}
