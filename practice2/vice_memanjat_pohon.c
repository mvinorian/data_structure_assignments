#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/**
 * Node structure and
 * uniqueBST structure
 */

typedef struct bstnode_t {
    int key;
    struct bstnode_t \
        *left, *right;
} BSTNode;

typedef struct bst_t {
    BSTNode *_root;
    unsigned int _size;
} BST;

bool is_odd(int);
bool is_even(int);
bool is_prime(int);
bool all(int);

/**
 * !!! WARNING UTILITY FUNCTION !!!
 * Recognized by prefix "__bst__"
 * ---------------------------------------------
 * Note that you better never access these functions, 
 * unless you need to modify or you know how these functions work.
 */

BSTNode* __bst__createNode(int value) {
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode* __bst__insert(BSTNode *root, int value) {
    if (root == NULL) 
        return __bst__createNode(value);

    if (value < root->key)
        root->left = __bst__insert(root->left, value);
    else if (value > root->key)
        root->right = __bst__insert(root->right, value);
    
    return root;
}

BSTNode* __bst__search(BSTNode *root, int value) {
    while (root != NULL) {
        if (value < root->key)
            root = root->left;
        else if (value > root->key)
            root = root->right;
        else
            return root;
    }
    return root;
}

BSTNode* __bst__findMinNode(BSTNode *node) {
    BSTNode *currNode = node;
    while (currNode && currNode->left != NULL)
        currNode = currNode->left;
    
    return currNode;
}

BSTNode* __bst__remove(BSTNode *root, int value) {
    if (root == NULL) return NULL;

    if (value > root->key) 
        root->right = __bst__remove(root->right, value);
    else if (value < root->key) 
        root->left = __bst__remove(root->left, value);
    else {
        
        if (root->left == NULL) {
            BSTNode *rightChild = root->right;
            free(root);
            return rightChild;
        }
        else if (root->right == NULL) {
            BSTNode *leftChild = root->left;
            free(root);
            return leftChild;
        }

        BSTNode *temp = __bst__findMinNode(root->right);
        root->key     = temp->key;
        root->right   = __bst__remove(root->right, temp->key);
    }
    return root;
}

void __bst__inorder(BSTNode *root, bool (*k)(int)) {
    if (root) {
        __bst__inorder(root->left, k);
        if(k(root->key)) printf("%d\n", root->key);
        __bst__inorder(root->right, k);
    }
}

void __bst__postorder(BSTNode *root, bool (*k)(int)) {
    if (root) {
        __bst__postorder(root->left, k);
        __bst__postorder(root->right, k);
        if(k(root->key)) printf("%d\n", root->key);
    }
}

void __bst__preorder(BSTNode *root, bool (*k)(int)) {
    if (root) {
        if(k(root->key)) printf("%d\n", root->key);
        __bst__preorder(root->left, k);
        __bst__preorder(root->right, k);
    }
}

void __bst__climb(BSTNode *root, int value) {
    if(value < root->key){
        __bst__climb(root->left, value);
    }
    if(value > root->key){
        __bst__climb(root->right, value);
    }
    printf("%d\n", root->key);
}

/**
 * PRIMARY FUNCTION
 * ---------------------------
 * Accessible and safe to use.
 */

void bst_init(BST *bst) {
    bst->_root = NULL;
    bst->_size = 0u;
}

bool bst_isEmpty(BST *bst) {
    return bst->_root == NULL;
}

bool bst_find(BST *bst, int value) {
    BSTNode *temp = __bst__search(bst->_root, value);
    if (temp == NULL)
        return false;
    
    if (temp->key == value)
        return true;
    else
        return false;
}

void bst_insert(BST *bst, int value) {
    if (!bst_find(bst, value)) {
        bst->_root = __bst__insert(bst->_root, value);
        bst->_size++;
    }
}

void bst_remove(BST *bst, int value) {
    if (bst_find(bst, value)) {
        bst->_root = __bst__remove(bst->_root, value);
        bst->_size--;
    }
}

/**
 * Binary search tree traversal
 * - Inorder
 * - Postorder
 * - Preorder
 */

void bst_inorder(BST *bst, bool (*k)(int)) {
    __bst__inorder(bst->_root, k);
}

void bst_postorder(BST *bst, bool (*k)(int)) {
    __bst__postorder(bst->_root, k);
}

void bst_preorder(BST *bst, bool (*k)(int)) {
    __bst__preorder(bst->_root, k);
}

void bst_climb(BST *bst, int value) {
    if(!bst_find(bst, value) || value == bst->_root->key){
        printf("Gabisa, dasar setan!\n");
        return;
    }
    BSTNode *node = __bst__search(bst->_root, value);
    if(node->left != NULL || node->right != NULL){
        printf("Gabisa, dasar setan!\n");
        return;
    }
    __bst__climb(bst->_root, value);
    bst_remove(bst, value);
}

bool is_odd(int x){
    return (x % 2) == 1;
}

bool is_even(int x){
    return (x % 2) == 0;
}

bool is_prime(int x){
    if(x < 2) return false;
    for(int i = 2; i * i <= x; i++){
        if(x % i == 0) return false;
    }
    return true;
}

bool all(int x){
    return true;
}

int main(){
    int n;
    BST bst;
    bst_init(&bst);

    while(1){
        scanf("%d", &n);
        if(n == -1) break;
        bst_insert(&bst, n);
    }

    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        int x;
        char c[10], k[10];
        scanf("%s", c);
        printf("Command : #%d\n", i);

        if(strcmp(c, "inorder") == 0){
            scanf("%s", k);
            if(strcmp(k, "ganjil") == 0) bst_inorder(&bst, is_odd);
            if(strcmp(k, "genap") == 0) bst_inorder(&bst, is_even);
            if(strcmp(k, "prima") == 0) bst_inorder(&bst, is_prime);
            if(strcmp(k, "semua") == 0) bst_inorder(&bst, all);
        }
        if(strcmp(c, "preorder") == 0){
            scanf("%s", k);
            if(strcmp(k, "ganjil") == 0) bst_preorder(&bst, is_odd);
            if(strcmp(k, "genap") == 0) bst_preorder(&bst, is_even);
            if(strcmp(k, "prima") == 0) bst_preorder(&bst, is_prime);
            if(strcmp(k, "semua") == 0) bst_preorder(&bst, all);
        }
        if(strcmp(c, "postorder") == 0){
            scanf("%s", k);
            if(strcmp(k, "ganjil") == 0) bst_postorder(&bst, is_odd);
            if(strcmp(k, "genap") == 0) bst_postorder(&bst, is_even);
            if(strcmp(k, "prima") == 0) bst_postorder(&bst, is_prime);
            if(strcmp(k, "semua") == 0) bst_postorder(&bst, all);
        }
        if(strcmp(c, "panjat") == 0){
            scanf("%d", &x);
            bst_climb(&bst, x);
        }
    }

    return 0;
}