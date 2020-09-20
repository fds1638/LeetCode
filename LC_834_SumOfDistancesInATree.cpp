// done 20 Sep 2020
// solves Leet Code 834 Sum Of Distances In A Tree
// https://leetcode.com/problems/sum-of-distances-in-tree/
// Difficulty: Hard

// Given a tree defined by a list of edges, return a vector with 
// each entry being the sum of distances from that node to all other
// nodes.

// Aargh. I was close to getting this without a hint, but needed the hint to
// try two passes dfs. 

// Idea 1: if I consider two adjacent nodes, the edge between them divides the tree in two.
// If one of the nodes has already the sum of all the distances to all the other nodes on its
// "half" of the tree and I know how many nodes are in that half, then I can find that half's
// contribution to the return value of the second node by summing those two numbers together.
// Idea 2: If you do two dfs passes, then on the first one you can get numbers of nodes and 
// distances in subtrees (going up), and on the second dfs you can the numbers of nodes and distances
// (going down). In each pass you're applying Idea 1. At whatever node you choose to be the 
// "root" of your tree, you'll have to account for information coming from multiple directions
// in the first dfs pass, and send the correct information down into each subtree for the second pass.

class Solution {
public:
    pair<int,int> firstdfs(int curnode, set<int>& visited, map<int, vector<int> >& adj, vector<int>& retval, vector<int>& nodes,vector<int>& distup) {
        // on the way back up the dfs, returns a pair
        // first is the total distance from root of subtree
        // second is the number of nodes in subtree
        // cout<<"dfs at "<<curnode<<endl;
        visited.insert(curnode);
        int sumofdist = 0;
        int numnodes = 0;
        for (int ii=0; ii<adj[curnode].size(); ii++) {
            if (visited.find(adj[curnode][ii])==visited.end()) {
                pair<int,int> current = firstdfs(adj[curnode][ii], visited, adj, retval,nodes, distup);
                retval[curnode]+=current.first;
                sumofdist += current.first+current.second;
                numnodes += current.second;
            }
        }
        
        sumofdist++;
        numnodes++;
        distup[curnode]+=sumofdist;
        nodes[curnode]+=numnodes;
        return {sumofdist,numnodes};
    }
public:
    void seconddfs(int curnode, set<int>& visited, map<int, vector<int> >& adj, vector<int>& retval, vector<int>& nodes,vector<int>& distup, pair<int,int> parent) {
        //cout<<"curnode "<<curnode<<" parent.first "<<parent.first<<" parent.second "<<parent.second<<endl;
        parent.first = parent.first+parent.second;
        parent.second +=  nodes[curnode];
        retval[curnode]+=parent.first;
        parent.first = retval[curnode];
        visited.insert(curnode);
        for (int ii=0; ii<adj[curnode].size(); ii++) {
            if (visited.find(adj[curnode][ii])==visited.end()) {
                int thisfirst = parent.first - distup[adj[curnode][ii]];
                int thissecond = parent.second - nodes[adj[curnode][ii]] ;
                seconddfs(adj[curnode][ii], visited,  adj,  retval, nodes, distup,{thisfirst,thissecond});
            }
        }
        
        //sumofdist++;
        //numnodes++;
        return;
        
    
    }
public:
    vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges) {
        if (edges.size()==0) {return {0};}
        // create adjacency map
        std::map<int, vector<int> > adj;
        for (int ee=0; ee<edges.size(); ee++) {
            adj[edges[ee][0]].push_back(edges[ee][1]);
            adj[edges[ee][1]].push_back(edges[ee][0]);
        }
        set<int> visited;
        visited.insert(0);
        vector<int> retval(N, 0);   // cumulative distances 
        vector<int> nodes(N, 0);   // cumulative distances 
        vector<int> distup(N, 0);   // cumulative distances 
        vector< pair<int,int> > seconds;
        for (int ii=0; ii<adj[0].size(); ii++) {
            pair<int,int> zeronode = firstdfs(adj[0][ii], visited, adj, retval, nodes, distup);
            //cout<<"distances "<<zeronode.first<<" count "<<zeronode.second<<endl;
            seconds.push_back(zeronode);
            retval[0]+=zeronode.first;
        }
        /*
        cout<<"retval: ";
        for (int nn=0; nn<N; nn++) {
            cout<<retval[nn]<<" ";
        }
        cout<<endl;
        cout<<"nodes: ";
        for (int nn=0; nn<N; nn++) {
            cout<<nodes[nn]<<" ";
        }
        cout<<endl;
        cout<<"distup: ";
        for (int nn=0; nn<N; nn++) {
            cout<<distup[nn]<<" ";
        }
        cout<<endl;
        */
        visited.clear();
        visited.insert(0);
        for (int ii=0; ii<adj[0].size(); ii++) {
            seconds[ii].first = retval[0]-seconds[ii].first;
            seconds[ii].second = N-seconds[ii].second;
            seconddfs(adj[0][ii], visited,  adj,  retval, nodes, distup, seconds[ii]);
        }

        return retval;
    }
};


