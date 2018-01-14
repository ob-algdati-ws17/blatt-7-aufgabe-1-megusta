#include "testAvlTree.h"

using namespace std;

TEST(AvlTreeTest, Test_EmptyTree) {
    AvlTree tree;
    EXPECT_EQ(nullptr, tree.inorder());
    EXPECT_EQ(nullptr, tree.preorder());
    EXPECT_EQ(nullptr, tree.postorder());
}

TEST(AvlTreeTest, Test_OneValue) {
    AvlTree tree;
    tree.insert(1);
    EXPECT_TRUE(tree.search(1));
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(1));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(1));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(1));

}

TEST(AvlTreeTest, Test_TwoValues) {
    AvlTree tree;
    tree.insert(1);
    tree.insert(2);
    EXPECT_TRUE(tree.search(1));
    EXPECT_TRUE(tree.search(2));
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(1, 2));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(1, 2));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(2, 1));
    EXPECT_THAT(tree.height(), 1);
}

TEST(AvlTreeTest, Test_Rotate_Right) {
    AvlTree tree;
    tree.insert(3);
    tree.insert(2);
    tree.insert(1);
    EXPECT_TRUE(tree.search(1));
    EXPECT_TRUE(tree.search(2));
    EXPECT_TRUE(tree.search(3));
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(1, 2, 3));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(2, 1, 3));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(1, 3, 2));
    EXPECT_THAT(tree.height(), 0);
}

TEST(AvlTreeTest, Test_Rotate_Left) {
    AvlTree tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    EXPECT_TRUE(tree.search(1));
    EXPECT_TRUE(tree.search(2));
    EXPECT_TRUE(tree.search(3));
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(1, 2, 3));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(2, 1, 3));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(1, 3, 2));
    EXPECT_THAT(tree.height(), 0);
}

TEST(AvlTreeTest, Test_Rotate_RightLeft) {
    AvlTree tree;
    tree.insert(1);
    tree.insert(3);
    tree.insert(2);
    EXPECT_TRUE(tree.search(1));
    EXPECT_TRUE(tree.search(2));
    EXPECT_TRUE(tree.search(3));
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(1, 2, 3));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(2, 1, 3));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(1, 3, 2));
    EXPECT_THAT(tree.height(), 0);
}

TEST(AvlTreeTest, Test_Rotate_LeftRight) {
    AvlTree tree;
    tree.insert(3);
    tree.insert(1);
    tree.insert(2);
    EXPECT_TRUE(tree.search(1));
    EXPECT_TRUE(tree.search(2));
    EXPECT_TRUE(tree.search(3));
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(1, 2, 3));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(2, 1, 3));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(1, 3, 2));
    EXPECT_THAT(tree.height(), 0);
}


TEST(AvlTreeTest, Test_Remove_One_Then_Empty) {
    AvlTree tree;
    tree.insert(1);
    tree.remove(1);
    EXPECT_EQ(nullptr, tree.inorder());
    EXPECT_EQ(nullptr, tree.preorder());
    EXPECT_EQ(nullptr, tree.postorder());
}

TEST(AvlTreeTest, Test_Remove_One_Then_One_Left) {
    AvlTree tree;
    tree.insert(1);
    tree.insert(2);
    tree.remove(2);
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(1));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(1));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(1));
    EXPECT_THAT(tree.height(), 0);
}

TEST(AvlTreeTest, Test_Remove_Without_Child_Without_Rotation) {
    AvlTree tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.remove(3);
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(1, 2));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(2, 1));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(1, 2));
    EXPECT_THAT(tree.height(), -1);
}

TEST(AvlTreeTest, Test_Remove_Without_Child_RightLeft_Rotation) {
    AvlTree tree;
    tree.insert(40);
    tree.insert(30);
    tree.insert(50);
    tree.insert(45);
    tree.remove(30);
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(40, 45, 50));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(45, 40, 50));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(40, 50, 45));
    EXPECT_THAT(tree.height(), 0);
}

