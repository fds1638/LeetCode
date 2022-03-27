class Solution {
private:
    // a struct to be able to sort in descending order
    struct myclass {
      bool operator() (int i,int j) { return (i>j);}
    } myobject;
    
    int recursiveRP(vector<int>& nums, int lo, int hi){
        // Working on interval [lo,hi), ie inclusive of lo and exclusive of hi.
        // If only one element, return 0.
        if ( lo+1==hi ) return 0;
        
        // Split into two parts and recursively get counts for each sub-interval.
        int mid = (lo+hi)/2;
        int locount = recursiveRP(nums,lo,mid);
        int hicount = recursiveRP(nums,mid,hi);
        
        // Now sort left and right sub-intervals descending order separately.
        // This allows O(n) check to see if a reverse pair exists with one element
        // in left sub-interval and one element in right sub-interval.
        sort(nums.begin()+lo,nums.begin()+mid,myobject);
        sort(nums.begin()+mid,nums.begin()+hi,myobject);
        int dd = max(mid-1,lo); // index of element in left sub-interval
        int thismerge = 0;      // count
        for (int ss=hi-1; ss>=mid; ss--){ // ss is index of element in right sub-interval
            long numsdd = dd>=lo?nums[dd]:0; // use longs to avoid overflow
            long numsss = nums[ss];
            while ( dd>=lo && numsdd<=2*numsss ){
                dd--; // when the next ss comes, never need to backtrack on dd b/c of sorting
                numsdd = dd>=lo?nums[dd]:0;
                numsss = nums[ss];
            }
            thismerge += dd-lo+1; // all elements between dd and lo form a reverse pair with current ss
        }
        return thismerge+locount+hicount;
    }
public:
    int reversePairs(vector<int>& nums) {
        // runtime = 559sm, which is 55th percentile
        // memory usage = 45MB, which is 95th percentile
        
        // Strategy: merge sort. 
        return recursiveRP(nums,0,nums.size());
    }
};