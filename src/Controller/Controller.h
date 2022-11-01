#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

namespace s21 {
class Model;

class Controller {
public:
    static Controller *getInstance();
    ~Controller();

    bool OpenFileRequest(const char *file_path);
    std::vector<double> *GetVertices();
    std::vector<int> *GetIndices();
    unsigned *GetVerticesCounter();
    unsigned *GetIndicesCounter();

    enum axis { x_axis = 1, y_axis, z_axis };
    void RotationRequest(const double angle, axis which_axis);
    void MoveRequest(const double x, const double y, const double z);
    void ScaleRequest(const double scale);

private:
    Model *Model_;
    static Controller *instance_;

    Controller();
    Controller(const Controller &other);
    Controller(Controller &&other);
    void operator=(const Controller &other);
};
}  // namespace s21

#endif  // SRC_CONTROLLER_CONTROLLER_H_
