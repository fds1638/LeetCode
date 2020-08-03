// Done August 3 2020
// Solves LeetCode problem 639, Decode Ways II
// https://leetcode.com/problems/decode-ways-ii/
// Difficulty: Hard, success rate 26.6%
// This is similar to another LC dynamic programming problem.
// Gives a string of numbers and asks how many ways can it be decoded
// as a sequence of letters, with A=1, Z=26, etc. The difficulty is in
// handling zeros and the new difficulty of wildcards. Essentially it
// is a straightforward dynamic programming problem.

// This solution is a bit slow, which could have been speeded up with
// some memoization. On the other hand, the memory usage is low.

class Solution {
public:
    int numDecodings(string s) {
        int slen=s.size();
        long use1=0;
        long use2=0;
        long modulus = pow(10,9)+7;
        
        // Since a letter can be encoded by a maximum of two numbers, we need only three
        // values: use1 is the number processed two steps ago; use2 is the number processed
        // last step; use3 is the number currently being processed as we move down the string.
        // First we set up base cases for use1 and use2 in case the string has only one or two
        // characters. Then starting at use3 we use dynamic programming.
        
        if (s[0]=='0') {return 0;} // encoding cannot start with a zero
        if (s[0]=='*') {use1=9;} else {use1=1;} // get initial value of use1
        if (slen==1) {return use1;} // return it if only one character
        
        { // set up initial value for use2
            int two;  // how many ways to interpret as two separate letters
            int combo;// how many ways to interpret as combination (two digit number)
            if (s[0]=='*') {
                if (s[1]>='1' and s[1]<='6') { two=9; combo=2;}
                else if (s[1]>='7' and s[1]<='9') { two=9; combo=1;}
                else if (s[1]=='0') { two=0; combo=2;}
                else if (s[1]=='*') { two=81; combo=15;}
            }
            else if (s[0]=='1' && s[1]=='*') { two=9; combo=9; }
            else if (s[0]=='2' && s[1]=='*') { two=9; combo=6; }
            else if (s[0]>='3' && s[0]<='9' && s[1]=='*') { two=9; combo=0; }
            else if (s[0]>='1' && s[0]<='2' && s[1]=='0') { two=0; combo=1; }
            else if (s[0]>='3' && s[0]<='9' && s[1]=='0') { two=0; combo=0; }
            else if (s[0]>='1' && s[0]<='2' && s[1]>='1' && s[1]<='6') { two=1; combo=1; }
            else if (s[0]>='1' && s[0]<='1' && s[1]>='7' && s[1]<='9') { two=1; combo=1; }
            else if (s[0]>='2' && s[0]<='2' && s[1]>='7' && s[1]<='9') { two=1; combo=0; }
            else if (s[0]>='3' && s[0]<='9' && s[1]>='1' && s[1]<='9') { two=1; combo=0; }
            else {std::cout<<"Error use2"<<endl;}
            use2 = two + combo;
        }
        if (slen==2) {return use2;} //return it if only two characters
        
        long use3;  //get ready to start dynamic programming
        for (int ii=2; ii<slen; ii++) {
            int alone;  // how many ways to interpret as two separate letters
            int combo;  // how many ways to interpret as combination (two digit number)

            if (s[ii]=='*') {alone=9;}
            else if (s[ii]>='1' && s[ii]<='9') {alone=1;}
            else if (s[ii]=='0') {alone=0;}
            else { std::cout<<"Error alone"<<endl;}
            
            if (s[ii-1]=='*') {
                if (s[ii]>='1' and s[ii]<='6') { combo=2;}
                else if (s[ii]>='7' and s[ii]<='9') { combo=1;}
                else if (s[ii]=='0') { combo=2;}
                else if (s[ii]=='*') { combo=15;}
            }
            else if (s[ii-1]=='1' && s[ii]=='*') { combo=9; }
            else if (s[ii-1]=='2' && s[ii]=='*') { combo=6; }
            else if (s[ii-1]>='3' && s[ii-1]<='9' && s[ii]=='*') { combo=0; }
            else if (s[ii-1]>='1' && s[ii-1]<='2' && s[ii]=='0') { combo=1; }
            else if (s[ii-1]>='3' && s[ii-1]<='9' && s[ii]=='0') { combo=0; }
            else if (s[ii-1]>='1' && s[ii-1]<='2' && s[ii]>='1' && s[ii]<='6') { combo=1; }
            else if (s[ii-1]>='1' && s[ii-1]<='1' && s[ii]>='7' && s[ii]<='9') { combo=1; }
            else if (s[ii-1]>='2' && s[ii-1]<='2' && s[ii]>='7' && s[ii]<='9') { combo=0; }
            else if (s[ii-1]>='3' && s[ii-1]<='9' && s[ii]>='1' && s[ii]<='9') { combo=0; }
            else if (s[ii-1]>='0') { combo=0; }
            else {std::cout<<"Error combo"<<endl;}
            use3 = (use1*combo)%modulus + (use2*alone)%modulus;
            use3 = use3%modulus;
            use1 = use2%modulus;
            use2 = use3%modulus;
        }
        int retval = use3;
        return use3;
    }
};