TEST(AvlTreeTest, Test_Remove_Without_Child_Left_Rotation) {
    AvlTree tree;
    tree.insert(40);
    tree.insert(30);
    tree.insert(50);
    tree.insert(55);
    tree.remove(30);
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(40, 50, 55));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(50, 40, 55));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(40, 55, 50));
    EXPECT_THAT(tree.height(), 0);
}

TEST(AvlTreeTest, Test_Remove_Without_Child_LeftRight_Rotation) {
    AvlTree tree;
    tree.insert(40);
    tree.insert(30);
    tree.insert(50);
    tree.insert(35);
    tree.remove(50);
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(30, 35, 40));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(35, 30, 40));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(30, 40, 35));
    EXPECT_THAT(tree.height(), 0);
}

TEST(AvlTreeTest, Test_Remove_Without_Child_Right_Rotation) {
    AvlTree tree;
    tree.insert(40);
    tree.insert(30);
    tree.insert(50);
    tree.insert(25);
    tree.remove(50);
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(25, 30, 40));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(30, 25, 40));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(25, 40, 30));
    EXPECT_THAT(tree.height(), 0);
}

TEST(AvlTreeTest, Test_Remove_Without_Child_Final) {
    AvlTree tree;
    tree.insert(20);
    tree.insert(10);
    tree.insert(25);
    tree.insert(5);
    tree.insert(14);
    tree.insert(26);
    tree.insert(12);
    tree.remove(26);
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(5, 10, 12, 14, 20, 25));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(14, 10, 5, 12, 20, 25));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(5, 12, 10, 25, 20, 14));
    EXPECT_THAT(tree.height(), 0);
}


TEST(AvlTreeTest, Test_Remove_With_One_Child_Right_Left) {
    AvlTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(25);
    tree.remove(30);
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(10, 20, 25));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(20, 10, 25));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(10, 25, 20));
    EXPECT_THAT(tree.height(), 0);
}

TEST(AvlTreeTest, Test_Remove_With_One_Child_Right_Right) {
    AvlTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(35);
    tree.remove(30);
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(10, 20, 35));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(20, 10, 35));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(10, 35, 20));
    EXPECT_THAT(tree.height(), 0);
}

TEST(AvlTreeTest, Test_Remove_With_One_Child_Left_Left) {
    AvlTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(5);
    tree.remove(10);
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(5, 20, 30));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(20, 5, 30));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(5, 30, 20));
    EXPECT_THAT(tree.height(), 0);
}

TEST(AvlTreeTest, Test_Remove_With_One_Child_Left_Right) {
    AvlTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.remove(10);
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(15, 20, 30));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(20, 15, 30));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(15, 30, 20));
    EXPECT_THAT(tree.height(), 0);
}


TEST(AvlTreeTest, Test_Remove_With_Two_Childs_Root) {
    AvlTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.remove(20);
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(10, 30));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(10, 30));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(30, 10));
    EXPECT_THAT(tree.height(), 1);
}

TEST(AvlTreeTest, Test_Remove_With_Two_Childs_Right) {
    AvlTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(25);
    tree.insert(35);
    tree.remove(30);
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(10, 20, 25, 35));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(20, 10, 25, 35));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(10, 35, 25, 20));
    EXPECT_THAT(tree.height(), 1);
}

TEST(AvlTreeTest, Test_Remove_With_Two_Childs_Left) {
    AvlTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(5);
    tree.insert(15);
    tree.remove(10);
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(5, 15, 20, 30));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(20, 5, 15, 30));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(15, 5, 30, 20));
    EXPECT_THAT(tree.height(), -1);
}

TEST(AvlTreeTest, Test_Remove_With_Two_Childs_Final) {
    AvlTree tree;
    tree.insert(20);
    tree.insert(15);
    tree.insert(25);
    tree.insert(21);
    tree.insert(30);
    tree.insert(10);
    tree.insert(16);
    tree.insert(18);
    tree.remove(20);
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(10, 15, 16, 18, 21, 25, 30));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(18, 15, 10, 16, 25, 21, 30));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(10, 16, 15, 21, 30, 25, 18));
    EXPECT_THAT(tree.height(), 0);
}



