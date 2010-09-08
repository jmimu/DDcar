#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    graph()
{
    ui->setupUi(this);

    ui->graphicsView->setScene(&graph);
    graph.setSceneRect(0, 0,2000, 2000);


    QObject::connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(quit_button_pushed()));

    /*dif_noms.push_back("hello");
    dif_noms.push_back("how");
    dif_noms.push_back("are");
    dif_noms.push_back("you");
    dif_noms.push_back("today");

    compteur=0;

    ui->quitButton->setText(dif_noms.at(compteur).c_str());*/
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::quit_button_pushed()
{
    /*QGraphicsRectItem *rect = scene.addRect(QRectF(0, 0, 100, 100));
    rect->setBrush(Qt::cyan);*/

    graph.load_background("track.png");

/*    std::cout<<ui->quitButton->text().toStdString()<<std::endl;
    //next text...
    compteur++;

    if (compteur<dif_noms.size())
        ui->quitButton->setText(dif_noms.at(compteur).c_str());
    else
    {
        std::cout<<"??????"<<std::endl;
        this->close();
    }*/
}
