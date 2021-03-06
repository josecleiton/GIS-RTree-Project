#ifndef FINDWINDOW_HPP
#define FINDWINDOW_HPP

#include <QDialog>
#include "icon.hpp"
#include <QMessageBox>
#include <iostream>
#include <sstream>
#include "disk.hpp"
#include "renderarea.hpp"

namespace Ui {
class FindWindow;
}

class FindWindow : public QDialog
{
    Q_OBJECT

public:
    explicit FindWindow(QWidget *parent = nullptr);
    ~FindWindow();
    bool setRegistros(DiskAPI::Registro** &, size_t, bool inter);
    bool getRemove();
    bool listaValida();
    void setInterCircle(bool op);
    void setByPoint(bool op);
    void setLibera(bool op);

private slots:
    void on_remove_clicked();

    void on_info_clicked();

private:
    Ui::FindWindow *ui;
    bool remove;
    unsigned count{};
    vector<Registro*> regs{};
    bool libera;
};

#endif // FINDWINDOW_HPP
