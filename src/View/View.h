#ifndef SRC_VIEW_VIEW_H_
#define SRC_VIEW_VIEW_H_

#include <QMainWindow>
#include <QMessageBox>

#include "../Model/Model.h"

namespace s21 {
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class View : public QMainWindow {
    Q_OBJECT

public:
    static View *getInstance();
    void SendDataToRender();
    ~View();

private:
    Controller *Controller_;
    static View *instance_;
    Ui::MainWindow *ui;

    View();
    View(const View &other);
    View(View &&other);
    void operator=(const View &other);
    QString obj_files_path_;

private slots:
    void on_file_browse_btn_clicked();

    void on_x_move_btn_clicked();
    void on_y_move_btn_clicked();
    void on_z_move_btn_clicked();
    void on_x_rot_btn_clicked();
    void on_y_rot_btn_clicked();
    void on_z_rot_btn_clicked();
    void on_zoom_in_btn_clicked();
    void on_zoom_out_btn_clicked();

    void on_width_edge_sbox_valueChanged();
    void on_red_clr_sbox_valueChanged();
    void on_green_clr_sbox_valueChanged(double arg1);
    void on_blue_clr_sbox_valueChanged(double arg1);
    void on_checkBox_stateChanged(int arg1);
    void on_parallel_projection_clicked();
    void on_central_projectioin_clicked();
    void on_red_edge_sbox_valueChanged();
    void on_green_edge_sbox_valueChanged();

    void on_blue_edge_sbox_valueChanged(double arg1);
};
}  // namespace s21
#endif  // SRC_VIEW_VIEW_H_
