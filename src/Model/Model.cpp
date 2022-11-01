#include "Model.h"

namespace s21 {

Model* Model::instance_ = nullptr;

void Model::ClearData() {
    vertices_counter_ = 0;
    indices_counter_ = 0;
    max_absolute_value = 0;
    vertices_.clear();
    indices_.clear();
}

void Model::CloseFile() {
    if (obj_file_.is_open()) obj_file_.close();
}

Model::Model() { ClearData(); }

Model::~Model() {
    CloseFile();
    delete instance_;
}

Model* Model::getInstance() {
    if (!instance_) {
        instance_ = new Model();
    }
    return instance_;
}

bool Model::OpenFile(const char* file_path) {
    ClearData();
    CloseFile();
    struct stat s;
    if (!stat(file_path, &s)) {
        if (s.st_mode & S_IFREG) {  // This allow us to check only files, if its
                                    // directory return false;
            obj_file_.open(file_path);
            if (obj_file_.is_open()) {
                GetDataFromFile();
                return true;
            }
        }
    }
    return false;
}

void Model::GetDataFromFile() {
    while (obj_file_) {
        std::string line;
        std::getline(obj_file_, line, '\n');
        if (line.size() < 7) continue;
        double x = 0, y = 0, z = 0;
        char ch1 = 0, ch2 = 0, ch3 = 0, ch4 = 0;
        if (sscanf(line.c_str(), "%c%c%lf%c%lf%c%lf", &ch1, &ch2, &x, &ch3, &y, &ch4, &z) == 7 &&
            ch1 == 'v' && ch2 == ' ' && ch3 == ' ' && ch4 == ' ') {
            PushVertex(x, y, z);
        } else if (ch1 == 'f' && ch2 == ' ') {
            PushIndices(line);
        }
    }
    if (max_absolute_value > 1) {
        double scale = 0.8, n = 0;
        while (max_absolute_value > 1) {  // If coordinates values are big, reduce them until 0 < max_val <= 1
            max_absolute_value *= scale;
            n++;
        }
        ChangeScale(pow(scale, n));
    }
}

void Model::PushVertex(const double x, const double y, const double z) {
    vertices_.push_back(x);
    vertices_.push_back(y);
    vertices_.push_back(z);
    vertices_counter_++;
    if (fabs(x) > fabs(max_absolute_value)) max_absolute_value = fabs(x);
    if (fabs(y) > fabs(max_absolute_value)) max_absolute_value = fabs(y);
    if (fabs(x) > fabs(max_absolute_value)) max_absolute_value = fabs(y);
}

void Model::PushIndices(std::string& line) {
    int space_flag = 0;
    int str_len = line.length();
    int offset_counter = 0;
    for (int i = 0; i < str_len; i++) {
        space_flag--;
        if (line[i] == ' ' && i != str_len - 1) space_flag = 2;
        if (line[i] - '0' >= 0 && line[i] - '0' <= 9 && space_flag == 1) {
            int value;
            if (indices_counter_ % 2 == 0) {
                sscanf(line.c_str() + i, "%u", &value);
                value--;
                indices_.push_back(value);
                indices_counter_++;
                offset_counter++;
            } else {
                sscanf(line.c_str() + i, "%u", &value);
                value--;
                indices_.push_back(value);
                indices_.push_back(value);
                indices_counter_ += 2;
                offset_counter += 2;
            }
            space_flag = 0;
        }
    }
    indices_.push_back(indices_[indices_counter_ - offset_counter]);
    indices_counter_++;
}

void Model::RotationOX(const double angle) {
    for (unsigned i = 0; i < vertices_counter_ * 3; i++) {
        if (i % 3 == 0) {
            double tmp_y = vertices_[i + 1];
            double tmp_z = vertices_[i + 2];
            vertices_[i + 1] = cos(angle) * tmp_y + sin(angle) * tmp_z;
            vertices_[i + 2] = -sin(angle) * tmp_y + cos(angle) * tmp_z;
        }
    }
}

void Model::RotationOY(const double angle) {
    for (unsigned i = 0; i < vertices_counter_ * 3; i++) {
        if (i % 3 == 0) {
            double tmp_x = vertices_[i];
            double tmp_z = vertices_[i + 2];
            vertices_[i] = cos(angle) * tmp_x + sin(angle) * tmp_z;
            vertices_[i + 2] = -sin(angle) * tmp_x + cos(angle) * tmp_z;
        }
    }
}

void Model::RotationOZ(const double angle) {
    for (unsigned i = 0; i < vertices_counter_ * 3; i++) {
        if (i % 3 == 0) {
            double tmp_x = vertices_[i];
            double tmp_y = vertices_[i + 1];
            vertices_[i] = cos(angle) * tmp_x - sin(angle) * tmp_y;
            vertices_[i + 1] = sin(angle) * tmp_x + cos(angle) * tmp_y;
        }
    }
}

void Model::MoveObject(const double x, const double y, const double z) {
    for (unsigned i = 0; i < vertices_counter_ * 3; i++) {
        if (i % 3 == 0) {
            vertices_[i] += x;
        } else if (i % 3 == 1) {
            vertices_[i] += y;
        } else {
            vertices_[i] += z;
        }
    }
}

void Model::ChangeScale(const double scale) {
    for (unsigned i = 0; i < vertices_counter_ * 3; i++) vertices_[i] *= scale;
}

}  // namespace s21
