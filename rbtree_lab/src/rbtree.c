#include "rbtree.h"

#include <stdlib.h>
#include <stdio.h>

rbtree *new_rbtree(void) {
  rbtree *p = calloc(1, sizeof(*p));
  if(!p){
    return NULL;
  }
  //초깃값 설정
  p->nil = calloc(1, sizeof(node_t));
  if(!p->nil){
    free(p);
    return NULL;
  }
  p->nil->color = RBTREE_BLACK;
  p->nil->left = p->nil->right = p->nil->parent = p->nil;
  p->root = p->nil;
  return p;
}

void delete_rbtree(rbtree *t) {
  node_t *cur = t->root; //동적으로 받아야 하나?
  free(t); 
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  //초기값 설정
  printf("hello10 \n");
  node_t *cur = t->root;
  node_t *prev;

  // key값으로 새로운 노드 생성
  node_t *z = malloc(sizeof(node_t));
  printf("mall : 5%p \n", z);
  if(!z){
    exit(EXIT_FAILURE);
  }
  z->key = key;
  z->color = RBTREE_RED;
  z->left = t->nil;
  z->right = t->nil;
  z->parent = t->nil;

  // root가 없을 때
  if(cur == t->nil){
    t->root = z;
    z->color = RBTREE_BLACK;
    return z;
  }

  // tree의 root부터 key가 들어갈 자리 탐색
  while(cur != t->nil){ //조건 이렇게 세우는게 맞는지 ;;
    prev = cur;
    if(z->key < cur->key){
      cur = cur->left;
    }else cur = cur->right;
  }
  
  // z가 부모를 선택!! 와!!!
  z->parent = prev;

  // 부모가 자식을 어떤 방에 넣을지 확인
  if(z->key < prev->key){
    prev->left = z;
  }else prev->right = z;

  // fix(t, z);

  return z;
}

void fix(rbtree* t, node_t *z){
  while(z->parent->color == RBTREE_RED){
    node_t *par = z->parent;
    if(par == par->parent->left){
      node_t *uncle = par->parent->right;
      if(uncle->color == RBTREE_RED){ //삼촌이 레드일 때 
        par->parent->color = RBTREE_RED;
        par->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        z = par->parent;
      }else if(z == z->parent->right){ //삼촌이 감둥이고, 부모의 오른쪽일 때
        leftRotate(t, par);
        par->color = RBTREE_RED;
        z->color = RBTREE_BLACK;
        rightRotate(t, par->parent);
      }
    }else{
      node_t *uncleR = par->parent->right;
      if(uncleR->color == RBTREE_RED){
        par->parent->color = RBTREE_RED;
        par->color = RBTREE_BLACK;
        uncleR->color = RBTREE_BLACK;
        z = par->parent;
      }else if(z == z->parent->left){
        rightRotate(t, par);
        par->color = RBTREE_RED;
        z->color = RBTREE_BLACK;
        leftRotate(t, par->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}

void leftRotate(rbtree* t, node_t *z){
  node_t *rightChd = z->right;
  z->right = rightChd->left;

  if(rightChd->left != t->nil){
    rightChd->left->parent = z;
  }
  
  rightChd->parent = z->parent;
  if(z == t->root){
    t->root = rightChd;
  }else if(z == z->parent->left){
    z->parent->left = rightChd;
  }else{
    z->parent->right = rightChd;
  }

  rightChd->left = z;
  z->parent = rightChd;
}
void rightRotate(rbtree* t, node_t *z){
    node_t *leftChd = z->left;
  z->left = leftChd->right;

  if(leftChd->right != t->nil){
    leftChd->parent = z;
  }
  if(z == t->root){
    t->root = leftChd;
  }else if(z == z->parent->right){
    z->parent->right = leftChd;
  }else{
    z->parent->left = leftChd;
  }

  leftChd->right = z;
  z->parent = leftChd;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
