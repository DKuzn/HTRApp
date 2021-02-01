#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "image.h"
#include "neuralnetwork.h"
#include <opencv2/opencv.hpp>
#include <Eigen/Eigen>

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new PaintScene();
    ui->drawArea->setScene(scene);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::slotTimer);
    timer->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotTimer()
{
    timer->stop();
    scene->setSceneRect(0,0, ui->drawArea->width() - 20, ui->drawArea->height() - 20);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    timer->start(100);
    QMainWindow::resizeEvent(event);
}

void MainWindow::on_clearButton_clicked()
{
    ui->drawArea->scene()->clear();
    ui->result->clear();
}

void MainWindow::on_recButton_clicked()
{
    std::vector<uint> topology = {784, 120, 10};
    neuralnetwork net = neuralnetwork(topology);
    QImage img = ui->drawArea->grab(ui->drawArea->sceneRect().toRect()).toImage(); // вылетает
    Image image = Image();
    image.open(img);
    RowVector input = image.getVector();
    RowVector pred = net.forward(input);
    RowVector::Index idx;
    pred.maxCoeff(&idx);
    std::string res = std::to_string(idx);
    QString qstr = QString::fromUtf8(res.c_str());
    ui->result->setText(qstr);
}
