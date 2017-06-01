#include "browser.h"
#include "ui_browser.h"


Browser::Browser(QWidget *parent, QObject *mainwin) : QFrame(parent), ui(new Ui::Browser){
    ui->setupUi(this);

    wg=new QObject();
    wg = mainwin;

    //signal,slotをconnectしている。
    //QObject::connect(ui->SlotButton,SIGNAL(clicked()),wg,SLOT(quit()));
}

Browser::~Browser()
{
    delete ui;
}
