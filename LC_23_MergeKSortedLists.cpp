// done 08 Oct 2020
// solves Leet Code 23, Merge K Sorted Lists
// https://leetcode.com/problems/merge-k-sorted-lists/
// Difficulty: Hard

// Given K sorted lists in a vector, merge them.

// Another "Hard" problem that wasn't too hard. Make a min heap of the
// current values in each list and attach the min value to the linked list
// return value. I actually haven't done too much with linked lists, so
// this was a good problem to do.

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    static bool compare(ListNode* l1, ListNode* l2) {
        if (l1->val<=l2->val) { return false;}
        return true;
    }
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // Big idea: create a heap and take the next one.
        // Heap is a min heap, so use compare to force min heap rather than max heap.
        
        // This section takes care of some corner-case null issues.
        // If just given an empty list, return nullptr.
        if (lists.size()==0) { return nullptr; }
        // Get rid of all vectors that have no elements.
        int ii=0;
        while (ii<lists.size()) {
            if (!lists[ii]) {lists.erase(lists.begin()+ii);ii--;}
            ii++;
        }
        // One more time return nullptr if empty list.
        if (lists.size()==0) { return nullptr; }
        
        // Create the heap.
        make_heap(lists.begin(), lists.end(), compare);
        
        // Initialize return value retval and create dummy to help create new nodes.
        ListNode* retval;
        int listsleft = lists.size();
        retval = new ListNode(lists[0]->val);
        ListNode* dummy = new ListNode(0);
        if (listsleft>1||lists[0]->next) {retval->next = dummy;}
        
        // Every time I come to the end of one of the linked lists, I decrement
        // the numbers of lists I have left. Go while I still have lists left.
        while (listsleft) {
            bool haveheap = false;
            if ( lists[0]->next ){
                lists[0]=lists[0]->next;
            } else {
                pop_heap(lists.begin(), lists.end(), compare);
                lists.pop_back();
                listsleft--;
                haveheap = true; // if I've run pop_heap, I now have a heap
            }
            // If I haven't run pop_heap, that means I have simply incremented
            // along one list, so I need to make the heap again.
            if (!haveheap) {make_heap(lists.begin(), lists.end(), compare);}

            // Give dummy a value and create a new node if either
            // I have another node on this list or I have another list to go to.
            dummy->val = lists[0]->val;
            if (listsleft>1||lists[0]->next) {
                dummy->next = new ListNode();
                dummy = dummy->next;             
            } 
        }
        return retval;
    }
};


