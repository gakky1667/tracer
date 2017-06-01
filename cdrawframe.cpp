#include "cdrawframe.h"
#include "ui_cdrawframe.h"


CDRawFrame::CDRawFrame(QWidget *parent,QObject *mainwin) : QFrame(parent), ui(new Ui::CDRawFrame){
    ui->setupUi(this);
    //以下、mainwindowクラスからのポインタを一度コピーして、signalの送信先オブジェクトとしている。
    wg=new QObject();
    wg = mainwin;

    //signal,slotをconnectしている。
    QObject::connect(ui->CloseButton,SIGNAL(clicked()),wg,SLOT(quit()));
    QObject::connect(ui->StartButton,SIGNAL(toggled(bool)),wg,SLOT(StartStopTrace(bool)));
    QObject::connect(ui->StopButton,SIGNAL(clicked()),wg,SLOT(valid_node_viz()));



}

CDRawFrame::~CDRawFrame()
{
    delete ui;
}
