#include "../include/project/binary_search_tree.h"

#include <algorithm>
#include <stdexcept>

BinarySearchTree::BinarySearchTree() : root_(nullptr), size_(0) {}

BinarySearchTree::~BinarySearchTree() {
    deleteSubtree(root_);
}

void BinarySearchTree::deleteSubtree(TreeNode* node) {
    if (node == nullptr) {
        return;
    }

    deleteSubtree(node->left);
    deleteSubtree(node->right);
    delete node;
}

bool BinarySearchTree::insert(int value){
TreeNode* nNode = new TreeNode(value);
if(root_ == nullptr){
    root_ = nNode;
    size_++;
    return true;
    } //If the root doesn't exist, then root becomes the value we set.
TreeNode *current = root_; //Our cursor that we can walk the node with
while(true){
    if(value == current->value){ //Checks if the node's value is duplicate. Starts at root.
        delete nNode;   //Delete nNode, we don't need it.
        return false; //Return's false
    }
//Core BST Logic, checks if current's value is < value we are trying to insert
//if so, it goes down left path.
//if not, we go right.
    if(value < current->value){
        if(current->left == nullptr){
            current->left = nNode; //Sets new value as node
            ++size_;
            return true;
        }
        current = current->left;
    } else{
            if(current->right == nullptr){
                current->right = nNode; //Sets new value as node
                ++size_;
                return true;
            }
            current = current->right;
        }
    }
}

bool BinarySearchTree::remove(int value) {
    TreeNode* prev = nullptr;
    TreeNode* current = root_;

    while(current != nullptr && current->value != value){
        if(value < current->value){
            prev = current;
            current = current->left;
        } else {
            prev = current;
            current = current->right;
        }
    }
    if (current == nullptr) {
        return false;
    }

        if(current->left == nullptr && current->right == nullptr){
            if(prev == nullptr){
                root_ = nullptr;
            }
            else if(prev->left == current){
                prev->left = nullptr;

            }else{
                prev->right = nullptr;
            }
            delete current;
            --size_;
            return true;
        }

        if((current -> left == nullptr) != (current -> right == nullptr)){
            TreeNode* child = (current->left != nullptr) ? current->left : current->right;

            if(prev == nullptr){
                root_ = child;
                delete current;
                --size_;
                return true;
            }

            else if(prev->left == current){
                prev->left = child;
                delete current;
                --size_;
                return true;
            } else{
                prev->right = child;
                delete current;
                --size_;
                return true;
            }
        }

        if(current->left != nullptr && current->right != nullptr){
            TreeNode* successor = current->right;
            TreeNode* successorParent = current;

            while(successor->left != nullptr){
                successorParent = successor;
                successor = successor->left;
            }
            current->value = successor->value;

            if (successorParent->left == successor) {
                successorParent->left = successor->right;
            } else {
                successorParent->right = successor->right;
            }
            delete successor;
            --size_;
            return true;
        }
        return false;
}


bool BinarySearchTree::search(int value) const {
    if(root_ == nullptr){
        return false;
    }
    TreeNode* seek = root_;

    while(seek != nullptr && seek->value != value){
        if(value < seek->value ){
            seek = seek->left;
        }
        else if(value > seek->value ){
            seek = seek->right;
        }
    }
    return seek != nullptr;
}

bool BinarySearchTree::contains(int value) const {
    return search(value);
}

bool BinarySearchTree::empty() const noexcept {
    return size_ == 0;
}

std::size_t BinarySearchTree::size() const noexcept {
    return size_;
}

int BinarySearchTree::height() const {
    return heightRecursive(root_);
}

std::vector<int> BinarySearchTree::inorderTraversal() const {
    std::vector<int> result;
    inorderRecursive(root_, result);
    return result;
}

std::vector<int> BinarySearchTree::preorderTraversal() const {
    std::vector<int> result;
    preorderRecursive(root_, result);
    return result;
}

std::vector<int> BinarySearchTree::postorderTraversal() const {
    std::vector<int> result;
    postorderRecursive(root_, result);
    return result;
}

int BinarySearchTree::minimum() const {
    if (empty()) {
        throw std::logic_error("BST is empty");
    }
    return minimumRecursive(root_);
}

int BinarySearchTree::maximum() const {
    if (empty()) {
        throw std::logic_error("BST is empty");
    }
    return maximumRecursive(root_);
}

TreeNode* BinarySearchTree::insertRecursive(TreeNode* node, int value) {
    if(node == nullptr){
        ++size_;
        return new TreeNode(value);
    }
    if(value < node->value){
        node->left = insertRecursive(node->left, value);
    }
    if(value > node->value){
        node->right = insertRecursive(node->right, value);
    }
    return node;
}

TreeNode* BinarySearchTree::removeRecursive(TreeNode* node, int value) {
    if(node == nullptr){
        return nullptr;
    }
    if(value < node->value){
        node->left = removeRecursive(node->left, value);
    } else if (value > node->value) {
        node->right = removeRecursive(node->right, value);
    } else {
         if (node->left == nullptr && node->right == nullptr){
             delete node;
             --size_;
             return nullptr;
        }
         if (node->left == nullptr || node->right == nullptr){
             TreeNode* child = (node->left != nullptr) ? node->left : node->right;
             delete node;
             --size_;
             return child;
        }
         TreeNode* successor = node->right;

         while (successor->left != nullptr){
             successor = successor->left;
        }
         node->value = successor->value;
         node->right = removeRecursive(node->right, successor->value);
    }

     return node;
}


bool BinarySearchTree::searchRecursive(const TreeNode* node, int value) const {
    if(node == nullptr){
        return false;
    }

    if(node->value == value){
        return true;
    }

    if(node->value > value){
       return searchRecursive(node->left, value);
    }
       return searchRecursive(node->right, value);
       //O(h), it follows down one path.
}

void BinarySearchTree::inorderRecursive(const TreeNode* node, std::vector<int>& result) const {
    if (node == nullptr) {
         return;
     }

    inorderRecursive(node->left, result);
    result.push_back(node->value);
    inorderRecursive(node->right, result);
    //O(n)
}

void BinarySearchTree::preorderRecursive(const TreeNode* node, std::vector<int>& result) const {
    if (node == nullptr) {
         return;
     }

    result.push_back(node->value);
    preorderRecursive(node->left, result);
    preorderRecursive(node->right, result);
    //O(n)
}

void BinarySearchTree::postorderRecursive(const TreeNode* node, std::vector<int>& result) const {
    if (node == nullptr) {
         return;
     }

    postorderRecursive(node->left, result);
    postorderRecursive(node->right, result);
    result.push_back(node->value);
    //O(n)
}

int BinarySearchTree::heightRecursive(const TreeNode* node) const {
    if (node == nullptr) {
        return 0;
    }
    int l =heightRecursive(node->left);
    int r =heightRecursive(node->right);

    return 1+ std::max(l , r);
    /*this is O(n). It makes a reccursive call on EVERY left and right, and keeps doing so to find the deepest one */
}

int BinarySearchTree::minimumRecursive(const TreeNode* node) const {
    if(node->left == nullptr){
        return node->value;
    }
    return minimumRecursive(node->left);
    //O(h)
}

int BinarySearchTree::maximumRecursive(const TreeNode* node) const {
    if(node->right == nullptr){
        return node->value;
    }
    return maximumRecursive(node->right);
    //O(h)
}
