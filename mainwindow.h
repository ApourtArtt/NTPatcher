#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <vector>
#include <QDebug>
#include <QCheckBox>


namespace Ui {
class MainWindow;
}

struct s_patch
{
    int address;
    QByteArray byte;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_PB_EXPORT_clicked();

private:
    void setVector();
    s_patch createVecElem(int address, QByteArray byte);
    void patchBytes(QByteArray *datas);
    void modifyBit(QByteArray *datas, QCheckBox *checkbox, std::vector<s_patch> patchStruc);
    bool fillData(QString filename);

    Ui::MainWindow *ui;
    QString filename;
    std::vector<s_patch> p_ctrlZ, p_zoomhack;



    // DEBUG PURPOSE ONLY
    QByteArray getFileText(QString filename);
    void runDiff(QByteArray original, QByteArray cracked);
};

#endif // MAINWINDOW_H
