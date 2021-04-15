// mainwindow.cpp
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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "image.h"
#include "neuralnetwork.h"
#include <Eigen/Eigen>

MainWindow::MainWindow(QMainWindow *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    scene = new PaintScene();
    ui->drawArea->setScene(scene);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::slotTimer);
    timer->start(100);

    std::vector<unsigned int> topology = {784, 120, 10};
    this->net = new NeuralNetwork(topology);
    std::string weightsPath = "./net_weights.csv";
    this->net->loadWeights(weightsPath);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::slotTimer() {
    timer->stop();
    scene->setSceneRect(0, 0, ui->drawArea->width() - 20, ui->drawArea->height() - 20);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    timer->start(100);
    QMainWindow::resizeEvent(event);
}

void MainWindow::on_clearButton_clicked() {
    ui->drawArea->scene()->clear();
    ui->result->clear();
}

void MainWindow::on_recButton_clicked() {
    QImage img = ui->drawArea->grab(ui->drawArea->sceneRect().toRect()).toImage();
    Image image = Image();
    image.open(img);
    RowVector input = image.getVector();
    RowVector pred = net->forward(input);
    RowVector::Index idx;
    pred.maxCoeff(&idx);
    std::string res = std::to_string(idx);
    QString qstr = QString::fromUtf8(res.c_str());
    ui->result->setText(qstr);
}
