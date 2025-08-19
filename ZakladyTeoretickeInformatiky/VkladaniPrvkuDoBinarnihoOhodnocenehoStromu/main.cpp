#include <iostream>


class Node
{
    public:
    int key;
    Node* right;
    Node* left;

    Node(int key)
    {
        this->key = key;
        right = NULL;
        left = NULL;
    }
};


 
/*
    Complexity of inserting element into a binary tree

    +-------------------+------------------------------+------------------------------+
|                   | Unbalanced Tree (General)    | Complete/Balanced Tree       |
+-------------------+------------------------------+------------------------------+
| Example Shape     |   1                          |       2                      |
|                   |  / \                         |      / \                     |
|                   | o   2                        |     1   3                    |
|                   |    / \                       |    / \ / \                   |
|                   |   o   3                      |   o  o o  o                   |
+-------------------+------------------------------+------------------------------+
| Best Case         | 1 check                      | 1 check                      |
| Worst Case        | Search(3) → 3 checks         | Search(3) → 2 checks         |
+-------------------+------------------------------+------------------------------+
| Worst-case time   | O(height)                    | O(height)                    |
| Max height        | N  → O(N)                    | ⌊log₂ N⌋ + 1 → O(log₂ N)     |
| Min height        | ⌊log₂ N⌋ + 1 → O(log₂ N)     | ⌊log₂ N⌋ + 1 → O(log₂ N)     |
+-------------------+------------------------------+------------------------------+
| Balanced Tree     | Not necessarily balanced     | No two siblings differ in    |
| Definition        |                              | height by more than 1        |
+-------------------+------------------------------+------------------------------+

*/



Node * insert(int key, Node* root)
{
    // if the current node is empty, we create a new one  
    if(root == NULL)
    {
        return new Node(key);
    }

    // if the value of current node is equal to key, we just replace it 
    if(root->key == key)
    {
        return root;
    }


    //if the value of the current node is bigger than the key we want to insert, we go to left child recursively and if it is smaller we do the same but left   
    if(root->key > key)
    {
        root->left = insert(key,root->left);
    }
    else
    {
        root->right = insert(key,root->right);
    }

    return root;
}


void print_tree(Node * node)
{
    if(node != NULL)
    {
        print_tree(node->left);
        std::cout<< node->key << " ";
        print_tree(node->right);
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
    root = insert(10,root);

    
    insert(20,root);
    insert(30,root);
    insert(40,root);
    insert(50,root);
    insert(60,root);
    insert(70,root);
    

    print_tree(root);
    std::cout << "\n";


    int a = 10;
    std::cout << "the value of a before increment is: "<< a<< std::endl;
    increment_value(&a);
    std::cout << "the value of a after increment is: "<< a<< std::endl;
    return 0;
}

