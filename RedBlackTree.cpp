#include<bits/stdc++.h>

using namespace std;

struct node 
{
    int v,c;
    node *l, *r, *p;

    node(int v)
    {
        this->v = v;
        l = r = p = NULL;
    }
}*root=NULL;

struct node * CreateNode(int v)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node *));
    temp->l = temp->r = temp->p = NULL;
    temp->v = v;
    temp->c = 0;
    return temp;
}

void LeftRotate(struct node *x)
{
    node *y = x->r;
    x->r = y->l;
    if(x->r!=NULL)
        x->r->p=x;
    y->p = x->p;
    if(x->p==NULL)
        root=y;
    else if(x==x->p->l)
        x->p->l=y;
    else
        x->p->r=y;

    y->l = x;
    x->p = y;    
}

void RightRotate(struct node *y)
{
    node *x = y->l;
    y->l = x->r;
    if(y->l!=NULL)
        y->l->p=y;
    x->p = y->p;
    if(y->p==NULL)
        root=x;
    else if(y->p->l==y)
        y->p->l=x;
    else
        y->p->r=x;
    x->r = y;
    y->p = x;
}

void RBInsertFixup(struct node *z)
{
    cout<<"inside\n";
    node *parent = NULL;
    cout<<"parent done\n";
    node *grandparent = NULL;
    cout<<"grandparent done\n";
    
    while((z!=root) && (z->c!=1) && (z->p->c==0))
    {
        cout<<"inside while\n";
        parent = z->p;
        grandparent = z->p->p;
        if(parent==grandparent->l)
        {
            node *uncle = grandparent->r;
            cout<<"uncle1done\n";
            if(uncle!=NULL && uncle->c==0)
            {
                parent->c = 1;
                uncle->c = 1;
                grandparent->c = 0;
                z = grandparent;
            }
            else
            {
                if(z = parent->r)
                {
                    LeftRotate(parent);
                    z = parent;
                    parent = z->p;
                }
                RightRotate(grandparent);
                int temp = parent->c;
                parent->c = grandparent->c;
                grandparent->c = parent->c;
                z = parent; 
            }
        }
        else
        {
            node *uncle = grandparent->l;
            cout<<"uncle2done\n";
            if(uncle!=NULL && uncle->c==0)
            {
                parent->c = 1;
                uncle->c = 1;
                grandparent->c = 0;
                z = grandparent;
            }
            else
            {
                if(z = parent->l)
                {
                    RightRotate(parent);
                    z = parent;
                    parent = z->p;
                }
                LeftRotate(grandparent);
                int temp = parent->c;
                parent->c = grandparent->c;
                grandparent->c = parent->c;
                z = parent;
            }
        }
    }
    root->c = 1;
    cout<<"goind outside\n";
}

void BSTInsert(struct node *n)
{
    if(root==NULL)
    {
        root = n;
        return ;
    } 

    if(n->v < root->v)
    {
        root->l = BSTInsert(root->l,n);
        root->l->p = root;
    }
    else if(n->v > root->v)
    {
        root->r = BSTInsert(root->r,n);
        root->r->p = root;
    }
}

void RBInsert(int v)
{
    BSTInsert(v);
    RBInsertFixup(temp);
}

void printInorder(struct node *n)
{
    if(n==NULL)
        return;
    printInorder(n->l);
    cout<<n->v<<"("<<n->c<<") ";
    printInorder(n->r); 
}

int main()
{
while(1)
    {
        printf("1-insert,2-delete,3-search,4-print inorder\n");
        int n,v;
        scanf("%d",&n);

        if(n==1)
        {
            printf("Enter value to be inserted\n");
            scanf("%d",&v);
            RBInsert(v);
        }
        else if(n==2)
        {
            printf("Enter value to delete\n");
            //cin>>v;
  //          del(v);
        }
        else if(n==3)
        {
            printf("Enter value to be searched\n");
            //cin>>v;
    //        search(root,v);
        }
        else if(n==4)
        {
            cout<<root<<"root value\n";
            cout<<"Inorder - ";
            printInorder(root);
//            cout<<endl<<"Postorder - ";
//            printPostorder(root);
            cout<<endl;
        }
        else
        {
            exit(0);
        }
    }

    return 0;
}