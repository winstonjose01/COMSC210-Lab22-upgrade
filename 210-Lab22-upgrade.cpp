// COMSC210 | Lab 22 | Winston Jose
// IDE used: Visual Studio Code
// Github link: 


#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int value) {
        Node* newNode = new Node(value);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }

    void delete_pos(int position){
        // Check if the position is valid (not negative)
        if (position < 0){
            cout << "Position muuse be >= 0."<< endl;
            return;
        }

        // Check if the list is empty
        if (!head){
            cout << "The list is empty." << endl;
            return;
        }

        Node *temp = head;

        // Traverse the list to the desired position
        for (int i = 0; i < position && temp; i++){
            temp = temp->next;
        }

        // Check if position exceeds the list size
        if (!temp){
            cout << "Position exceeds list size. Node does not exist" << endl;
            return;
        }
        
        // Unlink the node from the previouse node
        if (temp->prev){
            temp->prev->next = temp->next;
        }
        else{
            head = temp->next; // if deleting the head, updated the head
            if(head){
                head->next=nullptr;
            }
        }

        // Unlink the node from the next node
        if(temp->next){
            temp->next->prev = temp->prev; 
        }
        else{
            tail = tail->prev;
            if(tail){
                tail->next=nullptr; // If deleting the tail, update the tail
            }
        }
        delete temp; // Free memory for the deleted node

    }

    void pop_front(){
        if (!head) return; // Empty list

        Node *temp = head; // Assign temp the current head

        head = temp->next; // Update the head to the next node
        head->prev = nullptr; // Set the new head's previous pointer to nullptr

        delete temp; // Free memor
    }

    void pop_back(){
        if (!tail) return; // Empty list

        Node *temp = tail; // Assign temp to the current tail

        tail = temp->prev; // Update the tail to the previous node
        tail->next = nullptr; // Set the tail's next pointer to nullptr

        delete temp; // Free memory
    }

    void print() {
        Node* current = head;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {
    srand(time(0));
    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;
    int pos;

    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR-MIN_NR+1) + MIN_NR);
    cout << "List forward: ";
    list.print();

    cout << "List backward: ";
    list.print_reverse();

    cout << "\nWhat position do you want to delete :";
    cin >> pos;
    cout << "Deleting position " << pos << "." << endl;
    list.delete_pos(pos-1);
    cout << "\tUpdated list :";
    list.print();

    cout << "\nDeleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: ";
    list.print();

    return 0;
}
