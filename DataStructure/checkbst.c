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
    stack S;
    S = (stack)malloc(sizeof(struct StackRecord));
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