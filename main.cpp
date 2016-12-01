/* 
 * File:   main.cpp
 * Author: amirif
 *
 * Created on 20. listopad 2014, 19:38
 */


#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

struct node
{
  int key;

  struct node *left;

  struct node *right;
  struct node *parent;
  ~node(){
    //   if(left)delete left;
    //   if (right) delete right;
    //if (parent) delete parent;
     
  }

   
} *root;

class SplayTree {
public:
  // double ada; //avreage depth of access
     
  int find(int);
  void insert(int);
  void del(int);
  void splay(node *);
  void zig(node *);
  node * zig_zag(node *);
  node * zig_zig(node *);
  void empty(node *);
  SplayTree() {
    root = NULL;
  }
};

/*
 * 
 */
int main(int argc, char** argv) {
  char order;
  int key;
  SplayTree st;
  long n ;//Number of elements 
  long da ;//depth of access (search)
  double sda ;//depth of access (search per block)
  long * daArray= new long[300];    //Depth of access     
  bool cycle=true;
  long maxda=0;
  n=0;
  da=0;
  sda=0;
  //  node *temp;
   
  while (cycle) {
    cin >> order;
    //cout<<order;
    switch (order) {
    case 'I':
      //   cout<<"Enter the key number "<<endl;
      cin>>key;
      st.insert(key);
      ++(n);
      break;
    case 'F':
      //    cout << "Find a node" << endl;
      cin>>key;
      da=st.find(key);
      (daArray[da])++;
      sda+=da;
      //      maxda=(maxda<da)? da : maxda;
      break;
    case 'R':
      //     cout << "end block,empty tree"<<endl;
      st.empty(root);
      //    cout<<"tree is empty"<<endl;
      root =NULL;
      cout << n<<"  "<< std::fixed<<setprecision(1) <<(double)sda/(double)n<<endl;
      n=0;
      da=0;
      sda=0;
      maxda=0;
      break;
                

    case 'X':
      //   cout << "Exit Application and write second report" << endl;
      for(int t=0; t<=300; t++)
	{
	  cout << t<<" "<<daArray[t]<<endl;
	}
      cycle=false;
      break;
    default:
      //   cout << "Wrong Data Entry" << endl;
      break;
    }
  }
  //cin>>key;
  return 0;
}

void SplayTree::empty(node * x){
  // cout<<"empty tree"; 
  //  if(x->left) empty(x->left) ;
  //  if(x->right) empty(x->right) ;
  
  delete x;
}

int SplayTree::find(int key) {
  int da=0;
  if (root == NULL) return da;
  node * finder;
  finder = root;
  bool comp = false;
  bool res = false;
  while (finder) {
    res = (key == finder->key);
    if (res) {
      splay(finder);
      return da;
    } else {
      comp = (key > finder->key);
      if (comp) finder = finder->right;
      else finder = finder->left;
            
    }
    da++;
    //  cout <<da;
  }

  return da;

}

void SplayTree::insert(int key) {

  if (root == NULL) {
    root = new node;
    root->key = key;
    root->left = NULL;
    root->right = NULL;
    root->parent = NULL;
    //   cout<<"Root Node is Added"<<endl;
    return;
  }
  node * temp = root;
  node * gauge = temp;
  node * newNode = new node;
  newNode->key = key;
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->parent = NULL;
  bool di = false;
  while (temp != NULL) {
    di = (key > temp->key);
    gauge = temp;
    if (di)temp = temp->right;
    else temp = temp->left;

  }


  if (di) gauge->right = newNode;
  else gauge->left = newNode;
  newNode->parent = gauge;
  splay(newNode);
  return;
}

void SplayTree::splay(node * x) {

  while (x != root) {
    zig(x);
    x = zig_zig(x);
    x = zig_zag(x);

  }

}

void SplayTree::zig(node * x) {

  node * p;
  p = x->parent;
  if (p->parent != NULL) return;

  if (x == p->right) {
    if(x->left){x->left->parent=p;}
    p->right = x->left;
    x->left = p;
    x->parent = NULL;
    p->parent = x;
    root = x;
    return;
  }

  if (x == p->left) {

    if(x->right){x->right->parent=p;}
    p->left = x->right;
    x->right = p;
    x->parent = NULL;
    p->parent = x;
    root = x;
    return;
  }

  return;
}

node * SplayTree::zig_zig(node *x) {

  //p(parent) is not root 


  node * p;
  node * g;

  p = x->parent;
  if (!p)return x;
  g = p->parent;

  //x is left child and p is left child 

  if (x == p->left && p == g->left) {
    if (g->parent)
      if (g == g->parent->left)g->parent->left = x;
      else g->parent->right = x;
    else root = x;

    if(x->right){x->right->parent=p;}

    p->left = x->right;
    x->right = p;
    if(p->right)p->right->parent=g;
    g->left = p->right;
    p->right = g;

    x->parent = g->parent;
    g->parent = p;
    p->parent = x;

    return x;
  }

  //x is right child and p is right child 
  if (x == p->right && p == g->right) {
    if (g->parent)
      if (g == g->parent->right)g->parent->right = x;
      else g->parent->left = x;
    else root = x;
        
       
    if(x->left){x->left->parent=p;}
    if(p->left)p->left->parent=g;
    g->right = p->left;
       
    p->left = g;
    p->right = x->left;
        
    x->left = p;

    x->parent = g->parent;
    g->parent = p;
    p->parent = x;
    return x;
  }

  return x;

}

node * SplayTree::zig_zag(node *x) {

  //p(parent) is not root 


  node * p; //parent x
  node * g; //grandpa x
  p = x->parent;
  if (!p)return x;
  g = p->parent;
  if (!g)return x;
  //x is right child and p is left child 
  if (x == p->right && p == g->left) {


    if (g->parent)
      if (g == g->parent->right)g->parent->right = x;
      else g->parent->left = x;
    else root = x;

    if(x->right){x->right->parent=g;}
    if(x->left){x->left->parent=p;}
    g->left = x->right;
    p->right = x->left;
    x->left = p;
    x->right = g;



    x->parent = g->parent;

    p->parent = x;
    g->parent = x;
    return x;
  }

  //x is left child and p is right child 
  if (x == p->left && p == g->right) {

    if (g->parent)
      if (g == g->parent->right)g->parent->right = x;
      else g->parent->left = x;
    else root = x;
    if(x->right){x->right->parent=p;}
    if(x->left){x->left->parent=g;}
    g->right = x->left;
    p->left = x->right;
    x->left = g;
    x->right = p;

    x->parent = g->parent;
    p->parent = x;
    g->parent = x;
    return x;
  }

  return x;
}

