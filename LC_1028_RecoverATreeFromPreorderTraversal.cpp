// done 13 Oct 2020
// solves Leet Code 1028, Recover A Tree From Preorder Traversal
// https://leetcode.com/problems/recover-a-tree-from-preorder-traversal/
// difficulty: Hard

// Given a string representing the preorder traversal of a tree, reconstruct the tree.
// There are two key pieces of information: (1) each tree value is preceded by dashes
// indicating its depth; and (2) if a node has only one child, it is the left one.

// Do an iterative DFS as the hint given in the problem suggests. This code is 
// top 10% in speed.

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
    TreeNode* recoverFromPreorder(string S) {
        if (S.size()==0) { return nullptr;}
        // Get the first value and put it in the root node.
        int ii=0;
        string first="";
        while (S[ii]!='-'&&ii<S.size()) { first+=S[ii]; ii++;}
        TreeNode* root = new TreeNode(stoi(first));
        TreeNode* curnode;
        // In the dfs put the value of the node and its depth.
        stack<pair<TreeNode*,int> > dfs;
        dfs.push({root,0});
        while (ii<S.size()) { // ii is at the first dash after the last processed node value
            int depth=0;
            while (S[ii]=='-') { depth++; ii++;}    // get the depth
            string temp = "";
            while (S[ii]!='-'&&ii<S.size()) { temp+=S[ii]; ii++;}
            int val = stoi(temp);                   // get the value of the node
            while (depth!=dfs.top().second+1) { dfs.pop(); } // if too deep in the tree, pop
            curnode = new TreeNode(val);                        // create new node
            if (!dfs.top().first->left) {           // if no left child exists, make a left child
                dfs.top().first->left = curnode;
                dfs.push({curnode,depth});          
            } else {                                // else make a right child
                dfs.top().first->right = curnode;
                dfs.push({curnode,depth});
            }
        }
        return root;
    }
};


