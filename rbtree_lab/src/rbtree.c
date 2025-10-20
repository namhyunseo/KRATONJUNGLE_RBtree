#include "rbtree.h"

#include <stdlib.h>
#include <stdio.h>

static void leftRotate(rbtree *t, node_t *z);
static void rightRotate(rbtree *t, node_t *z);
static void fix(rbtree *t, node_t *z);

rbtree *new_rbtree(void) {
  rbtree *t = calloc(1, sizeof(*t));
  if(!t){
    return NULL;
  }
  //초깃값 설정
  t->nil = calloc(1, sizeof(node_t));
  if(!t->nil){
    free(t);
    return NULL;
  }
  t->nil->color = RBTREE_BLACK;
  t->nil->left = t->nil->right = t->nil->parent = t->nil;
  t->root = t->nil;
  return t;
}

void delete_rbtree(rbtree *t) {
  
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  //초기값 설정
  node_t *cur = t->root;
  node_t *prev;

  // key값으로 새로운 노드 생성
  node_t *z = malloc(sizeof(node_t));
  if(!z){
    return NULL;
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

  fix(t, z);

  return z;
}
//값이 같을 경우 처리
// 4 2 3 케이스 오류  
void fix(rbtree* t, node_t *z){
  while(z->parent->color == RBTREE_RED){
    node_t *par = z->parent;
    if(par == par->parent->left){ //left로 치우친 경우
      node_t *uncle = par->parent->right;
      if(uncle->color == RBTREE_RED){ //삼촌이 레드일 때 case 1
        par->parent->color = RBTREE_RED;
        par->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        z = par->parent;
      }else if(z == par->right){ //삼촌이 감둥이고, 부모의 오른쪽일 때 case2
        // rotate 잘 돌렸는지 확인
        // printf("before grand : %p \n", par->parent);
        // printf("my parent : %p \n", z->parent);
        leftRotate(t, par);
        // printf("me : %p \n", z);
        // printf("my parent : %p \n", z->parent);
        // printf("my left : %p \n", z->left);
        z->parent->color = RBTREE_RED;
        z->color = RBTREE_BLACK;
        z = z->parent;
        rightRotate(t, z);
      }else if(z == par->left){ // case 3
        par->parent->color = RBTREE_RED;
        par->color = RBTREE_BLACK;
        rightRotate(t, par->parent);
      }
    }else{
      node_t *uncleR = par->parent->left;
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
      }else if(z == par->right){
        par->parent->color = RBTREE_RED;
        par->color = RBTREE_BLACK;
        leftRotate(t, par->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}

void leftRotate(rbtree* t, node_t *z){
  node_t *rightChd = z->right;
  z->right = rightChd->left;

  // 왼쪽에 서브트리가 있을 경우 이동
  if(rightChd->left != t->nil){
    rightChd->left->parent = z;
  }
  // rigthchd를 z의 부모의 밑으로 옮긴다.
  rightChd->parent = z->parent;
  // printf("rightParent :%p\n", rightChd->parent);
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
  leftChd->parent = z->parent;
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
