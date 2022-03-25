#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

int max1 = 0, max2 = 0;

/**
 * Node structure and
 * uniqueBST structure
 */

typedef struct bstnode_t {
    int key;
    int depth;
    struct bstnode_t \
        *left, *right;
} BSTNode;

typedef struct bst_t {
    BSTNode *_root;
    unsigned int _size;
} BST;

/**
 * !!! WARNING UTILITY FUNCTION !!!
 * Recognized by prefix "__bst__"
 * ---------------------------------------------
 * Note that you better never access these functions, 
 * unless you need to modify or you know how these functions work.
 */

BSTNode* __bst__createNode(int value, int depth) {
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->depth = depth;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode* __bst__insert(BSTNode *root, int value, int depth) {
    if (root == NULL) {
        if (depth > max1) max1 = depth;
        else if (depth > max2) max2 = depth;
        return __bst__createNode(value, depth);
    }

    if (value < root->key)
        root->left = __bst__insert(root->left, value, root->depth+1);
    else if (value > root->key)
        root->right = __bst__insert(root->right, value, root->depth+1);
    
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
        bst->_root = __bst__insert(bst->_root, value, 0);
        bst->_size++;
    }
}

int main(){
    int n, m, x;
    BST bst;
    bst_init(&bst);
    scanf("%d", &n);
    while(n--){
        scanf("%d", &x);
        bst_insert(&bst, x);
        m = max1 + max2;
        if(m == 0) printf("Mulai!\n");
        else if(m % 2) printf("%d\n", m);
        else printf("IKKI!!! :(\n");
    }

    return 0;
}