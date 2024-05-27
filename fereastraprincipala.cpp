#include "fereastraprincipala.h"
#include "ui_fereastraprincipala.h"
#include <QFile>
#include <QFileDialog>
#include <QString>
#include <QTextStream>
#include <QList>

FereastraPrincipala::FereastraPrincipala(QWidget *parent) : QMainWindow(parent) , ui(new Ui::FereastraPrincipala){ /*Definire constructor Fereastra principala*/
    ui->setupUi(this);
}

FereastraPrincipala::~FereastraPrincipala(){ /*Definire deconstructor Fereastra principala*/
    delete ui;
}

void FereastraPrincipala::Default(){ /*Definire functie de configurare default a ferestrei principale*/
    QSizePolicy sp_retain = ui->tableWidget->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    ui->tableWidget->setSizePolicy(sp_retain);
    ui->tableWidget->hide();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->lineEdit->hide();
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    connect(ui->actionCreate_New_File, SIGNAL(triggered()), this, SLOT(Create_New_File()));
    connect(ui->actionOpen_Existing_File, SIGNAL(triggered()), this, SLOT(Open_File()));
    connect(ui->pushButton_3, &QPushButton::clicked, this, &FereastraPrincipala::Add_Row);
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(Save()));
    connect(ui->pushButton_2, &QPushButton::clicked, this, &FereastraPrincipala::Delete_Row);
}

void FereastraPrincipala::Create_New_File(){ /*Deschide un tabel care va putea fi salvat ulterior ca file*/
    if(ui->tableWidget->isHidden()){
        ui->tableWidget->show();
        ui->lineEdit->show();
        ui->pushButton->show();
        ui->pushButton_2->show();
        ui->pushButton_3->show();
    }

}

void FereastraPrincipala::Open_File(){ /*Deschide un fisier csv deja existent pentru modificare*/
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::AnyFile);
    QString strFile = dialog.getOpenFileName(this, "Open existing file", "", "CSV files (*.csv);;All files (*.*)");
    QFile file(strFile);
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream stream(&file);

    if(ui->tableWidget->isHidden() && strFile != ""){
        ui->tableWidget->show();
        ui->lineEdit->show();
        ui->pushButton->show();
        ui->pushButton_2->show();
        ui->pushButton_3->show();
    }
    else{
        if(strFile != ""){
            if(!ui->tableWidget->isHidden()){
                for(int i = ui->tableWidget->rowCount()-1; i >= 0; --i){
                    ui->tableWidget->removeRow(i);
                }
            }
        }
    }

    QString linie;
    QList <QString> parti;
    int i=0, j=0;

    while(!stream.atEnd()){
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        linie = stream.readLine();
        parti = linie.split(",");
        parti.pop_back();
        j = 0;
        for(QString e : parti){
            QTableWidgetItem *p = new QTableWidgetItem(e);
            ui->tableWidget->setItem(i, j, p);
            j++;
        }
        i++;
    }

    file.close();
}

void FereastraPrincipala::Add_Row(){ /*Functie de adaugare a unei linii noi in tabel*/
    ui->tableWidget->insertRow(ui->tableWidget->currentRow() + 1);
}

void FereastraPrincipala::Delete_Row(){ /*Functie de stergere a unei linii selectate*/
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
}

void FereastraPrincipala::Save(){ /*Functia de salvare a tabelului intr-un fisier csv*/
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::AnyFile);
    QString strFile = dialog.getSaveFileName(this, "Create New File", "filename.csv", "CSV files (.csv);");
    QFile file(strFile);
    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    QString casuta;

    for(int i = 0; i < ui->tableWidget->rowCount(); ++i){
        for(int j = 0; j < ui->tableWidget->columnCount(); ++j){
            if(ui->tableWidget->item(i, j) != NULL){
                casuta = ui->tableWidget->item(i, j)->text();
            }
            else{
                casuta = "-";
            }
            stream << casuta << ",";
        }
        stream << "\n";
    }

    file.close();
}
