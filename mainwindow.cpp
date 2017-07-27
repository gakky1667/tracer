#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTextBrowser>
#include <QDialog>
#include <QCheckBox>
#include "tracer.h"
#include <QGraphicsTextItem>
#include <QGraphicsItem>
#include <QGroupBox>
#include <QMessageBox>
#include <QTextEdit>
#include <string>
#include <QtCore/QString>
#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include "mysquare.h"
#define ZOOM 1000

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){

    ui->setupUi(this);

    requirePass();

    setWindowTitle(tr("ROSHC: TRACER"));
    NodeGroup = createNodeGroup();

    QVBoxLayout *toplayout = new QVBoxLayout;
    toplayout->addWidget(createCPUGroup());
    toplayout->addWidget(NodeGroup);
    toplayout->addWidget(createTextBrowser());
    toplayout->addWidget(createButtonGroup());

    QWidget *window = new QWidget();
    window->setLayout(toplayout);

    NodeGroup->hide();
    setCentralWidget(window);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::requirePass(){
    passWindow = new QDialog;
    QLabel *label = new QLabel("pass: ");
    QLineEdit *edit = new QLineEdit;
    QPushButton *button = new QPushButton("ok");
    QHBoxLayout *layout = new QHBoxLayout;

    QObject::connect(edit, SIGNAL(textChanged(const QString &)),this, SLOT(setPass(const QString &)));
    QObject::connect(button,SIGNAL(clicked()),this,SLOT(onSetPass()));

    layout->addWidget(label);
    layout->addWidget(edit);
    layout->addWidget(button);
    passWindow->setWindowTitle("Password");
    passWindow->setLayout(layout);


    passWindow->show();
}

void MainWindow::setPass(const QString &input){
    if(input!=pass){
        pass = input;
    }
}

void MainWindow::onSetPass(){
    passWindow->hide();
}

QGroupBox *MainWindow::createCPUGroup(){
    QGroupBox *groupBox = new QGroupBox("CPUs");
    QHBoxLayout *toplayout = new QHBoxLayout;

    QLabel *cpu0 = new QLabel("cpu 0");
    QLabel *cpu1 = new QLabel("cpu 1");
    QLabel *cpu2 = new QLabel("cpu 2");
    QLabel *cpu3 = new QLabel("cpu 3");
    QLabel *cpu4 = new QLabel("cpu 4");
    QLabel *cpu5 = new QLabel("cpu 5");
    QLabel *cpu6 = new QLabel("cpu 6");
    QLabel *cpu7 = new QLabel("cpu 7");
    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(cpu0); layout->addStretch();
    layout->addWidget(cpu1); layout->addStretch();
    layout->addWidget(cpu2); layout->addStretch();
    layout->addWidget(cpu3); layout->addStretch();
    layout->addWidget(cpu4); layout->addStretch();
    layout->addWidget(cpu5); layout->addStretch();
    layout->addWidget(cpu6); layout->addStretch();
    layout->addWidget(cpu7); layout->addStretch();
    toplayout->addLayout(layout);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);
    QPen blackpen(Qt::black);
    blackpen.setWidth(1);
#if 0
    // temp
    square = new MySquare(0,0,50);
    scene->addItem(square);
    square1 = new MySquare(10,100,50);
    scene->addItem(square1);
#endif

    view = new QGraphicsView(scene);
    toplayout->addWidget(view);
    groupBox->setLayout(toplayout);

    return groupBox;
}

// push_back
QGroupBox *MainWindow::createNodeGroup(){
    QGroupBox *groupBox = new QGroupBox("Node");
    QLabel *node0 = new QLabel("talker");
    QLabel *node1 = new QLabel("listener");
    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(node0);
    layout->addWidget(node1);
    layout->addStretch(1);
    groupBox->setLayout(layout);

    return groupBox;
}

QGroupBox *MainWindow::createTextBrowser(){
    QGroupBox *groupBox = new QGroupBox("Node Info");
    browser = new QTextBrowser;
    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(browser);
    layout->addStretch();
    browser->setText("Here, Node's informations are shown \n(e.g, PID, prio,...)");
    groupBox->setLayout(layout);

    return groupBox;
}

QGroupBox *MainWindow::createButtonGroup(){
    QGroupBox *groupBox = new QGroupBox("Operations");
    QPushButton *StartStopButton = new QPushButton("Start/Stop");
    QPushButton *NodeListButton = new QPushButton("Node List View");
    QPushButton *CloseButton = new QPushButton("Close");
    QHBoxLayout *layout = new QHBoxLayout;

    layout->addWidget(StartStopButton);
    layout->addWidget(NodeListButton);
    layout->addWidget(CloseButton);
    layout->addStretch(1);
    groupBox->setLayout(layout);

    StartStopButton->setCheckable(true);
    NodeListButton->setCheckable(true);

    QObject::connect(StartStopButton, SIGNAL(toggled(bool)), this, SLOT(StartStopTrace(bool)));
    QObject::connect(NodeListButton, SIGNAL(toggled(bool)), this, SLOT(ShowNodes(bool)));
    QObject::connect(CloseButton, SIGNAL(clicked()), this, SLOT(quit()));

    return groupBox;
}

void MainWindow::StartStopTrace(bool click){
  if (click){
    SchedViz::Tracer tracer;
    tracer.setup(pass.toStdString());
    tracer.start_ftrace(pass.toStdString());
  }else{
    SchedViz::Tracer tracer;
    tracer.reset(pass.toStdString());
    viz_process(tracer.get_info());
  }
}

void MainWindow::ShowNodes(bool click){

    if(click){
      NodeGroup->show();
    }
    else{
        NodeGroup->hide();
    }
}


void MainWindow::viz_process(std::vector<trace_info_t> info){
  double base_time = info[0].start_time;
  double base_x = 200;
  double base_y = 40;
  double width =0;
  double x=0;
  double y=0;

  for(int i=0;i<(int)info.size();i++){
    x = info[i].start_time - base_time;
    width = info[i].runtime;
    y = info[i].core * base_y;

    square = new MySquare(x*ZOOM+base_x,y,width*ZOOM,info[i],browser);

    process_info.push_back(square); 
    scene->addItem(process_info[i]);		
  }
}

void MainWindow::quit(){
    exit(1);
}
