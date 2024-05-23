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
    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::FereastraPrincipala *ui;
};
#endif // FEREASTRAPRINCIPALA_H
