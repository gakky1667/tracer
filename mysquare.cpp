#include "mysquare.h"
#include "mainwindow.h"


MySquare::MySquare(int my_x, int my_y,int my_width)
{
    Pressed = false;
    setFlag(ItemIsMovable);
    MyX = my_x;
    MyY = my_y;
    MyWidth = my_width;
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
        //show_node_info();
    }else{
        //brush.setColor(Qt::green);
    }

    painter->fillRect(rec,brush);
    painter->drawRect(rec);
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
