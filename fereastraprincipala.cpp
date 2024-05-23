#include "fereastraprincipala.h"
#include "ui_fereastraprincipala.h"
#include <QLabel>

FereastraPrincipala::FereastraPrincipala(QWidget *parent) : QMainWindow(parent) , ui(new Ui::FereastraPrincipala){ /*Definire constructor Fereastra principala*/
    ui->setupUi(this);
}

FereastraPrincipala::~FereastraPrincipala(){ /*Definire deconstructor Fereastra principala*/
    delete ui;
}

void FereastraPrincipala::on_pushButton_4_clicked(){ /*Definire actiune de click pe butonul 4*/
    QMainWindow *mesaj;
    QString text = "Apăsând butonul, se va deschide un meniu de adăugare de venituri noi.";
    QLabel *label;
    label = new QLabel(this);
    label->setAlignment(Qt::AlignCenter);
    label->setText(text);
    mesaj = new QMainWindow(this);
    mesaj->resize(500, 300);
    mesaj->show();
    mesaj->setWindowTitle("Adaugă Venituri");
    mesaj->setCentralWidget(label);
}


void FereastraPrincipala::on_pushButton_3_clicked(){ /*Definire actiune de click pe butonul 3*/
    QMainWindow *mesaj;
    QString text = "Apăsând butonul, se va deschide un meniu de adăugare de cheltuieli noi.";
    QLabel *label;
    label = new QLabel(this);
    label->setAlignment(Qt::AlignCenter);
    label->setText(text);
    mesaj = new QMainWindow(this);
    mesaj->resize(500, 300);
    mesaj->show();
    mesaj->setWindowTitle("Adaugă Venituri");
    mesaj->setCentralWidget(label);
}


void FereastraPrincipala::on_pushButton_clicked(){ /*Definire actiune de click pe butonul 2*/
    if(ui->tableWidget->isHidden()){
        ui->tableWidget->show();
    }
    else{
        if(!ui->tableWidget->isHidden()){
            ui->tableWidget->hide();
        }
    }
}


void FereastraPrincipala::on_pushButton_2_clicked(){ /*Definire actiune de click pe butonul 1*/
    QMainWindow *mesaj;
    QString text = "Apăsând butonul, deasupra tabelului va aparea un searchbar pentru cautarea directa in tabel.";
    QLabel *label;
    label = new QLabel(this);
    label->setAlignment(Qt::AlignCenter);
    label->setText(text);
    mesaj = new QMainWindow(this);
    mesaj->resize(500, 300);
    mesaj->show();
    mesaj->setWindowTitle("Adaugă Venituri");
    mesaj->setCentralWidget(label);
}

void FereastraPrincipala::Default(){ /*Definire functie de configurare default a ferestrei principale*/
    QSizePolicy sp_retain = ui->tableWidget->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    ui->tableWidget->setSizePolicy(sp_retain);
    ui->tableWidget->hide();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
