Oto implementacja strukturey listy dowiązaniowej (jednokierunkowej, niecyklicznej, bez wartownika),
której elementami są słowa (czyli ciągi znaków), oraz operacje:

init_list - inicjalizuje listę 
add s - Wstawia słowo s na początek listy 
print - Wypisuje elementy listy. W przypadku pustej listy program ma wyświetlić ciąg []
search s - Wyświetla na ekranie wartość True/False, jeśli odpowiednio słowo s znajduje się na liście
remove s - Usuwa z listy węzeł zawierający słowo s, o ile takie słowo znajduje się na liście
clean - Usuwa wszystkie węzły listy, wraz z wyczyszczeniem pamięci
non_repeated - Usuwa z listy wszystkie powtarzające się elementy
merge - Dokonuje "scalenia" na końcu listy z ustawioną wcześniej na sztywno listą postaci: ["one" -> "two" -> "three"].
Zwróć uwagę na wyświetlenie listy metodą print.

Program jest napisany w języku C++ i używa wskaźników. Struktura powinna być generowana dynamicznie.

W przypadku występowania błędu w jakiejkolwiek metodzie program wyświetlia komunikat Error nazwa_metody.

Sample Input jest skonstruowany jako ciąg poleceń reprezentujący powyższe metody. 

Sample output wyświetla wyniki (jeśli metoda ma je zwracać) używanej metody.

Sample Input 1:

init_list
print
add ala
print
add ma
print
add kota
print
search ala
search kot
remove kota
print
clean
print
Sample Output 1:

[]
[ala]
[ma -> ala]
[kota -> ma -> ala]
True
False
[ma -> ala]
Error print
Sample Input 2:

init_list
add ala
add ma
add kota
print
remove ma
print
merge
print
Sample Output 2:

[kota -> ma -> ala]
[kota -> ala]
[kota -> ala -> one -> two -> three]
Sample Input 3:

init_list
print
merge
merge
print
non_repeated
print
Sample Output 3:

[]
[one -> two -> three -> one -> two -> three]
[one -> two -> three]
*/

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
struct Node {
  std::string data;
  Node* next;
};

class LinkedList {
private:
  Node* head;

public:
  LinkedList() { head = nullptr; }

  void init_list() { head = nullptr; }

  void add(std::string s) {
    Node* newNode = new Node;
    newNode->data = s;
    newNode->next = head;
    head = newNode;
  }

  void print() {
    Node* current = head;
    std::cout << "[";
    while (current != nullptr) {
      std::cout << current->data;
      if (current->next != nullptr) {
        std::cout << " -> ";
      }
      current = current->next;
    }
    std::cout << "]" << std::endl;
  }

  bool search(std::string s) {
    Node* current = head;
    while (current != nullptr) {
      if (current->data == s) {
        return true;
      }
      current = current->next;
    }
    return false;
  }

  void remove(std::string s) {
    

    if (head->data == s) {
      Node* temp = head;
      head = head->next;
      delete temp;
      return;
    }

    Node* current = head;
    while (current->next != nullptr && current->next->data != s) {
      current = current->next;
    }

  

    Node* temp = current->next;
    current->next = current->next->next;
    delete temp;
  }

  void clean() {
    while (head != nullptr) {
      Node* temp = head;
      head = head->next;
      delete temp;
    }
  }

  void non_repeated() {
    if (head == nullptr) {
      return;
    }

    Node* current = head;
    while (current != nullptr) {
      Node* runner = current;
      while (runner->next != nullptr) {
        if (runner->next->data == current->data) {
          Node* temp = runner->next;
          runner->next = runner->next->next;
          delete temp;
        } else {
          runner = runner->next;
        }
      }
      current = current->next;
    }
  }
  void merge() {
  if (head == nullptr) {
    head = new Node{"one"};  
    Node* current = head;
    current->next = new Node{"two"};
    current = current->next;
    current->next = new Node{"three"};
    return;
  }

  Node* current = head;
  while (current->next != nullptr) {
    current = current->next;
  }

  current->next = new Node{"one"};
  current = current->next;
  current->next = new Node{"two"};
  current = current->next;
  current->next = new Node{"three"};
}

};

int main() {
  LinkedList list;

  bool initialized = false;

  
   while (true) {
    std::string line;
    std::getline(std::cin, line);

    if (line.empty()) {
      break;
    }

    std::istringstream iss(line);
    std::string operation;
    iss >> operation;

    if (operation == "init_list") {
      list.init_list();
      initialized = true;
    } else if (operation == "add") {
        if (!initialized) {
        std::cout << "Error add" << std::endl;
        continue;
        }
      std::string s;
      iss >> s;
      list.add(s);
    } else if (operation == "print") {
      if (!initialized) {
        std::cout << "Error print" << std::endl;
        continue;
      }
      list.print();
    } else if (operation == "search") {
        if(!initialized)
        {
            std::cout << "Error search"<<std::endl; 
            continue;
        } 
      std::string s;
      iss >> s;
      if (list.search(s)) {
        std::cout << "True" << std::endl;
      } else {
        std::cout << "False" << std::endl;
      }
    } else if (operation == "remove") {
        if(!initialized)
        {
            std::cout << "Error remove"<<std::endl; 
            continue;
        }
      std::string s;
      iss >> s;
      list.remove(s);
    } else if (operation == "clean") {
        if(!initialized)
        {
            std::cout << "Error clean"<<std::endl; 
            continue;
        }
      initialized = false;
      list.clean();
    } else if (operation == "non_repeated") {
        if(!initialized)
        {
            std::cout << "Error non_repeated"<<std::endl; 
            continue;
        }
      list.non_repeated();
    } else if (operation == "merge") {
        if(!initialized)
        {
            std::cout << "Error merge"<<std::endl; 
            continue;
        }
      list.merge();
    }
  }

  return 0;
}