#include <gtest/gtest.h>

#include <vector>

#include "model.h"

TEST(affine, scale) {
    s21::Model test_model;
    std::vector<double> result_model{2, -2, -2, 2, -2, 2, -2, -2, 2, -2, -2, -2,
                                     2, 2,  -2, 2, 2,  2, -2, 2,  2, -2, 2,  -2};
    const char* filename = "object/cube.obj";
    test_model.load_obj_model(filename);
    test_model.scale(2);

    for (size_t i = 0; i < test_model.getVertices().size(); i++) {
        ASSERT_EQ(result_model[i], test_model.getVertices()[i]);
    }
}

TEST(affine, move_x) {
    s21::Model test_model;
    std::vector<double> result_model{3, -1, -1, 3, -1, 1, 1, -1, 1, 1, -1, -1,
                                     3, 1,  -1, 3, 1,  1, 1, 1,  1, 1, 1,  -1};
    const char* filename = "object/cube.obj";
    test_model.load_obj_model(filename);
    test_model.move_x(2);

    for (size_t i = 0; i < test_model.getVertices().size(); i++) {
        ASSERT_EQ(result_model[i], test_model.getVertices()[i]);
    }
}

TEST(affine, move_y) {
    s21::Model test_model;
    std::vector<double> result_model{1, 1, -1, 1, 1, 1, -1, 1, 1, -1, 1, -1,
                                     1, 3, -1, 1, 3, 1, -1, 3, 1, -1, 3, -1};
    const char* filename = "object/cube.obj";
    test_model.load_obj_model(filename);
    test_model.move_y(2);

    for (size_t i = 0; i < test_model.getVertices().size(); i++) {
        ASSERT_EQ(result_model[i], test_model.getVertices()[i]);
    }
}

TEST(affine, move_z) {
    s21::Model test_model;
    std::vector<double> result_model{1, -1, 1, 1, -1, 3, -1, -1, 3, -1, -1, 1,
                                     1, 1,  1, 1, 1,  3, -1, 1,  3, -1, 1,  1};
    const char* filename = "object/cube.obj";
    test_model.load_obj_model(filename);
    test_model.move_z(2);

    for (size_t i = 0; i < test_model.getVertices().size(); i++) {
        ASSERT_EQ(result_model[i], test_model.getVertices()[i]);
    }
}

TEST(affine, rotation_x) {
    s21::Model test_model;
    std::vector<double> result_model{1,  1.3254442,   -0.49315059, 1,  -0.49315059, -1.3254442,
                                     -1, -0.49315059, -1.3254442,  -1, 1.3254442,   -0.49315059,
                                     1,  0.49315059,  1.3254442,   1,  -1.3254442,  0.49315059,
                                     -1, -1.3254442,  0.49315059,  -1, 0.49315059,  1.3254442};
    const char* filename = "object/cube.obj";
    test_model.load_obj_model(filename);
    test_model.rotation_x(2);

    for (size_t i = 0; i < test_model.getVertices().size(); i++) {
        ASSERT_FLOAT_EQ(result_model[i], test_model.getVertices()[i]);
    }
}

TEST(affine, rotation_y) {
    s21::Model test_model;
    std::vector<double> result_model{-1.3254442, -1, -0.49315059, 0.49315059,  -1, -1.3254442,
                                     1.3254442,  -1, 0.49315059,  -0.49315059, -1, 1.3254442,
                                     -1.3254442, 1,  -0.49315059, 0.49315059,  1,  -1.3254442,
                                     1.3254442,  1,  0.49315059,  -0.49315059, 1,  1.3254442};
    const char* filename = "object/cube.obj";
    test_model.load_obj_model(filename);
    test_model.rotation_y(2);

    for (size_t i = 0; i < test_model.getVertices().size(); i++) {
        ASSERT_FLOAT_EQ(result_model[i], test_model.getVertices()[i]);
    }
}

TEST(affine, rotation_z) {
    s21::Model test_model;
    std::vector<double> result_model{0.49315059,  1.3254442,   -1, 0.49315059,  1.3254442,   1,
                                     1.3254442,   -0.49315059, 1,  1.3254442,   -0.49315059, -1,
                                     -1.3254442,  0.49315059,  -1, -1.3254442,  0.49315059,  1,
                                     -0.49315059, -1.3254442,  1,  -0.49315059, -1.3254442,  -1};
    const char* filename = "object/cube.obj";
    test_model.load_obj_model(filename);
    test_model.rotation_z(2);

    for (size_t i = 0; i < test_model.getVertices().size(); i++) {
        ASSERT_FLOAT_EQ(result_model[i], test_model.getVertices()[i]);
    }
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
