#ifndef SRC_VIEW_RENDER_H_
#define SRC_VIEW_RENDER_H_

#include <QtOpenGLWidgets/qopenglwidget.h>

#include <QWidget>

#include "View.h"

namespace s21 {
QT_BEGIN_NAMESPACE
namespace Ui {
class Render;
}
QT_END_NAMESPACE

class Render : public QOpenGLWidget {
    friend void View::SendDataToRender();
    Q_OBJECT

public:
    explicit Render(QWidget *parent = nullptr);
    ~Render();

public slots:
    void slot_width_edge(const double width);
    void slot_red_bg(const double red_color);
    void slot_green_bg(const double green_color);
    void slot_blue_bg(const double blue_color);
    void slot_red_edge(const double red_color);
    void slot_green_edge(const double green_color);
    void slot_blue_edge(const double blue_color);
    void slot_parallel(bool is_parallel);
    void slot_change_are_dashed(bool dashed_info);

private:
    std::vector<double> *vertices_vector_ = nullptr;
    std::vector<int> *indices_vec_ = nullptr;
    unsigned *vertices_counter_;
    unsigned *indices_counter_;
    double red_color_ = 0, green_color_ = 0, blue_color_ = 0;
    double red_edge_ = 1, green_edge_ = 1, blue_edge_ = 1;
    double edge_width_ = 1;
    bool is_parallel_ = true, are_dashed = false;
    Ui::Render *ui;

    void DrawModel();
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};
}  // namespace s21

#endif  // SRC_VIEW_RENDER_H_
