#include "insertcirclewindow.hpp"
#include "ui_insertcirclewindow.h"

InsertCircleWindow::InsertCircleWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertCircleWindow)
{
    ui->setupUi(this);
    QRegExp regx(REAL_NUMBER_REGEX);
    QRegExpValidator *validator = new QRegExpValidator(regx, this);
    ui->raio->setValidator(validator);
    ui->xc->setValidator(validator);
    ui->yc->setValidator(validator);
    this->setWindowTitle("Insira uma circunferência");
    this->setWindowIcon(QIcon(ICON));
}

InsertCircleWindow::~InsertCircleWindow()
{
    delete ui->raio->validator();
    delete ui;
}

SpatialData::Circulo InsertCircleWindow::GetInfo(){
    return this->A;
}

void InsertCircleWindow::on_button_clicked()
{
    A.SetCentro(SpatialData::Ponto(ui->xc->text().toDouble(), ui->yc->text().toDouble()));
    A.SetRaio(ui->raio->text().toDouble());
}

void InsertCircleWindow::on_buttonBox_clicked()
{
    close();
}
