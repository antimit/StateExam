#include <iostream>

class Node {
    public:
    Node(int key)
    {
        this->right = NULL;
        this->left= NULL;
        this->key = key;
    }
    Node * right;
    Node * left;
    int key;
};



//if the node has two children replace it with the smallest on from right subtree 
Node * FindMin(Node * root)
{
    while(root->left)
    {
        root = root->left;
    }
    return root;
}

Node* Insert(int key, Node* root)
{
    if(root == NULL)
    {
        return new Node(key);
    }

    if(root->key == key)
    {
        return root;
    }

    if(root->key > key)
    {
        root->left = Insert(key,root->left);
    }
    else
    {
        root->right = Insert(key, root->right);
    }

    return root;
    
}


/*
    Complexity of deleting an element from a binary search tree

    +-------------------+------------------------------+------------------------------+
    |                   | Unbalanced Tree (General)    | Complete/Balanced Tree       |
    +-------------------+------------------------------+------------------------------+
    | Example Shape     |   1                          |       2                      |
    |                   |  / \                         |      / \                     |
    |                   | o   2                        |     1   3                    |
    |                   |    / \                       |    / \ / \                   |
    |                   |   o   3                      |   o  o o  o                   |
    +-------------------+------------------------------+------------------------------+
    | Best Case         | Delete a leaf → 1 search +   | Delete a leaf → 1 search +   |
    |                   | O(1) removal = O(1) + O(N)   | O(1) removal = O(1) + O(logN)|
    +-------------------+------------------------------+------------------------------+
    | Worst Case        | Delete node with 2 children  | Delete node with 2 children  |
    |                   | → Search path length N +     | → Search path length logN +  |
    |                   | find successor/predecessor N | find successor/predecessor   |
    |                   | → O(N) total                 | logN → O(logN) total         |
    +-------------------+------------------------------+------------------------------+
    | Worst-case time   | O(height) + O(height)        | O(height) + O(height)        |
    |                   | = O(N)                       | = O(log₂ N)                  |
    | Max height        | N  → O(N)                    | ⌊log₂ N⌋ + 1 → O(log₂ N)     |
    | Min height        | ⌊log₂ N⌋ + 1 → O(log₂ N)     | ⌊log₂ N⌋ + 1 → O(log₂ N)     |
    +-------------------+------------------------------+------------------------------+
    | Balanced Tree     | Not necessarily balanced     | No two siblings differ in    |
    | Definition        |                              | height by more than 1        |
    +-------------------+------------------------------+------------------------------+

    // Deletion involves:
    // 1. Searching for the target node → O(height)
    // 2. Removing it:
    //    - Leaf → O(1)
    //    - One child → O(1)
    //    - Two children → Find successor/predecessor (O(height)), 
    //      replace value, and delete successor/predecessor
    //
    // Balanced tree worst case:
    // O(log N) + O(log N) = O(log N)
*/

Node * Delete(int key, Node * root)
{
    //Go to the left
    if(root->key > key)
    {
        root->left = Delete(key,root->left);
    }

    //Go to the right
    else if( root->key < key)
    {
        root->right = Delete(key, root->right);
    }
    else
    {
        // no children (a leaf)
        if(root->left == NULL && root->right == NULL)
        {
            delete(root);
            root = NULL;
        }
        //1 left child
        else if(root->right==NULL)
        {
            Node * temp = root;
            root = root->left;
            delete(temp);
        }

        //1 right child
        else if(root->left == NULL)
        {
            Node * temp = root;
            root = root->right;
            delete(temp);
        }
        
        //2 children
        else
        {
            Node * temp = FindMin(root);
            root->key = temp->key;
            root->right = Delete(key,root->right);
            delete(temp);
        }

    }

    return root;

}

void print_tree(Node * root)
{
    if(root!=NULL)
    {
        print_tree(root->left);
        std::cout << root->key << " "; 
        print_tree(root->right);
    }
}



void increment_value(int * a)
{
    if(a!=NULL)
    {
        (*a)++;
    }
}



int main()
{
    Node * root = NULL;

    root = Insert(10,root);

    Insert(20,root);
    // Insert(30,root);
    // Insert(40,root);
    // Insert(50,root);
    // Insert(60,root);
    // Insert(70,root);

    print_tree(root);

    std::cout << std::endl;


    root = Delete(10,root);

    print_tree(root);


    int a = 10;
    std::cout << "the value of a before increment is: "<< a<< std::endl;
    increment_value(&a);
    std::cout << "the value of a after increment is: "<< a<< std::endl;
}