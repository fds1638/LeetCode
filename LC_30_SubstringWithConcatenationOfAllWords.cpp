// done 7 Oct 2020
// solves Leet Code problem 30, Substring With Concatenation Of All Words
// https://leetcode.com/problems/substring-with-concatenation-of-all-words/
// Difficulty: Hard

// A standard two-pointers / sliding window type of solution.

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        
        vector<int> retval ={};
        
        int wordlen = words[0].size();
        int wordnum = words.size();
        
        if (s.size()<wordlen*wordnum) {return {};}
        
        map<string, int> wordmap;
        for (int ii=0; ii<wordnum; ii++) {
            wordmap[words[ii]]++;
        }
        
        for (int ii=0; ii<=s.size()-wordlen*wordnum; ii++) {
            map<string, int> curmap;
            int streak = 0;
            for (int jj=0; jj<wordnum; jj++) {
                string curword = s.substr(ii+jj*wordlen,wordlen);
                if ( wordmap.find(curword)!=wordmap.end() 
                    && (curmap.find(curword)==curmap.end() || wordmap[curword]>curmap[curword] ) ) {
                    curmap[curword]++;
                    streak++;
                }
            }
            if ( streak==wordnum ) { retval.push_back(ii);}
        }
        return retval;
    }
};


