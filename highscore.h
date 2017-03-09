#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <QDialog>
#include <QString>
#include <QDir>
#include <QSettings>
#include <QInputDialog>

namespace Ui {
class Highscore;
}

class Highscore : public QDialog
{
    Q_OBJECT

public:
    explicit Highscore(QWidget *parent = 0);
    virtual ~Highscore();
    bool newResult(int diff ,int time);
    void tableLoad();
    void tableSave();
    //Hanterar load/save mha settings
    void settingsHandler(QSettings * setting);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Highscore *ui;
    QSettings *mineSettings;
};

#endif // HIGHSCORE_H
