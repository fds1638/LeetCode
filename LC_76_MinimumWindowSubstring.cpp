// done 07 Oct 2020
// solves Leet Code problem 76, Minimum Window Substring
// https://leetcode.com/problems/minimum-window-substring/
// Difficulty: Hard

// A two-pointer solution with a couple of maps and variables
// to keep track of letters found.

class Solution {
public:
    string minWindow(string s, string t) {
        string retval = s;
        if (s.size()<t.size()) { return ""; }
        if (s.size()==t.size()) {
            if (s.compare(t)==0) {return s;} 
        }
        map<char,int> tmap;
        map<char,int> tmaporig;
        for (int tt=0; tt<t.size(); tt++) {
            tmap[t[tt]]=0;
            tmaporig[t[tt]]++;
        }
        int lo=0, hi=0;
        int used = 0;
        bool found = false;
        bool madestep = true;
        while ((hi<s.size()||lo<s.size())&&madestep) {
            // increase hi until get all chars of t or reach end
            // then increase lo until don't have all chars of t
            // repeat
            madestep = false;
            if (used<t.size()&&hi<s.size()) {
                if (tmap.find(s[hi])!=tmap.end() && tmap[s[hi]]<tmaporig[s[hi]]) {
                    used++;
                }
                if (tmap.find(s[hi])!=tmap.end()) {
                    tmap[s[hi]]++;
                }
                hi++;
                madestep=true;
            } 
            if ( !madestep) {
                if (tmap.find(s[lo])!=tmap.end() && tmap[s[lo]]>0) {
                    if (tmap[s[lo]]<=tmaporig[s[lo]]) {used--;}
                    tmap[s[lo]]--;
                }
                lo++;
                madestep=true;
            }
            if ( used==t.size() && hi-lo<=retval.size()) { retval = s.substr(lo, hi-lo); found=true;}
        }
        if ( !found ) { return ""; }
        return retval;
    }
};


