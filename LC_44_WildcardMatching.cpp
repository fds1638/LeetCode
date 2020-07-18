// July 18 2020
// Solves Hard LeetCode problem 44
// https://leetcode.com/problems/wildcard-matching/
// Dynamic Programming solution, just like problem 10.
// The conditions are a little bit easier, I must admit.
class Solution {
public:
    bool isMatch(string s, string p) {
        bool T[s.size()+1][p.size()+1];
        T[0][0]=true;
        int starflag=true;
        for (int pp=1; pp<=p.size(); pp++) { // fill in top row
            if ( p.at(pp-1)!='*') { starflag=false; } //only match empty s if all stars in p
            if ( starflag ) { T[0][pp]=true; }
            else { T[0][pp]=false; }
        }
        for (int ss=1; ss<=s.size(); ss++) { // fill in left column
            T[ss][0]=false;
        }
        for (int ss=1; ss<=s.size(); ss++) { // fill in the rest
            for (int pp=1; pp<=p.size(); pp++) { 
                if ( p.at(pp-1) == '*') { // matches zero or more characters
                    T[ss][pp]=T[ss][pp-1]||T[ss-1][pp];
                }
                else if ( p.at(pp-1) == '?' ) { // matches one character
                    T[ss][pp]=T[ss-1][pp-1];
                }
                else { // p.at(pp-1) is a letter from a to z
                    if ( s.at(ss-1)==p.at(pp-1) ) { T[ss][pp]=T[ss-1][pp-1]; }
                    else { T[ss][pp]=false; }
                }
            }
        }

        
        return T[s.size()][p.size()];
    }
};

