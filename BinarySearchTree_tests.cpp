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
    // assignment operator calls the
    // destroy_nodes_impl() function
    bst2 = bst1;
    ASSERT_EQUAL(15, bst2.size());
    ASSERT_EQUAL(15, bst2.height());
}

TEST(test_find_impl_basic) {
    BinarySearchTree<int> bst;
    // initialize bst with values [0, 15]
    for (int i = 0; i < 15; ++i) {
        bst.insert(i);
    }

    auto i1 = bst.begin();
    ASSERT_EQUAL(i1, bst.find(0));

    for (int i = 0; i < 15; ++i) {
        ASSERT_EQUAL(i1, bst.find(i));
        ++i1;
    }
    i1 = bst.end();
    ASSERT_EQUAL(i1, bst.find(30));
}

TEST(test_insert_impl_basic) {
    BinarySearchTree<int> bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(12);
    bst.insert(3);
    bst.insert(6);
    bst.insert(15);
    bst.insert(11);
    ASSERT_EQUAL(3, bst.height());
    ASSERT_EQUAL(7, bst.size());
}

TEST_MAIN()