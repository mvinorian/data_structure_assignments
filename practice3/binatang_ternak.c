#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct AVLNode_t
{
    int data;
    struct AVLNode_t *parent, *left,*right;
    int height;
}AVLNode;

typedef struct AVL_t
{
    AVLNode *_root;
    unsigned int _size;
}AVL;

AVLNode* _avl_createNode(AVLNode *parent, int value) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->height=1;
    newNode->parent = parent;
    newNode->left = newNode->right = NULL;
    return newNode;
}

AVLNode* _search(AVLNode *root, int value) {
    while (root != NULL) {
        if (value < root->data)
            root = root->left;
        else if (value > root->data)
            root = root->right;
        else
            return root;
    }
    return root;
}

int _getHeight(AVLNode* node){
    if(node==NULL)
        return 0; 
    return node->height;
}

int _max(int a,int b){
    return (a > b)? a : b;
}

AVLNode* _rightRotate(AVLNode* pivotNode) {

    AVLNode* newParrent = pivotNode->left;
    newParrent->parent = pivotNode->parent;
    if(newParrent->right) newParrent->right->parent = pivotNode;
    pivotNode->left = newParrent->right;
    pivotNode->parent = newParrent;
    newParrent->right = pivotNode;

    pivotNode->height=_max(_getHeight(pivotNode->left),
                      _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left),
                       _getHeight(newParrent->right))+1;
    
    return newParrent;
}

AVLNode* _leftRotate(AVLNode* pivotNode) {

    AVLNode* newParrent = pivotNode->right;
    newParrent->parent = pivotNode->parent;
    if(newParrent->left) newParrent->left->parent = pivotNode;
    pivotNode->right = newParrent->left;
    pivotNode->parent = newParrent;
    newParrent->left = pivotNode;

    pivotNode->height=_max(_getHeight(pivotNode->left),
                      _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left),
                       _getHeight(newParrent->right))+1;
    
    return newParrent;
}

AVLNode* _leftCaseRotate(AVLNode* node){
    return _rightRotate(node);
}

AVLNode* _rightCaseRotate(AVLNode* node){
    return _leftRotate(node);
}

AVLNode* _leftRightCaseRotate(AVLNode* node){
    AVLNode *newLeft = _leftRotate(node->left);
    if(newLeft) newLeft->parent = node;
    node->left = newLeft;
    return _rightRotate(node);
}

AVLNode* _rightLeftCaseRotate(AVLNode* node){
    AVLNode *newRight = _rightRotate(node->right);
    if(newRight) newRight->parent = node;
    node->right = newRight;
    return _leftRotate(node);
}

int _getBalanceFactor(AVLNode* node){
    if(node==NULL)
        return 0;
    return _getHeight(node->left)-_getHeight(node->right);
}

AVLNode* _insert_AVL(AVL *avl,AVLNode* node,AVLNode* parent,int value) {
    
    if(node==NULL) // udah mencapai leaf
        return _avl_createNode(parent, value);
    if(value < node->data){
        AVLNode* newLeft = _insert_AVL(avl, node->left, node, value);
        if(newLeft) newLeft->parent = node;
        node->left = newLeft;
    }
    else if(value > node->data){
        AVLNode* newRight = _insert_AVL(avl, node->right, node, value);
        if(newRight) newRight->parent = node;
    	node->right = newRight;
    }
    
    node->height= 1 + _max(_getHeight(node->left),_getHeight(node->right)); 

    int balanceFactor=_getBalanceFactor(node);
    
    if(balanceFactor > 1 && value < node->left->data) // skewed kiri (left-left case)
        return _leftCaseRotate(node);
    if(balanceFactor > 1 && value > node->left->data) // 
		return _leftRightCaseRotate(node);
    if(balanceFactor < -1 && value > node->right->data)
        return _rightCaseRotate(node);
    if(balanceFactor < -1 && value < node->right->data)
        return _rightLeftCaseRotate(node);
    
    return node;
}

AVLNode* _findMinNode(AVLNode *node) {
    AVLNode *currNode = node;
    while (currNode && currNode->left != NULL)
        currNode = currNode->left;
    return currNode;
}

AVLNode* _remove_AVL(AVLNode* node,int value){
    if(node==NULL)
        return node;
    if(value > node->data){
        AVLNode* newRight = _remove_AVL(node->right, value);
        if(newRight) newRight->parent = node;
    	node->right=newRight;
    }
    else if(value < node->data){
        AVLNode* newLeft = _remove_AVL(node->left, value);
        if(newLeft) newLeft->parent = node;
    	node->left=newLeft;
    }
    else{
        AVLNode *temp;
        if((node->left==NULL)||(node->right==NULL)){
            temp=NULL;
            if(node->left==NULL) temp=node->right;  
            else if(node->right==NULL) temp=node->left;
            
            if(temp==NULL){
                temp=node;
                node=NULL;
            }
            else
                *node=*temp;   
            
            free(temp);
        }
        else{
            temp = _findMinNode(node->right);
            node->data=temp->data;
            node->right=_remove_AVL(node->right,temp->data);
        }    
    }

	if(node==NULL) return node;
    
    node->height=_max(_getHeight(node->left),_getHeight(node->right))+1;

    int balanceFactor= _getBalanceFactor(node);
    
    if(balanceFactor>1 && _getBalanceFactor(node->left)>=0) 
        return _leftCaseRotate(node);

    if(balanceFactor>1 && _getBalanceFactor(node->left)<0) 
        return _leftRightCaseRotate(node);
  
    if(balanceFactor < -1 && _getBalanceFactor(node->right)<=0) 
        return _rightCaseRotate(node);

    if(balanceFactor < -1 && _getBalanceFactor(node->right)>0) 
        return _rightLeftCaseRotate(node);
    
    return node;
}

void avl_init(AVL *avl) {
    avl->_root = NULL;
    avl->_size = 0u;
}

bool avl_isEmpty(AVL *avl) {
    return avl->_root == NULL;
}

bool avl_find(AVL *avl, int value) {
    AVLNode *temp = _search(avl->_root, value);
    if (temp == NULL)
        return false;
    
    if (temp->data == value)
        return true;
    else
        return false;
}

void avl_insert(AVL *avl,int value){
    if(!avl_find(avl,value)){
        avl->_root=_insert_AVL(avl,avl->_root,NULL,value);
        avl->_size++;
    }

}

void avl_remove(AVL *avl,int value){
    if(avl_find(avl,value)){
        avl->_root=_remove_AVL(avl->_root,value);
        avl->_size--;
    }

}

void compute(AVL *avl, int value){
    AVLNode* node = _search(avl->_root, value);
    if(node == avl->_root){
        printf("0\n");
        return;
    }
    AVLNode* parent = node->parent;
    AVLNode* grandp = parent->parent;
    int diff = parent->data;
    if(grandp && grandp->left && grandp->right){
        if(grandp->left == parent) diff = abs(diff - grandp->right->data);
        else if(grandp->right == parent) diff = abs(diff - grandp->left->data);
    }
    printf("%d\n", diff);
}

int main(){
    AVL avl;
    avl_init(&avl);
    
    int n, t, x;
    scanf("%d %d", &n, &t);

    while(n--){
        scanf("%d", &x);
        avl_insert(&avl, x);
    }

    while(t--){
        scanf("%d", &x);
        compute(&avl, x);
    }

    return 0;
}