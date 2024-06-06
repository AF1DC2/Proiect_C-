#include "fereastraprincipala.h"
#include "ui_fereastraprincipala.h"
#include <QFile>
#include <QFileDialog>
#include <QString>
#include <QTextStream>
#include <QList>
#include <QMessageBox>
#include <QDate>
#include <QSignalBlocker>
#include <QFileInfo>

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
    ui->comboBox->hide();
    connect(ui->actionCreate_New_File, SIGNAL(triggered()), this, SLOT(Create_New_File()));     //
    connect(ui->actionOpen_Existing_File, SIGNAL(triggered()), this, SLOT(Open_File()));        //
    connect(ui->pushButton_3, &QPushButton::clicked, this, &FereastraPrincipala::Add_Row);      //
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(Save()));                           //
    connect(ui->pushButton_2, &QPushButton::clicked, this, &FereastraPrincipala::Delete_Row);   //   Conectearea semnalelor(actiunilor) cu slot-urile(efectele) acestora
    connect(ui->pushButton, &QPushButton::clicked, this, &FereastraPrincipala::Search);         //
    connect(ui->lineEdit, SIGNAL(textEdited(QString)), this, SLOT(Search_Reset()));             //
    connect(ui->comboBox, SIGNAL(activated(int)), this, SLOT(Search_Reset()));                  //
    connect(ui->tableWidget, SIGNAL(cellChanged(int,int)), this, SLOT(Check_Date()));           //
    connect(ui->tableWidget, SIGNAL(cellChanged(int,int)), this, SLOT(Check_Sum()));            //
}

bool C_D(const QString& d){ /*Functia care verifică formatul datei*/
    const QString forma_data("dd.MM.yyyy");
    QDate Data = QDate::fromString(d, forma_data);
    return Data.isValid() && d == Data.toString(forma_data);
}

int C_S(const QString& suma){ /*Funcția care verifică formatul strict numeric*/
    QString s = suma.trimmed();
    bool is_double;
    double d  = s.toDouble(&is_double);
    if (is_double){
        return d;
    }
    bool is_int;
    int i = s.toDouble(&is_int);
    if (is_int){
        return i;
    }
    return 0;
}


void FereastraPrincipala::Create_New_File(){ /*Deschide un tabel care va putea fi salvat ulterior ca file*/
    if(ui->tableWidget->isHidden()){
        ui->tableWidget->show();
        ui->lineEdit->show();
        ui->pushButton->show();
        ui->pushButton_2->show();
        ui->pushButton_3->show();
        ui->comboBox->show();
    }
    else{
        for(int i = ui->tableWidget->rowCount()-1; i >= 0; --i){
            ui->tableWidget->removeRow(i);
        }
    }
}

