// done 26 sep 2020
// solves Leet Code 968 Binary Tree Cameras
// https://leetcode.com/problems/binary-tree-cameras/
// Difficulty: Hard

// Given a binary tree and cameras each of which can "see"
// themselves as well as all neighboring nodes, find the 
// minimum number of cameras needed to cover the tree. This is
// a dynamic programming problem on a tree.

// Solution is top quarter in speed, but uses a lot of space.

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def subtreeCover(self, curnode, depth):
        # Return values:
        # count is count of cameras in this subtree
        # used=1 if a camera was put on this node, used=0 if not
        # dist is
        # distance to next camera if used=1
        # distance to first camera if used=0
        
        # No need to place a camera on a leaf, can always
        # place the camera one level up.
        if not curnode.left and not curnode.right:
            return 0, 0, sys.maxint

        # The next two sections mirror each other. One is
        # for when there is a left subtree but not a right,
        # the other for the opposite case.
        # General idea: if the child does not have a camera,
        # then place a camera. If the child does have a camera,
        # look to see how far the next camera is to see if the
        # child's camera can be moved up the tree.
        elif curnode.left and not curnode.right:
            count, used, dist = self.subtreeCover(curnode.left, depth+1)
            # If the child doesn't have a camera then place one,
            # updating the distance to the next camera if it isn't
            # already "infinite."
            if used==0: 
                if dist==sys.maxint:
                    return count+1, 1, dist
                else:
                    return count+1, 1, dist+1 
            # If the child does have a camera and the distance to
            # the next camera is <=2, then can move the child's camera
            # up and still have coverage. Thus this node would have
            # a camera but the number of cameras doesn't change.
            # Else, if can't move child's camera, no need to place
            # a camera here.
            else: #child used
                if dist<=2: #can move it
                    if dist==sys.maxint:
                        return count, 1, dist
                    else:
                        return count, 1, dist+1
                else: #cannot move it
                    return count, 0, 1
        # This is the mirror image of the above code.
        elif not curnode.left and curnode.right:
            count, used, dist = self.subtreeCover(curnode.right, depth+1)
            if used==0: # child not used
                if dist==sys.maxint:
                    return count+1, 1, dist
                else:
                    return count+1, 1, dist+1  
            else: #child used
                if dist<=2: #can move it
                    if dist==sys.maxint:
                        return count, 1, dist
                    else:
                        return count, 1, dist+1
                else: #cannot move it
                    return count, 0, 1
        # Now we have both a left subtree and a right subtree.
        # Reasoning is similar to that for the above cases of just
        # one subtree, but just considering the distances down both
        # subtrees.
        else:
            cl, ul, dl = self.subtreeCover(curnode.left, depth+1)
            cr, ur, dr = self.subtreeCover(curnode.right, depth+1)
            # If neither child has a camera, put one here.
            if ul==0 and ur==0: 
                if max(dl,dr)==sys.maxint:
                    return cl+cr+1, 1, sys.maxint
                else:
                    return cl+cr+1, 1, max(dl,dr)+1
            # Next two sections: one child has a camera but the other
            # not. If the camera can be moved up, do so. If not, then
            # no need to place a camera here.
            elif ul==0 and ur!=0:  #right child has camera
                if dr<=2: #can move right child's camera up
                    return cl+cr, 1, max(dl,dr)+1
                else:   # cannot move right child's camera up
                    if dl<=2:   #left child's is close enough to cover 
                        return cl+cr,0,1   
                    else:       #must place a camera here and cannot move it
                        return cl+cr+1,1,sys.maxint
            elif ul!=0 and ur==0: #left child has camera
                if dl<=2: #can move left child's camera up
                    return cl+cr, 1, max(dl,dr)+1
                else:   # cannot move left child's camera up
                    if dr<=2:   #right child's is close enough to cover
                        return cl+cr,0,1 
                    else:       #must place a camera here and cannot move it
                        return cl+cr+1,1,sys.maxint
            else: #both children have cameras
                if dl<=2 and dr<=2: #can move both
                    # camera at this node can replace cameras of both children
                    return cl+cr-1, 1, max(dl,dr)+1
                elif dl<=2 and dr>2: #can move left camera up so no increase in count
                    return cl+cr, 1, dr+1
                elif dl>2 and dr<=2: #can move right camera up so no increase in count
                    return cl+cr, 1, dl+1
                else: #cannot move either camera up, no need to place a camera here
                    return cl+cr, 0, 1   #if both used no need to add

        return 1,0,0 # dummy return value that should never be reached

    def minCameraCover(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        # address some simple cases first
        if not root: return 0
        if not root.left and not root.right: return 1
        # Work from the leaves to the root recursively.
        count, used, dist = self.subtreeCover(root,0)
        return count
        


