#pragma once
#include<iostream>
using namespace std;
template<typename T>
struct LLnode {
    T data;
    LLnode* next;
    LLnode() {
        next = NULL;
    }
    LLnode(T x) {
        data = x;
        next = NULL;
    }

    //temporary test func
    void change(T a) {
        data = a;
    }
};

template<typename T>
class list {
public:
    LLnode<T>* head;
    int numItems;

    list() {
        head = NULL;
        numItems = 0;
    }

    T remove(int ind) {//remove at specific ind and return that item
        LLnode<T>* temp = head;
        int count = 0;
        while (temp->next && count < (ind - 1)) {
            temp = temp->next;
            count++;
        }
        //now at the index right before the index to remove the element
        //Eg to delete at ind 3, we are at ind 2
        T ret = temp->next->data;
        LLnode<T>* del = temp->next;
        temp->next = temp->next->next;
        delete del; del = NULL;
        return ret;
    }

    void add(T item, int i = -1) {//insert in order OR at the index, if passed
        if (head == NULL)
            head = new LLnode<T>(item);
        else {
            if (i != -1) {//index passed
                LLnode<T>* temp = head;
                int count = 0;
                while (temp->next && count < (i - 1)) {
                    temp = temp->next;
                    count++;
                }
                //now at the index right before the index to insert the element
                //Eg to insert at ind 3 we are at ind 2
                LLnode<T>* newElement = new LLnode<T>(item);
                newElement->next = temp->next;
                temp->next = newElement;
            }
            else {//no index passed
                if (item < head->data) {
                    LLnode<T>* newHead = new LLnode<T>(item);
                    newHead->next = head;
                    head = newHead;
                }
                else { //Insert in order
                    LLnode<T>* temp = head;
                    while (temp->next && temp->next->data < item) {
                        temp = temp->next;
                    }
                    LLnode<T>* newElement = new LLnode<T>(item);
                    newElement->next = temp->next;
                    temp->next = newElement;
                }
            }
        }
        numItems++;
    }

    void disp() {
        if (head == NULL)
            cout << "---Empty---";
        else {
            LLnode<T>* temp = head;
            while (temp) {
                cout << temp->data << endl;
                temp = temp->next;
            }
        }
        return;
    }
    int size() {//return numItems
        if (head != NULL) {
            int count = 0;
            LLnode<T>* temp = head;
            while (temp) {
                count++;
                temp = temp->next;
            }
            return count;
        }
        else if (head == NULL) {
            return 0;
        }
    }

    //T remove(T item) {
    //    if (head != NULL) {
    //        if (head->data == item) {
    //            LLnode<T>* temp = head;
    //            T ret = head->data;
    //            head = head->next;
    //            delete temp; temp = NULL;
    //            numItems--;
    //            return ret;

    //        }
    //        else {
    //            LLnode<T>* temp = head;
    //            while (temp->next) {
    //                if (temp->next->data == item) {
    //                    LLnode<T>* temp2 = temp->next;//to be delet
    //                    T ret = temp2->data;
    //                    temp->next = temp->next->next;
    //                    delete temp2; temp2 = NULL;
    //                    numItems--;
    //                    return ret;
    //                }
    //                temp = temp->next;
    //            }
    //        }
    //    }
    //}

    int getIndex(T item) {//Get the index of a particular item in the LL (-1 if not present or empty list)

        if (head != NULL) {
            if (head->data == item) {
                return 0;
            }
            else {
                LLnode<T>* temp = head;
                int i = 0;
                while (temp) {
                    if (temp->data == item) {
                        return i;
                    }
                    temp = temp->next;
                    i++;
                }
            }
        }

        return -1;

    }
    T operator[](int index) {//only for accessing-will not return anything if list empty, so be careful
        if (head != NULL) {
            LLnode<T>* temp = head;
            for (int i = 0; temp; i++, temp = temp->next) {
                if (i == index) {
                    T ret = temp->data;
                    return ret;
                }
            }
        }
    }

    void change(int ind, T value) {//change value at idnex "i" to "value"
        if (head != NULL) {
            LLnode<T>* temp = head;
            for (int i = 0; temp; i++, temp = temp->next) {
                if (i == ind) {
                    temp->data = value;
                    return;
                }
            }
        }
    }

};

template<typename T>
void operator&&(list<T> l1, list<T>l2) {
    LLnode<T>* temp = l1.head;
    LLnode<T>* temp2 = l2.head;
    while (temp != NULL && temp2 != NULL) {
        if (temp2.getIndex(temp->data) != -1 && temp.getIndex(temp2->data) != -1) {
            cout << temp->data << endl;
            temp2 = temp2->next;
            temp = temp->next;
        }
    }
}

template<typename T>
void operator||(list<T> l1, list<T>l2) {
    l1.disp();
    l2.disp();
}