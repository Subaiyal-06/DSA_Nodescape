/*
    DSA NoteScapes - CT-159 Data Structures and Algorithms
    NED University of Engineering & Technology, Karachi

    Group members:
    Syed Abdullah Hussain (CT-25283), Group Lead: main menu, AVL Tree, Time Complexity
    Mohammad Subaiyal (CT-25270): Singly, Doubly and Circular Linked List
    Mohammad Ali Ahad (CT-25269): Stack, Queue, Array ADT
    Mohammad Arif (CT-25273): Binary Tree, Binary Search Tree

    Sirf ek file hai aur sirf iostream use hua hai, koi STL nahi.
    Struct ki jagah classes aur constructors use kiye hain.
*/

#include <iostream>
using namespace std;


// Input helpers (sab members use karte hain)

// integer leta hai, agar user harf likh de to dobara poochta hai
int readInt(const char* msg)
{
    int x = 0;
    cout << msg;
    while (!(cin >> x))
    {
        if (cin.eof()) return 0;            // input khatam to 0 return, menu band ho jayega
        cin.clear();                        // cin ka error flag hatao
        char c;
        while (cin.get(c) && c != '\n') { } // galat line pori nikal do
        cout << "Invalid input, enter a number: ";
    }
    return x;
}

// ek line char array mein padhta hai (string class ke bagair)
void readLine(char* buf, int maxLen)
{
    char c;
    int n = 0;
    buf[0] = '\0';
    bool got = false;
    while (cin.get(c))                      // shuru ke enter / space chhor do
    {
        if (c != '\n' && c != '\r' && c != ' ') { got = true; break; }
    }
    if (!got) return;
    buf[n++] = c;
    while (n < maxLen - 1 && cin.get(c) && c != '\n') buf[n++] = c;
    buf[n] = '\0';
}


// Member: Mohammad Subaiyal
// 1. SINGLY LINKED LIST

// ek node: data aur agle node ka address
// data public hai taake list, stack aur queue classes seedha use kar saken
class Node
{
public:
    int data;
    Node* next;

    Node(int d = 0) { data = d; next = nullptr; }
};

class SinglyLinkedList
{
    Node* head;
    int size;
public:
    SinglyLinkedList() { head = nullptr; size = 0; }

    // destructor saari nodes delete karta hai taake memory leak na ho
    ~SinglyLinkedList()
    {
        while (head != nullptr)
        {
            Node* t = head;
            head = head->next;
            delete t;
        }
    }

    // O(1): naya node head ke aage lagta hai
    void insertAtFront(int v)
    {
        Node* n = new Node(v);
        n->next = head;
        head = n;
        size++;
    }

    // O(n): aakhri node tak chalna parta hai
    void insertAtEnd(int v)
    {
        Node* n = new Node(v);
        if (head == nullptr) head = n;
        else
        {
            Node* t = head;
            while (t->next != nullptr) t = t->next;
            t->next = n;
        }
        size++;
    }

    // position 1 se shuru hoti hai
    void insertAtPosition(int pos, int v)
    {
        if (pos < 1 || pos > size + 1)
        {
            cout << "Invalid position (valid range: 1 to " << size + 1 << ")\n";
            return;
        }
        if (pos == 1) { insertAtFront(v); return; }
        Node* t = head;
        for (int i = 1; i < pos - 1; i++) t = t->next;   // (pos-1) wali node tak
        Node* n = new Node(v);
        n->next = t->next;      // pehle naye ko aage se jorro
        t->next = n;            // phir peeche walay ko naye se
        size++;
    }

    void deleteFront()
    {
        if (head == nullptr) { cout << "List is empty.\n"; return; }
        Node* t = head;
        head = head->next;
        cout << "Deleted " << t->data << "\n";
        delete t;
        size--;
    }

    void deleteEnd()
    {
        if (head == nullptr) { cout << "List is empty.\n"; return; }
        if (head->next == nullptr)
        {
            cout << "Deleted " << head->data << "\n";
            delete head;
            head = nullptr;
            size--;
            return;
        }
        Node* t = head;
        while (t->next->next != nullptr) t = t->next;    // aakhri se pehli node
        cout << "Deleted " << t->next->data << "\n";
        delete t->next;
        t->next = nullptr;
        size--;
    }

    void deleteValue(int v)
    {
        if (head == nullptr) { cout << "List is empty.\n"; return; }
        if (head->data == v)
        {
            Node* t = head;
            head = head->next;
            delete t;
            size--;
            cout << "Deleted " << v << "\n";
            return;
        }
        Node* t = head;
        while (t->next != nullptr && t->next->data != v) t = t->next;
        if (t->next == nullptr) { cout << v << " not found.\n"; return; }
        Node* d = t->next;
        t->next = d->next;      // delete hone wali node ko skip karo
        delete d;
        size--;
        cout << "Deleted " << v << "\n";
    }

    void search(int v) const
    {
        int pos = 1;
        for (Node* t = head; t != nullptr; t = t->next, pos++)
        {
            if (t->data == v) { cout << v << " found at position " << pos << "\n"; return; }
        }
        cout << v << " not found.\n";
    }

    // teen pointers se saare links ulte kar do
    void reverse()
    {
        Node* prev = nullptr;
        Node* cur = head;
        while (cur != nullptr)
        {
            Node* nxt = cur->next;
            cur->next = prev;
            prev = cur;
            cur = nxt;
        }
        head = prev;
    }

    void display() const
    {
        if (head == nullptr) { cout << "List is empty.\n"; return; }
        cout << "HEAD -> ";
        for (Node* t = head; t != nullptr; t = t->next) cout << t->data << " -> ";
        cout << "NULL   (size = " << size << ")\n";
    }
};

