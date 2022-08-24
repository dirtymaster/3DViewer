#include "View.h"
#include "ui_View.h"

#include <QFileDialog>

namespace s21 {

View* View::instance_ = nullptr;

View::View() : QMainWindow(nullptr) , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    Controller_ = Controller::getInstance();
    ui->x_move_sbox->setValue(0.5);
    ui->y_move_sbox->setValue(0.5);
    ui->z_move_sbox->setValue(0.5);
    ui->x_rot_sbox->setValue(0.5);
    ui->y_rot_sbox->setValue(0.5);
    ui->z_rot_sbox->setValue(0.5);
}

View* View::getInstance() {
    if (!instance_) {
        instance_ = new View();
    }
    return instance_;
}

View::~View() {
    delete ui;
    delete instance_;
}

void View::SendDataToRender() {
    ui->openGLWidget->vertices_vector_ = Controller_->GetVertices();
    ui->openGLWidget->vertices_counter_ = Controller_->GetVerticesCounter();
    ui->openGLWidget->indices_vec_ = Controller_->GetIndices();
    ui->openGLWidget->indices_counter_ = Controller_->GetIndicesCounter();
    ui->vertex_count_label->setText(QString::number(*(ui->openGLWidget->vertices_counter_)));
    ui->index_count_label->setText(QString::number(*(ui->openGLWidget->indices_counter_)));
}

void View::on_file_browse_btn_clicked() {
    QStringList QSL = QFileDialog::getOpenFileNames(this, tr("Open File"), "/path/to/file/",
    tr("Object Files (*.obj)"));
    QString Path = QSL.join(Path);
    QByteArray ba = Path.toLocal8Bit();
    const char *file_path = ba.data();
    if (Controller_->OpenFileRequest(file_path)) {
        SendDataToRender();
        ui->file_name->setText(Path);
    } else {
        QMessageBox::warning(this, "Error", "Can't open the file");
    }
}


void View::on_x_move_btn_clicked() {
    Controller_->MoveRequest(ui->x_move_sbox->value(), 0, 0);
    ui->openGLWidget->update();
}


void View::on_y_move_btn_clicked() {
    Controller_->MoveRequest(0, ui->y_move_sbox->value(), 0);
    ui->openGLWidget->update();
}


void View::on_z_move_btn_clicked() {
     Controller_->MoveRequest(0, 0, ui->z_move_sbox->value());
     ui->openGLWidget->update();
}


void View::on_x_rot_btn_clicked() {
    Controller_->RotationRequest(ui->x_rot_sbox->value(), Controller::x_axis);
    ui->openGLWidget->update();
}


void View::on_y_rot_btn_clicked() {
    Controller_->RotationRequest(ui->y_rot_sbox->value(), Controller::y_axis);
    ui->openGLWidget->update();
}


void View::on_z_rot_btn_clicked() {
    Controller_->RotationRequest(ui->z_rot_sbox->value(), Controller::z_axis);
    ui->openGLWidget->update();
}


void View::on_zoom_in_btn_clicked() {
    Controller_->ScaleRequest(1.2);
    ui->openGLWidget->update();
}


void View::on_zoom_out_btn_clicked() {
    Controller_->ScaleRequest(0.8);
    ui->openGLWidget->update();
}


void View::on_red_bg_clicked() {
    ui->openGLWidget->slot_red_bg(ui->red_clr_sbox->value());
}


void View::on_green_bg_clicked() {
    ui->openGLWidget->slot_blue_bg(ui->green_clr_sbox->value());
}


void View::on_blue_bg_clicked() {
    ui->openGLWidget->slot_green_bg(ui->blue_clr_sbox->value());
}


void View::on_parallel_proj_btn_clicked() {
    ui->openGLWidget->slot_parallel(true);
}


void View::on_central_proj_btn_clicked() {
    ui->openGLWidget->slot_parallel(false);
}


void View::on_red_edge_btn_clicked() {
    ui->openGLWidget->slot_red_edge(ui->red_edge_sbox->value());
}


void View::on_green_edge_btn_clicked() {
    ui->openGLWidget->slot_green_edge(ui->green_edge_sbox->value());
}


void View::on_blue_edge_btn_clicked() {
    ui->openGLWidget->slot_blue_edge(ui->blue_edge_sbox->value());
}


void View::on_width_edge_btn_clicked() {
    ui->openGLWidget->slot_width_edge(ui->width_edge_sbox->value());
}


void View::on_dashed_btn_clicked() {
    ui->openGLWidget->slot_change_are_dashed(true);
}


void View::on_straight_btn_clicked() {
    ui->openGLWidget->slot_change_are_dashed(false);
}


}  // namespace s21
