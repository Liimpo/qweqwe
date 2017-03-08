#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <QDialog>

namespace Ui {
class Highscore;
}

class Highscore : public QDialog
{
    Q_OBJECT

public:
    explicit Highscore(QWidget *parent = 0);
    virtual ~Highscore();
    bool newResult(int,int,int);
    void tableLoad();
    void tableSave();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Highscore *ui;
};

#endif // HIGHSCORE_H