void singlyListMenu()
{
    SinglyLinkedList list;
    int ch;
    do
    {
        cout << "\nSingly Linked List\n"
             << "1. Insert at front\n2. Insert at end\n3. Insert at position\n"
             << "4. Delete front\n5. Delete end\n6. Delete by value\n"
             << "7. Search\n8. Reverse\n9. Display\n0. Back\n";
        ch = readInt("Choice: ");
        int v, p;
        switch (ch)
        {
        case 1: v = readInt("Value: "); list.insertAtFront(v); list.display(); break;
        case 2: v = readInt("Value: "); list.insertAtEnd(v); list.display(); break;
        case 3: p = readInt("Position: "); v = readInt("Value: "); list.insertAtPosition(p, v); list.display(); break;
        case 4: list.deleteFront(); list.display(); break;
        case 5: list.deleteEnd(); list.display(); break;
        case 6: v = readInt("Value: "); list.deleteValue(v); list.display(); break;
        case 7: v = readInt("Value: "); list.search(v); break;
        case 8: list.reverse(); list.display(); break;
        case 9: list.display(); break;
        case 0: break;
        default: cout << "Invalid choice.\n";
        }
    } while (ch != 0);
}


// Member: Mohammad Subaiyal
// 2. DOUBLY LINKED LIST

// is node mein prev aur next dono hain
class DNode
{
public:
    int data;
    DNode* prev;
    DNode* next;

    DNode(int d = 0) { data = d; prev = nullptr; next = nullptr; }
};

class DoublyLinkedList
{
    DNode* head;
    DNode* tail;        // tail ki wajah se end par insert/delete O(1) hai
    int size;
public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; size = 0; }

    ~DoublyLinkedList()
    {
        while (head != nullptr)
        {
            DNode* t = head;
            head = head->next;
            delete t;
        }
    }

    void insertAtFront(int v)
    {
        DNode* n = new DNode(v);
        n->next = head;
        if (head != nullptr) head->prev = n;
        else tail = n;              // list khali thi
        head = n;
        size++;
    }

    void insertAtEnd(int v)
    {
        DNode* n = new DNode(v);
        n->prev = tail;
        if (tail != nullptr) tail->next = n;
        else head = n;
        tail = n;
        size++;
    }

    void insertAtPosition(int pos, int v)
    {
        if (pos < 1 || pos > size + 1)
        {
            cout << "Invalid position (valid range: 1 to " << size + 1 << ")\n";
            return;
        }
        if (pos == 1) { insertAtFront(v); return; }
        if (pos == size + 1) { insertAtEnd(v); return; }
        DNode* t = head;
        for (int i = 1; i < pos - 1; i++) t = t->next;
        DNode* n = new DNode(v);
        n->next = t->next;          // chaar pointers theek karne parte hain
        n->prev = t;
        t->next->prev = n;
        t->next = n;
        size++;
    }

    void deleteFront()
    {
        if (head == nullptr) { cout << "List is empty.\n"; return; }
        DNode* t = head;
        head = head->next;
        if (head != nullptr) head->prev = nullptr;
        else tail = nullptr;
        cout << "Deleted " << t->data << "\n";
        delete t;
        size--;
    }

    void deleteEnd()
    {
        if (tail == nullptr) { cout << "List is empty.\n"; return; }
        DNode* t = tail;
        tail = tail->prev;
        if (tail != nullptr) tail->next = nullptr;
        else head = nullptr;
        cout << "Deleted " << t->data << "\n";
        delete t;
        size--;
    }

    void deleteValue(int v)
    {
        DNode* t = head;
        while (t != nullptr && t->data != v) t = t->next;
        if (t == nullptr) { cout << v << " not found.\n"; return; }
        if (t->prev != nullptr) t->prev->next = t->next;
        else head = t->next;
        if (t->next != nullptr) t->next->prev = t->prev;
        else tail = t->prev;
        delete t;
        size--;
        cout << "Deleted " << v << "\n";
    }

    void search(int v) const
    {
        int pos = 1;
        for (DNode* t = head; t != nullptr; t = t->next, pos++)
        {
            if (t->data == v) { cout << v << " found at position " << pos << "\n"; return; }
        }
        cout << v << " not found.\n";
    }

    void displayForward() const
    {
        if (head == nullptr) { cout << "List is empty.\n"; return; }
        cout << "NULL <-> ";
        for (DNode* t = head; t != nullptr; t = t->next) cout << t->data << " <-> ";
        cout << "NULL   (size = " << size << ")\n";
    }

    void displayBackward() const
    {
        if (tail == nullptr) { cout << "List is empty.\n"; return; }
        cout << "Backward: ";
        for (DNode* t = tail; t != nullptr; t = t->prev) cout << t->data << " ";
        cout << "\n";
    }
};

void doublyListMenu()
{
    DoublyLinkedList list;
    int ch;
    do
    {
        cout << "\nDoubly Linked List\n"
             << "1. Insert at front\n2. Insert at end\n3. Insert at position\n"
             << "4. Delete front\n5. Delete end\n6. Delete by value\n"
             << "7. Search\n8. Display forward\n9. Display backward\n0. Back\n";
        ch = readInt("Choice: ");
        int v, p;
        switch (ch)
        {
        case 1: v = readInt("Value: "); list.insertAtFront(v); list.displayForward(); break;
        case 2: v = readInt("Value: "); list.insertAtEnd(v); list.displayForward(); break;
        case 3: p = readInt("Position: "); v = readInt("Value: "); list.insertAtPosition(p, v); list.displayForward(); break;
        case 4: list.deleteFront(); list.displayForward(); break;
        case 5: list.deleteEnd(); list.displayForward(); break;
        case 6: v = readInt("Value: "); list.deleteValue(v); list.displayForward(); break;
        case 7: v = readInt("Value: "); list.search(v); break;
        case 8: list.displayForward(); break;
        case 9: list.displayBackward(); break;
        case 0: break;
        default: cout << "Invalid choice.\n";
        }
    } while (ch != 0);
}


