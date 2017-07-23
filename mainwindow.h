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
#include <QGroupBox>

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

		QGroupBox *NodeGroup;
		QDialog *passWindow;
private:
    Ui::MainWindow *ui;

		void viz_process(std::vector<trace_info_t> info);
		void requirePass();

		QString pass;

		std::vector<QGraphicsRectItem*> process_info;
    QSplitter *getGBSplitter(QGraphicsView *lview1,Browser *tBrowser);
    QSplitter *getGGSplitter(QGraphicsView *lview2);
    CDRawFrame *cotf;//コントロールパネルクラスの変数
    Browser *browser;

		QGroupBox *createCPUGroup();
		QGroupBox *createNodeGroup();
		QGroupBox *createTextBrowser();
		QGroupBox *createButtonGroup();

public slots:
	void StartStopTrace(bool click);//View1に対してのslot関数
	void ShowNodes(bool click);
	void quit();
	void setPass(const QString &);
	void onSetPass();

};
