// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"
#include <sstream>

using namespace std;

TEST(empty_impl) {
    BinarySearchTree<int> bst;
    ASSERT_TRUE(bst.empty());
    int val = 0;
    bst.insert(val);
    ASSERT_FALSE(bst.empty());
}


TEST_MAIN()