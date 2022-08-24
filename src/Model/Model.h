#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_

#include <sys/stat.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../Controller/Controller.h"

namespace s21 {
class Model {
    // Controller interface
    friend std::vector<double>* Controller::GetVertices();
    friend std::vector<int>* Controller::GetIndices();
    friend unsigned* Controller::GetIndicesCounter();
    friend unsigned* Controller::GetVerticesCounter();

    friend bool Controller::OpenFileRequest(const char *file_path);
    friend void Controller::MoveRequest(const double x, const double y, const double z);
    friend void Controller::RotationRequest(const double angle, axis which_axis);
    friend void Controller::ScaleRequest(const double scale);

 public:
    ~Model();
    static Model* getInstance();

 private:
    Model();
    Model(const Model &other);
    Model(Model &&other);
    void operator=(const Model &other);
    static Model *instance_;

    std::vector<double> vertices_;
    unsigned vertices_counter_;
    double max_absolute_value;
    std::vector<int> indices_;
    unsigned indices_counter_;
    std::ifstream obj_file_;

    void ClearData();
    bool OpenFile(const char* file_path);
    void CloseFile();
    void GetDataFromFile();
    void PushVertex(const double x, const double y, const double z);
    void PushIndices(std::string& line);

    void MoveObject(const double x, const double y, const double z);
    void RotationOX(const double angle);
    void RotationOY(const double angle);
    void RotationOZ(const double angle);
    void ChangeScale(const double scale);
};

}  // namespace s21

#endif  // SRC_MODEL_MODEL_H_
