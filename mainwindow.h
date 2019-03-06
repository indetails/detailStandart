#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QFile>
#include <QTextStream>

#include "deviceStruct.h"

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

private slots:

    void on_b_add_ventilation_clicked();
    void on_bChooseVentilation_clicked();
    void setup_Visuals();
    device addPart(QString type, device newPart);

    void on_btnGenerateBOM_clicked();
};

#endif // MAINWINDOW_H
