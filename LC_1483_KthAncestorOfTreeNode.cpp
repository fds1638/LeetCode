// July 25 2020
// Solves Leet Code 1483, Kth Ancestor of a Tree Node
// https://leetcode.com/problems/kth-ancestor-of-a-tree-node/
// Hard problem, 27.3% solve rate.
// In this problem I learned about binary lifting.
// I started it using vectors before I had fully understood the algorithm,
// so it is very slow. It could be done more quickly using arrays, since
// the dynamic nature of vectors is unnecessary.

class TreeAncestor {
public: std::vector<vector<int>> binlift;

public:
    TreeAncestor(int n, vector<int>& parent) {
        // set up the binary lifting table
        for (int jj=0; jj<n; jj++) {
            binlift.push_back({0});
            binlift.at(jj).at(0)=parent.at(jj);
        }
        for (int kk=-1; kk<log2(n)-1; kk++) {
            binlift.at(0).push_back(-1);
        }
        for (int jj=1; jj<n; jj++) {
            int kk=0;
            do {
                kk++;
                binlift.at(jj).push_back(binlift.at(binlift.at(jj).at(kk-1)).at(kk-1));
            } while ( binlift.at(binlift.at(jj).at(kk-1)).at(kk-1)!=-1 );
            while ( kk<log2(n)) {
                kk++;
                binlift.at(jj).push_back(-1);
                
            }
        }

    }
    
    int getKthAncestor(int node, int k) {
        int ii=0;
        while (ii<binlift.at(node).size() && binlift.at(node).at(ii)!=-1) { ii++;}
        ii--;   // ii is now index of the last non-neg-one entry
        
        if (k>pow(2, ii+1)) {return -1;} // too large a jump
        
        // set up binary value of k, which is vector kbin
        int retval=node;
        std::vector<int> kbin(log2(k)+1,0);
        int krem=k;
        for (int kk=kbin.size()-1; kk>=0; kk--) {
            int p2=pow(2,kk);
            kbin.at(kbin.size()-1-kk)=krem/p2;
            krem=krem%p2;
        }
        
        //use kbin to specify which jumps to make in binlift table
        int kk=0;
        while (kk<kbin.size() && retval!=-1) {
            if ( kbin.at(kk)==1 ) { 
                retval = binlift.at(retval).at( kbin.size()-1-kk );
            }
            kk++;
        }

        return retval;
    }
};

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */

 
