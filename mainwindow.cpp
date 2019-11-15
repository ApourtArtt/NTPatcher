#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setVector();
    //QByteArray patched  = getFileText("FilePatched");
    //QByteArray original = getFileText("File");
    //runDiff(original, patched);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setVector()
{
    p_zoomhack.push_back(createVecElem(491593, "v"));
    p_zoomhack.push_back(createVecElem(491594, "\x6"));
    p_zoomhack.push_back(createVecElem(491595, "\x0090"));

    p_ctrlZ.push_back(createVecElem(2949370, "\x0090"));
    p_ctrlZ.push_back(createVecElem(2949371, "\x0090"));
}

s_patch MainWindow::createVecElem(int address, QByteArray byte)
{
    s_patch in;
    in.address = address;
    in.byte = byte;
    return in;
}

void MainWindow::patchBytes(QByteArray *datas)
{
    modifyBit(datas, ui->CB_CTRLZ, p_ctrlZ);
    modifyBit(datas, ui->CB_ZOOM, p_zoomhack);
}

void MainWindow::modifyBit(QByteArray *datas, QCheckBox *checkbox, std::vector<s_patch> patchStruc)
{
    if(checkbox->isChecked())
        for(unsigned long i = 0 ; i < patchStruc.size() ; i++)
            datas->replace(patchStruc[i].address, 1, patchStruc[i].byte);
}

bool MainWindow::fillData(QString filename)
{
    QFile outFile(filename + "Patched.exe");
    QFile inFile(filename + ".exe");
    QDataStream in(&outFile);
    if(!outFile.open(QIODevice::WriteOnly))
        return false;
    if(!inFile.open(QIODevice::ReadOnly))
       return false;
    QByteArray datas = inFile.read(inFile.size());
    patchBytes(&datas);
    in.writeRawData(datas, static_cast<int>(inFile.size()));
    inFile.close();
    outFile.close();
    return true;
}

void MainWindow::on_PB_EXPORT_clicked()
{
    fillData("File");
}



// DEBUG PURPOSE ONLY

QByteArray MainWindow::getFileText(QString filename)
{
    QFile file(filename + ".exe");
    QDataStream in(&file);
    if(!file.open(QIODevice::ReadOnly))
       return "";
    QByteArray datas = file.read(file.size());
    in.writeRawData(datas, static_cast<int>(file.size()));
    file.close();
    return datas;
}

void MainWindow::runDiff(QByteArray original, QByteArray cracked)
{
    qDebug() << "Size : " << original.size() << " " << cracked.size();
    for(int i = 0 ; i < original.size() ; i++)
    {
        if(original[i] != cracked[i])
            qDebug() << i << ", Original : " << original[i] << " | Patched : " << cracked[i];
    }
}
