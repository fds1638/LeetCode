// Done August 10 2020
// Solves Leet Code 902, Numbers At Most N Given Digit Set
// https://leetcode.com/problems/numbers-at-most-n-given-digit-set/
// Difficulty: Hard, success rate 31.5%

// This solution I didn't really use dynamic programming. It is a
// fast solution (faster than 100% of solutions in c++, whatever
// that means), though it uses more memory than most (in the lower
// quartile). 

// Basically, just process the digits one by one.

class Solution {
public:
    int atMostNGivenDigitSet(vector<string>& D, int N) {
        int dlen = D.size();
        int pow10 = floor(log10(N));
        int count = 0;
        // If N is greater than 10^p, then for all numbers with fewer
        // digits than N has, can take any combination of digits from D.
        // E.g. if have four available digits, can make 4^1=4 one-digit
        // numbers and 4^2=16 two-digit numbers, etc.
        for (int ii=0; ii<pow10; ii++) { count += pow(dlen,ii+1); }
        // Now start to deal with not being able to use all digits in 
        // D as the first digit.
        for (int ii=pow10; ii>=0; ii--) {
            int nextdig = N/pow(10,pow10);
            int available = 0;
            int cont = 0;
            // available tells me how many digits I can use in the first slot,
            // generally it is all the digits less than nextdig.
            // cont is for continue: if I have no digits less than nextdig then
            // I can't create any more numbers.
            // Note: if we are on the last digit, want to make available the 
            // case of a number in D equalling nextdig.
            for (int jj=0; jj<dlen; jj++) { 
                if (stoi(D[jj])<nextdig) {available++;} 
                if (stoi(D[jj])==nextdig) {cont=1; if (pow10==0) {available++;}} 
            }
            count += available*pow(dlen,ii);
            if (cont==0) break;
            N = N - nextdig*pow(10,pow10);
            pow10-=1;
        }
        return count;
    }
};


