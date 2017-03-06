#ifndef B_H
#define B_H
#include <QPushButton>
#include <QMouseEvent>

class b : public QPushButton
{
    Q_OBJECT


public:
    explicit b(QWidget *parent = 0);
    ~b();

signals:
    void rightClicked();
    void leftClicked();

protected:
    virtual void mousePressEvent(QMouseEvent *e);
};

#endif // B_H
