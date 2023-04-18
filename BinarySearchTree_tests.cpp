// Project UID db1f506d06d84ab787baf250c265e24e
// https://eecs280staff.github.io/p5-ml/#testing
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
    ASSERT_EQUAL(0, bst.size());
    ASSERT_EQUAL(0, bst.height());
    for (int i = 0; i < 20; ++i) {
        bst.insert(i);
    }
    ASSERT_EQUAL(20, bst.size());
    ASSERT_EQUAL(20, bst.height());
}

TEST(test_size_height_impl_empty) {
    BinarySearchTree<int> bst;
    ASSERT_EQUAL(0, bst.size());
    ASSERT_EQUAL(0, bst.height());
}

TEST(test_size_height_impl_single) {
    BinarySearchTree<int> bst;
    bst.insert(42);
    ASSERT_EQUAL(1, bst.size());
    ASSERT_EQUAL(1, bst.height());
}

TEST(test_size_height_impl_balanced) {
    BinarySearchTree<int> bst;
    for (int i = 0; i < 7; ++i) {
        bst.insert(i);
    }
    ASSERT_EQUAL(7, bst.size());
    ASSERT_NOT_EQUAL(3, bst.height());
}

TEST(test_size_height_impl_unbalanced) {
    BinarySearchTree<int> bst;
    for (int i = 0; i < 15; ++i) {
        bst.insert(i);
    }
    ASSERT_EQUAL(15, bst.size());
    ASSERT_NOT_EQUAL(14, bst.height());
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

TEST(test_copy_node_impl_empty) {
    BinarySearchTree<int> bst;
    BinarySearchTree<int> copy(bst);

    ASSERT_TRUE(copy.empty());
    ASSERT_EQUAL(0, copy.size());
    ASSERT_EQUAL(0, copy.height());
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
    ASSERT_EQUAL(15, bst1.size());
    ASSERT_EQUAL(15, bst1.height());
}

TEST(test_destroy_nodes_impl_empty) {
    BinarySearchTree<int> bst1;
    BinarySearchTree<int> bst2;
    bst2.insert(100);
    bst2 = bst1;
    ASSERT_TRUE(bst2.empty());
    ASSERT_EQUAL(0, bst2.size());
    ASSERT_EQUAL(0, bst2.height());
}

TEST(test_end_basic) {
    BinarySearchTree<int> bst;
    ASSERT_TRUE(bst.end() == bst.end());
    ASSERT_FALSE(bst.end() != bst.end());
    ASSERT_TRUE(bst.end() == bst.begin());
    ASSERT_FALSE(bst.end() != bst.begin());
}

TEST(test_begin_basic) {
    BinarySearchTree<int> bst;
    ASSERT_TRUE(bst.begin() == bst.begin());
    ASSERT_FALSE(bst.begin() != bst.begin());
    ASSERT_TRUE(bst.begin() == bst.end());
    ASSERT_FALSE(bst.begin() != bst.end());
}

TEST(test_dtor_empty) {
    BinarySearchTree<int> bst;
    bst.~BinarySearchTree();
    ASSERT_TRUE(bst.empty());
    ASSERT_EQUAL(0, bst.size());
    ASSERT_EQUAL(0, bst.height());
}

TEST(test_find_impl_basic) {
    BinarySearchTree<int> bst;
    // initialize bst with values [0, 14]
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

TEST(test_find_impl_empty) {
    BinarySearchTree<int> bst;
    ASSERT_TRUE(bst.find(0) == bst.end());
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

TEST(test_insert_impl_empty) {
    BinarySearchTree<int> bst;
    bst.insert(10);
    ASSERT_EQUAL(10, *bst.begin());
    ASSERT_EQUAL(1, bst.size());
    ASSERT_EQUAL(1, bst.height());
}

TEST(test_min_max_element_impl_basic) {
    BinarySearchTree<int> bst;
    // initialize bst with values [0, 3]
    for (int i = 0; i < 4; ++i) {
        bst.insert(i);
    }
    // test min element;
    auto i1 = bst.begin();
    ASSERT_EQUAL(i1, bst.min_element());

    // test max element;
    ++i1;
    ++i1;
    ++i1;
    ASSERT_EQUAL(i1, bst.max_element());
}

TEST(test_min_max_element_impl_empty) {
    BinarySearchTree<int> bst;
    ASSERT_TRUE(bst.min_element() == bst.end());
    ASSERT_TRUE(bst.max_element() == bst.end());
}

TEST(test_check_sorting_invariant_basic) {
    BinarySearchTree<int> bst1;
    // initialize bst with values [0, 3]
    for (int i = 0; i < 4; ++i) {
        bst1.insert(i);
    }
    ASSERT_TRUE(bst1.check_sorting_invariant());

    BinarySearchTree<int> bst2;
    bst2.insert(0);
    bst2.insert(1);

    *bst2.begin() = 2;
    ASSERT_FALSE(bst2.check_sorting_invariant());
}

TEST(test_check_sorting_invariant_empty) {
    BinarySearchTree<int> bst;
    ASSERT_TRUE(bst.check_sorting_invariant());
}

TEST(test_traverse_order_impl_basic) { 
    BinarySearchTree<int> bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(12);
    bst.insert(3);
    bst.insert(6);
    bst.insert(15);
    bst.insert(11);
    // 3, 5, 6, 10, 11, 12, 15 (expected output)
    bst.traverse_inorder(std::cout);
    std::cout << std::endl;
    ASSERT_EQUAL(3, bst.height());
    // 10, 5, 3, 6, 12, 11, 15 (expected output)
    bst.traverse_preorder(std::cout);
    std::cout << std::endl;
}    

TEST(test_traverse_order_impl_empty) {
    BinarySearchTree<int> bst;
    bst.traverse_inorder(std::cout);
    std::cout << std::endl;
    ASSERT_EQUAL(0, bst.height());
    bst.traverse_preorder(std::cout);
    std::cout << std::endl;
}

TEST(test_min_greater_impl_basic) {
    BinarySearchTree<int> bst;
    for (int i = 0; i < 20; ++i) {
        bst.insert(i);
    }
    auto i1 = bst.begin();
    ++i1;
    ASSERT_EQUAL(i1, bst.min_greater_than(0));
    ++i1;
    ++i1;
    ++i1;
    ++i1;
    ASSERT_EQUAL(i1, bst.min_greater_than(4));
    ++i1;
    ASSERT_EQUAL(i1, bst.min_greater_than(5));
    ++i1;
    ++i1;
    ++i1;
    ++i1;
    ++i1;
    ASSERT_EQUAL(i1, bst.min_greater_than(10));
}

TEST(test_min_greater_impl_empty) {
    BinarySearchTree<int> bst;
    ASSERT_TRUE(bst.min_greater_than(0) == bst.end());
    bst.insert(42);
    ASSERT_TRUE(bst.min_greater_than(42) == bst.end());
    ASSERT_TRUE(bst.min_greater_than(100) == bst.end());
}

TEST_MAIN()
