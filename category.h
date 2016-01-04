#ifndef CATEGORY_H
#define CATEGORY_H
#include <QToolBox>
#include <QToolButton>

class category : public QToolBox
{
    Q_OBJECT
public:
    category(QWidget *parent = 0,Qt::WindowFlags f= 0);

private slots:
    void add_entry();

private:
    QToolButton *outBtn_1;
    QToolButton *outBtn_2;
    QToolButton *outBtn_3;
    QToolButton *outBtn_4;
    QToolButton *outBtn_5;
    QToolButton *outBtn_6;
    QToolButton *outBtn_7;
    QToolButton *outBtn_8;
    QToolButton *outBtn_9;
    QToolButton *outBtn_10;
    QToolButton *outBtn_11;
    QToolButton *outBtn_12;
    QToolButton *outBtn_add;
    QToolButton *inBtn_1;
    QToolButton *inBtn_2;
    QToolButton *inBtn_3;
    QToolButton *inBtn_4;
    QToolButton *inBtn_add;

};

#endif // CATEGORY_H
