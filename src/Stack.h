/*Function templates are special functions that can operate
with generic types. This allows us to create a function
template whose functionality can be adapted to more than
one type or class without repeating the entire code for each type.*/

/*To use this function template we use the following format for the function call:

function_name <type> (parameters);

*/
#include "iostream"
using namespace std;

template <typename T>
class Stack {
public:
    Stack(){
        _head = NULL; //an empty stack
        _size = 0;
    }
    ~Stack(){
        cout << "destructor has been called" << endl;
    }

    bool isEmpty() const{
        if(_head == NULL){
            return true;
        }
        else{
            return false;
        }
    }
    int size() const{
        return _size;
    }

    //Push: Place item on top of the stack
    void push(const T& newItem){
        // Create new node temp and allocate memory
        ListNode* temp;
        temp = new ListNode();
        temp->item = newItem;

        // Put top pointer reference into temp link
        temp->next = _head;

        // Make temp as top of Stack
        _head = temp;
        _size++; //increase the size of the stack
    }
    //Top: Take a look at the topmost item without removing it
    void getTop(T& stackTop) const{
        if (!isEmpty())
            stackTop = _head->item;
        else {
            cout << "\nStack is empty" << endl;
            exit(1);
        }
    }
    //Pop: Remove item from the top of the stack
    void pop(){
        ListNode* temp;
        // Check for stack underflow
        if (_head == NULL) {
            cout << "\nStack Underflow" << endl;
            exit(1);
        }
        else {
            temp = _head;
            // Assign second node to top
            _head = _head->next;
            // Destroy connection between first and second
            temp->next = NULL;
            free(temp);
            _size--; //decrease the size of the stack
        }
    }

private:
    struct ListNode {
        T item;
        ListNode* next;
    };
    ListNode* _head;
    int _size;
};







