#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace yarp::os;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    connected=false;
    
    client_port.open("/crawlingGUI/client");
    if (!yarp::os::Network::connect("/crawlingGUI/client","/crawlManager/in"))
    {
        std::cout << "Error! Could not connect to server /crawlManager/in" << std::endl;
        //return -1;
    }
    else
    {
        connected=true;
        service.yarp().attachAsClient(client_port);
        service.yarp().setStreamingMode(true);
    }
}

MainWindow::~MainWindow()
{
    client_port.close();
    delete ui;
}

void MainWindow::on_pushButton_stop_clicked()
{
    if(connected==true) service.stopCrawling();
    else
        cout<<"The GUI is not connected! Please check_connections!"<<endl;
}

void MainWindow::on_pushButton_crawl_clicked()
{
    if(connected==true) service.startCrawling();
    else
        cout<<"The GUI is not connected! Please check_connections!"<<endl;
}

void MainWindow::on_pushButton_gotoinit_clicked()
{
    if(connected==true) service.goToInitPose();
    else
        cout<<"The GUI is not connected! Please check_connections!"<<endl;
}

void MainWindow::on_pushButton_turnleft_clicked()
{
    if(connected==true) service.turnLeft();
    else
        cout<<"The GUI is not connected! Please check_connections!"<<endl;
}

void MainWindow::on_pushButton_turnright_clicked()
{
    if(connected==true) service.turnRight();
    else
        cout<<"The GUI is not connected! Please check_connections!"<<endl;
}

void MainWindow::on_pushButton_slower_clicked()
{
    if(connected==true) service.slower();
    else
        cout<<"The GUI is not connected! Please check_connections!"<<endl;
}

void MainWindow::on_pushButton_faster_clicked()
{
    if(connected==true) service.faster();
    else
        cout<<"The GUI is not connected! Please check_connections!"<<endl;
}

void MainWindow::on_pushButton_checkconnection_clicked()
{
    if(connected==false)
    {
        
        if (!yarp::os::Network::connect("/crawlingGUI/client","/crawlManager/in"))
        {
            std::cout << "Error! Could not connect to server /crawlManager/in" << std::endl;
        }
        else
        {
            connected=true;
            service.yarp().attachAsClient(client_port);
            service.yarp().setStreamingMode(true);
        }
    }
    
    if(connected==true) service.checkConnections();
    else
        cout<<"The GUI is not connected! Please check_connections!"<<endl;
}
