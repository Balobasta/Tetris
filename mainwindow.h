#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "field.h"
#include <QPaintEvent>
#include <QKeyEvent>
#include <QTimer>

namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
private slots:
    void update();
    void hardUp();
    void onButtonClicked();
private:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    Ui::MainWindow *ui;
    field *pole = new field;
    QTimer *timer = new QTimer;
    int msecForMoveDown = 500;
    int lastLevel = 0;
};

#endif // MAINWINDOW_H
