/*
Oto implementacja działania drzewa binarnego, gdzie w działaniu programu będzie można (z poziomu użytkownika wpisać następujące opcje): 


init_tree - Inicjalizuje drzewo zdefiniowane wcześniej w programie 

insert value - wstawia do drzewa binarnego wartość value (liczba całkowita). W przypadku wprowadzenia tej samej wartości, węzeł ma je zliczać. 
 
search value - wyświetla True/False, jeżeli value znajduje się w drzewie binarnym 

delete value - usuwa węzeł z wartością value (liczba całkowita) w drzewie binarnym. W przypadku usunięcia wartości z węzła, która ma więcej niż jedną wartość, ilość elementów ma się zmniejszać. Przyjmujemy tutaj strategię znajdywania poprzednika w przypadku, kiedy węzeł ma obydwu synów. 

in_order - wypisuje porządek inorder drzewa binarnego 

pre_order - wypisuje porządek preorder drzewa binarnego 

post_order - wypisuje porządek postorder drzewa binarnego 

Program jest napisany w C++ i używa wskaźników. Struktura jest generowana dynamicznie. 

W przypadku występowania błędu w jakiejkolwiek metodzie program wyświetlia komunikat Error nazwa_metody. 

Sample Input jest skonstruowany jako ciąg poleceń reprezentujący powyższe metody.  

Sample output wyświetla wyniki (jeśli metoda ma je zwracać) używanej metody. 
  
Sample Input:  

init_tree 
insert 5 
insert 1 
insert 10 
insert 5 
insert 10 
in_order 
pre_order 
post_order 
search 1 
search 2 
delete 10 
search 10  

Sample Output:  

1 5:2 10:2 
5:2 1 10:2 
1 10:2 5:2 
True 
False 
True 

*/

#include <iostream> 
#include <sstream> 

 
using namespace std; 

  

struct Node { 

    int value; 

    int count;   

    Node* left; 

    Node* right; 

  

    Node(int value) { 

        this->value = value; 

        this->count = 1;   

        this->left = nullptr; 

        this->right = nullptr; 

    } 

}; 

  

class BinaryTree { 

private: 

    Node* root; 

  

    void inOrder(Node* node, stringstream& s) { 

    if (node == nullptr) { 

        return; 

    } 

    inOrder(node->left, s); 

    if (node->count > 1) { 

        s << node->value << ":" << node->count << " "; 

    } else { 

        s << node->value << " "; 

    } 

    inOrder(node->right, s); 

  

} 

  

void postOrder(Node* node, stringstream& s) { 

    if (node == nullptr) { 

        return; 

    } 

    postOrder(node->left, s); 

    postOrder(node->right, s); 

    if (node->count > 1) { 

        s << node->value << ":" << node->count << " "; 

    } else { 

        s << node->value << " "; 

    } 

} 

  

void preOrder(Node* node, stringstream& s) { 

    if (node == nullptr) { 

        return; 

    } 

    if (node->count > 1) { 

        s << node->value << ":" << node->count << " "; 

    } else { 

        s << node->value << " "; 

    } 

    preOrder(node->left, s); 

    preOrder(node->right, s); 

} 

  

public: 

    BinaryTree() { 

        root = nullptr; 

    } 

  

void insert(int value) { 

    if (root == nullptr) { 

        root = new Node(value); 

        return; 

    } 

    Node* current = root; 

    while (true) { 

        if (value < current->value) { 

            if (current->left == nullptr) { 

                current->left = new Node(value); 

                break; 

            } 

            current = current->left; 

        } else if (value > current->value) { 

            if (current->right == nullptr) { 

                current->right = new Node(value); 

                break; 

            } 

            current = current->right; 

        } else { 

            current->count++;  

            break; 

        } 

    } 

} 

