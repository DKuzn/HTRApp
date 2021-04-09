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
