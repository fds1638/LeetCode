// Done July 29 2020
// Solves LeetCode problem 214, Shortest Palindrome
// https://leetcode.com/problems/shortest-palindrome/
// Difficulty: Hard, 29.7% solution rate
// Given a string, find the shortest palindrome that can be created
// by prefixing letters to the string.

class Solution {
public:
    string shortestPalindrome(string s) {
        int slen=s.size();
        if ( slen==0 ) { return ""; } 
        
        //want to find shortest palindrom within s
        //which includes the left-most letter
        //use palstrb and palstre to find it (don't really need palstrb)
        //palestre is s in reverse, so looking for match between
        //palestrb and palestre is looking for palindrome within s
        string palstrb=s;
        string palstre=s;
        reverse(palstre.begin(), palstre.end());
        
        // use a KMP-like algorithm
        // try to match up palstrb moving starting point along palstre
        // until get a match (however short, at least 1 obviously)
        // which goes to the end of palestre
        int ii=0;           //goes back to beginning of palestrb
        int curstart=0;     //current starting point on palestre
        int newstart=0;     //next starting point on palestre
        int matchrange=0;   //keep track of length of match which can skip
        int inrange=0;      //flag of am I tracking a match or not
        while ( ii+curstart<slen ){
            inrange=0;
            while ( ii+curstart<slen && palstrb.at(ii)==palstre.at(ii+curstart)  ) {
                if ( ii>0 ) { 
                    //this is the KMP part, finding a stretch up ahead that
                    //also matches the beginning of palstrb
                    if ( inrange==0 ) { newstart=ii+curstart; inrange=1; }
                    else { matchrange++; }                    
                }
                ii++;
            }
            if (ii+curstart<slen) { //if hadn't reached the end, jump ahead
                if ( newstart>curstart) { curstart = newstart+matchrange; } else { curstart++;}
                ii=0;
            }
        }
        
        //now have longest palindrome in s which includes first letter
        //need to add the remaining letters as a prefix to s and return it
        string retval="";
        for (int ij=0; ij<curstart; ij++) { retval+=palstre.at(ij);}
        retval+=s;
        return retval;
    }
};

