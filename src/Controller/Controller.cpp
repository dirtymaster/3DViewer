#include "../Model/Model.h"

namespace s21 {

Controller* Controller::instance_ = nullptr;

Controller::Controller() {
    Model_ = Model::getInstance();
}

Controller::~Controller() {
    delete instance_;
}

Controller* Controller::getInstance() {
    if (!instance_) {
        instance_ = new Controller();
    }
    return instance_;
}

bool Controller::OpenFileRequest(const char *file_path) {
    return Model_->OpenFile(file_path);
}

std::vector<double>* Controller::GetVertices() {
    return &Model_->vertices_;
}

std::vector<int>* Controller::GetIndices() {
    return &Model_->indices_;
}

unsigned* Controller::GetVerticesCounter() {
    return &Model_->vertices_counter_;
}

unsigned* Controller::GetIndicesCounter() {
    return &Model_->indices_counter_;
}

void Controller::MoveRequest(const double x, const double y, const double z) {
    Model_->MoveObject(x, y, z);
}

void Controller::RotationRequest(const double angle, axis which_axis) {
    if (which_axis == x_axis)
        Model_->RotationOX(angle);
    else if (which_axis == y_axis)
        Model_->RotationOY(angle);
    else if (which_axis == z_axis)
        Model_->RotationOZ(angle);
}

void Controller::ScaleRequest(const double scale) {
    Model_->ChangeScale(scale);
}

}  // namespace s21
