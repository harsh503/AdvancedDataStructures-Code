#include<bits/stdc++.h>
using namespace std;

void deleteNode(struct node *);

int flag = 1;

struct node
{
    int v;
    struct node *l, *r;    
}*root=NULL,*t1;

void searchInsert(struct node *n, int x)
{
    if(x<n->v && n->l==NULL)
    {
        struct node *temp = (struct node *)malloc(sizeof(struct node *));
        temp->v = x;
        temp->l = temp->r = NULL;
        n->l = temp;
    }
    else if(x<n->v && n->l!=NULL)
    {
        searchInsert(n->l,x);
    }
    else if(x>=n->v && n->r==NULL)
    {
        struct node *temp = (struct node *)malloc(sizeof(struct node *));
        temp->v = x;
        temp->l = temp->r = NULL;
        n->r = temp;
    }
    else
    {
        searchInsert(n->r,x);
    }
}

void insert(int x)
{
    if(root==NULL)
    {
        struct node *n = (struct node *)malloc(sizeof(struct node *));
        n->v = x;
        n->l = n->r = NULL;
        root = n;
    }
    else
        searchInsert(root,x);
}

void print(struct node *n)
{
    if(root==NULL)
    {
        cout<<"Tree is empty"<<endl;
        return;
    }
    
    if(n->l!=NULL)
        print(n->l);
    printf("%d -> ",n->v);
    if(n->r!=NULL)
        print(n->r);
}

void search(struct node *n, int x)
{
    if(root==NULL)
    {
        printf("Tree empty\n");
        return ;
    }

    if(n->v==x)
    {
        printf("Value present\n");
        return ;
    }
    else
    {
        if(x<n->v && n->l!=NULL)
            search(n->l,x);
        else if(x>n->v && n->r!=NULL)
            search(n->r,x);
        else if(x<n->v && n->l==NULL)
        {
            cout<<"Value not present"<<endl;
            return ;
        }
        else if(x>n->v && n->r==NULL)
        {
            cout<<"Value not present"<<endl;
            return ;
        }
    }

}

int findSmallest(struct node *t)
{
    if(t->l!=NULL)
    {
        return(findSmallest(t->l));
    }
    else
        return(t->v);
}

int findLargest(struct node *t)
{
    if(t->r!=NULL)
    {
        return(findLargest(t->r));
    }
    else
        return(t->v);
}

void searchDelete(struct node *n, int x)
{
    if(x<n->v && n->l!=NULL)
    {
        t1=n;
        searchDelete(n->l,x);
    }
    else if(x>n->v && n->r!=NULL)
    {
        t1=n;
        searchDelete(n->r,x);
    }
    else if(x>n->v && n->r==NULL)
    {
        cout<<"Value not present in tree. Cannot delete"<<endl;
        return ;
    }
    else if(x<n->v && n->l==NULL)
    {
        cout<<"Value not present in tree. Cannot delete"<<endl;
        return ;
    }
    else if(x==n->v)
    {
        deleteNode(n);
    }
}

void deleteNode(struct node *t)
{
    int k;

    if(t->l==NULL && t->r==NULL)
    {
        if(t1==t)
            t1=t=root=NULL;
        else if(t1->l==t)
            t1->l=NULL;
        else
            t1->r=NULL;
        t=NULL;
        free(t);
        return ;
    }
    else if(t->r==NULL)
    {
        if(t1==t)
        {
            root=t->l;
            t1=root;
        }
        else if(t1->l==t)
            t1->l=t->l;
        else
            t1->r=t->l;
        t=NULL;
        free(t);
        return ;
    }
    else if(t->l==NULL)
    {
        if(t1==t)
        {
            root=t->r;
            t1=root;
        }
        else if(t1->r==t)
            t1->r=t->r;
        else 
            t1->l=t->r;
        t=NULL;
        free(t);
        return ;
    }
    else
    {
        if(t->r!=NULL)
        {
            k = findSmallest(t->r);
            flag = 1;
        }
        else
        {
            k = findLargest(t->l);
            flag = 2;
        }
        searchDelete(root,k);
        t->v = k;
    }
}

void del(int x)
{
    t1=root;
    if(root==NULL)
    {
        cout<<"Tree empty"<<endl;
        return ;
    }
    else
        searchDelete(root,x);
}

int main()
{

    while(1)
    {
        printf("1-insert,2-delete,3-search,4-print inorder\n");
        int n,v;
        cin>>n;

        if(n==1)
        {
            printf("Enter value to be inserted\n");
            cin>>v;
            insert(v);
        }
        else if(n==2)
        {
            printf("Enter value to delete\n");
            cin>>v;
            del(v);
        }
        else if(n==3)
        {
            printf("Enter value to be searched\n");
            cin>>v;
            search(root,v);
        }
        else if(n==4)
        {
            print(root);
            cout<<endl;
        }
        else
        {
            exit(0);
        }
    }

    return 0;
}