void FereastraPrincipala::Open_File(){ /*Deschide un fisier csv deja existent pentru modificare*/
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::AnyFile);
    QString strFile = dialog.getOpenFileName(this, "Open existing file", "", "CSVAlternate files (*.csva);;All files (*.*)");
    QFile file(strFile);
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream stream(&file);
    QFileInfo info(file);

    if(info.suffix() == "csva"){
        if(ui->tableWidget->isHidden() && strFile != ""){
            ui->tableWidget->show();
            ui->lineEdit->show();
            ui->pushButton->show();
            ui->pushButton_2->show();
            ui->pushButton_3->show();
            ui->comboBox->show();
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

        QSignalBlocker block(ui->tableWidget);                                      //
                                                                                    //
        QString linie;                                                              //
        QList <QString> parti;                                                      //
        int i=0, j=0;                                                               //
                                                                                    //
        while(!stream.atEnd()){                                                     //
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());                //
            linie = stream.readLine();                                              //
            parti = linie.split(",");                                               //    Construirea tabelului cu datele din fișier
            parti.pop_back();                                                       //
            j = 0;                                                                  //
            for(const auto &e : parti){                                             //
                QTableWidgetItem *p = new QTableWidgetItem(e);                      //
                ui->tableWidget->setItem(i, j, p);                                  //
                j++;                                                                //
            }                                                                       //
            i++;                                                                    //
        }                                                                           //
                                                                                    //
        block.unblock();                                                            //
    }
    else{
        if(strFile != ""){
            QMessageBox msg;
            msg.setText("Fișierul nu poate fi deschis.\nAsigurați-vă că fișierul selectat este de tip CSVA");
            msg.exec();
        }
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
    if(!ui->tableWidget->isHidden() && ui->tableWidget->rowCount() != 0){
        QFileDialog dialog;
        dialog.setDefaultSuffix("csva");
        dialog.setFileMode(QFileDialog::AnyFile);
        QString strFile = dialog.getSaveFileName(this, "Create New File", "filename.csva", "CSVAlternate files (*.csva);");
        QFile file(strFile);
        file.open(QIODevice::WriteOnly);
        QTextStream stream(&file);
        QString casuta;

        for(int i = 0; i < ui->tableWidget->rowCount(); ++i){
            for(int j = 0; j < ui->tableWidget->columnCount(); ++j){
                if(ui->tableWidget->item(i, j) != NULL && ui->tableWidget->item(i, j)->text() != ""){
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
    else{
        QMessageBox msg;
        msg.setText("Nu există tabel care să fie salvat");
        msg.exec();
    }
}

void FereastraPrincipala::Search(){ /*Functia de cautare si evidentierea rezultatelor cautate*/
    QSignalBlocker block(ui->tableWidget);
    if(ui->lineEdit->text() != nullptr){
        QList <QTableWidgetItem *> total =  ui->tableWidget->findItems(ui->lineEdit->text(), Qt::MatchContains);
        if(!total.isEmpty()){
            for(QTableWidgetItem *e : total){
                if(ui->comboBox->currentText() == "Sursă"){
                    if(ui->tableWidget->column(e) == 1){
                        ui->tableWidget->item(ui->tableWidget->row(e), 1)->setBackground(Qt::darkGreen);
                    }
                }
                else{
                    if(ui->tableWidget->column(e) == 2){
                        ui->tableWidget->item(ui->tableWidget->row(e), 2)->setBackground(Qt::darkGreen);
                    }
                }
            }
        }
    }
    block.unblock();
}

void FereastraPrincipala::Search_Reset(){ /*Resetarea casutelor evidentiate anterior*/
    QSignalBlocker block(ui->tableWidget);
    for(int i  = 0; i < ui->tableWidget->rowCount(); ++i){
        for(int j = 0; j < 4; ++j){
            if(ui->tableWidget->item(i, j) != nullptr && ui->tableWidget->item(i, j)->background() == Qt::darkGreen){
                ui->tableWidget->item(i, j)->setBackground(ui->tableWidget->item(i, j)->foreground());
            }
        }
    }
    block.unblock();
}

void FereastraPrincipala::Check_Date(){ /*Efectul apelat pentru verificarea formatului datei*/
    if(ui->tableWidget->currentItem()->column() == 3 && ui->tableWidget->currentItem()->text() != "" && ui->tableWidget->currentItem()->text() != "-" && ui->tableWidget->currentItem() != nullptr){
        if(!C_D(ui->tableWidget->currentItem()->text())){
            ui->tableWidget->currentItem()->setText("");
            QMessageBox msg;
            msg.setText("Data introdusă nu este corectă sau nu respectă formatul\n<zi.lună.an>");
            msg.exec();
        }
    }
}

void FereastraPrincipala::Check_Sum(){ /*Efectul apelat pentru verificarea formatului strict numeric*/
    if(ui->tableWidget->currentItem()->column() == 0 && ui->tableWidget->currentItem()->text() != "" && ui->tableWidget->currentItem()->text() != "-" && ui->tableWidget->currentItem() != nullptr){
        if(!C_S(ui->tableWidget->currentItem()->text())){
            ui->tableWidget->currentItem()->setText("");
            QMessageBox msg;
            msg.setText("Suma introdusă nu este sub formă numerică");
            msg.exec();
        }
        else{
            ui->tableWidget->currentItem()->setText(ui->tableWidget->currentItem()->text().trimmed());
        }
    }
}
