#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->PB_BROWSENTDIR, &QPushButton::clicked, this, [=]
    {
        QString directory = QFileDialog::getOpenFileName(this, tr("Select NostaleClientX.exe"), QDir::currentPath(), "*.exe");
        if (!directory.isEmpty())
            ui->LE_NTDIR->setText(directory);
    });
    connect(ui->PB_SAVE, &QPushButton::clicked, this, [=]
    {
        save();
    });
    pZoom = "\xd8\x5b\x5c\xdf\xe0\x9e\x76\x08\x8b\x43\x5c\xa3????\xd9\x43\x18\0";
    nZoom = "\xd8\x5b\x5c\xdf\xe0\x9e\xeb\x08\x8b\x43\x5c\xa3????\xd9\x43\x18\0";
    pCtrlZ = "\x77\x04\x84\xdb\x74\x09\xb2\x01\x8b\xc3\xe8????\x5b\xc3\0";
    nCtrlZ = "\x77\x04\x90\x90\x74\x09\xb2\x01\x8b\xc3\xe8????\x5b\xc3\0";
    pGfSkipper = "\xe9????\xa1????\x80\x38\x01\x0f\x85????\xa1????\x8a?\x34\x01\xe8????\x84\xc0\x75\x20\x6a";
    nGfSkipper = "\xe9????\xa1????\x80\x38\x01\x0f\x85????\xa1????\x8a?\x34\x01\xe9\xb3";
    nGfSkipper.append('\0');nGfSkipper.append('\0');nGfSkipper.append('\0');
    nGfSkipper.append("\x84\xc0\x75\x20\x6a");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::save()
{
    QStringList dir = ui->LE_NTDIR->text().split("/");
    QString file = "";
    for(int i = 0 ; i < dir.size() - 1 ; i++)
        file = file + dir[i] + '/';
    file += ui->LE_NEWFILENAME->text();
    if (QFile::exists(file))
    {
        ui->statusBar->showMessage(tr("Patched file already exist, please change filename."), 5000);
        return;
    }
    modify(file, ui->LE_NTDIR->text());
}

void MainWindow::modify(QString newFilename, QString originalFilename)
{
    QFile ofile(originalFilename);
    QDataStream inO(&ofile);
    if(!ofile.open(QIODevice::ReadOnly))
    {
        ui->statusBar->showMessage(tr("Something went wrong in original file opening"), 5000);
        return;
    }
    QByteArray data = ofile.read(ofile.size());
    //data.toHex();
    ofile.close();

    QFile nfile(newFilename);
    QDataStream inN(&nfile);
    if(!nfile.open(QIODevice::WriteOnly))
    {
        ui->statusBar->showMessage(tr("Something went wrong in new file opening"), 5000);
        return;
    }

    data = parseOptions(ui->CB_CTRLZ, pCtrlZ, nCtrlZ, data);
    data = parseOptions(ui->CB_ZOOMHACK, pZoom, nZoom, data);
    data = parseOptions(ui->CB_GFSKIPPER, pGfSkipper, nGfSkipper, data);

    inN.writeRawData(data, data.size());
    nfile.close();
}

QByteArray MainWindow::parseOptions(QCheckBox *checkbox, QByteArray pattern, QByteArray newData, QByteArray data)
{
    if(!(checkbox->isChecked()))
        return data;
    int firstBit = getBitToBegin(pattern, data);
    if(firstBit == -1)
        return data;
    return patch(firstBit, newData, data);
}

int MainWindow::getBitToBegin(QByteArray pattern, QByteArray data)
{
    for(int i = 0 ; i < data.size() ; i++)
    {
        if(data[i] == pattern[0])
        {
            int j = 0;
            bool equal = true;
            for(; j < pattern.size() ; j++)
            {
                if(pattern[j] != data[i+j] && pattern[j] != '?')
                {
                    equal = false;
                    break;
                }
            }
            if(equal)
                return i;
        }
    }
    return -1;
}

QByteArray MainWindow::patch(int firstBit, QByteArray newBytes, QByteArray data)
{
    for(int i = 0 ; i < newBytes.size() ; i++)
    {
        if(newBytes[i] != '?')
            data[i+firstBit] = newBytes[i];
    }
    return data;
}
