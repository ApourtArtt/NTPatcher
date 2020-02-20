#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void save();
    void modify(QString newFilename, QString originalFilename);
    QByteArray parseOptions(QCheckBox *checkbox, QByteArray pattern, QByteArray newData, QByteArray data);
    int getBitToBegin(QByteArray pattern, QByteArray data);
    QByteArray patch(int firstBit, QByteArray newBytes, QByteArray data);
    Ui::MainWindow *ui;

    QByteArray pZoom, pCtrlZ, pGfSkipper; // Pattern
    QByteArray nZoom, nCtrlZ, nGfSkipper; // New data
};


#endif // MAINWINDOW_H
