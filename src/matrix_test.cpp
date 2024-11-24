#include <Matrix.h>
#include <vector>
#include <gtest/gtest.h>
#include <iostream>


TEST(cast, TestingExplicitCast) {
    Matrix m{{1.0, 2.0, 3.0, 4.0}};

    EXPECT_DOUBLE_EQ((double)m, 10.0);
}

TEST(equals, TestingMatrixEq) {
    Matrix m1{{1.0, 2.0, 3.0, 4.0}};
    Matrix m2{{5.0, 6.0, 7.0, 8.0}};

    EXPECT_TRUE(m1 == m1);
    EXPECT_FALSE(m1 == m2);
}

TEST(not_equals, TestingMatrixNeq) {
    Matrix m1{{1.0, 2.0, 3.0, 4.0}};
    Matrix m2{{5.0, 6.0, 7.0, 8.0}};

    EXPECT_FALSE(m1 != m1);
    EXPECT_TRUE(m1 != m2);
}

TEST(indexing, TestingSingleIndexing) {
    Matrix m{{1.0, 2.0, 3.0, 4.0}};
    vector<double> v{1.0, 0.0, 0.0, 0.0};

    EXPECT_TRUE(m[0] == v);
    EXPECT_FALSE(m[1] == v);
}

TEST(indexing, TestingDoubleIndexing) {
    Matrix m{{1.0, 2.0, 3.0, 4.0}};

    EXPECT_DOUBLE_EQ(m[0][0], 1.0);
    EXPECT_DOUBLE_EQ(m[1][0], 0.0);

    m[0][0] = -51.0;
    m[0][3] = 12.0;

    EXPECT_DOUBLE_EQ(m[0][0], -51.0);
    EXPECT_DOUBLE_EQ(m[0][3], 12.0);
}

TEST(sum, TestingMatrixSum) {
    Matrix m1{{1.0, 2.0, 3.0, 4.0}};
    Matrix m2{{5.0, 6.0, 7.0, 8.0}};
    Matrix m3{{6.0, 8.0, 10.0, 12.0}};

    EXPECT_EQ(m1 + m2, m3);
}

TEST(sum, TestingSumEquals) {
    Matrix m1{{1.0, 2.0, 3.0, 4.0}};
    Matrix m2{{5.0, 6.0, 7.0, 8.0}};
    Matrix m3{{6.0, 8.0, 10.0, 12.0}};
    m1 += m2;

    EXPECT_EQ(m1, m3);
}

TEST(mul, TestingMulScalar) {
    Matrix m1{{1.0, 2.0, 3.0, 4.0}};
    Matrix m2{{2.0, 4.0, 6.0, 8.0}};

    EXPECT_EQ(2*m1, m2);
}

TEST(mul, TestingMulEqScalar) {
    Matrix m1{{1.0, 2.0, 3.0, 4.0}};
    Matrix m2{{2.0, 4.0, 6.0, 8.0}};
    m1 *= 2.0;

    EXPECT_EQ(m1, m2);
}

TEST(mul, TestingMulMatrix) {
    Matrix m1{{
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}}};
    Matrix m2{{
        {10.0, 11.0, 12.0},
        {13.0, 14.0, 15.0},
        {16.0, 17.0, 18.0}}};
    Matrix m3{{
        {84.0, 90.0, 96.0},
        {201.0, 216.0, 231.0},
        {318.0, 342.0, 366.0}}};

    EXPECT_EQ(m1*m2, m3);
}

TEST(mul, TestingMulEqMatrix) {
    Matrix m1{{
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}}};
    Matrix m2{{
        {10.0, 11.0, 12.0},
        {13.0, 14.0, 15.0},
        {16.0, 17.0, 18.0}}};
    Matrix m3{{
        {84.0, 90.0, 96.0},
        {201.0, 216.0, 231.0},
        {318.0, 342.0, 366.0}}};
    m1 *= m2;

    EXPECT_EQ(m1, m3);
}

TEST(mul, TestingMulVector) {
    Matrix m1{{
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}}};
    
    vector<double> v1 = {1.0, 0.0, 0.0};
    vector<double> v2 = {1.0, 4.0, 7.0};
    EXPECT_EQ(m1 * v1, v2);
}

