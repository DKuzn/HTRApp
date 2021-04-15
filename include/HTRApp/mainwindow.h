// mainwindow.h
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QResizeEvent>

#include "paintscene.h"
#include "neuralnetwork.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QMainWindow *parent = nullptr);

    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    QTimer *timer;

    PaintScene *scene;
    NeuralNetwork *net;

private:
    void resizeEvent(QResizeEvent *event) override;

private slots:

    void slotTimer();

    void on_clearButton_clicked();

    void on_recButton_clicked();
};

#endif // MAINWINDOW_H
