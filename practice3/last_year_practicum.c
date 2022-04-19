#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#define M (ll)(1e9+7)
#define ll long long

typedef struct AVLNode_t
{
    ll data;
    struct AVLNode_t *left,*right;
    ll height, size;
}AVLNode;

typedef struct AVL_t
{
    AVLNode *_root;
    unsigned ll _size;
}AVL;

ll size(AVLNode *root){
    if(root) return root->size;
    return 0;
}

AVLNode* _avl_createNode(ll value) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->height=1;
    newNode->size=1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

AVLNode* _search(AVLNode *root, ll value, ll *count) {
    while (root != NULL) {
        if (value < root->data)
            root = root->left;
        else if (value > root->data){
            *count = *count + size(root->left) + 1;
            root = root->right;
        }
        else{
            *count = *count + size(root->left);
            return root;
        }
    }
    return root;
}

ll _getHeight(AVLNode* node){
    if(node==NULL)
        return 0; 
    return node->height;
}

ll _max(ll a,ll b){
    return (a > b)? a : b;
}

AVLNode* _rightRotate(AVLNode* pivotNode) {

    AVLNode* newParrent=pivotNode->left;
    pivotNode->left=newParrent->right;
    newParrent->right=pivotNode;

    pivotNode->height=_max(_getHeight(pivotNode->left),
                      _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left),
                       _getHeight(newParrent->right))+1;
    pivotNode->size = size(pivotNode->left) + size(pivotNode->right) + 1;
    newParrent->size = size(newParrent->left) + size(newParrent->right) + 1;
    
    return newParrent;
}

AVLNode* _leftRotate(AVLNode* pivotNode) {

    AVLNode* newParrent=pivotNode->right;
    pivotNode->right=newParrent->left;
    newParrent->left=pivotNode;

    pivotNode->height=_max(_getHeight(pivotNode->left),
                      _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left),
                       _getHeight(newParrent->right))+1;
    pivotNode->size = size(pivotNode->left) + size(pivotNode->right) + 1;
    newParrent->size = size(newParrent->left) + size(newParrent->right) + 1;
    
    return newParrent;
}

AVLNode* _leftCaseRotate(AVLNode* node){
    return _rightRotate(node);
}

AVLNode* _rightCaseRotate(AVLNode* node){
    return _leftRotate(node);
}

AVLNode* _leftRightCaseRotate(AVLNode* node){
    node->left=_leftRotate(node->left);
    return _rightRotate(node);
}

AVLNode* _rightLeftCaseRotate(AVLNode* node){
    node->right=_rightRotate(node->right);
    return _leftRotate(node);
}

ll _getBalanceFactor(AVLNode* node){
    if(node==NULL)
        return 0;
    return _getHeight(node->left)-_getHeight(node->right);
}

AVLNode* _insert_AVL(AVL *avl,AVLNode* node,ll value) {
    
    if(node==NULL)
        return _avl_createNode(value);
    if(value < node->data)
        node->left = _insert_AVL(avl,node->left,value);
    else if(value > node->data)
        node->right = _insert_AVL(avl,node->right,value);
    
    node->size = size(node->left) + size(node->right) + 1;
    node->height= 1 + _max(_getHeight(node->left),_getHeight(node->right)); 

    ll balanceFactor=_getBalanceFactor(node);
    
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

AVLNode* _remove_AVL(AVLNode* node,ll value){
    if(node==NULL)
        return node;
    if(value > node->data)
        node->right=_remove_AVL(node->right,value);
    else if(value < node->data)
        node->left=_remove_AVL(node->left,value);
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
    node->size = size(node->left) + size(node->right) + 1;

    ll balanceFactor= _getBalanceFactor(node);
    
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

ll avl_find(AVL *avl, ll value) {
    ll count = 0;
    AVLNode *temp = _search(avl->_root, value, &count);
    if (temp == NULL)
        return 0;
    
    if (temp->data == value)
        return count;
    else
        return 0;
}

void avl_insert(AVL *avl,ll value){
    avl->_root=_insert_AVL(avl,avl->_root,value);
    avl->_size++;

}

void avl_remove(AVL *avl,ll value){
    avl->_root=_remove_AVL(avl->_root,value);
    avl->_size--;

}

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        ll n;
        scanf("%lld", &n);
        AVL avl;
        avl_init(&avl);
        
        ll f[n], a[n];
        f[0] = 1;
        for(ll i = 0; i < n; i++){
            scanf("%lld", &a[i]);
            avl_insert(&avl, a[i]);
            if(i > 0) f[i] = (i * (f[i-1]%M)) % M;
        }
        
        ll rank, res = 1;
        for(ll i = 0; i < n; i++){
            rank = avl_find(&avl,a[i]);
            res = ((res%M) + ((f[n-i-1]%M)*(rank%M))%M)%M;
            avl_remove(&avl, a[i]);
        }
        printf("%lld\n", res);
    }

    return 0;
}