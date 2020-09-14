// done 14 sep 2020
// solves Leet Code 297, Serialize and Deserialize Binary Tree
// Diffiulty: Hard

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (!root) {return "";}
        string retval="[";
        deque<TreeNode*> bfs;
        bfs.push_back(root);
        bool nextlevel = false;
        if (root->left||root->right) {nextlevel=true;}
        else {retval += to_string(root->val); }
        while (bfs.size()>0&&nextlevel) {
            deque<TreeNode*> thislevel;
            thislevel.swap(bfs);
            nextlevel = false;
            while (thislevel.size()>0) {
                TreeNode* curnode = thislevel.front();
                thislevel.pop_front();
                if (curnode->val!=INT_MIN) {
                    if (curnode->left) {bfs.push_back(curnode->left); nextlevel=true; }
                    else{bfs.push_back(new TreeNode(INT_MIN));}
                    if (curnode->right) {bfs.push_back(curnode->right); nextlevel=true; }
                    else{bfs.push_back(new TreeNode(INT_MIN));}
                }
                if (retval.compare("[")==0) {
                    retval += to_string(curnode->val);
                } else {
                    if (curnode->val!=INT_MIN) {
                        retval += ','+to_string(curnode->val);
                    } else {
                        retval += ",null";
                    }
                }
            }
        }
        retval += "]";
        //cout<<"retval "<<retval;
        return retval;
    }

    // Decodes your encoded data to tree.
    TreeNode* recdes(int ii, vector<int>& values, vector<int>& children) {
        TreeNode* curnode;
            curnode = new TreeNode(values[ii]);
            if (children[ii]+1<values.size()&&values[children[ii]+1]!=INT_MIN) { 
                curnode->left = recdes(children[ii]+1,values, children); }
            else { curnode->left = nullptr; }
            if (children[ii]+2<values.size()&&values[children[ii]+2]!=INT_MIN) { 
                curnode->right = recdes(children[ii]+2,values, children); }
            else { curnode->right = nullptr; }
        return curnode;
    }

    TreeNode* deserialize(string data) {
        if (data.compare("")==0) { return NULL;}
        //cout<<"data "<<data<<endl;
        vector<int> values;
        vector<int> children;
        int childidx = 0;
        string temp="";
        for (int ii=1; ii<data.size(); ii++) {
            if (data[ii]==','||data[ii]==']') {
                if (temp.compare("null")==0) { 
                    values.push_back(INT_MIN);
                    children.push_back(INT_MIN);
                }
                else { 
                    values.push_back(stoi(temp));
                    children.push_back(childidx);
                    childidx+=2;
                }
                temp = "";
            } else {
                temp += data[ii];
            }
        }
        /*
        cout<<"values   ";
        for (int kk=0; kk<values.size(); kk++) {
            cout<<values[kk]<<" ";
        }
        cout<<endl;
        cout<<"children ";
        for (int kk=0; kk<children.size(); kk++) {
            cout<<children[kk]<<" ";
        }
        cout<<endl;
        */
        TreeNode* retval = recdes(0,values,children);
        return retval;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));


