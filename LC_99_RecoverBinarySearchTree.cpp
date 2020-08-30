// Done 30 August 2020
// Solves LeetCode problem 99, Recover Binary Search Tree
// https://leetcode.com/problems/recover-binary-search-tree
// Difficulty: Hard

// You're given a binary search tree with two nodes swapped. Those
// nodes could be anywhere, they don't have to be adjacent, they
// don't have to be (grand)parent and (grand)child, etc.

// I realized that I was interested in the nodes furthest to the left
// and right, and created a coordinate in powers of 2 to located the
// nodes that failed the binary search tree criterion. When I read
// the other answers, I realized that in order traversal would have
// solved this problem for me. Nevertheless, this is done. It's poor
// in space usage and pretty variable in speed (from 90th percentile
// down to 20th).

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    void recoverTree(TreeNode* root) {
        double base = 2.0;
        double lmost = INT_MAX;
        double rmost = INT_MIN;
        TreeNode* lswap = NULL;
        TreeNode* rswap = NULL;
        stack< tuple<int, double, TreeNode*, double, TreeNode*, double, TreeNode*> > dfs;
        dfs.push({0, 0.0, root, INT_MIN, NULL, INT_MAX, NULL});
        while ( dfs.size()>0 ) {
            tuple<int, double, TreeNode*, double, TreeNode*, double, TreeNode*> curnodeinfo = dfs.top();
            dfs.pop();
            int iteration = std::get<0>(curnodeinfo);
            double curloc = std::get<1>(curnodeinfo);
            TreeNode* curnode = std::get<2>(curnodeinfo);
            double lloc = std::get<3>(curnodeinfo);
            TreeNode* lpnode = std::get<4>(curnodeinfo);
            double rloc = std::get<5>(curnodeinfo);
            TreeNode* rpnode = std::get<6>(curnodeinfo);
            if ( lpnode && curnode->val<= lpnode->val) {
                //know lloc < curloc
                if ( lloc < lmost ) {
                    lmost = lloc;
                    lswap = lpnode;
                }
                
                if ( curloc > rmost ) {
                    rmost = curloc;
                    rswap = curnode;
                }

            }
            if ( rpnode && curnode->val>= rpnode->val) {
                // know rloc > curloc
                if ( rloc > rmost ) {
                    rmost = rloc;
                    rswap = rpnode;
                }
                
                if ( curloc < lmost ) {
                    lmost = curloc;
                    lswap = curnode;
                }

            }
            if (curnode->right) {
                dfs.push({iteration-1, curloc+pow(base*1.0,iteration), curnode->right, curloc, curnode, rloc, rpnode});
            }
            if (curnode->left) {
                dfs.push({iteration-1, curloc-pow(base*1.0,iteration), curnode->left, lloc, lpnode, curloc, curnode});
            }
        }
        
        if (lswap&&rswap) {
            int temp = lswap->val;
            lswap->val = rswap->val;
            rswap->val = temp;
        }
        
        return;
    }
};

