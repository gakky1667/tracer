#ifndef CDRAWFRAME_H
#define CDRAWFRAME_H

#include <QFrame>

namespace Ui {
class CDRawFrame;
}

class CDRawFrame : public QFrame
{
    Q_OBJECT

public:
    //explicit CDrawFrame(QWidget *parent = 0);  original
    CDRawFrame(QWidget *parent,QObject* mainwin);
    ~CDRawFrame();

private:
    Ui::CDRawFrame *ui;

private:
     QObject *wg;//signal,slotを扱うためにメッセージを送信する先のオブジェクト(Widget)をコピーする。おまじない

};

#endif // CDRAWFRAME_H
