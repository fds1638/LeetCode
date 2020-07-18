// July 18 2020
// Solves LeetCode Regular Expression Matching
// https://leetcode.com/problems/regular-expression-matching/
// Used the dynamic programming algorithm.
class Solution {
public:
    bool isMatch(string s, string p) {    
        if ( p.compare(".*")==0) { return true;}
        if ( s.size()>0 && p.size()==0) { return false;}
        if ( s.size()==0 && p.size()==0) { return true;}
        
        bool T[s.size()+1][p.size()+1];
        int starflag=p.find('*');
        T[s.size()][p.size()]=true;
        //std::cout << "starflag " << starflag << endl;
        //std::cout << "T[s.size()][p.size()] " << T[s.size()][p.size()] << endl;
        T[0][0]=true;
        for (int jj=1; jj<=p.size()-1; jj++) {
            if ( p.at(jj-1)=='*' || p.at(jj)=='*' ) {T[0][jj]=T[0][jj-1];}
            else { T[0][jj]=false;}
        }
        if (p.size()>=1) {
            if ( p.at(p.size()-1)=='*' ) {T[0][p.size()]=T[0][p.size()-1];}
            else { T[0][p.size()]=false;}
        }
        
        //std::cout << "starflag " << starflag << endl;
        for (int ii=1; ii<=s.size(); ii++) {
            T[ii][0]=false;
        }

        
        
        for (int ss=1; ss<=s.size(); ss++) {
            for (int pp=1; pp<=p.size(); pp++) {
                if ( s.at(ss-1)==p.at(pp-1) || p.at(pp-1)=='.') { T[ss][pp]=T[ss-1][pp-1];}
                else if (p.at(pp-1)=='*') {
                    if ( s.at(ss-1)==p.at(pp-2) || p.at(pp-2)=='.') { T[ss][pp]=T[ss-1][pp]||T[ss][pp-2];}
                    else { T[ss][pp]=T[ss][pp-2];}
                }
                else {
                    T[ss][pp] = false;
                }
            }
        }

        // If I want to see the table.
        //for (int ss=0; ss<=s.size(); ss++) {
        //    for (int pp=0; pp<=p.size(); pp++) {
        //        std::cout << T[ss][pp] << " ";
        //    }
        //    std::cout << endl;
        //}

        return T[s.size()][p.size()];
     }
};



