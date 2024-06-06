#ifndef FEREASTRAPRINCIPALA_H
#define FEREASTRAPRINCIPALA_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class FereastraPrincipala;
}
QT_END_NAMESPACE

class FereastraPrincipala : public QMainWindow
{
    Q_OBJECT

public:
    FereastraPrincipala(QWidget *parent = nullptr);
    ~FereastraPrincipala();
    void Default();

private slots:
    void Create_New_File();

    void Open_File();

    void Add_Row();

    void Save();

    void Delete_Row();

    void Search();

    void Search_Reset();

    void Check_Sum();

    void Check_Date();

private:
    Ui::FereastraPrincipala *ui;
};
#endif // FEREASTRAPRINCIPALA_H