// Member: Mohammad Subaiyal
// 3. CIRCULAR LINKED LIST
// Aakhri node ka next head ko point karta hai. Sirf tail rakhte hain,
// head hamesha tail->next hota hai.

class CircularLinkedList
{
    Node* tail;
    int size;
public:
    CircularLinkedList() { tail = nullptr; size = 0; }

    ~CircularLinkedList()
    {
        if (tail == nullptr) return;
        Node* cur = tail->next;
        tail->next = nullptr;       // pehle circle tor do warna loop khatam nahi hoga
        while (cur != nullptr)
        {
            Node* t = cur;
            cur = cur->next;
            delete t;
        }
    }

    void insertAtFront(int v)
    {
        Node* n = new Node(v);
        if (tail == nullptr)
        {
            tail = n;
            n->next = n;            // akeli node khud ko point karti hai
        }
        else
        {
            n->next = tail->next;
            tail->next = n;
        }
        size++;
    }

    void insertAtEnd(int v)
    {
        insertAtFront(v);
        tail = tail->next;          // naya node ab tail ban gaya
    }

    void deleteFront()
    {
        if (tail == nullptr) { cout << "List is empty.\n"; return; }
        Node* h = tail->next;
        cout << "Deleted " << h->data << "\n";
        if (h == tail) tail = nullptr;      // sirf ek node thi
        else tail->next = h->next;
        delete h;
        size--;
    }

    void deleteValue(int v)
    {
        if (tail == nullptr) { cout << "List is empty.\n"; return; }
        Node* prev = tail;
        Node* cur = tail->next;
        do
        {
            if (cur->data == v)
            {
                if (cur == prev) tail = nullptr;    // sirf ek node
                else
                {
                    prev->next = cur->next;
                    if (cur == tail) tail = prev;
                }
                delete cur;
                size--;
                cout << "Deleted " << v << "\n";
                return;
            }
            prev = cur;
            cur = cur->next;
        } while (prev != tail);             // ek poora chakkar
        cout << v << " not found.\n";
    }

    void search(int v) const
    {
        if (tail == nullptr) { cout << "List is empty.\n"; return; }
        Node* t = tail->next;
        int pos = 1;
        do
        {
            if (t->data == v) { cout << v << " found at position " << pos << "\n"; return; }
            t = t->next;
            pos++;
        } while (t != tail->next);
        cout << v << " not found.\n";
    }

    void display() const
    {
        if (tail == nullptr) { cout << "List is empty.\n"; return; }
        Node* t = tail->next;
        cout << "HEAD -> ";
        do { cout << t->data << " -> "; t = t->next; } while (t != tail->next);
        cout << "(back to HEAD)   size = " << size << "\n";
    }
};

void circularListMenu()
{
    CircularLinkedList list;
    int ch;
    do
    {
        cout << "\nCircular Linked List\n"
             << "1. Insert at front\n2. Insert at end\n3. Delete front\n"
             << "4. Delete by value\n5. Search\n6. Display\n0. Back\n";
        ch = readInt("Choice: ");
        int v;
        switch (ch)
        {
        case 1: v = readInt("Value: "); list.insertAtFront(v); list.display(); break;
        case 2: v = readInt("Value: "); list.insertAtEnd(v); list.display(); break;
        case 3: list.deleteFront(); list.display(); break;
        case 4: v = readInt("Value: "); list.deleteValue(v); list.display(); break;
        case 5: v = readInt("Value: "); list.search(v); break;
        case 6: list.display(); break;
        case 0: break;
        default: cout << "Invalid choice.\n";
        }
    } while (ch != 0);
}


// Member: Mohammad Ali Ahad
// 4. STACK (LIFO)

// array wala stack, size constructor mein milti hai
class ArrayStack
{
    int* arr;
    int capacity;
    int top;            // -1 matlab stack khali
public:
    ArrayStack(int cap = 10)
    {
        capacity = cap;
        arr = new int[capacity];
        top = -1;
    }
    ~ArrayStack() { delete[] arr; }

    bool isEmpty() const { return top == -1; }
    bool isFull() const { return top == capacity - 1; }

    bool push(int v)
    {
        if (isFull()) return false;     // overflow
        arr[++top] = v;
        return true;
    }

    bool pop(int& v)
    {
        if (isEmpty()) return false;    // underflow
        v = arr[top--];
        return true;
    }

    bool peek(int& v) const
    {
        if (isEmpty()) return false;
        v = arr[top];
        return true;
    }

    void display() const
    {
        if (isEmpty()) { cout << "Stack is empty.\n"; return; }
        cout << "TOP -> ";
        for (int i = top; i >= 0; i--) cout << arr[i] << " ";
        cout << "<- BOTTOM\n";
    }
};

// linked list wala stack: top hi list ka head hai
class LinkedStack
{
    Node* top;
public:
    LinkedStack() { top = nullptr; }
    ~LinkedStack()
    {
        while (top != nullptr)
        {
            Node* t = top;
            top = top->next;
            delete t;
        }
    }

    bool isEmpty() const { return top == nullptr; }

    void push(int v)
    {
        Node* n = new Node(v);
        n->next = top;
        top = n;
    }

    bool pop(int& v)
    {
        if (top == nullptr) return false;
        Node* t = top;
        v = t->data;
        top = top->next;
        delete t;
        return true;
    }

    bool peek(int& v) const
    {
        if (top == nullptr) return false;
        v = top->data;
        return true;
    }

    void display() const
    {
        if (top == nullptr) { cout << "Stack is empty.\n"; return; }
        cout << "TOP -> ";
        for (Node* t = top; t != nullptr; t = t->next) cout << t->data << " ";
        cout << "<- BOTTOM\n";
    }
};

