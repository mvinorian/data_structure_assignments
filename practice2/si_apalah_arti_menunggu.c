#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

/**
 * Node structure and
 * uniqueBST structure
 */

typedef struct bstnode_t {
    int hp, atk, s;
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

BSTNode* __bst__createNode(int hp, int atk, int s) {
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->hp = hp;
    newNode->atk = atk;
    newNode->s = s;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode* __bst__insert(BSTNode *root, int hp, int atk, int s) {
    if (root == NULL) 
        return __bst__createNode(hp, atk, s);

    if (hp < root->hp)
        root->left = __bst__insert(root->left, hp, atk, s);
    else if (hp > root->hp)
        root->right = __bst__insert(root->right, hp, atk, s);
    
    return root;
}

BSTNode* __bst__search(BSTNode *root, int hp) {
    while (root != NULL) {
        if (hp < root->hp)
            root = root->left;
        else if (hp > root->hp)
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

BSTNode* __bst__remove(BSTNode *root, int hp) {
    if (root == NULL) return NULL;

    if (hp > root->hp) 
        root->right = __bst__remove(root->right, hp);
    else if (hp < root->hp) 
        root->left = __bst__remove(root->left, hp);
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
        root->hp     = temp->hp;
        root->right   = __bst__remove(root->right, temp->hp);
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

bool bst_find(BST *bst, int hp) {
    BSTNode *temp = __bst__search(bst->_root, hp);
    if (temp == NULL)
        return false;
    
    if (temp->hp == hp)
        return true;
    else
        return false;
}

void bst_insert(BST *bst, int hp, int atk, int s) {
    if (!bst_find(bst, hp)) {
        bst->_root = __bst__insert(bst->_root, hp, atk, s);
        bst->_size++;
    }
}

void bst_remove(BST *bst, int hp) {
    if (bst_find(bst, hp)) {
        bst->_root = __bst__remove(bst->_root, hp);
        bst->_size--;
    }
}

/**
 * CUSTOM FUNCTION
 */

void __bst__fight(BSTNode *root, int dt0, int *dt, int *ds, int *bb){
    if(root == NULL) return;
    __bst__fight(root->left, dt0, dt, ds, bb);
    __bst__fight(root->right, dt0, dt, ds, bb);

    if(*bb <= 0) return;

    if(root->atk < *ds){
        if(root->s == 1) *dt = *dt + root->hp;
    }else{
        *dt = *dt - root->atk;
    }
    
    if(*dt <= 0 && *bb > 0){
        *dt = dt0;
        *bb = *bb - 1;
    }
}

void __bst__printFight(BSTNode *root, int dt0, int *dt, int *ds, int *bb){
    if(root == NULL) return;
    __bst__printFight(root->left, dt0, dt, ds, bb);
    __bst__printFight(root->right, dt0, dt, ds, bb);
    
    if(*bb <= 0){
        printf("Ybag gagal sebelum lawan %d\n", root->hp);
        return;
    }

    if(root->atk < *ds){
        if(root->s == 1){
            printf("Kerbau %d membuat Ybag semakin posesif\n", root->hp);
            *dt = *dt + root->hp;
        }else printf("Jujur Jd canggung bgt lawan setelah lawan kerbau %d\n", root->hp);
    }else{
        if(root->s == 1) printf("Kerbau %d membuat Ybag kewalahan\n", root->hp);
        else printf("udah deh, gausa cari perkara lawan kerbau %d\n", root->hp);
        *dt = *dt - root->atk;
    }
    
    if(*dt <= 0 && *bb > 0){
        *dt = dt0;
        *bb = *bb - 1;
    }
    
    // printf("hp: %d; dt: %d; atk: %d; ds: %d; bb: %d;\n", root->hp, *dt, root->atk, *ds, *bb);
}

bool bst_fight(BST *bst, int dt, int ds, int bb, int t){
    int dt0 = dt, ds0 = ds, bb0 = bb;
    if(bst->_root->left != NULL) __bst__fight(bst->_root->left, dt0, &dt, &ds, &bb);
    if(bst->_root->right != NULL) __bst__fight(bst->_root->right, dt0, &dt, &ds, &bb);
    if(bb <= 0 && t > 0) return false;

    dt = dt0; ds = ds0; bb = bb0;
    if(bst->_root->left != NULL) __bst__printFight(bst->_root->left, dt0, &dt, &ds, &bb);
    if(bst->_root->right != NULL) __bst__printFight(bst->_root->right, dt0, &dt, &ds, &bb);
    if(bb > 0) printf("Makasi banya ya:)\n");
    else printf("gajadi gapapa_-\n");
    
    return true;
}

int main(){
    int n, t, a, b, c;
    BST bst;
    bst_init(&bst);
    scanf("%d %d", &n, &t);

    bst_insert(&bst, 50000, 696969, 0);
    while(n--){
        scanf("%d %d %d", &a, &b, &c);
        bst_insert(&bst, a, c, b);
    }

    while(t--){
        scanf("%d %d %d", &a, &b, &c);
        if(bst_fight(&bst, a, b, c, t)) break;
    }

    return 0;
}