    bool search(int value) { 

    Node* current = root; 

    while (current != nullptr) { 

        if (value < current->value) { 

            current = current->left; 

        } else if (value > current->value) { 

            current = current->right; 

        } else { 

            return true; 

        } 

    } 

    return false; 

} 

    void deleteValue(int value) { 

    root = deleteValue(root, value); 

} 

     

Node* deleteValue(Node* node, int value) { 

    if (node == nullptr) { 

        return nullptr; 

    } 

    if (value < node->value) { 

        node->left = deleteValue(node->left, value); 

    } else if (value > node->value) { 

        node->right = deleteValue(node->right, value); 

    } else { 

        node->count--;  // decrement count 

        if (node->count == 0) { 

            if (node->left == nullptr && node->right == nullptr) { 

                delete node; 

                return nullptr; 

            } 

            if (node->left == nullptr) { 

                Node* temp = node->right; 

                delete node; 

                return temp; 

            } 

            if (node->right == nullptr) { 

                Node* temp = node->left; 

                delete node; 

                return temp; 

            } 

            node->value = findMax(node->left)->value;   

            node->count = findMax(node->left)->count;  

            node->left = deleteValue(node->left, node->value);   

        } 

    } 

    return node; 

} 

Node* findMax(Node* node) { 

    while (node->right != nullptr) { 

        node = node->right; 

    } 

    return node; 

} 

Node* findMin(Node* node) { 

    while (node->left != nullptr)  

    { 

        node = node->left; 

    } 

    return node; 

    } 

    string inOrder() { 

        stringstream s; 

        inOrder(root, s); 

        string output = s.str(); 

        output = output.substr(0, output.length() - 1); 

        return output; 

    } 

    string postOrder() { 

        stringstream s; 

        postOrder(root, s); 

        string output = s.str(); 

        output = output.substr(0, output.length() - 1); 

        return output; 

    } 

    string preOrder() { 

        stringstream s; 

        preOrder(root, s); 

        string output = s.str(); 

        output = output.substr(0, output.length() - 1); 

        return output; 

    } 

}; 

int main() { 

    BinaryTree tree; 

    bool initialized = false; 

    while (true) { 

        string input; 

        getline(cin, input); 

        if (input.empty()) { 

            break; 

        } 

        istringstream iss(input); 

        string command; 

        iss >> command; 

  

        if (command == "init_tree") { 

            tree = BinaryTree(); 

            initialized =true; 

  

        } else if (command == "insert") { 

            if(initialized) 

            { 

            int value; 

            iss >> value; 

            tree.insert(value); 

            } else 

            cout<<"Error insert"<<endl; 

             

        } else if (command == "in_order") { 

              if(initialized) 

            { 

            string inOrderOutput = tree.inOrder(); 

            cout << inOrderOutput <<endl; 

            } else 

            cout<<"Error in_order"<<endl; 

             

        } else if (command == "post_order") { 

            if(initialized) 

            { 

                string postOrderOutput = tree.postOrder(); 

                cout << postOrderOutput <<endl; 

            } 

            else 

            cout<<"Error post_order"<<endl; 

             

        }  else if (command == "pre_order") { 

            if(initialized) 

            { 

                string preOrderOutput = tree.preOrder(); 

                cout<< preOrderOutput << endl; 

            } 

            else  

            cout<<"Error pre_order"<<endl; 

  

        } else if(command == "search" ) { 

            if(initialized) 

            { 

                int value; 

                iss >> value; 

                if(tree.search(value)) 

                cout<<"True"<<endl; 

                else 

                cout<<"False"<<endl; 

               } 

            else 

            cout<<"Error search"<<endl; 

             

        }  else if(command == "delete") 

        { 

            if(initialized) 

            { 

  

                int value; 

                iss >> value; 

                if(tree.search(value)) 

                tree.deleteValue(value); 

                else 

                {cout<< "Error delete"<<endl;} 

            } else 

            cout<<"Error delete"<<endl; 

             

        } 

    }  

    return 0; 

} 