// stack ki application: brackets balanced hain ya nahi
bool isBalanced(const char* s, int len)
{
    ArrayStack st(len + 1);
    for (int i = 0; i < len; i++)
    {
        char c = s[i];
        if (c == '(' || c == '[' || c == '{')
            st.push(c);                     // opening bracket push
        else if (c == ')' || c == ']' || c == '}')
        {
            int o;
            if (!st.pop(o)) return false;   // closing aayi lekin stack khali
            if ((c == ')' && o != '(') || (c == ']' && o != '[') || (c == '}' && o != '{'))
                return false;               // jora match nahi hua
        }
    }
    return st.isEmpty();                    // koi opening bachi to balanced nahi
}

void stackMenu()
{
    ArrayStack as(5);
    LinkedStack ls;
    int ch, v;
    do
    {
        cout << "\nStack\n"
             << "Array stack (capacity 5):\n"
             << "  1. Push   2. Pop   3. Peek   4. Display\n"
             << "Linked stack:\n"
             << "  5. Push   6. Pop   7. Peek   8. Display\n"
             << "9. Check balanced brackets\n0. Back\n";
        ch = readInt("Choice: ");
        switch (ch)
        {
        case 1:
            v = readInt("Value: ");
            if (!as.push(v)) cout << "Stack overflow.\n";
            as.display();
            break;
        case 2:
            if (as.pop(v)) cout << "Popped " << v << "\n"; else cout << "Stack underflow.\n";
            as.display();
            break;
        case 3:
            if (as.peek(v)) cout << "Top = " << v << "\n"; else cout << "Stack is empty.\n";
            break;
        case 4: as.display(); break;
        case 5: v = readInt("Value: "); ls.push(v); ls.display(); break;
        case 6:
            if (ls.pop(v)) cout << "Popped " << v << "\n"; else cout << "Stack underflow.\n";
            ls.display();
            break;
        case 7:
            if (ls.peek(v)) cout << "Top = " << v << "\n"; else cout << "Stack is empty.\n";
            break;
        case 8: ls.display(); break;
        case 9:
        {
            char s[200];
            cout << "Enter expression: ";
            readLine(s, 200);
            int len = 0;
            while (s[len] != '\0') len++;
            cout << (isBalanced(s, len) ? "Balanced.\n" : "Not balanced.\n");
            break;
        }
        case 0: break;
        default: cout << "Invalid choice.\n";
        }
    } while (ch != 0);
}


// Member: Mohammad Ali Ahad
// 5. QUEUE (FIFO)

// circular array queue: index % capacity se wapas shuru par aa jata hai
class CircularQueue
{
    int* arr;
    int capacity;
    int front, rear, count;
public:
    CircularQueue(int cap = 5)
    {
        capacity = cap;
        arr = new int[capacity];
        front = 0;
        rear = -1;
        count = 0;
    }
    ~CircularQueue() { delete[] arr; }

    bool isEmpty() const { return count == 0; }
    bool isFull() const { return count == capacity; }

    bool enqueue(int v)
    {
        if (isFull()) return false;
        rear = (rear + 1) % capacity;
        arr[rear] = v;
        count++;
        return true;
    }

    bool dequeue(int& v)
    {
        if (isEmpty()) return false;
        v = arr[front];
        front = (front + 1) % capacity;
        count--;
        return true;
    }

    bool peek(int& v) const
    {
        if (isEmpty()) return false;
        v = arr[front];
        return true;
    }

    void display() const
    {
        if (isEmpty()) { cout << "Queue is empty.\n"; return; }
        cout << "FRONT -> ";
        for (int i = 0, idx = front; i < count; i++, idx = (idx + 1) % capacity)
            cout << arr[idx] << " ";
        cout << "<- REAR   (" << count << "/" << capacity << ")\n";
    }
};

class LinkedQueue
{
    Node* front;
    Node* rear;
public:
    LinkedQueue() { front = nullptr; rear = nullptr; }
    ~LinkedQueue()
    {
        while (front != nullptr)
        {
            Node* t = front;
            front = front->next;
            delete t;
        }
    }

    void enqueue(int v)
    {
        Node* n = new Node(v);
        if (rear == nullptr) front = rear = n;
        else
        {
            rear->next = n;
            rear = n;
        }
    }

    bool dequeue(int& v)
    {
        if (front == nullptr) return false;
        Node* t = front;
        v = t->data;
        front = front->next;
        if (front == nullptr) rear = nullptr;   // queue khali ho gayi
        delete t;
        return true;
    }

    bool peek(int& v) const
    {
        if (front == nullptr) return false;
        v = front->data;
        return true;
    }

    void display() const
    {
        if (front == nullptr) { cout << "Queue is empty.\n"; return; }
        cout << "FRONT -> ";
        for (Node* t = front; t != nullptr; t = t->next) cout << t->data << " ";
        cout << "<- REAR\n";
    }
};

void queueMenu()
{
    CircularQueue cq(5);
    LinkedQueue lq;
    int ch, v;
    do
    {
        cout << "\nQueue\n"
             << "Circular queue (capacity 5):\n"
             << "  1. Enqueue   2. Dequeue   3. Peek   4. Display\n"
             << "Linked queue:\n"
             << "  5. Enqueue   6. Dequeue   7. Peek   8. Display\n"
             << "0. Back\n";
        ch = readInt("Choice: ");
        switch (ch)
        {
        case 1:
            v = readInt("Value: ");
            if (!cq.enqueue(v)) cout << "Queue overflow.\n";
            cq.display();
            break;
        case 2:
            if (cq.dequeue(v)) cout << "Removed " << v << "\n"; else cout << "Queue underflow.\n";
            cq.display();
            break;
        case 3:
            if (cq.peek(v)) cout << "Front = " << v << "\n"; else cout << "Queue is empty.\n";
            break;
        case 4: cq.display(); break;
        case 5: v = readInt("Value: "); lq.enqueue(v); lq.display(); break;
        case 6:
            if (lq.dequeue(v)) cout << "Removed " << v << "\n"; else cout << "Queue underflow.\n";
            lq.display();
            break;
        case 7:
            if (lq.peek(v)) cout << "Front = " << v << "\n"; else cout << "Queue is empty.\n";
            break;
        case 8: lq.display(); break;
        case 0: break;
        default: cout << "Invalid choice.\n";
        }
    } while (ch != 0);
}


