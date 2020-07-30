// Done July 30 2020
// Solves LeetCode problem 321, Create Maximum Number
// https://leetcode.com/problems/create-maximum-number/
// Difficulty: Hard, success rate 27.0%
// Given two vectors of integers, use them to create a decimal with number of digits k.
// Want to maximize k, but must use digits in order they appear in each vector.

class Solution {
// Break up the question into several sub-questions.
// If want k digits, need p from first vector nums1 and k-p from second vector nums2.
// Knowing how many digits you want from a vector, used bigDec to get the biggest
// decimal you can from that vector.
// Now that you have the two vectors of digits, one from each of nums1 and nums2,
// combine them together as if they were stacks, always taking the bigger available digit.
// If there is a tie, look ahead to break the tie.
private:    
    vector<int> bigDec (vector<int> nums, int k) {
        vector<int> retval;
        if (k==0) { return retval; }
        int nlen = nums.size();
        if ( k==nlen ) { return nums; }
        int offbeg=0;
        int offend=k-1;
        // offend is the key idea: if you want 4 digits out of a possible 9,
        // then your first digit will be the max of the first 6 digits, because you have to leave
        // at least 3 digits in reserve to complete the 4. Then for the second digit, you maximize
        // similarly starting at the first digit after the one you just took. If you need m more digits
        // and there are m digits left, take them all.
        for (int ii=1; ii<=k; ii++) {
            int maxnum = *max_element( nums.begin()+offbeg, nums.end()-offend );
            retval.push_back(maxnum);
            auto it = find(nums.begin()+offbeg, nums.end()-offend, maxnum);
            offbeg = distance(nums.begin(), it)+1;
            offend--;
            if ( offbeg == nlen-offend ) {
                for (int jj=offbeg; jj<nlen; jj++) { retval.push_back(nums[jj]); }
            }
        }
        return retval;
    }
    
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<int> candidates;
        int n1size = nums1.size();
        int n2size = nums2.size();
        vector<int> vcombmax;
        string vcombstrmax (k,'0');
        for (int ii=0; ii<=k; ii++) {  // loop through all possibilities of taking ii from nums1 and k-ii from nums2
            int l1 = ii;
            int l2 = k-ii;
            vector<int> vcomb;
            long long vcombnum=0;
            if (l1<=n1size && l2<=n2size) {
                vector<int> v1 = bigDec (nums1, l1); // here have the two vectors of digits for given ii
                vector<int> v2 = bigDec (nums2, l2); // start to combine them below
                int v1size = v1.size();
                int v2size = v2.size();
                int i1=0;
                int i2=0;
                while ( i1<v1size || i2<v2size ) { // keep going until all digits used
                    if (i1==v1size) {  // if reached the end of one, use the other
                        vcomb.push_back(v2[i2]); 
                        i2++; 
                    }
                    else if (i2==v2size) { vcomb.push_back(v1[i1]); i1++;}
                    else {    // neither v1 nor v2 exhausted yet
                        if (v1[i1]>v2[i2]) { vcomb.push_back(v1[i1]); i1++; } // take larger
                        else if (v1[i1]<v2[i2]) { vcomb.push_back(v2[i2]); i2++; } // take larger
                        else if (v1[i1]==v2[i2]) { // this is all the tiebreaker
                            int j1=0;
                            int j2=0;
                            int changemade=0;
                            while (i1+j1<v1size && i2+j2<v2size && changemade==0) {
                                if (v1[i1+j1]>v2[i2+j2]) { vcomb.push_back(v1[i1]); i1++; changemade=1; break;}
                                if (v1[i1+j1]<v2[i2+j2]) { vcomb.push_back(v2[i2]); i2++; changemade=1; break;}
                                j1++;
                                j2++;
                            }
                            if ( i1+j1==v1size && changemade==0) { vcomb.push_back(v2[i2]); i2++; }
                            else if ( i2+j2==v2size && changemade==0) { vcomb.push_back(v1[i1]); i1++; }
                        }
                        
                    }
                    
                }        
            }
            // now have our vector for this value of ii, need to check if it's a max over all ii
            // use a string to do this
            string vcombstr="";
            for (int ij=0; ij<vcomb.size(); ij++) { 
                vcombstr+=to_string(vcomb[ij]); 
            } 
            if ( vcombstr.compare(vcombstrmax)>0 ) { vcombstrmax = vcombstr; vcombmax = vcomb; }
        }
        return vcombmax;
    }
};


