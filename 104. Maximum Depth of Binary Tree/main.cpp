#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <queue>
#include <random>
#include <vector>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

class Solution {
  public:
    int maxDepth(TreeNode *root) {
        if (!root)
            return 0;
        return 1 + std::max(maxDepth(root->left), maxDepth(root->right));
    }
};

// Helper function to create a random binary tree
TreeNode *createRandomTree(int depth, std::mt19937 &gen) {
    if (depth == 0 || gen() % 3 == 0)
        return nullptr;

    TreeNode *root = new TreeNode(gen() % 1000);
    root->left = createRandomTree(depth - 1, gen);
    root->right = createRandomTree(depth - 1, gen);
    return root;
}

// Helper function to delete the tree
void deleteTree(TreeNode *root) {
    if (!root)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// Unit tests
void runUnitTests() {
    Solution sol;

    // Test case 1: Empty tree
    assert(sol.maxDepth(nullptr) == 0);

    // Test case 2: Single node tree
    TreeNode *root1 = new TreeNode(1);
    assert(sol.maxDepth(root1) == 1);
    delete root1;

    // Test case 3: Balanced tree
    TreeNode *root2 = new TreeNode(3);
    root2->left = new TreeNode(9);
    root2->right = new TreeNode(20);
    root2->right->left = new TreeNode(15);
    root2->right->right = new TreeNode(7);
    assert(sol.maxDepth(root2) == 3);
    deleteTree(root2);

    // Test case 4: Unbalanced tree
    TreeNode *root3 = new TreeNode(1);
    root3->right = new TreeNode(2);
    root3->right->right = new TreeNode(3);
    root3->right->right->right = new TreeNode(4);
    assert(sol.maxDepth(root3) == 4);
    deleteTree(root3);

    std::cout << "All unit tests passed!" << std::endl;
}

// Performance test
void runPerformanceTest() {
    Solution sol;
    std::mt19937 gen(std::random_device{}());
    const int numTests = 1000;
    const int maxDepth = 1000;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numTests; ++i) {
        TreeNode *root = createRandomTree(maxDepth, gen);
        sol.maxDepth(root);
        deleteTree(root);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Performance test: " << duration.count() << " ms for "
              << numTests << " trees" << std::endl;
}

int main() {
    runUnitTests();
    runPerformanceTest();
    return 0;
}