// Member: Mohammad Ali Ahad
// 6. ARRAY ADT

class ArrayADT
{
    int* data;
    int capacity;
    int size;       // abhi kitne elements hain
public:
    ArrayADT(int cap = 100)
    {
        capacity = cap;
        data = new int[capacity];
        size = 0;
    }
    ~ArrayADT() { delete[] data; }

    // pos par jagah banane ke liye elements ko right shift karte hain, O(n)
    bool insertAt(int pos, int v)
    {
        if (size == capacity || pos < 1 || pos > size + 1) return false;
        for (int i = size; i >= pos; i--) data[i] = data[i - 1];
        data[pos - 1] = v;
        size++;
        return true;
    }

    // delete ke baad khali jagah bharne ke liye left shift, O(n)
    bool deleteAt(int pos, int& removed)
    {
        if (pos < 1 || pos > size) return false;
        removed = data[pos - 1];
        for (int i = pos - 1; i < size - 1; i++) data[i] = data[i + 1];
        size--;
        return true;
    }

    bool update(int pos, int v)
    {
        if (pos < 1 || pos > size) return false;
        data[pos - 1] = v;
        return true;
    }

    int getSize() const { return size; }

    // linear search: index return karta hai (-1 agar nahi mila), steps mein comparisons
    int linearSearch(int v, int& steps) const
    {
        steps = 0;
        for (int i = 0; i < size; i++)
        {
            steps++;
            if (data[i] == v) return i;
        }
        return -1;
    }

    bool isSorted() const
    {
        for (int i = 0; i + 1 < size; i++)
            if (data[i] > data[i + 1]) return false;
        return true;
    }

    // binary search sirf sorted array par chalti hai
    int binarySearch(int v, int& steps) const
    {
        steps = 0;
        int lo = 0, hi = size - 1;
        while (lo <= hi)
        {
            int mid = lo + (hi - lo) / 2;
            steps++;
            if (data[mid] == v) return mid;
            if (v < data[mid]) hi = mid - 1;
            else lo = mid + 1;
        }
        return -1;
    }

    void bubbleSort()
    {
        for (int i = 0; i < size - 1; i++)
        {
            bool swapped = false;
            for (int j = 0; j < size - 1 - i; j++)
            {
                if (data[j] > data[j + 1])
                {
                    int t = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = t;
                    swapped = true;
                }
            }
            if (!swapped) break;        // koi swap nahi hua to array sorted hai
        }
    }

    void display() const
    {
        if (size == 0) { cout << "Array is empty.\n"; return; }
        cout << "[ ";
        for (int i = 0; i < size; i++) cout << data[i] << " ";
        cout << "]   size = " << size << "\n";
    }
};

void arrayMenu()
{
    ArrayADT arr(100);
    int ch, v, p, steps, idx;
    do
    {
        cout << "\nArray ADT\n"
             << "1. Insert at position\n2. Delete at position\n3. Update\n"
             << "4. Linear search\n5. Binary search\n6. Bubble sort\n"
             << "7. Display\n0. Back\n";
        ch = readInt("Choice: ");
        switch (ch)
        {
        case 1:
            p = readInt("Position: ");
            v = readInt("Value: ");
            if (!arr.insertAt(p, v)) cout << "Invalid position (valid range: 1 to " << arr.getSize() + 1 << ")\n";
            arr.display();
            break;
        case 2:
            p = readInt("Position: ");
            if (arr.deleteAt(p, v)) cout << "Deleted " << v << "\n";
            else cout << "Invalid position.\n";
            arr.display();
            break;
        case 3:
            p = readInt("Position: ");
            v = readInt("New value: ");
            if (!arr.update(p, v)) cout << "Invalid position.\n";
            arr.display();
            break;
        case 4:
            v = readInt("Value: ");
            idx = arr.linearSearch(v, steps);
            if (idx >= 0) cout << v << " found at position " << idx + 1 << " (" << steps << " comparisons)\n";
            else cout << v << " not found (" << steps << " comparisons)\n";
            break;
        case 5:
            if (!arr.isSorted()) { cout << "Array must be sorted first. Use bubble sort.\n"; break; }
            v = readInt("Value: ");
            idx = arr.binarySearch(v, steps);
            if (idx >= 0) cout << v << " found at position " << idx + 1 << " (" << steps << " steps)\n";
            else cout << v << " not found (" << steps << " steps)\n";
            break;
        case 6: arr.bubbleSort(); arr.display(); break;
        case 7: arr.display(); break;
        case 0: break;
        default: cout << "Invalid choice.\n";
        }
    } while (ch != 0);
}


// TREES
// Hierarchy:   Tree  ->  BinaryTree
//               Tree  ->  BST  ->  AVLTree
// Tree base class mein wo kaam hain jo teeno ke common hain
// (traversals, height, drawing). Is liye code repeat nahi hota.

class TreeNode
{
public:
    int data;
    TreeNode* left;
    TreeNode* right;
    int height;         // sirf AVL ke liye use hota hai

