#include <iostream>


template <typename T>
class List {
public:
    List();
    ~List();
    void push_back(T data);
    int GetSize() { return this->size; }
    T& operator[](const int index);
    void pop_front();
    void clear();
    void push_front(T data);
    void insert(T data, int index);
    void removeAt(int index);
    void pop_back();
private:
    //класс для элементов(узлов)
    template <typename T>
    class Node {
    public:
        Node* pNext; //Node for next element
        T data;
        Node(T data = T(), Node* pNext = nullptr) {
            this->data = data;
            this->pNext = pNext;
        }
    };

    int size;
    Node<T>* head;
};
//Выносим методы, деструктор и конструктор вне класса
template <typename T>
List<T>::List() {
    size = 0;
    head = nullptr;
}

template <typename T>
List<T>::~List() {
    this->clear();
}

template <typename T>
void List<T>::clear() {
    //Пока размер не равен еденицы
    while (size) {
        this->pop_front();
    }
}


template <typename T>
void List<T>::pop_front() {
    Node<T>* temp = this->head;
    head = head->pNext;
    delete temp;
    size--;
}


template <typename T>
void List<T>::push_back(T data) {
    if (this->head == nullptr) { this->head = new Node<T>(data);}
    else {
        Node<T>* current = this->head;
        while (current->pNext != nullptr) {
            current = current->pNext;
        }
        current->pNext = new Node<T>(data);
    }
    //new because of we have to single out memory for this object
    this->size++;
}


template <typename T>
void List<T>::push_front(T data) {
    this->head = new Node<T>(data, this->head);
    size++;
}

template <typename T>
T& List<T>::operator[](const int index) {
    int counter = 0;
    Node<T>* current = this->head;
    while (current != nullptr) {
        if (counter == index) {
            return current->data;
        }
        current = current->pNext;
        counter++;
    }
}


template <typename T>
void List<T>::removeAt(int index)
{
    if (index == 0) { this->pop_front(); }
    else {
        Node<T>* prev = this->head;
        for (int i = 0; i < index - 1; i++) {
            prev = prev->pNext;
        }
        Node<T>* toDelete = prev->pNext;
        prev->pNext = toDelete->pNext;
        
        delete toDelete;
        size--;
    }
}

template <typename T>
void List<T>::insert(T data,int index) {
    if (index == 0) { this->push_front(data); }
    else {
        Node<T>* prev = head;
        for (int i = 0; i < index - 1; i++) {
            prev = prev->pNext;
        }
        Node<T>* newNode = new Node<T>(data, prev->pNext);
        prev->pNext = newNode;
        
        size++;
    }
}

template <typename T>
void List<T>::pop_back() {
    this->remove(this->size - 1);
}

int main()
{
    List<int> arr;
  
    arr.push_back(1);
    arr.push_back(2);
    arr.clear();
    std::cout << arr.GetSize();
    return 0;
}

