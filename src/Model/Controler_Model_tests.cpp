#include <gtest/gtest.h>

#include "Model.h"

using s21::Controller;
using s21::Model;

TEST(Controller_Model_Interacions, file_path_check) {
    Controller* controller = Controller::getInstance();
    EXPECT_TRUE(controller->OpenFileRequest("Object_files/cub.obj"));
    EXPECT_EQ(*(controller->GetIndicesCounter()), 72);
    EXPECT_EQ(*(controller->GetVerticesCounter()), 8);
    EXPECT_FALSE(controller->OpenFileRequest("NoSuchFile.txt"));
    EXPECT_FALSE(controller->OpenFileRequest("View"));
}

TEST(Controller_Model_Interacions, move_test) {
    Controller* controller = Controller::getInstance();
    EXPECT_TRUE(controller->OpenFileRequest("Object_files/car.obj"));
    std::vector<double>* vec = controller->GetVertices();
    double x_before_move = (*vec)[3];
    double y_before_move = (*vec)[4];
    double z_before_move = (*vec)[5];
    controller->MoveRequest(0.123, -0.123, 0.123);
    EXPECT_FLOAT_EQ(x_before_move + 0.123, (*vec)[3]);
    EXPECT_FLOAT_EQ(y_before_move - 0.123, (*vec)[4]);
    EXPECT_FLOAT_EQ(z_before_move + 0.123, (*vec)[5]);
}

TEST(Controller_Model_Interacions, rotate_test) {
    Controller* controller = Controller::getInstance();
    EXPECT_TRUE(controller->OpenFileRequest("Object_files/car.obj"));
    std::vector<double>* vec = controller->GetVertices();
    double x_before_rotate = (*vec)[3];
    double y_before_rotate = (*vec)[4];
    double z_before_rotate = (*vec)[5];
    controller->RotationRequest(6.2831853, Controller::x_axis);
    controller->RotationRequest(6.2831853, Controller::y_axis);
    controller->RotationRequest(6.2831853, Controller::z_axis);
    EXPECT_FLOAT_EQ(x_before_rotate, (*vec)[3]);
    EXPECT_FLOAT_EQ(y_before_rotate, (*vec)[4]);
    EXPECT_FLOAT_EQ(z_before_rotate, (*vec)[5]);
}

TEST(Controller_Model_Interacions, scale_test) {
    Controller* controller = Controller::getInstance();
    EXPECT_TRUE(controller->OpenFileRequest("Object_files/car.obj"));
    std::vector<double>* vec = controller->GetVertices();
    double x_before_scale = (*vec)[3];
    double y_before_scale = (*vec)[4];
    double z_before_scale = (*vec)[5];
    controller->ScaleRequest(0.42);
    controller->ScaleRequest(1.21);
    EXPECT_FLOAT_EQ(0.42 * 1.21 * x_before_scale, (*vec)[3]);
    EXPECT_FLOAT_EQ(0.42 * 1.21 * y_before_scale, (*vec)[4]);
    EXPECT_FLOAT_EQ(0.42 * 1.21 * z_before_scale, (*vec)[5]);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
