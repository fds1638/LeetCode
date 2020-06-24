#Another Hard problem, with 38.2% acceptance rate as of 23 Jun 2020.
#But even though it has a high acceptance rate, my code is in the 80/90th
#percentile in runtime/ memory usage. Did a BFS.
class Solution(object):
    def kSimilarity(self, A, B):
        """
        :type A: str
        :type B: str
        :rtype: int
        """
        #def getswaps(s):
        #    sswaps=[]
        #    for ii in range(len(s)-1):
        #        for jj in range(ii+1,len(s)):
        #            sswaps.append(s[:ii]+s[jj]+s[ii+1:jj]+s[ii]+s[jj+1:])
        #    return sswaps
        lena=len(A)
        incorrect=[0]*lena
        for ii in range(lena):
            if A[ii]==B[ii]: incorrect[ii]=1
        #print(incorrect)
        # BFS starting at A
        if A==B: return 0
        Q = [A]
        visited = {}
        dist = 0
        #print(getswaps("abcd"))
        while Q:
            q = Q[:]
            Q[:]=[]
            #print(Q,q)
            while q:
                a = q.pop(0)
                #print(visited)
                #print(q,a)
                if a not in visited:
                    visited[a]=1
                    if a == B: 
                        return dist
                    else:
                        kk=0
                        while a[kk]==B[kk]: kk+=1
                        for mm in range(kk+1,lena):
                            if a[kk]==B[mm]: 
                                swap = a[:kk]+a[mm]+a[kk+1:mm]+a[kk]+a[mm+1:]
                                if swap not in visited: Q.append(swap)
            dist+=1
'''                        for ii in range(lena-1):
                            for jj in range(ii+1,lena):
                                swapped = a[:ii]+a[jj]+a[ii+1:jj]+a[ii]+a[jj+1:]
                                if swapped not in visited: Q.append(swapped)
                                #swapped=[]
                                #for kk in range(lena):
                                #    if kk==ii: swapped.append(a[jj])
                                #    elif kk==jj: swapped.append(a[ii])
                                #    else: swapped.append(a[kk])
                                #tswapped=''.join(swapped)
                                #if tswapped not in visited:
                        #            #print(swapped)
                                #    Q.append(tswapped)
                    #print(visited)
                    #print(Q,a)
'''
            #dist += 1
                        #print("dada")
                        #for ii in range(len(a)-1):
                        #    for jj in range(ii+1,len(a)):
                        #        #swapped = a[:ii]+a[jj]+a[ii+1:jj]+a[ii]+a[jj+1:]
                        #        
                        #        #swapped[ii],swapped[jj]=swapped[jj],swapped[ii]
        

