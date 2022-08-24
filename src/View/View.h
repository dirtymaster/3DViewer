#ifndef SRC_VIEW_VIEW_H_
#define SRC_VIEW_VIEW_H_

#include "../Model/Model.h"
#include <QMainWindow>
#include <QMessageBox>

namespace s21 {
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class View : public QMainWindow {
    Q_OBJECT

 public:
    static View* getInstance();
    void SendDataToRender();
    ~View();

 private:
    Controller *Controller_;
    static View* instance_;
    Ui::MainWindow *ui;

    View();
    View(const View &other);
    View(View &&other);
    void operator=(const View &other);

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

    void on_red_bg_clicked();
    void on_green_bg_clicked();
    void on_blue_bg_clicked();
    void on_parallel_proj_btn_clicked();
    void on_central_proj_btn_clicked();
    void on_red_edge_btn_clicked();
    void on_green_edge_btn_clicked();
    void on_blue_edge_btn_clicked();
    void on_width_edge_btn_clicked();
    void on_dashed_btn_clicked();
    void on_straight_btn_clicked();
};
}  // namespace s21
#endif  // SRC_VIEW_VIEW_H_
