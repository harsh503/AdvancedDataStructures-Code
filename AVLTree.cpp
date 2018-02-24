#include<bits/stdc++.h>

using namespace std;

int flag=0;

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

int GetBalance(struct node *n)
{
    if(n==NULL)
        return 0;
    return ((GetHeight(n->l))-(GetHeight(n->r)));
}

int AVLBalance(struct node *root)
{
    if(root->l == NULL && root->r == NULL)
    {
        root->h = 1;
        return 1;
    }
    else if(root->l == NULL)
    {
        root->h = 1 + AVLBalance(root->r);
        return 1 + AVLBalance(root->r);
    }
    else if(root->r == NULL)
    {
        root->h = 1 + AVLBalance(root->l);
        return 1 + AVLBalance(root->l);
    }
    else
    {
        root->h = 1 + max(AVLBalance(root->l),AVLBalance(root->r));
        return 1 + max(AVLBalance(root->l),AVLBalance(root->r));
    }
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

int getSmallestChild(struct node *n)
{
    if(n->l==NULL)
        return n->v;
    return getSmallestChild(n->l);
}

struct node *RecurseLeft(struct node *n, int h)
{
    if(GetHeight(n) > h+1)
        return RecurseLeft(n->l, h);
    else 
        return n;
}

struct node *RecurseRight(struct node *n, int h)
{
    if(GetHeight(n) > h+1)
        return RecurseRight(n->r,h);
    else    
        return n;
}

struct node *GetParentLeftRecurse(struct node *n, struct node *nodeBreak, struct node *parent)
{
    if(parent==NULL && n==nodeBreak)
    {
        return NULL;
    }
    else if(n==nodeBreak)
    {
        return parent;
    }
    else
    {
        parent = n;
        return GetParentLeftRecurse(n->l,nodeBreak, parent);
    }    
}

struct node *GetParentRightRecurse(struct node *n, struct node *nodeBreak, struct node *parent)
{
    if(parent==NULL && n==nodeBreak)
        return NULL;
    else if(n==nodeBreak)
        return parent;
    else
    {
        parent = n;
        return GetParentRightRecurse(n->r,nodeBreak, parent);
    }
}

struct node * findBalanceNodeLeft(struct node *root, int ht, int rem, struct node *left)
{
    struct node *nodeBreak = RecurseLeft(root,ht);
    struct node *parent = GetParentLeftRecurse(root, nodeBreak, NULL);
    struct node *grandParent = GetParentLeftRecurse(root, parent, NULL);
    
    struct node *temp = (struct node *)malloc(sizeof(struct node *));
    temp->v = rem;
    temp->l = left;
    temp->r = nodeBreak;

    if(parent==NULL)
        return temp;
    else
    {
        parent->l = temp;
        parent->h = AVLBalance(parent);
        if(grandParent==NULL)
        {
            int b = GetBalance(parent);
            if(b>=-1 && b<=1)
            {
                return parent;
            }
            else
            {
                struct node *templ = (struct node *)malloc(sizeof(struct node *));
                templ = parent->l->r->l;
                struct node *tempr = (struct node *)malloc(sizeof(struct node *));
                tempr = parent->l->r->r; 
                root = parent->l->r;
                root->l = parent->l;
                root->r = parent; 
                root->l->r = templ;
                root->r->l = tempr;
                return root;  
            }
        }
        else
        {
            struct node *templ = (struct node *)malloc(sizeof(struct node *));
            templ = parent->l->r->l;
            struct node *tempr = (struct node *)malloc(sizeof(struct node *));
            tempr = parent->l->r->r;
            struct node *temp = (struct node *)malloc(sizeof(struct node *));
            temp = parent->l->r;
            temp->l = parent->l;
            temp->r = parent;
            temp->l->r = templ;
            temp->r->l = tempr;
            grandParent->l = temp;
            return root;
        }
    }
}

struct node * findBalanceNodeRight(struct node *root, int ht, int rem, struct node *right)
{
    struct node *nodeBreak = RecurseRight(root,ht);
    struct node *parent = GetParentRightRecurse(root, nodeBreak, NULL);
    struct node *grandParent = GetParentRightRecurse(root, parent, NULL);

    struct node *temp = (struct node *)malloc(sizeof(struct node *));
    temp->v = rem;
    temp->r = right;
    temp->l = nodeBreak;

    if(parent==NULL)
        return temp;
    else
    {
        parent->r = temp;
        parent->h = AVLBalance(parent);
        if(grandParent==NULL)
        {
            int b = GetBalance(parent);
            if(b>=-1 && b<=1)
            {
                return parent;
            }
            else
            {
                struct node *templ = (struct node *)malloc(sizeof(struct node *));
                templ = parent->r->l->l;
                struct node *tempr = (struct node *)malloc(sizeof(struct node *));
                tempr = parent->r->l->r; 
                root = parent->r->l;
                root->r = parent->r;
                root->l = parent; 
                root->l->r = templ;
                root->r->l = tempr;
                return root;  
            }
        }
        else
        {
            struct node *templ = (struct node *)malloc(sizeof(struct node *));
            templ = parent->r->l->l;
            struct node *tempr = (struct node *)malloc(sizeof(struct node *));
            tempr = parent->r->l->r;
            struct node *temp = (struct node *)malloc(sizeof(struct node *));
            temp = parent->r->l;
            temp->r = parent->r;
            temp->l = parent;
            temp->l->r = templ;
            temp->r->l = tempr;
            grandParent->r = temp;
            return root;
        }
    }
}

void mergeAVL(struct node *root1, struct node *root2)
{
    int h1 = GetHeight(root1);
    int h2 = GetHeight(root2);

    if(h1==0 && h2==0)
    {
        cout<<"\nNo input to process\n";
        return;
    }
    else if(h1==0)
    {
        mroot = root2;
        cout<<"\n\nThe MERGED AVL Tree is as follows : ";
        cout<<endl<<"Inorder Traversal - ";
        printin(mroot);
        cout<<endl<<"Preorder Traversal - ";
        printpre(mroot);
        cout<<endl;
        return;
    }
    else if(h2==0)
    {
        mroot = root1;
        cout<<"\n\nThe MERGED AVL Tree is as follows : ";
        cout<<endl<<"Inorder Traversal - ";
        printin(mroot);
        cout<<endl<<"Preorder Traversal - ";
        printpre(mroot);
        cout<<endl;
        return;
    }

    if(h2>=h1)
    {
        int rem = getLargestChild(root1);
        root1 = AVLDelete(root1,rem);
        int lHeight = GetHeight(root1);
        mroot = findBalanceNodeLeft(root2,lHeight,rem,root1);
        mroot->h = AVLBalance(mroot);
        cout<<"\n\nThe MERGED AVL Tree is as follows : ";
        cout<<endl<<"Inorder Traversal - ";
        printin(mroot);
        cout<<endl<<"Preorder Traversal - ";
        printpre(mroot);
        cout<<endl;
    }   
    else
    {
        int rem = getSmallestChild(root2);
        root2 = AVLDelete(root2,rem);
        int rHeight = GetHeight(root2);
        mroot = findBalanceNodeRight(root1,rHeight,rem,root2);
        mroot->h = AVLBalance(mroot);
        cout<<"\n\nThe MERGED AVL Tree is as follows : ";
        cout<<endl<<"Inorder Traversal - ";
        printin(mroot);
        cout<<endl<<"Preorder Traversal - ";
        printpre(mroot);
        cout<<endl;
    } 

}

void search(struct node *root, int v)
{
    if(root==NULL)
        return;
    if(root->v==v)
    {
        flag=1;
        return;
    }
    else if(v<root->v)
        return search(root->l,v);
    else    
        return search(root->r,v);

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
            flag=0;
            search(root,v);
            if(flag==0)
                printf("Value %d not found\n",v);
            else    
                printf("Value %d found\n",v);
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
            printf("Enter value to delete\n");
            cin>>v;
            root2 = AVLDelete(root2,v);
        }
        else if(n==3)
        {
            printf("Enter value to be searched\n");
            cin>>v;
            flag=0;
            search(root,v);
            if(flag==0)
                printf("Value %d not found\n",v);
            else    
                printf("Value %d found\n",v);
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
    return 0;
}