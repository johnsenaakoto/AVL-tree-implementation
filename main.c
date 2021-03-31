#include <stdio.h>
#include<stdlib.h>

typedef struct node{
  int data;
  struct node* left;
  struct node* right;
  int height;
}node_t;

int max(int a, int b){
  return ((a > b) ? a : b);
}

int height(node_t*root){
  if(root==NULL){
    return(0);
  }
  return(root->height);
}

void preorder(node_t* root){
  if(root == NULL){}
  else{
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
  }
}

void insert_node(node_t**, int data);

int main(void) {
  node_t* root=NULL;
  insert_node(&root, 10);
  insert_node(&root, 20);
  insert_node(&root, 30);
  insert_node(&root, 40);
  insert_node(&root, 50);
  insert_node(&root, 25);

  printf("Preorder traversal of AVL tree is\n");
  preorder(root);
  return 0;
}

void rightrotate(node_t** root){
  node_t* temp1 = (*root)->left;
  node_t* temp2 = temp1->right;

  temp1->right=(*root);
  (*root)->left = temp2;

  (*root)->height = 1 + max(height((*root)->right), height((*root)->left));
  temp1->height = 1 + max(height(temp1->right), height(temp1->left));
}

void leftrotate(node_t** root){
  node_t* temp1 = (*root)->right;
  node_t* temp2 = temp1->left;

  temp1->left=(*root);
  (*root)->right = temp2;

  (*root)->height = 1 + max(height((*root)->right), height((*root)->left));
  temp1->height = 1+ max(height(temp1->right), height(temp1->left));
}



void insert_node(node_t**root, int data){
  if(*root==NULL){
    *root=(node_t*)malloc(sizeof(node_t));
    (*root)->left=NULL;
    (*root)->right=NULL;
    (*root)->data=data;
    (*root)->height=1;
  }
  else{
    if(data < (*root)->data){
      insert_node(&(*root)->left, data);
    }
    else{
      insert_node(&(*root)->right, data);
    }
    (*root)->height= 1 + max(height((*root)->left),height((*root)->left));

    int b_factor = height((*root)->left) - height((*root)->right);

    if(b_factor > 1){
      if(data < (*root)->left->data){
        rightrotate(root);
      }
      else{
        leftrotate(&(*root)->left);
        rightrotate(root);
      }
    }
    else if(b_factor < -1){
      if(data > (*root)->left->data){
        leftrotate(root);
      }
      else{
        rightrotate(&(*root)->right);
        leftrotate(root);
      }
    }
  }
}