#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "testing.h"
#include "highscore.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_actionEasy_clicked();

    void on_hiscoreButton_clicked();

private:
    Highscore *scorePtr;
    testing *testPtr;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
