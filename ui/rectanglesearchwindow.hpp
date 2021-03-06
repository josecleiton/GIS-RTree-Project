#ifndef RECTANGLESEARCHWINDOW_HPP
#define RECTANGLESEARCHWINDOW_HPP

#include <QDialog>
#include "icon.hpp"
#include <QMessageBox>
#include <vector>
#include "variaveis.hpp"
#include "rtree.hpp"
#include "spatialdata.hpp"
#include "regex.hpp"
#include "disk.hpp"
#include "findwindow.hpp"

namespace Ui {
class RectangleSearchWindow;
}

class RectangleSearchWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RectangleSearchWindow(QWidget *parent = nullptr);
    ~RectangleSearchWindow();
    DiskAPI::Registro** GetRegistro();
    void SetInterseccao(bool);
    void SetMBR(SpatialData::Retangulo);
    SpatialData::Retangulo GetMBR();
    bool Interseccao();
    void ClearForm();
    void ClearReg();
    bool GetNuke();

private slots:
    void on_button_clicked();

    void on_cancel_clicked();
private:
    Ui::RectangleSearchWindow *ui{};
    DiskAPI::Registro** listaRegistros{};
    SpatialData::Retangulo MBR{};
    bool interseccao{};
    bool nuke{};
};

#endif // RECTANGLESEARCHWINDOW_HPP