    TreeNode(int d)
    {
        data = d;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class Tree
{
protected:
    TreeNode* root;

    void destroy(TreeNode* n)       // postorder: pehle bachay phir parent
    {
        if (n == nullptr) return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }

    void inorder(TreeNode* n) const
    {
        if (n == nullptr) return;
        inorder(n->left);
        cout << n->data << " ";
        inorder(n->right);
    }
    void preorder(TreeNode* n) const
    {
        if (n == nullptr) return;
        cout << n->data << " ";
        preorder(n->left);
        preorder(n->right);
    }
    void postorder(TreeNode* n) const
    {
        if (n == nullptr) return;
        postorder(n->left);
        postorder(n->right);
        cout << n->data << " ";
    }

    int countNodes(TreeNode* n) const
    {
        if (n == nullptr) return 0;
        return 1 + countNodes(n->left) + countNodes(n->right);
    }
    int countLeaves(TreeNode* n) const
    {
        if (n == nullptr) return 0;
        if (n->left == nullptr && n->right == nullptr) return 1;
        return countLeaves(n->left) + countLeaves(n->right);
    }
    int treeHeight(TreeNode* n) const
    {
        if (n == nullptr) return 0;
        int l = treeHeight(n->left);
        int r = treeHeight(n->right);
        return 1 + (l > r ? l : r);
    }

    // drawing mein har node ka text; AVL isay badal deta hai (balance factor ke liye)
    virtual void printNode(TreeNode* n) const { cout << n->data; }

    // tree ko 90 degree ghuma kar print karta hai (right upar, left neeche)
    void printSideways(TreeNode* n, int level) const
    {
        if (n == nullptr) return;
        printSideways(n->right, level + 1);
        for (int i = 0; i < level; i++) cout << "        ";
        printNode(n);
        cout << "\n";
        printSideways(n->left, level + 1);
    }

    // level order: queue array se banayi hai, size nodes ke barabar
    void levelOrder() const
    {
        int total = countNodes(root);
        TreeNode** q = new TreeNode*[total];
        int f = 0, r = 0;
        q[r++] = root;
        while (f < r)
        {
            TreeNode* c = q[f++];
            cout << c->data << " ";
            if (c->left != nullptr) q[r++] = c->left;
            if (c->right != nullptr) q[r++] = c->right;
        }
        delete[] q;
    }

public:
    Tree() { root = nullptr; }
    virtual ~Tree() { destroy(root); }      // virtual taake derived class ka bhi sahi destructor chale

    bool isEmpty() const { return root == nullptr; }

    void showTraversals() const
    {
        if (root == nullptr) { cout << "Tree is empty.\n"; return; }
        cout << "Inorder    : "; inorder(root); cout << "\n";
        cout << "Preorder   : "; preorder(root); cout << "\n";
        cout << "Postorder  : "; postorder(root); cout << "\n";
        cout << "Level order: "; levelOrder(); cout << "\n";
    }

    void showTree() const
    {
        if (root == nullptr) { cout << "Tree is empty.\n"; return; }
        cout << "\nTree (root on the left, right subtree on top):\n";
        printSideways(root, 0);
    }

    void showInfo() const
    {
        cout << "Nodes = " << countNodes(root) << ", Leaves = " << countLeaves(root)
             << ", Height = " << treeHeight(root) << "\n";
    }
};


// Member: Mohammad Arif
// 7. BINARY TREE  (level order insert, koi value ka rule nahi)

class BinaryTree : public Tree
{
    int count;
public:
    BinaryTree() : Tree() { count = 0; }

    void insert(int v)
    {
        TreeNode* n = new TreeNode(v);
        count++;
        if (root == nullptr) { root = n; return; }
        // pehli khali jagah dhoondo: upar se neeche, left se right
        TreeNode** q = new TreeNode*[count + 1];
        int f = 0, r = 0;
        q[r++] = root;
        while (f < r)
        {
            TreeNode* c = q[f++];
            if (c->left == nullptr) { c->left = n; break; }
            q[r++] = c->left;
            if (c->right == nullptr) { c->right = n; break; }
            q[r++] = c->right;
        }
        delete[] q;
    }

    bool search(int v) const { return searchFrom(root, v); }

private:
    bool searchFrom(TreeNode* n, int v) const
    {
        if (n == nullptr) return false;
        if (n->data == v) return true;
        return searchFrom(n->left, v) || searchFrom(n->right, v);
    }
};

void binaryTreeMenu()
{
    BinaryTree t;
    int ch, v;
    do
    {
        cout << "\nBinary Tree\n"
             << "1. Insert\n2. Traversals\n3. Draw tree\n4. Height / nodes / leaves\n"
             << "5. Search\n0. Back\n";
        ch = readInt("Choice: ");
        switch (ch)
        {
        case 1: v = readInt("Value: "); t.insert(v); t.showTree(); break;
        case 2: t.showTraversals(); break;
        case 3: t.showTree(); break;
        case 4: t.showInfo(); break;
        case 5: v = readInt("Value: "); cout << v << (t.search(v) ? " found.\n" : " not found.\n"); break;
        case 0: break;
        default: cout << "Invalid choice.\n";
        }
    } while (ch != 0);
}


// Member: Mohammad Arif
// 8. BINARY SEARCH TREE
// Rule: left < node < right

class BST : public Tree
{
    TreeNode* insertNode(TreeNode* n, int v, bool& added)
    {
        if (n == nullptr) { added = true; return new TreeNode(v); }
        if (v < n->data) n->left = insertNode(n->left, v, added);
        else if (v > n->data) n->right = insertNode(n->right, v, added);
        return n;       // barabar value ho to kuch nahi (duplicate)
    }

    TreeNode* removeNode(TreeNode* n, int v, bool& found)
    {
        if (n == nullptr) return nullptr;
        if (v < n->data) n->left = removeNode(n->left, v, found);
        else if (v > n->data) n->right = removeNode(n->right, v, found);
        else
        {
            found = true;
            // case 1 aur 2: leaf ya ek bacha
            if (n->left == nullptr) { TreeNode* t = n->right; delete n; return t; }
            if (n->right == nullptr) { TreeNode* t = n->left; delete n; return t; }
            // case 3: do bachay, right subtree ka sab se chhota (inorder successor) lo
            TreeNode* s = n->right;
            while (s->left != nullptr) s = s->left;
            n->data = s->data;
            bool dummy = false;
            n->right = removeNode(n->right, s->data, dummy);
        }
        return n;
    }

public:
    BST() : Tree() { }

    // virtual hai taake AVLTree apna balancing wala insert/remove de sake
    virtual bool insert(int v)
    {
        bool added = false;
        root = insertNode(root, v, added);
        return added;
    }

    virtual bool remove(int v)
    {
        bool found = false;
        root = removeNode(root, v, found);
        return found;
    }

    bool search(int v, int& steps) const
    {
        steps = 0;
        TreeNode* t = root;
        while (t != nullptr)
        {
            steps++;
            if (v == t->data) return true;
            t = (v < t->data) ? t->left : t->right;
        }
        return false;
    }

    bool minMax(int& mn, int& mx) const
    {
        if (root == nullptr) return false;
        TreeNode* a = root;
        while (a->left != nullptr) a = a->left;       // sab se left = minimum
        TreeNode* b = root;
        while (b->right != nullptr) b = b->right;     // sab se right = maximum
        mn = a->data;
        mx = b->data;
        return true;
    }
};

void bstMenu()
{
    BST t;
    int ch, v, mn, mx, steps;
    do
    {
        cout << "\nBinary Search Tree\n"
             << "1. Insert\n2. Delete\n3. Search\n4. Min / Max\n"
             << "5. Traversals\n6. Draw tree\n7. Height / nodes / leaves\n0. Back\n";
        ch = readInt("Choice: ");
        switch (ch)
        {
        case 1:
            v = readInt("Value: ");
            if (!t.insert(v)) cout << v << " already exists.\n";
            t.showTree();
            break;
        case 2:
            v = readInt("Value: ");
            cout << (t.remove(v) ? "Deleted.\n" : "Value not found.\n");
            t.showTree();
            break;
        case 3:
            v = readInt("Value: ");
            if (t.search(v, steps)) cout << v << " found (" << steps << " steps)\n";
            else cout << v << " not found (" << steps << " steps)\n";
            break;
        case 4:
            if (t.minMax(mn, mx)) cout << "Minimum = " << mn << ", Maximum = " << mx << "\n";
            else cout << "Tree is empty.\n";
            break;
        case 5: t.showTraversals(); break;
        case 6: t.showTree(); break;
        case 7: t.showInfo(); break;
        case 0: break;
        default: cout << "Invalid choice.\n";
        }
    } while (ch != 0);
}


// Member: Syed Abdullah Hussain (Group Lead)
// 9. AVL TREE
// BST hi hai lekin har insert/delete ke baad balance factor check hota
// hai: BF = height(left) - height(right), sirf -1, 0, 1 allowed.
// Is se bahar jaye to rotation se tree balance hota hai.

class AVLTree : public BST
{
    int nodeHeight(TreeNode* n) const { return n == nullptr ? 0 : n->height; }

    int balanceFactor(TreeNode* n) const
    {
        return n == nullptr ? 0 : nodeHeight(n->left) - nodeHeight(n->right);
    }

    void updateHeight(TreeNode* n)
    {
        int l = nodeHeight(n->left);
        int r = nodeHeight(n->right);
        n->height = 1 + (l > r ? l : r);
    }

    // rotateRight(y): x = y->left; y->left = x->right; x->right = y; x naya root ban jata hai
    TreeNode* rotateRight(TreeNode* y)
    {
        TreeNode* x = y->left;
        TreeNode* b = x->right;
        x->right = y;
        y->left = b;
        updateHeight(y);        // pehle neeche wali node ka height, phir upar wali ka
        updateHeight(x);
        return x;
    }

    // rotateLeft bilkul ulta hai
    TreeNode* rotateLeft(TreeNode* x)
    {
        TreeNode* y = x->right;
        TreeNode* b = y->left;
        y->left = x;
        x->right = b;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    // insert aur delete dono ke baad bulaya jata hai
    TreeNode* rebalance(TreeNode* n)
    {
        updateHeight(n);
        int bf = balanceFactor(n);
        if (bf > 1)                                     // left bhaari
        {
            if (balanceFactor(n->left) < 0)        // LR case
            {
                cout << "  [Rotation: LR at " << n->data << "]\n";
                n->left = rotateLeft(n->left);
            }
            else cout << "  [Rotation: LL at " << n->data << "]\n";
            return rotateRight(n);
        }
        if (bf < -1)                                    // right bhaari
        {
            if (balanceFactor(n->right) > 0)       // RL case
            {
                cout << "  [Rotation: RL at " << n->data << "]\n";
                n->right = rotateRight(n->right);
            }
            else cout << "  [Rotation: RR at " << n->data << "]\n";
            return rotateLeft(n);
        }
        return n;
    }

    TreeNode* avlInsert(TreeNode* n, int v, bool& added)
    {
        if (n == nullptr) { added = true; return new TreeNode(v); }
        if (v < n->data) n->left = avlInsert(n->left, v, added);
        else if (v > n->data) n->right = avlInsert(n->right, v, added);
        else return n;                  // duplicate
        return rebalance(n);            // wapsi par har node check hoti hai
    }

    TreeNode* avlRemove(TreeNode* n, int v, bool& found)
    {
        if (n == nullptr) return nullptr;
        if (v < n->data) n->left = avlRemove(n->left, v, found);
        else if (v > n->data) n->right = avlRemove(n->right, v, found);
        else
        {
            found = true;
            if (n->left == nullptr) { TreeNode* t = n->right; delete n; return t; }
            if (n->right == nullptr) { TreeNode* t = n->left; delete n; return t; }
            TreeNode* s = n->right;
            while (s->left != nullptr) s = s->left;
            n->data = s->data;
            bool dummy = false;
            n->right = avlRemove(n->right, s->data, dummy);
        }
        return rebalance(n);
    }

protected:
    // drawing mein value ke saath balance factor bhi dikhao
    void printNode(TreeNode* n) const
    {
        cout << n->data << " (bf=" << balanceFactor(n) << ")";
    }

public:
    AVLTree() : BST() { }

    bool insert(int v)
    {
        bool added = false;
        root = avlInsert(root, v, added);
        return added;
    }

    bool remove(int v)
    {
        bool found = false;
        root = avlRemove(root, v, found);
        return found;
    }
};

void avlMenu()
{
    AVLTree t;
    int ch, v, steps;
    do
    {
        cout << "\nAVL Tree\n"
             << "1. Insert\n2. Delete\n3. Search\n4. Traversals\n"
             << "5. Draw tree (with balance factors)\n6. Height / nodes / leaves\n0. Back\n";
        ch = readInt("Choice: ");
        switch (ch)
        {
        case 1:
            v = readInt("Value: ");
            if (!t.insert(v)) cout << v << " already exists.\n";
            t.showTree();
            break;
        case 2:
            v = readInt("Value: ");
            cout << (t.remove(v) ? "Deleted.\n" : "Value not found.\n");
            t.showTree();
            break;
        case 3:
            v = readInt("Value: ");
            if (t.search(v, steps)) cout << v << " found (" << steps << " steps)\n";
            else cout << v << " not found (" << steps << " steps)\n";
            break;
        case 4: t.showTraversals(); break;
        case 5: t.showTree(); break;
        case 6: t.showInfo(); break;
        case 0: break;
        default: cout << "Invalid choice.\n";
        }
    } while (ch != 0);
}


// Member: Syed Abdullah Hussain (Group Lead)
// 10. TIME COMPLEXITY
// Asal steps gin kar dikhata hai ke O(n), O(log n), O(n^2) mein
// kitna fark hota hai.

class ComplexityAnalyzer
{
public:
    void showTable() const
    {
        cout << "\nStructure           Search     Insert      Delete\n"
             << "Array               O(n)       O(n)        O(n)\n"
             << "Singly list         O(n)       O(1) front  O(1) front\n"
             << "Doubly list         O(n)       O(1) ends   O(1) ends\n"
             << "Stack / Queue       O(n)       O(1)        O(1)\n"
             << "BST (average)       O(log n)   O(log n)    O(log n)\n"
             << "BST (worst)         O(n)       O(n)        O(n)\n"
             << "AVL tree            O(log n)   O(log n)    O(log n)\n";
    }

    // n elements ka array banakar teen algorithms ke worst case steps ginta hai
    void runDemo(int n) const
    {
        int* a = new int[n];
        for (int i = 0; i < n; i++) a[i] = i + 1;       // sorted 1..n

        // linear search: aakhri element dhoondo (worst case)
        long long linearSteps = 0;
        for (int i = 0; i < n; i++)
        {
            linearSteps++;
            if (a[i] == n) break;
        }

        // binary search: aakhri element
        long long binarySteps = 0;
        int lo = 0, hi = n - 1;
        while (lo <= hi)
        {
            int mid = lo + (hi - lo) / 2;
            binarySteps++;
            if (a[mid] == n) break;
            if (a[mid] < n) lo = mid + 1;
            else hi = mid - 1;
        }

        // bubble sort: ulta array (worst case) ke comparisons
        for (int i = 0; i < n; i++) a[i] = n - i;
        long long bubbleSteps = 0;
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - 1 - i; j++)
            {
                bubbleSteps++;
                if (a[j] > a[j + 1])
                {
                    int t = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = t;
                }
            }
        }
        delete[] a;

        cout << "\nWorst case steps for n = " << n << ":\n"
             << "Linear search  O(n)     : " << linearSteps << " comparisons\n"
             << "Binary search  O(log n) : " << binarySteps << " comparisons\n"
             << "Bubble sort    O(n^2)   : " << bubbleSteps << " comparisons\n";
    }
};

void complexityMenu()
{
    ComplexityAnalyzer ca;
    int ch;
    do
    {
        cout << "\nTime Complexity\n"
             << "1. Complexity table\n2. Live demo\n0. Back\n";
        ch = readInt("Choice: ");
        switch (ch)
        {
        case 1: ca.showTable(); break;
        case 2:
        {
            int n = readInt("Enter n (1 to 2000): ");
            if (n < 1 || n > 2000) cout << "n must be between 1 and 2000.\n";
            else ca.runDemo(n);
            break;
        }
        case 0: break;
        default: cout << "Invalid choice.\n";
        }
    } while (ch != 0);
}


// Member: Syed Abdullah Hussain (Group Lead)
// MAIN MENU

int main()
{
    int ch;
    do
    {
        cout << "\nDSA NoteScapes\n"
             << " 1. Singly Linked List\n"
             << " 2. Doubly Linked List\n"
             << " 3. Circular Linked List\n"
             << " 4. Stack\n"
             << " 5. Queue\n"
             << " 6. Array ADT\n"
             << " 7. Binary Tree\n"
             << " 8. Binary Search Tree\n"
             << " 9. AVL Tree\n"
             << "10. Time Complexity\n"
             << " 0. Exit\n";
        ch = readInt("Choice: ");
        switch (ch)
        {
        case 1: singlyListMenu(); break;
        case 2: doublyListMenu(); break;
        case 3: circularListMenu(); break;
        case 4: stackMenu(); break;
        case 5: queueMenu(); break;
        case 6: arrayMenu(); break;
        case 7: binaryTreeMenu(); break;
        case 8: bstMenu(); break;
        case 9: avlMenu(); break;
        case 10: complexityMenu(); break;
        case 0: cout << "Program ended.\n"; break;
        default: cout << "Invalid choice. Enter 0 to 10.\n";
        }
    } while (ch != 0);
    return 0;
}
