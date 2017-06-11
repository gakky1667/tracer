#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QSplitter>
#include <QGraphicsItem>
#include "cdrawframe.h"//QFrameを基底クラスとしたコントロールパネルのクラス宣言
#include "browser.h"
#include <QtGui>
#include <QTextBrowser>
#include <QPushButton>
#include <QCheckBox>
#include "tracer.h"

class QMenu;
class SecondDialog;

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsView *m_view1;//add
    QGraphicsScene *m_scene1;//add
    QGraphicsView *m_view2;//add
    QGraphicsScene *m_scene2;//add


    QSplitter *vsplit2;
    QSplitter *vsplit4;

    QGraphicsEllipseItem *item1;//描画用
    QGraphicsEllipseItem *item2;

    void InitView1();
    void InitView2();
		void viz_process(std::vector<trace_info_t> info);

		std::vector<QColor> my_color;

		std::vector<QGraphicsRectItem*> process_info;
    QSplitter *getGBSplitter(QGraphicsView *lview1,Browser *tBrowser);
    QSplitter *getGGSplitter(QGraphicsView *lview2);
    CDRawFrame *cotf;//コントロールパネルクラスの変数
    Browser *browser;


public slots:
	void StartStopTrace(bool click);//View1に対してのslot関数
	void valid_node_viz();
  void quit();

};
