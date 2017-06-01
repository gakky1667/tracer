#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTextBrowser>
#include <QDialog>
#include <QCheckBox>
#include "tracer.h"



MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){

    ui->setupUi(this);

    InitView1();
    InitView2();

    cotf = new CDRawFrame(0,(QObject*)this);
	  browser = new Browser(0,(QObject*)this);

    vsplit2=getGBSplitter(m_view1,browser);
    vsplit4=getGGSplitter(m_view2);


    QSplitter *vsplit = new QSplitter(Qt::Vertical);
    vsplit->addWidget(vsplit2);
    vsplit->addWidget(vsplit4);
    vsplit->addWidget(cotf);
    setCentralWidget(vsplit);

}

MainWindow::~MainWindow(){
    delete ui;
}

QSplitter *MainWindow::getGBSplitter(QGraphicsView *lview1, Browser *tBrowser){
    QSplitter *hsplit = new QSplitter(Qt::Horizontal);
    hsplit->addWidget(lview1);
    QSplitter *hsplit1 = new QSplitter(Qt::Horizontal);
    hsplit1->addWidget(tBrowser);
    hsplit->addWidget(hsplit1);
    return hsplit;
}


QSplitter *MainWindow::getGGSplitter(QGraphicsView *lview1){
	SchedViz::Tracer tracer;

	/**splitterの設定*/
	QSplitter *hsplit = new QSplitter(Qt::Horizontal);
	hsplit->addWidget(lview1);

	QSplitter *hsplit1 = new QSplitter(Qt::Vertical);
	for(int i(0); i < (int)tracer.v_node_info_.size(); i++){
		hsplit1->addWidget(new QCheckBox(tr(tracer.v_node_info_.at(i).name.c_str())));
		hsplit->addWidget(hsplit1);
	}

	QSplitter *vsplit = new QSplitter(Qt::Vertical);
	vsplit->addWidget(new QPushButton(tr("Apply")));
	hsplit1->addWidget(vsplit);
	return hsplit;
}

void MainWindow::InitView1(){
    item1 = new QGraphicsEllipseItem(100, 100, 200, 100);
    item1->setBrush(QBrush(QColor("pink")));

    m_scene1 = new QGraphicsScene();
    m_scene1->setSceneRect(-20,-30,640,480);
    m_scene1->addItem(item1);

    m_view1 = new QGraphicsView();//viewの生成
    m_view1->setScene(m_scene1);//viewにsceneをセット
}

void MainWindow::InitView2(){
    item2 = new QGraphicsEllipseItem(100, 100, 200, 100);
    item2->setBrush(QBrush(QColor("blue")));
    m_scene2 = new QGraphicsScene();
    m_scene2->setSceneRect(-20,-30,640,480);
    m_scene2->addItem(item2);
    m_view2 = new QGraphicsView();
    m_view2->setScene(m_scene2);
}

void MainWindow::StartStopTrace(bool click){
//	setuid(0);
	if (click){
		std::cout << "start" << std::endl;
		//SchedViz::Tracer tracer;
		//tracer.setup();
		//tracer.start_ftrace();
	}else{
		std::cout << "stop" << std::endl; 
		//SchedViz::Tracer tracer; 
		//tracer.reset();
	}
	//setuid(getuid());
}

void MainWindow::valid_node_viz(){
	QMessageBox::warning(0,"View1","View1message"); 
}

void MainWindow::quit(){
    exit(1);
}
