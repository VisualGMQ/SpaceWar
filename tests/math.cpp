#include "unittest.hpp"
#include "tinyengine/libmath.hpp"

int main(int argc, char** argv) {
    Point p1{1.2, 3.3},
          p2{2.7, 3.8};
    TEST_TRUE(feq(p1.x, 1.2));
    TEST_TRUE(feq(p1.y, 3.3));
    TEST_TRUE(feq(p2.x, 2.7));
    TEST_TRUE(feq(p2.y, 3.8));

    Point result = p1 + p2;
    TEST_TRUE(feq(result.x, p1.x + p2.x));
    TEST_TRUE(feq(result.y, p1.y + p2.y));

    result = p1 / 2.8;
    TEST_TRUE(feq(result.x, p1.x / 2.8));
    TEST_TRUE(feq(result.y, p1.y / 2.8));

    result = p1 / p2;
    TEST_TRUE(feq(result.x, p1.x / p2.x));
    TEST_TRUE(feq(result.y, p1.y / p2.y));
}
