/*
Given a binary tree, you are supposed to tell if it is a binary search tree. 
If the answer is yes, try to find the KK-th largest key, else try to find the height of the tree.
The function CheckBST is supposed to return the K-th largest key if T is a binary search tree; 
or if not, return the negative height of T (for example, if the height is 5, you must return −5).
Here the height of a leaf node is defined to be 1. 
T is not empty and all its keys are positive integers. 
K is positive and is never more than the total number of nodes in the tree.

**judge a tree is a Binary Search Tree or not, and calculate its height by recursion**
**to find the k-th largest node, spread it to an array or a stack is easy**
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct TNode *BinTree;
struct TNode{
    int Key;
    BinTree Left;
    BinTree Right;
};

BinTree BuildTree(); /* details omitted */
int CheckBST ( BinTree T, int K );

int main()
{
    BinTree T;
    int K, out;

    T = BuildTree();
    scanf("%d", &K);
    out = CheckBST(T, K);
    if ( out < 0 )
        printf("No.  Height = %d\n", -out);
    else
        printf("Yes.  Key = %d\n", out);

    return 0;
}

BinTree BuildTree()
{
    BinTree haha = NULL;
    char temp;
    int size = sizeof(struct TNode);

    scanf("%c", &temp);
    if(temp != '#'){
        haha = (BinTree)malloc(size);
        haha -> Key = temp;
        haha -> Left = BuildTree();
        haha -> Right = BuildTree();
    }
    return haha;
}

struct StackRecord{
    int Keys[100];
    int sp;
};
typedef struct StackRecord* stack;

int isBST(BinTree T, stack S);
int find(BinTree T, int K, stack S);
int height(BinTree T);

int CheckBST ( BinTree T, int K )
{
    stack S = malloc(sizeof(struct StackRecord));
    S -> sp = -1;
    if(isBST(T, S) == 1)
        return find(T, K, S);
    else
        return -height(T);
}

int isBST(BinTree T, stack S)
{
    int flag1, flag2, flag3;
    if(T){
        flag1 = isBST(T -> Left, S);
        if(S -> sp == -1 || T -> Key > S -> Keys[S -> sp]){
            S -> Keys[++(S -> sp)] = T -> Key;
            flag2 = 1;
        }
        else
            flag2 = 0;
        flag3 = isBST(T -> Right, S);
        return flag1 && flag2 && flag3;
    }
    return 1;
}

int find(BinTree T, int K, stack S)
{
    return S -> Keys[S -> sp - K + 1];
}

int height(BinTree T)
{
    int L = 0, R = 0;

    if(T -> Left)
        L = height(T -> Left);
    if(T -> Right)
        R = height(T -> Right);
    if(L > R)
        return L + 1;
    else
        return R + 1;
}