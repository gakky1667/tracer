#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTextBrowser>
#include <QDialog>
#include <QCheckBox>
#include "tracer.h"
#include <QGraphicsTextItem>
#include <QGraphicsItem>
#define TEMP_RATE 1000

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
	int base_x=0;
	int base_y=0;
	int space=40;
	
	//TODO:vector
	QGraphicsTextItem *core0 = new QGraphicsTextItem();
	QGraphicsTextItem *core1 = new QGraphicsTextItem();
	QGraphicsTextItem *core2 = new QGraphicsTextItem();
	QGraphicsTextItem *core3 = new QGraphicsTextItem();
	QGraphicsTextItem *core4 = new QGraphicsTextItem();
	QGraphicsTextItem *core5 = new QGraphicsTextItem();
	QGraphicsTextItem *core6 = new QGraphicsTextItem();
	QGraphicsTextItem *core7 = new QGraphicsTextItem();

	core0->setPlainText("core 0");
	core1->setPlainText("core 1");
	core2->setPlainText("core 2");
	core3->setPlainText("core 3");
	core4->setPlainText("core 4");
	core5->setPlainText("core 5");
	core6->setPlainText("core 6");
	core7->setPlainText("core 7");
		
	core0->setPos(base_x,base_y); base_y+=space;
	core1->setPos(base_x,base_y); base_y+=space;
	core2->setPos(base_x,base_y); base_y+=space;
	core3->setPos(base_x,base_y); base_y+=space;
	core4->setPos(base_x,base_y); base_y+=space;
	core5->setPos(base_x,base_y); base_y+=space;
	core6->setPos(base_x,base_y); base_y+=space;
	core7->setPos(base_x,base_y); base_y+=space;

  m_scene1 = new QGraphicsScene();
  m_scene1->setSceneRect(-20,-30,4000,380);

  m_scene1->addItem(core0);
  m_scene1->addItem(core1);
  m_scene1->addItem(core2);
  m_scene1->addItem(core3);
  m_scene1->addItem(core4);
  m_scene1->addItem(core5);
  m_scene1->addItem(core6);
  m_scene1->addItem(core7);

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
		SchedViz::Tracer tracer;
		tracer.setup();
		tracer.start_ftrace();
	}else{
		SchedViz::Tracer tracer; 
		tracer.reset();
		viz_process(tracer.get_info());
	}
	//setuid(getuid());
}

void MainWindow::valid_node_viz(){
	QMessageBox::warning(0,"View1","View1message"); 
}

void MainWindow::quit(){
	exit(1);
}

void MainWindow::viz_process(std::vector<trace_info_t> info){
	double base_time = info[0].start_time;
	double base_x = 70;
	double base_y = 40;
	double width =0;
	int height =20;
	double x=0;
	double y=0;

	for(int i=0;i<(int)info.size();i++){
		x = info[i].start_time - base_time;
		width = info[i].runtime;
		y = info[i].core * base_y;
		QGraphicsRectItem *process = new QGraphicsRectItem(x*TEMP_RATE+base_x,y,width*TEMP_RATE,height);
		//temp ...
		if(info[i].name == "3953")
			process->setBrush(QBrush(QColor("pink")));
		else
			process->setBrush(QBrush(QColor("red")));
//		process->setFlags(QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsSelectable);
		process_info.push_back(process);
		m_scene1->addItem(process_info[i]);
		m_view1->setScene(m_scene1);
	}

}
