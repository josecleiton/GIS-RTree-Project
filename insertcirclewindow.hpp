#ifndef INSERTCIRCLEWINDOW_HPP
#define INSERTCIRCLEWINDOW_HPP

#include <QDialog>
#include "regex.hpp"
#include "spatialdata.hpp"

namespace Ui {
class InsertCircleWindow;
}

class InsertCircleWindow : public QDialog
{
    Q_OBJECT

public:
    explicit InsertCircleWindow(QWidget *parent = nullptr);
    ~InsertCircleWindow();
    SpatialData::Circulo GetInfo();

private:
    Ui::InsertCircleWindow *ui;
};

#endif // INSERTCIRCLEWINDOW_HPP
