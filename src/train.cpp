// train.cpp
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

#include "neuralnetwork.h"
#include "dataset.h"
#include <iostream>

int main() {
    std::string path = "./train.csv";
    Dataset ds = Dataset(path);
    std::vector<unsigned int> topology = {784, 120, 10};
    NeuralNetwork net = NeuralNetwork(topology, 0.0001);
    for (int j = 0; j < 10; j++) {
        for (int i = 0; i < 42000; i++) {
            net.train({ds[i].x}, {ds[i].y});
        }
        net.saveWeights("./net_weights.csv");
    }
}

