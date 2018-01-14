#include "testAvlTree.h"

using namespace std;

TEST(AvlTreeTest, Test_Empty_Tree) {
    AvlTree a;
    EXPECT_EQ(nullptr, a.inorder());
    EXPECT_EQ(nullptr, a.preorder());
    EXPECT_EQ(nullptr, a.postorder());
}

TEST(AvlTreeTest, Test_One_Value) {
    AvlTree a;
    a.insert(1);
    EXPECT_TRUE(a.search(1));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(1));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(1));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(1));

}

TEST(AvlTreeTest, Test_Two_Values) {
    AvlTree a;
    a.insert(1);
    a.insert(2);
    EXPECT_TRUE(a.search(1));
    EXPECT_TRUE(a.search(2));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(1, 2));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(1, 2));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(2, 1));
    EXPECT_THAT(a.height(), 1);
}

TEST(AvlTreeTest, Test_Rotate_Right) {
    AvlTree a;
    a.insert(3);
    a.insert(2);
    a.insert(1);
    EXPECT_TRUE(a.search(1));
    EXPECT_TRUE(a.search(2));
    EXPECT_TRUE(a.search(3));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(1, 2, 3));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(2, 1, 3));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(1, 3, 2));
    EXPECT_THAT(a.height(), 0);
}

TEST(AvlTreeTest, Test_Rotate_Left) {
    AvlTree a;
    a.insert(1);
    a.insert(2);
    a.insert(3);
    EXPECT_TRUE(a.search(1));
    EXPECT_TRUE(a.search(2));
    EXPECT_TRUE(a.search(3));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(1, 2, 3));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(2, 1, 3));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(1, 3, 2));
    EXPECT_THAT(a.height(), 0);
}

TEST(AvlTreeTest, Test_Rotate_Right_Left) {
    AvlTree a;
    a.insert(1);
    a.insert(3);
    a.insert(2);
    EXPECT_TRUE(a.search(1));
    EXPECT_TRUE(a.search(2));
    EXPECT_TRUE(a.search(3));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(1, 2, 3));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(2, 1, 3));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(1, 3, 2));
    EXPECT_THAT(a.height(), 0);
}

TEST(AvlTreeTest, Test_Rotate_Left_Right) {
    AvlTree a;
    a.insert(3);
    a.insert(1);
    a.insert(2);
    EXPECT_TRUE(a.search(1));
    EXPECT_TRUE(a.search(2));
    EXPECT_TRUE(a.search(3));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(1, 2, 3));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(2, 1, 3));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(1, 3, 2));
    EXPECT_THAT(a.height(), 0);
}


TEST(AvlTreeTest, Test_Remove_Root) {
    AvlTree a;
    a.insert(1);
    EXPECT_TRUE(a.search(1));
    a.remove(1);
    EXPECT_FALSE(a.search(1));
    EXPECT_EQ(nullptr, a.inorder());
    EXPECT_EQ(nullptr, a.preorder());
    EXPECT_EQ(nullptr, a.postorder());
}

TEST(AvlTreeTest, Test_Remove_Without_Child_One) {
    AvlTree a;
    a.insert(1);
    a.insert(2);
    EXPECT_TRUE(a.search(1));
    EXPECT_TRUE(a.search(2));
    a.remove(2);
    EXPECT_FALSE(a.search(2));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(1));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(1));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(1));
    EXPECT_THAT(a.height(), 0);
}

TEST(AvlTreeTest, Test_Remove_Without_Child_Two) {
    AvlTree a;
    a.insert(1);
    a.insert(2);
    a.insert(3);
    EXPECT_TRUE(a.search(1));
    EXPECT_TRUE(a.search(2));
    EXPECT_TRUE(a.search(3));
    a.remove(3);
    EXPECT_FALSE(a.search(3));
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(1, 2));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(2, 1));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(1, 2));
    EXPECT_THAT(a.height(), -1);
}

TEST(AvlTreeTest, Test_Remove_Without_Child_Three) {
    AvlTree a;
    a.insert(200);
    a.insert(100);
    a.insert(250);
    a.insert(50);
    a.insert(140);
    a.insert(260);
    a.insert(120);
    a.remove(260);
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(50, 100, 120, 140, 200, 250));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(140, 100, 50, 120, 200, 250));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(50, 120, 100, 250, 200, 140));
    EXPECT_THAT(a.height(), 0);
}

TEST(AvlTreeTest, Test_Remove_Without_Child_RightLeft_Rotation) {
    AvlTree a;
    a.insert(400);
    a.insert(300);
    a.insert(500);
    a.insert(450);
    a.remove(300);
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(400, 450, 500));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(450, 400, 500));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(400, 500, 450));
    EXPECT_THAT(a.height(), 0);
}

