#include "mysquare.h"
#include "mainwindow.h"
#include <QTextBrowser>

MySquare::MySquare(int my_x, int my_y,int my_width, trace_info_t my_node_info, QTextBrowser *browser)
{
    Pressed = false;
    setFlag(ItemIsMovable);
    MyX = my_x;
    MyY = my_y;
    MyWidth = my_width;
		MyNodeInfo = my_node_info;
		TextBrowser = browser;
}

QRectF MySquare::boundingRect() const
{
    int MyHeight = 10;

    return QRectF(MyX,MyY,MyWidth,MyHeight);
}

void MySquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::blue);
    QPen blackpen(Qt::black);
    blackpen.setWidth(6);

    if (Pressed){
        brush.setColor(Qt::red);
				show_node_info();
    }else{
        //brush.setColor(Qt::green);
    }

    painter->fillRect(rec,brush);
    painter->drawRect(rec);
}

//TODO:: Show info in node_info_t
void MySquare::show_node_info(){
	QString qstr;
	
	
	
	qstr = QString::fromStdString(MyNodeInfo.name);
	TextBrowser->setText(qstr);
}

void MySquare::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);

}

void MySquare::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
