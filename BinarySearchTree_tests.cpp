// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"


TEST(test_empty_impl) {
    BinarySearchTree<int> bst;
    ASSERT_TRUE(bst.empty());
    bst.insert(0);
    ASSERT_FALSE(bst.empty());
}

TEST(test_size_height_impl_basic) {
    BinarySearchTree<int> bst;
    for (int i = 0; i < 20; ++i) {
        bst.insert(i);
    }
    ASSERT_EQUAL(20, bst.size());
    ASSERT_EQUAL(20, bst.height());
}

TEST(test_copy_node_impl_basic) {
    BinarySearchTree<int> bst;
    for (int i = 0; i < 20; ++i) {
        bst.insert(i);
    }
    BinarySearchTree<int> copy(bst);

    ASSERT_EQUAL(20, copy.size());
    ASSERT_EQUAL(20, copy.height());
}

TEST(test_destroy_nodes_impl_basic) {
    BinarySearchTree<int> bst1;
    for (int i = 0; i < 15; ++i) {
        bst1.insert(i);
    }
    BinarySearchTree<int> bst2;
    bst2.insert(100);

  bst2 = bst1;

  ASSERT_EQUAL(15, bst2.size());
  ASSERT_EQUAL(15, bst2.height());
}
// FIXME:
// insert doesn't work for BSTs that are not constantly
// increasing or decreasing

TEST_MAIN()
