#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QSplitter>
#include <QGraphicsItem>
#include <QtGui>
#include <QTextBrowser>
#include <QPushButton>
#include <QCheckBox>
#include "tracer.h"
#include <QGroupBox>
#include "mysquare.h"
#include <QtCore>
#include <QtGui>
#include <QGraphicsView>

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

		std::vector<MySquare*> process_info;
    QGraphicsView *view;
    QGraphicsScene *scene;
    MySquare *square;
    MySquare *square1;
		QTextBrowser *browser;

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
