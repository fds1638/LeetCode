// done 15 Oct 2020
// solves Leet Code 1224, Maximum Equal Frequency
// https://leetcode.com/problems/maximum-equal-frequency/
// difficulty: Hard

// I was just trying this solution to see if I understood the problem, and it ended up
// being fast enough to pass all testcases, though only at about the 20th percentile of speed.

class Solution {
public:
    int maxEqualFreq(vector<int>& nums) {
        // The map numtocount tells you the count of each number, e.g. three 2's or two 5's.
        // The map countofcounts tells you, e.g., that there were four number which appeared
        // twice.
        // The idea is to pass through the vector once going forwards to get these counts.
        // Then coming backwards remove the numbers one by one and check if it satisfies
        // the solution requirement.
        map<int,int> numtocount;
        map<int,int> countofcounts;
        for (int ii=0; ii<nums.size(); ii++) {
            numtocount[nums[ii]]++;
            countofcounts[numtocount[nums[ii]]]++;
            if (numtocount[nums[ii]]!=1) {
                countofcounts[numtocount[nums[ii]]-1]--;
            }
        }
        map<int,int>::iterator nn;
        map<int,int>::iterator cc;

        // Before we take any numbers off, see if nums itself satisifies the solution.
        // This can happen in one of four ways:
        // - there is one number with a count one more than the other numbers
        // - all the numbers have one count and there is one number with a count of 1
        // - every number appears once (this is like the one above in a way )
        // - only one number appears
        // These last two were combined into one if statement below.
        int nz = 0;
        int fn = 0;
        int fv = 0;
        int sn = 0;
        int sv = 0;
        for (cc=countofcounts.begin(); cc!=countofcounts.end(); cc++) {
            if (cc->second!=0) {
                if (nz==0) { nz++; fn=cc->first; fv = cc->second; }
                else if (nz==1) { nz++; sn=cc->first; sv = cc->second; }
                else {nz++;}
            }
        }
        if (nz==2&&sn==fn+1&&sv==1) {return nums.size();}
        if (nz==2&&fn==1&&fv==1) {return nums.size();}
        if (nz==1&&(fn==1||fv==1)) { return nums.size(); }
         
        // Repeat the code above while removing numbers from the back one-by-one.
        for (int ii=nums.size()-1; ii>=0; ii--) {
            numtocount[nums[ii]]--;
            if (numtocount[nums[ii]]!=0) {countofcounts[numtocount[nums[ii]]]++;}
            countofcounts[numtocount[nums[ii]]+1]--;
            int nonzeros = 0;   // number of nonzero counts
            int firstnon = 0;   // the first nonzero count 
            int firstval = 0;   // the number of numbers with that first nonzero count
            int secnon = 0;     // the second nonzero count
            int secval = 0;     // the number of numbers with that second nonzero count
            for (cc=countofcounts.begin(); cc!=countofcounts.end(); cc++) {
                if (cc->second!=0) {
                    if (nonzeros==0) { nonzeros++; firstnon=cc->first; firstval = cc->second;}
                    else if (nonzeros==1) { nonzeros++; secnon=cc->first; secval = cc->second; }
                    else {nonzeros++;}
                }
            }
            if (nonzeros==2&&secnon==firstnon+1&&secval==1) { return ii; }
            if (nonzeros==2&&firstnon==1&&firstval==1) { return ii; }
            if (nonzeros==1&&(firstnon==1||firstval==1)) { return nums.size(); }
        }
        // If there are 2 numbers left, it works for sure.
        return 2;
    }
};


