#include<bits/stdc++.h>

using namespace std;

struct node 
{
    int v,h;
    struct node *l, *r;
}*root=NULL,*root2=NULL,*mroot=NULL;

int GetHeight(struct node *n)
{
    if(n==NULL)
        return 0;
    return n->h;
}

int GetBalance(struct node *n)
{
    if(n==NULL)
        return 0;
    return ((GetHeight(n->l))-(GetHeight(n->r)));
}

struct node * LeftRotate(struct node *x)
{
    struct node *y = (struct node *)malloc(sizeof(struct node *));
    y = x->r;
    x->r = y->l;
    y->l = x;
    x->h = 1 + max(GetHeight(x->l),GetHeight(x->r));
    y->h = 1 + max(GetHeight(y->l),GetHeight(y->r));
    return y;
}

struct node * RightRotate(struct node *y)
{
    struct node *x = (struct node *)malloc(sizeof(struct node *));
    x = y->l;
    y->l = x->r;
    x->r = y;
    y->h = 1 + max(GetHeight(y->l),GetHeight(y->r));
    x->h = 1 + max(GetHeight(x->l),GetHeight(x->r));
    return x;
}

struct node * AVLInsert(struct node *n, int x)
{
    if(n==NULL)
    {
        struct node *temp = (struct node *)malloc(sizeof(struct node *));
        temp->v = x;
        temp->l = temp->r = NULL;
        temp->h = 1;
        return temp;
    }

    if(x<n->v)
        n->l = AVLInsert(n->l,x);
    else if(x>n->v)
        n->r = AVLInsert(n->r,x);
    else 
        return n;

    n->h = 1 + max(GetHeight(n->l),GetHeight(n->r));

    int b = GetBalance(n);
    if(b>1 && x<n->l->v)
        return RightRotate(n);
    else if(b<-1 && x>n->r->v)
        return LeftRotate(n);
    else if(b>1 && x>n->l->v)
    {
        n->l = LeftRotate(n->l);
        return RightRotate(n);
    }
    else if(b<-1 && x<n->r->v)
    {
        n->r = RightRotate(n->r);
        return LeftRotate(n);
    }

    return n;
}

struct node * FindMinInRight(struct node *n)
{
    while(n->l!=NULL)
        n = n->l;
    return n;
}

struct node * AVLDelete(struct node *n, int x)
{
    if(n==NULL)
        return n;

    if(x<n->v)
        n->l = AVLDelete(n->l,x);
    else if(x>n->v)
        n->r = AVLDelete(n->r,x);
    else
    {
        if(n->l==NULL||n->r==NULL)
        {
            struct node *t = (struct node *)malloc(sizeof(struct node *));
            t = n->l ? n->l : n->r;

            if(t==NULL)
            {
                t=n;
                n=NULL;
            }
            else    
                *n=*t;
            
            free(t);
        }
        else
        {
            struct node *t = (struct node *)malloc(sizeof(struct node *));
            t = FindMinInRight(n->r);
            n->v = t->v;
            n->r = AVLDelete(n->r,t->v);
        }
    }

    if(n==NULL)
        return n;

    n->h = 1 + max(GetHeight(n->l),GetHeight(n->r));
    int b = GetBalance(n);

    if(b>1 && GetBalance(n->l)>=0)
        return RightRotate(n);
    else if(b>1 && GetBalance(n->l)<0)
    {
        n->l = LeftRotate(n->l);
        return RightRotate(n);
    }
    else if(b<-1 && GetBalance(n->r)<=0)
        return LeftRotate(n);
    else if(b<-1 && GetBalance(n->r)>0)
    {
        n->r = RightRotate(n->r);
        return LeftRotate(n);
    }
    return n;
}

int getLargestChild(struct node *n)
{
    if(n->r==NULL)
        return n->v;
    return getLargestChild(n->r);

}

void mergeAVL(struct node *root, struct node *root2)
{
    int t = getLargestChild(root);
    cout<<"Val"<<t<<endl;
    root = AVLDelete(root,t);
    struct node *temp = (struct node *)malloc(sizeof(struct node *));
    temp->v = t;
    temp->l = temp-> r = NULL;
    mroot = temp;
    mroot->l = root;
    mroot->r = root2;

    mroot->h = 1 + max(GetHeight(mroot->l),GetHeight(mroot->r));

    int balance = GetBalance(mroot); 
 
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
}

void printpre(struct node *n)
{
    if(n==NULL)
        return;
    printf("%d(%d) ",n->v,n->h);
    printpre(n->l);
    printpre(n->r);
}

void printin(struct node *n)
{
    if(n==NULL)
        return;
    printin(n->l);
    printf("%d(%d) ",n->v,n->h);
    printin(n->r);
}

void printpost(struct node *n)
{
    if(n==NULL)
        return;
    printpost(n->l);
    printpost(n->r);
    printf("%d(%d) ",n->v,n->h);
}

int main()
{
    printf("Insert the nodes for the first AVL tree. (Completely smaller than the second tree)\n");
    while(1)
    {
        printf("1-insert,2-delete,3-search,4-printf preorder,5-print inorder,6-print postorder\n");
        int n,v;
        cin>>n;

        if(n==1)
        {
            printf("Enter value to be inserted\n");
            cin>>v;
            root = AVLInsert(root,v);
        }
        else if(n==2)
        {
            printf("Enter value to delete\n");
            cin>>v;
            root = AVLDelete(root,v);
        }
        else if(n==3)
        {
            printf("Enter value to be searched\n");
            cin>>v;
            //search(root,v);
        }
        else if(n==4)
        {
            printpre(root);
            cout<<endl;
        }
        else if(n==5)
        {
            printin(root);
            cout<<endl;
        }
        else if(n==6)
        {
            printpost(root);
            cout<<endl;
        }
        else
        {
            break;
        }
    }

    printf("\nInsert the nodes for the second AVL tree.\n");
    while(1)
    {
        printf("1-insert,2-delete,3-search,4-printf preorder,5-print inorder,6-print postorder\n");
        int n,v;
        cin>>n;

        if(n==1)
        {
            printf("Enter value to be inserted\n");
            cin>>v;
            root2 = AVLInsert(root2,v);
        }
        else if(n==2)
        {
            //printf("Enter value to delete\n");
            //cin>>v;
            //root = AVLDelete(root,v);
        }
        else if(n==3)
        {
            printf("Enter value to be searched\n");
            cin>>v;
            //search(root,v);
        }
        else if(n==4)
        {
            printpre(root2);
            cout<<endl;
        }
        else if(n==5)
        {
            printin(root2);
            cout<<endl;
        }
        else if(n==6)
        {
            printpost(root2);
            cout<<endl;
        }
        else
        {
            break;
        }
    }

    mergeAVL(root,root2);
    printin(mroot);
    cout<<endl;
    printpre(mroot);
    return 0;
}