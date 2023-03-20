/*Function templates are special functions that can operate
with generic types. This allows us to create a function
template whose functionality can be adapted to more than
one type or class without repeating the entire code for each type.*/

/*To use this function template we use the following format for the function call:

function_name <type> (parameters);
*/
#include "iostream"
using namespace std;

template<typename T>
class Queue {
public:
    Queue(){
        //initially an empty queue
        _lastNode = _head = NULL;
        _size = 0;
    }
    ~Queue(){
        cout << "destructor has been called" << endl;
    }

    bool isEmpty() const{
        if(_head == NULL)
            return true;
        else
            return false;
    }
    int size() const{
        return _size;
    }

    //Enqueue: Items are added to the back of the queue
    void enqueue(const T& newItem){
        // Create a new LL node
        QueueNode* temp = new QueueNode();
        temp->item = newItem;
        temp->next = NULL;

        // If queue is empty, then
        // new node is front and rear both
        if (_lastNode == NULL) {
            _head = _lastNode = temp;
            return;
        }

        // Add the new node at
        // the end of queue and change rear
        _lastNode->next = temp;
        _lastNode = temp;
    }
    //Dequeue: Items are removed from the front of the queue
    void dequeue(){
        QueueNode* temp = _head;
        if (_head == NULL)
            return;

        if(_head == _lastNode){
            _head = _lastNode = NULL;
        }
        else{
            _head = _head->next;
        }

        free(temp);
    }
    //Get Front: Take a look at the first item
    void getFront(T& queueTop) const{
        if (!isEmpty())
            queueTop = _head->item;
        else {
            cout << "\nQueue is empty" << endl;
            exit(1);
        }
    }

private:
    struct QueueNode {
        T item;
        QueueNode *next;
    };
    int _size;
    /* to avoid the traversal to the last node,
     an additional pointer to the last node is defined*/
    QueueNode* _lastNode;
    QueueNode* _head;
};


