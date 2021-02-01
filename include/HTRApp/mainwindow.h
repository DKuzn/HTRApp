#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QResizeEvent>

#include "paintscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QMainWindow *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer *timer;

    PaintScene *scene;

private:
    void resizeEvent(QResizeEvent * event);

private slots:
    void slotTimer();
    void on_clearButton_clicked();
    void on_recButton_clicked();
};
#endif // MAINWINDOW_H
