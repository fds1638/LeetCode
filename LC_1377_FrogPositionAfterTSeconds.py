// done 26 sep 2020
// solves Leet Code 1377, Frog Position After T Seconds
// https://leetcode.com/problems/frog-position-after-t-seconds/
// Difficulty: Hard

// This solution is faster than 100% of other Python solutions, although
// it is towards the bottom when it comes to using less memory.

// The problem gives you a tree with a frog on it, and asks what the probability
// is for the frog to end up at a given node if it moves randomly. Overall it is
// pretty straightforward, the difficulty being that the frog must move if it can,
// and so the question becomes whether the frog is at the right place at the right
// time, and with what probability.

class Solution(object):
    def frogPosition(self, n, edges, t, target):
        """
        :type n: int
        :type edges: List[List[int]]
        :type t: int
        :type target: int
        :rtype: float
        """
        # Create an adjacency list.
        # Note that edges are undirected but we always start from node 1.
        # This means that for node 1 all the nodes in its adjacency list
        # are its "children," while for all other nodes there is one node
        # which is its parent.
        adj = [[] for _ in range(n)]
        for ee in edges:
            adj[ee[0]-1].append(ee[1])
            adj[ee[1]-1].append(ee[0])
        
        # dfs includes: current node, current probability (not taking time into
        # account), and current time.
        # visited is set of visited nodes, so that frog can't try to go back to
        # a parent.
        dfs = []
        dfs.append([1,1.0,0])
        visited = {1}
        while True:
            curnode, curprob, time = dfs.pop()
            # check if the current node is the target
            if curnode==target: 
                # We have two possibilities for a non-zero solution:
                # 1: arrived at the target node just in time
                # 2: arrived at the target node too soon.
                # Number 2 breaks down into two further possibilities
                # 2a: we are at a leaf node and can just stay here until right t
                # 2b: we are at a root node and there are no edges from root node
                # The commonality between 2a and 2b is that we are at the target node
                # but can't go anywhere else so can just stay here until time.
                # The difference is in the condition of not being able to go elsewhere:
                # for any other node to be a leaf means only one in its adjacency list
                # (its parent), but for node 1 it means nothing in its adjacency list.
                if time==t or (curnode!=1 and len(adj[curnode-1])==1 and time<=t) or (curnode==1 and len(adj[curnode-1])==0 ):
                    return curprob
                else:
                    return 0
            # We're not at the target, so put all children of current node in dfs.
            # Adjust the childcount for whether or not are at node 1 in order to 
            # compute conditional probabilities for this step.
            if curnode==1 or len(adj[curnode-1])>1:
                childcount = len(adj[curnode-1])
                if not curnode==1: childcount = childcount-1
                childprob = 1.0/( childcount )
                for child in adj[curnode-1]:
                    if child not in visited:
                        dfs.append([child,curprob*childprob,time+1])
                        visited.add(child)
        return -1
                