TEST(AvlTreeTest, Test_Remove_Without_Child_Left_Rotation) {
    AvlTree a;
    a.insert(400);
    a.insert(300);
    a.insert(500);
    a.insert(550);
    a.remove(300);
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(400, 500, 550));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(500, 400, 550));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(400, 550, 500));
    EXPECT_THAT(a.height(), 0);
}

TEST(AvlTreeTest, Test_Remove_Without_Child_LeftRight_Rotation) {
    AvlTree a;
    a.insert(400);
    a.insert(300);
    a.insert(500);
    a.insert(350);
    a.remove(500);
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(300, 350, 400));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(350, 300, 400));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(300, 400, 350));
    EXPECT_THAT(a.height(), 0);
}

TEST(AvlTreeTest, Test_Remove_Without_Child_Right_Rotation) {
    AvlTree a;
    a.insert(400);
    a.insert(300);
    a.insert(500);
    a.insert(250);
    a.remove(500);
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(250, 300, 400));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(300, 250, 400));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(250, 400, 300));
    EXPECT_THAT(a.height(), 0);
}



TEST(AvlTreeTest, Test_Remove_With_One_Child_Right_Left_Rotation) {
    AvlTree a;
    a.insert(100);
    a.insert(200);
    a.insert(300);
    a.insert(250);
    a.remove(300);
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(100, 200, 250));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(200, 100, 250));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(100, 250, 200));
    EXPECT_THAT(a.height(), 0);
}

TEST(AvlTreeTest, Test_Remove_With_One_Child_Right_Right_Rotation) {
    AvlTree a;
    a.insert(100);
    a.insert(200);
    a.insert(300);
    a.insert(350);
    a.remove(300);
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(100, 200, 350));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(200, 100, 350));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(100, 350, 200));
    EXPECT_THAT(a.height(), 0);
}

TEST(AvlTreeTest, Test_Remove_With_One_Child_Left_Left_Rotation) {
    AvlTree a;
    a.insert(100);
    a.insert(200);
    a.insert(300);
    a.insert(50);
    a.remove(100);
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(50, 200, 300));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(200, 50, 300));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(50, 300, 200));
    EXPECT_THAT(a.height(), 0);
}

TEST(AvlTreeTest, Test_Remove_With_One_Child_Left_Right_Rotation) {
    AvlTree a;
    a.insert(100);
    a.insert(200);
    a.insert(300);
    a.insert(150);
    a.remove(100);
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(150, 200, 300));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(200, 150, 300));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(150, 300, 200));
    EXPECT_THAT(a.height(), 0);
}


TEST(AvlTreeTest, Test_Remove_With_Two_Childs_Root) {
    AvlTree a;
    a.insert(100);
    a.insert(200);
    a.insert(300);
    a.remove(200);
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(100, 300));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(100, 300));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(300, 100));
    EXPECT_THAT(a.height(), 1);
}

TEST(AvlTreeTest, Test_Remove_With_Two_Childs_Right) {
    AvlTree a;
    a.insert(100);
    a.insert(200);
    a.insert(300);
    a.insert(250);
    a.insert(350);
    a.remove(300);
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(100, 200, 250, 350));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(200, 100, 250, 350));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(100, 350, 250, 200));
    EXPECT_THAT(a.height(), 1);
}

TEST(AvlTreeTest, Test_Remove_With_Two_Childs_Left) {
    AvlTree a;
    a.insert(100);
    a.insert(200);
    a.insert(300);
    a.insert(50);
    a.insert(150);
    a.remove(100);
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(50, 150, 200, 300));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(200, 50, 150, 300));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(150, 50, 300, 200));
    EXPECT_THAT(a.height(), -1);
}

TEST(AvlTreeTest, Test_Remove_With_Two_Childs) {
    AvlTree a;
    a.insert(200);
    a.insert(150);
    a.insert(250);
    a.insert(210);
    a.insert(300);
    a.insert(100);
    a.insert(160);
    a.insert(180);
    a.remove(200);
    EXPECT_THAT(*a.inorder(), testing::ElementsAre(100, 150, 160, 180, 210, 250, 300));
    EXPECT_THAT(*a.preorder(), testing::ElementsAre(180, 150, 100, 160, 250, 210, 300));
    EXPECT_THAT(*a.postorder(), testing::ElementsAre(100, 160, 150, 210, 300, 250, 180));
    EXPECT_THAT(a.height(), 0);
}



