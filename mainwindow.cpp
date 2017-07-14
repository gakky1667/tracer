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
#define TEMP_RATE 3000

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){

	ui->setupUi(this);

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

QGroupBox *MainWindow::createCPUGroup(){
	QGroupBox *groupBox = new QGroupBox("CPUs");
	QLabel *cpu0 = new QLabel("cpu 0");
	QLabel *cpu1 = new QLabel("cpu 1");
	QLabel *cpu2 = new QLabel("cpu 2");
	QLabel *cpu3 = new QLabel("cpu 3");
	QLabel *cpu4 = new QLabel("cpu 4");
	QLabel *cpu5 = new QLabel("cpu 5");
	QLabel *cpu6 = new QLabel("cpu 6");
	QLabel *cpu7 = new QLabel("cpu 7");
	QVBoxLayout *layout = new QVBoxLayout;

	layout->addWidget(cpu0);
	layout->addWidget(cpu1);
	layout->addWidget(cpu2);
	layout->addWidget(cpu3);
  layout->addWidget(cpu4);
	layout->addWidget(cpu5);
	layout->addWidget(cpu6);
	layout->addWidget(cpu7);
	layout->addStretch(1);
	groupBox->setLayout(layout);

	return groupBox;
}

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
	QTextBrowser *browser = new QTextBrowser;
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
		tracer.setup();
		tracer.start_ftrace();
	}else{
 		SchedViz::Tracer tracer; 
		tracer.reset();
	//	viz_process(tracer.get_info());
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


#if 0
void MainWindow::viz_process(std::vector<trace_info_t> info){
	double base_time = info[0].start_time;
	double base_x = 200;
	double base_y = 40;
	double width =0;
	int height =20;
	double x=0;
	double y=0;
	std::string color_flag = info[0].name;
	int color_index=0;

	for(int i=0;i<(int)info.size();i++){
		x = info[i].start_time - base_time;
		width = info[i].runtime;
		y = info[i].core * base_y;
		QGraphicsRectItem *process = new QGraphicsRectItem(x*TEMP_RATE+base_x,y,width*TEMP_RATE,height);

		// Change Color each by PID
		if(info[i].name != color_flag){
			color_index++;
		}

		process->setBrush(QBrush(QColor(my_color[color_index])));
		color_flag = info[i].name;

//		process->setFlags(QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsSelectable);
		process_info.push_back(process);
		m_scene1->addItem(process_info[i]);
		m_view1->setScene(m_scene1);
	}

}
#endif
void MainWindow::quit(){
	exit(1);
}
