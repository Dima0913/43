#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class PriorityQueue {
private:
    struct Node {
        T data;
        int priority;
        Node* next;
        Node(T d, int p) : data(d), priority(p), next(nullptr) {}
    };

    Node* head;
    int size;
public:
    PriorityQueue() : head(nullptr), size(0) {}
    ~PriorityQueue() {
        while (!IsEmpty()) {
            PullHighestPriorityElement();
        }
    }

    bool IsEmpty() const {
        return head == nullptr;
    }

    bool IsFull() const {
        return false;
    }

    void InsertWithPriority(const T& element, int priority) {
        Node* newNode = new Node(element, priority);
        if (IsEmpty() || head->priority < priority) {
            newNode->next = head;
            head = newNode;
        }
        else {
            Node* current = head;
            while (current->next != nullptr && current->next->priority >= priority) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        size++;
    }

    void PullHighestPriorityElement() {
        if (IsEmpty()) {
            throw out_of_range("Queue is empty");
        }
        Node* temp = head;
        head = head->next;
        delete temp;
        size--;
    }

    T Peek() const {
        if (IsEmpty()) {
            throw out_of_range("Queue is empty");
        }
        return head->data;
    }

    int GetSize() const {
        return size;
    }

    void Show() const {
        Node* current = head;
        while (current != nullptr) {
            cout << "Element: " << current->data << ", Priority: " << current->priority << endl;
            current = current->next;
        }
    }
};

int main() {
    PriorityQueue<string> pq;

    pq.InsertWithPriority("Low Priority", 1);
    pq.InsertWithPriority("Medium Priority", 5);
    pq.InsertWithPriority("High Priority", 10);

    cout << "Queue elements:" << endl;
    pq.Show();

    cout << "Highest priority element: " << pq.Peek() << endl;

    pq.PullHighestPriorityElement();
    cout << "After removing the highest priority element:" << endl;
    pq.Show();
}