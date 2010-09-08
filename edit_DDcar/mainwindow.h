#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <vector>
#include <QGraphicsScene>
#include "graph_ut.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    Ui::MainWindow *ui;
/*    std::vector<std::string> dif_noms;
    unsigned int compteur;*/
    Graph_Ut graph;

public slots:
    void quit_button_pushed();
    //void on_view_click();

};

#endif // MAINWINDOW_H
