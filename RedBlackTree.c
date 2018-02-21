#include<stdio.h>
#include<stdlib.h>

struct node 
{
    int v;
    struct node *l, *r, *p;
    int c;
}*root=NULL;

struct node * CreateNode(int v)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node ));
    temp->l = temp->r = temp->p = NULL;
    temp->v = v;
    temp->c = 0;
    return temp;
}

void printInorder(struct node *n)
{
    if(n==NULL)
        return;
    printInorder(n->l);
    printf("%d(%d) ",n->v,n->c);
    printInorder(n->r); 
}

void printPreorder(struct node *n)
{
    if(n==NULL)
        return;
    printf("%d(%d) ",n->v,n->c);
    printPreorder(n->l);
    printPreorder(n->r); 
}

void LeftRotate(struct node *x)
{
    struct node *y = CreateNode(0);
    y = x->r;
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
    struct node *x = CreateNode(0);
    x = y->l;
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
    struct node *parent = (struct node *)malloc(sizeof(struct node ));
    parent = NULL;
    struct node *grandparent = CreateNode(0);
    grandparent = NULL;
    while(z->p!=NULL && z->p->c==0 && z!=root && z->c!=1)
    {
        printf("\n");
        printInorder(root);
        printPreorder(root);
        printf("\n");
        parent = z->p;
        grandparent = z->p->p;
        if(parent==grandparent->l)
        {
            struct node *uncle = CreateNode(0);
            uncle = grandparent->r;
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
            struct node *uncle = CreateNode(0);
            uncle = grandparent->l;
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
                    printf("\ncheck\n");
                    RightRotate(parent);
                    z = parent;
                    parent = z->p;
                }
                LeftRotate(grandparent);
                int temp = parent->c;
                parent->c = grandparent->c;
                grandparent->c = temp;
                z = parent;
            }
        }
    }
    root->c = 1;
}

struct node * BSTInsert(struct node *root, struct node *n)
{
    if(root==NULL)
        return n; 

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

    return root;
}

void RBInsert(int v)
{
    struct node *temp = CreateNode(v);
    root = BSTInsert(root,temp);
    RBInsertFixup(temp);
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
            printf("Root - %d\n",root->v);
            printf("Inorder - ");
            printInorder(root);
            printf("\nPreorder - ");
            printPreorder(root);
//            cout<<endl<<"Postorder - ";
//            printPostorder(root);
            printf("\n");
        }
        else
        {
            exit(0);
        }
    }

    return 0;
}