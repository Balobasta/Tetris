#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(550,840);
    this->setFixedSize(560, 840);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    connect(ui->Dark, SIGNAL(triggered()), this, SLOT(onButtonClicked()));
    connect(ui->Indian, SIGNAL(triggered()), this, SLOT(onButtonClicked()));
    connect(ui->Light, SIGNAL(triggered()), this, SLOT(onButtonClicked()));
    connect(ui->Special, SIGNAL(triggered()), this, SLOT(onButtonClicked()));
    connect(ui->Square, SIGNAL(triggered()), this, SLOT(onButtonClicked()));
    connect(ui->RoundSquare, SIGNAL(triggered()), this, SLOT(onButtonClicked()));
    connect(ui->Circle, SIGNAL(triggered()), this, SLOT(onButtonClicked()));
    timer->start(msecForMoveDown);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pole;
}

void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    pole->draw(painter, this->width(), this->height());
    ui->points->display(QString::number(pole->getPoints()));
    ui->Lines->display(QString::number(pole->getLines()));
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space){
        if (pole->isPause()){
            pole->setPause(false);
        }else{
            pole->setPause(true);
        }
        repaint();
        return;
    }
    if (pole->isPause())
        return;
    if (event->key() == Qt::Key_A){
        pole->moveLeft();
        repaint();
        return;
    }
    if (event->key() == Qt::Key_D){
        pole->moveRight();
        repaint();
        return;
    }
    if (event->key() == Qt::Key_S){
        pole->moveDown();
        repaint();
        return;
    }
    if (event->key() == Qt::Key_W){
        pole->rotate();
        repaint();
        return;
    }
}

void MainWindow::update()
{
    if (pole->isPause()){
        repaint();
        return;
    }
    if (pole->getLevel() != lastLevel){
        lastLevel = pole->getLevel();
        qDebug() << "level  " << lastLevel;
        hardUp();
    }
    pole->moveDown();
    repaint();
}

void MainWindow::hardUp()
{
    if (msecForMoveDown < 20)
        return;
    msecForMoveDown -= 30;
    timer->start(msecForMoveDown);
}

void MainWindow::onButtonClicked()
{
    if (sender() == ui->Dark){
        pole->gameStyle.setDarkStyle();
        repaint();
        return;
    }
    if (sender() == ui->Indian){
        pole->gameStyle.setIndianStyle();
        repaint();
        return;
    }
    if (sender() == ui->Light){
        pole->gameStyle.setLightStyle();
        repaint();
        return;
    }
    if (sender() == ui->Special){
        pole->gameStyle.setSpecialStyle();
        repaint();
        return;
    }
    if (sender() == ui->Square){
        pole->gameStyle.setTileType(TileType::rect);
        repaint();
        return;
    }
    if (sender() == ui->RoundSquare){
        pole->gameStyle.setTileType(TileType::roundedRect);
        repaint();
        return;
    }
    if (sender() == ui->Circle){
        pole->gameStyle.setTileType(TileType::circle);
        repaint();
        return;
    }
}
