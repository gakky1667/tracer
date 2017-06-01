#ifndef BROWSER_H
#define BROWSER_H

#include <QFrame>

namespace Ui {
class Browser;
}

class Browser : public QFrame
{
    Q_OBJECT

public:
    //explicit Browser(QWidget *parent = 0);
    Browser(QWidget *parent, QObject *mainwin);
    ~Browser();

private:
    Ui::Browser *ui;

private:
    QObject *wg;
};

#endif // BROWSER_H
