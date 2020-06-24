#Another Hard problem, with only about 32% of submissions accepted.
#This is a question about directed graphs, asking which edge can be removed
#to leave only a tree (i.e. no cycle).
#Did a DFS to find cycles.
class Solution(object):
    def findRedundantDirectedConnection(self, edges):
        """
        :type edges: List[List[int]]
        :rtype: List[int]
        """
        def findloop(edges, visited, start): #return true if loop found
            #print ("edges",edges,"start",start)
            lene = len(edges)
            # if have no visited yet, add starting spot
            if len(visited)==0: visited.append(edges[start][0])
            # check if origin of edges[start] is last visited
            if edges[start][0]==visited[-1]:
                # check if destination of edges[start] has not been visited
                if edges[start][1] in visited: 
                    return True
                visited.append(edges[start][1])
                #print ("visited", visited)
                for ii in range(lene-1): #how to loop through all edges not start
                    if findloop(edges[:start] + edges[start+1 :],visited,ii): 
                        #print("returning True")
                        return True
            #print("returning False")
            return False
                    
        
        lasts=[] #get a list of destination of edges
        firsts=[] #get. list of origins of edges
        lenn = len(edges)
        for ii in range(lenn):
            lasts.append(edges[ii][1])
            firsts.append(edges[ii][0])
        #print lasts
        #print firsts
        
        # get a list of indices of edges 
        # which lead to the same node
        lastdupes = []
        for ii in range(lenn-1,-1,-1):
            #print (ii,lasts[ii])
            rump = lasts[:ii] + lasts[ii+1 :]
            #print (rump, lasts)
            if lasts[ii] in rump: lastdupes.append(ii)
        #print lastdupes
        
        for jj in lastdupes:
            #print("in here")
            wout = edges[:jj] + edges[jj+1 :]
            if not(findloop(wout,[],0)): 
                #print("returning that")
                return edges[jj]
            #return wout
            #print jj
        
        # there are no nodes with two edges pointing in
        # so start at the last node and see if removing 
        # an edge means there is no loop 
        for kk in range(lenn-1,-1,-1):
            if not(findloop(edges[:kk] + edges[kk+1 :],[],0)): 
                #print("returning this")
                return edges[kk]
        
        return [] #if the edges are fine as-is

