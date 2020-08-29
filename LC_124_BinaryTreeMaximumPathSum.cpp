// 29 August 2020 
// Solves Leet Code problem 124, Binary Tree Maximum Path Sum
// https://leetcode.com/problems/binary-tree-maximum-path-sum/
// Difficulty: Hard

// This solution is top 10% in speed but bottom 10% in memory usage. I just
// modified code used for a simpler problem, which is why there are all those
// maximizations there -- this was a quick one.
// It works recursively, building from the bottom. For each subtree, calculate
// the max path within the subtree (and record it if it is the maximum overall),
// and also record what would be the maximum path leading out of the subtree,
// ie including the root of the subtree, and pass that up to the next level of
// the tree.

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
    int retval;
public:
    int subtreemaxexiting(TreeNode* curnode) {
        int subtreepath=0;
        int maxthissubtree = INT_MIN;
        if (!curnode->left && !curnode->right) { return curnode->val; }
        int leftsubtree=0;
        if (curnode->left) { leftsubtree = subtreemaxexiting(curnode->left);}
        int rightsubtree=0;
        if (curnode->right) { rightsubtree = subtreemaxexiting(curnode->right);}
        //std::cout<<"node "<<curnode->val<<" left "<<leftsubtree<<" right "<<rightsubtree<<" retval "<<retval<<endl;
        if (curnode->left&&curnode->right) {
            maxthissubtree = leftsubtree + rightsubtree + curnode->val;
            maxthissubtree = max(maxthissubtree,leftsubtree);
            maxthissubtree = max(maxthissubtree,leftsubtree + curnode -> val);
            maxthissubtree = max(maxthissubtree,rightsubtree);
            maxthissubtree = max(maxthissubtree,rightsubtree + curnode -> val);
            maxthissubtree = max(maxthissubtree, curnode -> val);
            //std::cout<<"node "<<curnode->val<<" maxthissubtree "<<maxthissubtree<<endl;
            if (maxthissubtree>retval) { retval = maxthissubtree; }
            int provisional = max(leftsubtree+curnode->val,rightsubtree+curnode->val);
            return max(curnode->val,provisional);
        } else if (curnode->left) {
            maxthissubtree = leftsubtree + curnode->val;
            maxthissubtree = max(maxthissubtree,leftsubtree);
            maxthissubtree = max(maxthissubtree,leftsubtree + curnode -> val);
            maxthissubtree = max(maxthissubtree, curnode -> val);
            if (maxthissubtree>retval) { retval = maxthissubtree; }
            //return maxthissubtree;
            return max(curnode->val,leftsubtree + curnode->val);
        } else if (curnode->right) {
            maxthissubtree = rightsubtree + curnode->val;
            maxthissubtree = max(maxthissubtree,rightsubtree);
            maxthissubtree = max(maxthissubtree,rightsubtree + curnode -> val);
            maxthissubtree = max(maxthissubtree, curnode -> val);
            if (maxthissubtree>retval) { retval = maxthissubtree; }
            //return maxthissubtree;
            return max(curnode->val,rightsubtree + curnode->val);
        } else {
            return 0;
        }
            
        
        return INT_MIN;
        
    }
public:
    int maxPathSum(TreeNode* root) {
        if (!root) return 0;
        if (!root->left&&!root->right) return root->val;
        
        retval = INT_MIN;
        int maxstringincludingroot = subtreemaxexiting(root);
        return retval;
        
    }
    
};

