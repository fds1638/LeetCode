// done 24 sep 2020
// solves Leet Code 301, Remove Invalid Parentheses
// https://leetcode.com/problems/remove-invalid-parentheses/
// Difficulty: Hard

// With the hints LeetCode gave, it's straightforward. Given an expression
// with ( and ) parentheses, can easily count how many left parens are out
// of place and how many right are out of place. So know how many left to
// drop and how many right to drop. The do a DFS (or BFS) to find all possible
// ways one can drop those parentheses.

class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        int badleft = 0;
        int badright = 0;
        int countleft = 0;
        int countright = 0;
        for (int ss=0; ss<s.size(); ss++) {
            if (s[ss]=='(') { countleft++; } 
            else if (s[ss]==')') {  
                if (countleft>0) {countleft--;}
                else { countright++; badright++; }
            }
        }
        badleft = countleft;
        //cout<<"badleft "<<badleft<<" badright "<<badright<<endl;
        
        set<string> found;
        vector<string> retval;
        stack< pair< string, vector<int> > > dfs; //curstring, index, leftdrop, rightdrop, leftcount, rightcount
        dfs.push({"",{0,0,0,0,0}});
        while (!dfs.empty()) {
            string curstring = dfs.top().first;
            int ss = dfs.top().second[0];
            int ld = dfs.top().second[1];
            int rd = dfs.top().second[2];
            int lc = dfs.top().second[3];
            int rc = dfs.top().second[4];
            dfs.pop();
            // check to see if this is a solution
            if (curstring.size()==s.size()-badleft-badright&&lc==rc) {
                if (found.find(curstring)==found.end()){
                    retval.push_back(curstring);
                    found.insert(curstring);
                }
            }                
            // consider all possible actions
            // can only add if not too long already
            // if a left parens, can always add it unless have reached the end. 
            // can drop it if haven't dropped too many already
            // if a right parens, can only add if leftcount > rightcount
            // can drop it if haven't dropped too many already
            if (curstring.size()<s.size()-badleft-badright) {
                if (s[ss]=='(') {
                    if (curstring.size()<s.size()-badleft-badright) {
                        dfs.push({curstring+s[ss],{ss+1,ld,rd,lc+1,rc}});
                    }
                    if (ld<badleft) {
                        dfs.push({curstring,{ss+1,ld+1,rd,lc,rc}});
                    }
                } else if (s[ss]==')'){
                    if (lc>rc) {
                        dfs.push({curstring+s[ss],{ss+1,ld,rd,lc,rc+1}});
                    }
                    if (rd<badright) {
                        dfs.push({curstring,{ss+1,ld,rd+1,lc,rc}});
                    }
                } else { //always add anything else
                    dfs.push({curstring+s[ss],{ss+1,ld,rd,lc,rc}});
                }
            }
        }
        
        return retval;
    }
};


