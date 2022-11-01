#include "Render.h"

#include <iostream>
namespace s21 {
Render::Render(QWidget *parent) : QOpenGLWidget(parent) {}

Render::~Render() { delete ui; }

void Render::initializeGL() {
    if (vertices_vector_) {
        glEnable(GL_DEPTH_TEST);
    }
}

void Render::resizeGL(int w, int h) {
    if (vertices_vector_) {
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-2, 2, -2, 2, 1, 100);
    }
}

void Render::paintGL() {
    if (vertices_vector_) {
        glClearColor(red_color_, blue_color_, green_color_, 0);
        glColor3d(red_edge_, green_edge_, blue_edge_);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        if (is_parallel_ == false)
            glFrustum(-2, 2, -2, 2, 1, 100);
        else
            glOrtho(-2, 2, -2, 2, 1, 100);
        glScalef(0.8, 0.8, 0.8);
        glTranslatef(0, 0, -4);
        glLineWidth(edge_width_);

        if (are_dashed == true) {
            glLineStipple(2, 0x00F0);
            glEnable(GL_LINE_STIPPLE);
        } else {
            glDisable(GL_LINE_STIPPLE);
        }
        DrawModel();
    }
}

void Render::DrawModel() {
    glVertexPointer(3, GL_DOUBLE, 0, &((*vertices_vector_)[0]));
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawElements(GL_LINES, *indices_counter_, GL_UNSIGNED_INT, &((*indices_vec_)[0]));
    glDisableClientState(GL_VERTEX_ARRAY);
}

void Render::slot_red_bg(const double red_color) {
    red_color_ = red_color;
    update();
}

void Render::slot_green_bg(const double green_color) {
    green_color_ = green_color;
    update();
}

void Render::slot_blue_bg(const double blue_color) {
    blue_color_ = blue_color;
    update();
}

void Render::slot_parallel(bool is_parallel) {
    is_parallel_ = is_parallel;
    update();
}

void Render::slot_red_edge(double red_color) {
    red_edge_ = red_color;
    update();
}

void Render::slot_green_edge(double green_color) {
    green_edge_ = green_color;
    update();
}

void Render::slot_blue_edge(double blue_color) {
    blue_edge_ = blue_color;
    update();
}

void Render::slot_width_edge(double width) {
    edge_width_ = width;
    update();
}

void Render::slot_change_are_dashed(bool dashed_info) {
    are_dashed = dashed_info;
    update();
}

}  // namespace s21
