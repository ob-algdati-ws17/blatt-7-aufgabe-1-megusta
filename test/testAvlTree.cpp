#include "testAvlTree.h"
#include <memory>

using namespace std;

// empty tree

TEST(AvlTreeTest, Empty_Tree) {
    AvlTree a;
    EXPECT_EQ(nullptr, a.preorder());
    EXPECT_EQ(nullptr, a.inorder());
    EXPECT_EQ(nullptr, a.postorder());
}

TEST(AvlTreeTest, One_Node) {
    AvlTree a;
    a.insert(15);
    EXPECT_TRUE(a.search(15));
    EXPECT_FALSE(a.search(-15));
    EXPECT_FALSE(a.search(16));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(15));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(15));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(15));

}

TEST(AvlTreeTest, Two_Nodes) {
    AvlTree a;
    a.insert(12213);
    a.insert(215);
    EXPECT_TRUE(a.search(12213));
    EXPECT_TRUE(a.search(215));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(12213, 215));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(215, 12213));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(215, 12213));
}

TEST(AvlTreeTest, Three_Nodes) {
    AvlTree a;
    a.insert(12213);
    a.insert(215);
    a.insert(123712);
    EXPECT_TRUE(a.search(12213));
    EXPECT_TRUE(a.search(123712));
    EXPECT_TRUE(a.search(215));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(12213, 215, 123712));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(215, 12213, 123712));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(215, 123712, 12213));
}

TEST(AvlTreeTest, Three_Nodes_With_Balance) {
    AvlTree a;
    a.insert(12213);
    a.insert(215);
    a.insert(123712);
    EXPECT_TRUE(a.search(12213));
    EXPECT_TRUE(a.search(123712));
    EXPECT_TRUE(a.search(215));
    EXPECT_EQ(0,a.height());
}
