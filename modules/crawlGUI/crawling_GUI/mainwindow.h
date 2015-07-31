#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <yarp/os/all.h>
#include <crawlManagerService.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_stop_clicked();

    void on_pushButton_crawl_clicked();

    void on_pushButton_gotoinit_clicked();

    void on_pushButton_turnleft_clicked();

    void on_pushButton_turnright_clicked();

    void on_pushButton_slower_clicked();

    void on_pushButton_faster_clicked();

    void on_pushButton_checkconnection_clicked();

private:
    Ui::MainWindow *ui;
    
    yarp::os::Port client_port;
    crawlManagerService service;
    bool connected;
};

#endif // MAINWINDOW_H
