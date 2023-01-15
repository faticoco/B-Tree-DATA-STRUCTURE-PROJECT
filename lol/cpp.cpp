#pragma once
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include"LinkedList.h"
using namespace std;
const int m = 40;  // fixed order for the tree
string getRecord(string fref);
void deleteFromFile(string);

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

    void removeHead() {//remove at specific ind and return that item
        LLnode<T>* temp = head;
        head = head->next;
        delete temp; temp = NULL;
    }

    void add(T item, int i = -1) {//insert in order OR at the index, if passed
        if (head == NULL)
            head = new LLnode<T>(item);
        else {
            LLnode<T>* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = new LLnode<T>(item);
           
        }
        numItems++;
    }

    /*Clears the entire linked list*/
    void clear() {
        while (head != NULL) {
            removeHead();
        }
    }

    bool isEmpty() {
        if (head == NULL)
            return true;
        else
            return false;
    }

    void disp() {
        if (head == NULL)
            return;
        else {
            LLnode<T>* temp = head;
            while (temp) {
                cout << getRecord(temp->data) << endl;
                //cout << temp->data << endl;
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
void operator&&(list<T>& l1, list<T>&l2) {
    LLnode<T>* temp1 = l1.head;
    LLnode<T>* temp2 = l2.head;
    while (temp1 != NULL && temp2 != NULL) {
        if (l2.getIndex(temp1->data) != -1)  {  //if the current item in L1 is also present in L2
            cout << getRecord(temp1->data) << endl;
        }
        if (l1.getIndex(temp2->data) != -1) { //if the current item in L2 is also present in L1
            cout << getRecord(temp2->data) << endl;
        }
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
}

template<typename T>
void operator||(list<T>& l1, list<T>&l2) {
    l1.disp();
    l2.disp();
}

//Enter int within a range
void inputInt(int& op, int min = INT_MIN, int max = INT_MAX) {
    while (!(cin >> op) || !(op >= min && op <= max)) {
        cin.clear();
        cin.ignore(50, '\n');
        cout << "\n\tInvalid; Try again: ";
    }
}

//Input character out of 2 options
void inputChar(char& op, char c1, char c2) {
    cin >> op;
    while ( !(op == c1 || op== c2)) {
        cout << "\n\tTry again, "<<c1<<" or " << c2 << ": ";
        cin >> op;
    }
}

enum months { Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec };
int counter = 0;
int queryNo = -1;
list<string> query1;                                 
list<string> query2;                                 

struct Date {
    string date;
    int day;
    int month;
    int year;
    Date() {
        date = "\0";
        day = 0;
        month = 0;
        year = 0;
    }
    Date(string s) {
        date = s;
        string dy = "", yr = "", mnth = "";
        int i;
        for (i = 0; s[i] != '-' && s[i] != '/'; i++) {
            dy += s[i];
        }
        for (++i; s[i] != '-' && s[i] != '/'; i++) {
            mnth += s[i];
        }
        for (++i; s[i] != '\0'; i++) {
            yr += s[i];
        }
        day = stoi(dy);//member var
        year = stoi(yr);//member var
        if (mnth == "Jan")
            month = 1;
        else if (mnth == "Feb")
            month = 2;
        else if (mnth == "Mar")
            month = 3;
        else if (mnth == "Apr")
            month = 4;
        else if (mnth == "May")
            month = 5;
        else if (mnth == "Jun")
            month = 6;
        else if (mnth == "Jul")
            month = 7;
        else if (mnth == "Aug")
            month = 8;
        else if (mnth == "Sep")
            month = 9;
        else if (mnth == "Oct")
            month = 10;
        else if (mnth == "Nov")
            month = 11;
        else if (mnth == "Dec")
            month = 12;
    }

    void set(string s) {
        date = s;
        string dy = "", yr = "", mnth = "";
        int i;
        for (i = 0; s[i] != '-' && s[i] != '/'; i++) {
            dy += s[i];
        }
        for (++i; s[i] != '-' && s[i] != '/'; i++) {
            mnth += s[i];
        }
        for (++i; s[i] != '\0'; i++) {
            yr += s[i];
        }
        day = stoi(dy);//member var
        year = stoi(yr);//member var
        if (mnth == "Jan")
            month = 1;
        else if (mnth == "Feb")
            month = 2;
        else if (mnth == "Mar")
            month = 3;
        else if (mnth == "Apr")
            month = 4;
        else if (mnth == "May")
            month = 5;
        else if (mnth == "Jun")
            month = 6;
        else if (mnth == "Jul")
            month = 7;
        else if (mnth == "Aug")
            month = 8;
        else if (mnth == "Sep")
            month = 9;
        else if (mnth == "Oct")
            month = 10;
        else if (mnth == "Nov")
            month = 11;
        else if (mnth == "Dec")
            month = 12;
    }
};

bool operator>(Date d1, Date d2) {
    if (d1.year <= 30) {
        return true;
    }
    if (d1.year < d2.year) {
        return false;
    }
    if (d1.year > d2.year) {
        return true;
    }
    //year is same
    if (d1.month < d2.month) {
        return false;
    }
    if (d1.month > d2.month) {
        return true;
    }
    //month is same
    if (d1.day < d2.day) {
        return false;
    }
    else
        return true;
}


bool operator<(Date d1, Date d2) {
    if (d2.year <= 30) {
        return true;
    }
    if (d1.year > d2.year) {
        return false;
    }
    if (d1.year < d2.year) {
        return true;
    }
    //year is same
    if (d1.month > d2.month) {
        return false;
    }
    if (d1.month < d2.month) {
        return true;
    }
    //month is same
    if (d1.day > d2.day) {
        return false;
    }
    else
        return true;
}

ostream& operator<<(ostream& out, Date d) {
    out << d.date;
    return out;
}

istream& operator>>(istream& in, Date& d) {
    string s = "";
    cout << "\n\t\tEnter date in the format DD-MMM-YY: ";
    cin >> s;
    string mnth = "", dy = "";
    for (int i = 3; i < 6; i++) {
        mnth += s[i];
    }
    dy += s[0];
    dy += s[1];

    //Input validation
    while (stoi(dy) > 31 || stoi(dy) <= 0 || s.length() != 9 || s[2] != '-' || s[6] != '-' ||
        !(mnth == "Jan" || mnth == "Feb" || mnth == "Mar" || mnth == "Apr" || mnth == "May" || mnth == "Jun" || mnth == "Jul" || mnth == "Aug"
            || mnth == "Sep" || mnth == "Oct" || mnth == "Nov" || mnth == "Dec")) {
        cout << "\n\t\tEnter date in the VALID format DD-MMM-YY , \n\t\t(Month should be sentence case Jan/Feb/Mar...): ";
        cin >> s;
        mnth = "";
        for (int i = 3; i < 6; i++) {
            mnth += s[i];
        }
    }

    d.set(s);
    cout << "\n\tDate inputted." << endl;
    return in;
}


bool operator>(string s1, string s2) {
    int i;
    for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++) {
        if (s1[i] == s2[i]) {
            continue;
        }
        else if (s1[i] > s2[i]) {
            return true;
        }
        else if (s1[i] < s2[i]) {
            return false;
        }
    }
    if (s1[i] == '\0' && s2[i] == '\0') {
        return true;
    }
    else if (s1[i] == '\0' && s2[i] != '\0') {  // s2 is longer than s1
        return false;
    }
    else if (s1[i] != '\0' && s2[i] == '\0') {  // s2 is shorter than s1
        return true;
    }
}
bool operator<(string s1, string s2) {
    int i;
    for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++) {
        if (s1[i] == s2[i]) {
            continue;
        }
        else if (s1[i] < s2[i]) {
            return true;
        }
        else if (s1[i] > s2[i]) {
            return false;
        }
    }
    if (s1[i] == '\0' && s2[i] == '\0') {
        return true;
    }
    else if (s1[i] == '\0' && s2[i] != '\0') {  // s2 is longer than s1
        return true;
    }
    else if (s1[i] != '\0' && s2[i] == '\0') {  // s2 is shorter than s1
        return false;
    }
}

template <typename T>
struct Node {
    //Storing the elements and their filerefs in parallel.
    T* node_key;
    string* filerefs;

    //Number of items in the node at one time.
    int count;

    //Next pointer (would be utilized in linked list).
    Node<T>* next;

    //Storing children pointers.
    Node<T>** node_childs;

    //Mark if it is a leaf node or no.
    bool leaf_node;

    //Default constructor.
    Node() {
        node_key = new T[m];
        filerefs = new string[m];
        node_childs = new Node * [m + 1];  // store +1 to temporarily store more than one
                                 // node from which median would be sent up as
                                 // Parent_NODE later
        next = NULL;
        leaf_node = true;
        count = 0;
    }

    //Parameterized constructor
    Node(T val, string fref)
    {
        node_key = new T[m];
        filerefs = new string[m];
        for (int i = 0; i < m; i++)
        {
            filerefs[i] = "\0";
        }
        node_childs = new Node * [m + 1];  // store +1 to temporarily store more than one
                                 // node from which median would be sent up as

                                 // Parent_NODE later
        count = 1;
        leaf_node = true;
        node_key[0] = val;
        filerefs[0] = fref;
        next = NULL;
    }
};


template <typename T>
class B_tree {
private:
    Node<T>* Root;

public:
    //Default constructor
    B_tree() {
        Root = NULL;
    }
    //Function to insert a key along with its filereference
    //Filref format L____F___

    void shifting_keys_in_array(T* extra_key, string* filerefs, int ct) {

        int shiftCt = m + 1;

        while (shiftCt > ct) {
            extra_key[shiftCt] = extra_key[shiftCt - 1];
            filerefs[shiftCt] = filerefs[shiftCt - 1];
            shiftCt--;
        }
    }


    void insert(T num, string& fileref) {
        if (Root == NULL) {
            // adding to root
            Root = new Node<T>(num, fileref);
        }
        else {
            // root already exist
            Node<T>* ptrCurrent = Root;//For Traversal

            //To mark the parent node we keep this pointer.
            Node<T>* Parent_NODE = new Node<T>;

            // reach the leaf node to insert
            //if only root exist it will skip this loop
            while (ptrCurrent->leaf_node != true) {
                //Set the parent node to current node before moving the current node to a lower position.
                Parent_NODE = ptrCurrent;
                //Moving current node:
                for (int i = 0; i < ptrCurrent->count; i++) {
                    //Less than keys[0] is in childs[0]
                    //Less than keys[1] is in childs[1]....etc
                    if (num < (ptrCurrent->node_key[i])) {
                        ptrCurrent = ptrCurrent->node_childs[i];
                        break;
                    }
                    //After checking all childs it is still greater
                    if (i == (ptrCurrent->count - 1)) {
                        //move to last child
                        ptrCurrent = ptrCurrent->node_childs[i + 1];
                        break;
                    }
                }
            }

            //Inserting in current node's keys
            //if the no items in node is smaller than the order(max keys)
            int currentKeys = ptrCurrent->count;
            if (m>currentKeys) {
                
                //Find the exact index where the new item will be stored
                for (int counter = 0; num > ptrCurrent->node_key[counter] && counter < ptrCurrent->count; counter++);
                

                // sorting all the keys inorder to insert in order
                int j = ptrCurrent->count;
                while (j > counter)
                {
                    ptrCurrent->node_key[j] = ptrCurrent->node_key[j - 1];
                    ptrCurrent->filerefs[j] = ptrCurrent->filerefs[j - 1];
                    j--;
                }
                
                //Now at the required index place the itmem and corresponding file-ref
                ptrCurrent->node_key[counter] = num;
                ptrCurrent->filerefs[counter] = fileref;

                //Increased number of itmes
                ptrCurrent->count += 1;

                //Save the size of the current node;
                int size = ptrCurrent->count;
                // copy the position to be emptied to the next position
                ptrCurrent->node_childs[size] = ptrCurrent->node_childs[size - 1];

                // empty the position in which we want to insert and then move it to the next position
                ptrCurrent->node_childs[size - 1] = NULL;
            }
            // if the size exceeds the maximum size to store the keys
             // create a new node
            else {
                Node<T>* node = new Node<T>;

                //temporary arrays having larger size to store new value and median value
                //before splitting
                T extra_key[m + 2] = {};
                string extra_filerefs[m + 2] = {};

                // vector<T> extra_key;
                int count = 0, count_2;

                // copying all current items and filerefs into a temp array
                while (count < m) {
                    extra_key[count] = ptrCurrent->node_key[count];
                    extra_filerefs[count] = ptrCurrent->filerefs[count];
                    count++;
                }

                //*************Finding the median*********
                count = 0;
                // find the index till when num is greater than temp array  elements
                while ( count < m) {
                    if ( extra_key[count]< num) {
                        count++;  // finding index to insert
                    }
                    else {
                        break;
                    }
                }
                // pushing the arrays 
                int shiftCt = m + 1;

                //Shift keys uptill the requried index
                while (shiftCt > count) {
                    extra_key[shiftCt] = extra_key[shiftCt - 1];
                    extra_filerefs[shiftCt] = extra_filerefs[shiftCt - 1];
                    shiftCt--;
                }
                
                // storing the value to be inserted into the temp array
                extra_key[count] = num;
                extra_filerefs[count] = fileref;

                // splitting the node to make Parent_NODE
                split_and_make_parent(node, ptrCurrent);

                // EMPTYING THE LAST [EXTRA] KEY
                ptrCurrent->node_childs[m] = NULL;

                // copying the extra key values in actual node
                count = 0;
                while (count < ptrCurrent->count) {
                    ptrCurrent->node_key[count] = extra_key[count];
                    ptrCurrent->filerefs[count] = extra_filerefs[count];
                    count++;
                }
                // storing the other half values in new leaf node
                count = 0;
                count_2 = ptrCurrent->count;
                while (count < node->count) {
                    node->node_key[count] = extra_key[count_2];
                    node->filerefs[count] = extra_filerefs[count_2];
                    count++;
                    count_2++;
                }

                bool is_Root = updating_root(ptrCurrent, node);
                // if its not root then insert it as internal node
                if (!is_Root) {
                    inserting_internal_node_of_tree(Parent_NODE, node,
                        node->node_key[0]);
                }
            }
        }
    }

    bool updating_root(Node<T>* ptrCurrent, Node<T>* node) {
        bool is_root = (ptrCurrent == Root);
        if (is_root) {
            // making new root
            Node<T>* updated_root = new Node<T>;
            // updating size of root to one
            updated_root->count = 1;
            // inserting its children
            updated_root->node_childs[0] = ptrCurrent;
            updated_root->node_childs[1] = node;
            // not a leaf node
            updated_root->leaf_node = false;

            updated_root->node_key[0] = node->node_key[0];

            // updating root now
            Root = updated_root;
            return true;
        }
        return false;
    }

    void split_and_make_parent(Node<T>* node, Node<T>* ptrCurrent) {
        node->leaf_node = true;

        int half_size = (m + 1) / 2;
        int next_half = m + 1 - (m + 1) / 2;
        ptrCurrent->count = half_size;
        node->count = next_half;
        ptrCurrent->node_childs[half_size] = node;
        node->node_childs[next_half] = ptrCurrent->node_childs[m];
    }

    void inserting_internal_node_of_tree(Node<T>* ptrCurrent, Node<T>* child_node, T key) {
        if (ptrCurrent->count < m) {
            int count = 0;
            for (count = 0; key > ptrCurrent->node_key[count] &&
                count < ptrCurrent->count;) {
                count++;
            }

            for (int count_2 = ptrCurrent->count; count_2 > count; count_2--) {
                ptrCurrent->node_key[count_2] =
                    ptrCurrent->node_key[count_2 - 1];
            }
            for (int count_3 = ptrCurrent->count + 1; count_3 > count + 1;
                count_3--) {
                ptrCurrent->node_childs[count_3] = ptrCurrent->node_childs[count_3 - 1];
            }

            ptrCurrent->node_key[count] = key;
            ptrCurrent->node_childs[count + 1] = child_node;
            ptrCurrent->count += 1;

        }
        else {
            Node<T>* internal_node = new Node<T>;
            T temp_key[m + 2];
            Node<T>* temp_ptr[m + 2];
            int count = 0;
            while (count < m) {
                temp_key[count] = ptrCurrent->node_key[count];
                count++;
            }

            count = 0;
            while (count < m + 1) {
                temp_ptr[count] = ptrCurrent->node_childs[count];
                count++;
            }
            count = 0;

            while (key > temp_key[count] && count < m) {
                count++;
            }
            int count_2 = m + 1;
            while (count_2 > count) {
                temp_key[count_2] = temp_key[count_2 - 1];
                count_2--;
            }

            temp_key[count] = key;

            count_2 = m + 2;

            while (count_2 > count + 1) {
                temp_ptr[count_2] = temp_ptr[count_2 - 1];
                count_2--;
            }

            temp_ptr[count + 1] = child_node;
            internal_node->leaf_node = false;
            int size = (m + 1) / 2;
            ptrCurrent->count = size;
            internal_node->count = m - size;

            count_2 = ptrCurrent->count + 1;
            for (count = 0; count < internal_node->count; count++) {
                internal_node->node_key[count] = temp_key[count_2];
                count_2++;
            }

            count_2 = ptrCurrent->count + 1;
            for (count = 0; count < internal_node->count + 1; count++) {
                internal_node->node_childs[count] = temp_ptr[count_2];
                count_2++;
            }

            bool is_root = (ptrCurrent == Root);
            if (is_root) {
                // making new root
                Node<T>* updated_root = new Node<T>;
                // updating size of root to one
                updated_root->count = 1;
                // inserting its children
                updated_root->node_childs[0] = ptrCurrent;
                updated_root->node_childs[1] = internal_node;
                // not a leaf node
                updated_root->leaf_node = false;

                updated_root->node_key[0] =
                    ptrCurrent->node_key[ptrCurrent->count];

                // updating root now
                Root = updated_root;
            }
            else {
                inserting_internal_node_of_tree(
                    find_the_parent_of_current_node(Root, ptrCurrent),
                    internal_node, ptrCurrent->node_key[ptrCurrent->count]);
            }
            return;
        }
    }

    Node<T>* find_the_parent_of_current_node(Node<T>* ptrCurrent,
        Node<T>* child_node) {
        Node<T>* parent_node = new Node<T>;
        bool is_leaf = ptrCurrent->leaf_node;
        if (is_leaf || (ptrCurrent->node_childs[0])->leaf_node) {
            return NULL;
        }
        int count = 0;
        while (count < ptrCurrent->count + 1) {
            if (ptrCurrent->node_childs[count] == child_node) {
                parent_node = ptrCurrent;
                return parent_node;
            }
            else {
                parent_node = find_the_parent_of_current_node(
                    ptrCurrent->node_childs[count], child_node);
                if (!parent_node == NULL) {
                    return parent_node;
                }
            }

            count++;
        }
        return parent_node;
    }

    void display_public() { display(Root); }
    void display(Node<T>* ptrCurrent) {
        if (ptrCurrent != NULL) {
            if (ptrCurrent->leaf_node) {
                cout << "leaf node: ";
            }
            for (int i = 0; i < ptrCurrent->count; i++) {
                cout << ptrCurrent->node_key[i] << "\t";
            }
            cout << endl;
            cout << "filerefs: ";
            if (ptrCurrent->filerefs[0] == "\0")
                cout << "THERE ARE NO FILEREFS";
            for (int i = 0; i < ptrCurrent->count; i++) {
                cout << ptrCurrent->filerefs[i] << "\t";
            }
            cout << endl;

            if (ptrCurrent->leaf_node != true) {
                for (int i = 0; i < ptrCurrent->count + 1; i++) {
                    display(ptrCurrent->node_childs[i]);
                }
            }
        }
        return;
    }

    //******************************* Deletion part starts *****************************************//
    void deleting_node(T to_delete)
    {
        int num_index = -99;
        int sibling_ind[2] = {};

        if (Root == NULL)
        {
            cout << "\nCannot find the element searched as the tree is empty" << endl;
            return;

        }
        else
        {     //sibling_ind[0]
            //finding if the element is present in the tree
            int i = 0;
            Node<T>* Parent_node = new Node<T>;
            Node <T>* ptrCurrent = Root;

            //Finding the node in where the key is stored
            while (ptrCurrent->leaf_node != true)
            {
                while (i < ptrCurrent->count)
                {
                    //***********initializing of siblings relative to upper node***********//
                    //khala khaloo
                    sibling_ind[0] = i - 1;
                    sibling_ind[1] = i + 1;

                    Parent_node = ptrCurrent;
                    if (to_delete < ptrCurrent->node_key[i]) {
                        //traversal (finding the correct childnode)
                        ptrCurrent = ptrCurrent->node_childs[i];
                        //break inner loop
                        break;
                    }

                    if (i == ptrCurrent->count - 1)
                    {
                        ptrCurrent = ptrCurrent->node_childs[i + 1];
                        sibling_ind[0] = i;
                        sibling_ind[1] = i + 2;
                        break;
                    }
                    i++;
                }
            }

            i = 0;
            //Now at node where key is, traversing the keys of ptr current
            while (i < ptrCurrent->count)
            {
                //if the value is found
                if (ptrCurrent->node_key[i] == to_delete)
                {
                    num_index = i;
                    break;
                }
                i++;
            }

            //deleting record from the file
            deleteFromFile(ptrCurrent->filerefs[i]);

            //if elemet not found
            if (num_index == -99)
            {
                cout << "\n\t\t(!) Cannot delete as such an element is not present in tree" << endl;
                return;
            }
            //if element is found in the tree
            else
            {
                //*********When the element is found in the array*********//
                //************Move all the forward elements one index less so that the last index of array gets empty   *********** //
                int count = num_index;

                while (count < ptrCurrent->count) {
                    ptrCurrent->filerefs[count] = ptrCurrent->filerefs[count + 1];
                    ptrCurrent->node_key[count] = ptrCurrent->node_key[count + 1];
                    count += 1;
                }

                //***********Decreasing array size to remove empty slot from the end   **********//
                ptrCurrent->count -= 1;

                check_if_root_is_null(ptrCurrent);

                //*********If the size of the array is greater than the minimum keys    ************//
                int min_keys = (m + 1) / 2;
                if (ptrCurrent->count >= min_keys) {
                    //Deletion is completed and we can return
                    return;
                }

                //**************Left and right siblings of the node to be deleted  *************//



                //***********Checking left side for borrowing an element ********//
                //(1) Check if left ind is not negative (IF LEFT SIBLING EXISTS)
                ///(if it is negative, it means it is out of range)
                if (sibling_ind[0] >= 0)
                {
                    //initialize left sibling
                    Node<T>* node_on_left = Parent_node->node_childs[sibling_ind[0]];
                    //(2) check if it has sufficient keys that it will not be <min after borrowin
                    if (node_on_left->count >= (min_keys + 1)) {
                        //START BORROWING
                        //**********Emptying the first index of the current node to be deleted  to fill the deleted empty space  ***********//
                        int k = ptrCurrent->count;
                        while (k > 0) {
                            //array being pushed forward
                            //because left will give its maximum (to store in [0])
                            ptrCurrent->node_key[k] = ptrCurrent->node_key[k - 1];
                            ptrCurrent->filerefs[k] = ptrCurrent->filerefs[k - 1];
                            k--;
                        }


                        //********* Initializing current pointer size with inremented ct ***************//
                        int current_size = ++ptrCurrent->count;

                        //*****************   Adjusting childs      ***************
                        ptrCurrent->node_childs[current_size] = ptrCurrent->node_childs[current_size - 1];
                        ptrCurrent->node_childs[current_size - 1] = NULL;

                        //Replace 0th index of current node with maximum key from the left child//
                        int lefts_max = node_on_left->count;
                        ptrCurrent->node_key[0] = node_on_left->node_key[lefts_max - 1];
                        ptrCurrent->filerefs[0] = node_on_left->filerefs[lefts_max - 1];//add the corresponding fileref

                        //subtracting the max element of left key//
                        node_on_left->count -= 1;

                        node_on_left->node_childs[lefts_max] = ptrCurrent;
                        node_on_left->node_childs[lefts_max + 1] = NULL;

                        //Replacing the borrowed key
                        Parent_node->node_key[sibling_ind[0]] = ptrCurrent->node_key[0];
                        Parent_node->filerefs[sibling_ind[0]] = ptrCurrent->filerefs[0];

                        //Borrowing completed
                        return;
                    }
                }

                //**********  Checking right side for borrowing an element  ************//
                //               it will only come here if the left side was unable to borrow 

                //(1) If the right index is within the range i.e., the right sibling exist
                if (sibling_ind[1] <= Parent_node->count) {
                    //Initialize right sibling
                    Node<T>* node_on_right = Parent_node->node_childs[sibling_ind[1]];
                    //If the right sibling has sufficient keys that it will not be <min after borrowing
                    if (node_on_right->count >= min_keys + 1)
                    {
                        //*********    Increasing current pointer size by one as to add an element from right sibling at its last index *************//
                        ptrCurrent->count += 1;

                        ptrCurrent->node_childs[ptrCurrent->count] = ptrCurrent->node_childs[ptrCurrent->count - 1];
                        ptrCurrent->node_childs[ptrCurrent->count - 1] = NULL;

                        //when taking from right , take its minimum key and move corresponding file//
                        ptrCurrent->node_key[ptrCurrent->count - 1] = node_on_right->node_key[0];
                        ptrCurrent->filerefs[ptrCurrent->count - 1] = node_on_right->filerefs[0];

                        //subtracting the size of right key//
                        node_on_right->count--;


                        node_on_right->node_childs[node_on_right->count] = node_on_right->node_childs[node_on_right->count + 1];
                        node_on_right->node_childs[node_on_right->count + 1] = NULL;

                        //**********Emptying the smallest element from the right node ***********//
                        int k = 0;
                        while (i < node_on_right->count)
                        {
                            node_on_right->node_key[k] = node_on_right->node_key[k + 1];
                            node_on_right->filerefs[k] = node_on_right->filerefs[k + 1];
                            k++;
                        }
                        Parent_node->node_key[sibling_ind[1] - 1] = node_on_right->node_key[0];
                        Parent_node->filerefs[sibling_ind[1] - 1] = node_on_right->filerefs[0];
                        return;
                    }
                }

                //***********Checking left side for deleting an element********//
                if (sibling_ind[0] >= 0)
                {
                    Node<T>* node_on_left = Parent_node->node_childs[sibling_ind[0]];
                    //first counter begins at last key of left sibling
                    int ct1 = node_on_left->count;
                    //second counter begins at 0
                    int ct2 = 0;
                    while (ct2 < ptrCurrent->count)
                    {
                        //Adjusting the values 
                        node_on_left->node_key[ct1] = ptrCurrent->node_key[ct2];
                        node_on_left->filerefs[ct1] = ptrCurrent->filerefs[ct2];
                        //Incrementing loop variables
                        ct1++;
                        ct2++;
                    }
                    //Setting the last child to NULL
                    node_on_left->node_childs[node_on_left->count] = NULL;

                    //Left node has one key added
                    node_on_left->count += ptrCurrent->count;

                    node_on_left->node_childs[node_on_left->count] = ptrCurrent->node_childs[ptrCurrent->count];

                    //delete_non_leaf(Parent_node->node_key[ sibling_ind[0]], Parent_node, ptrCurrent);

                    delete[] ptrCurrent->node_key;
                    delete[] ptrCurrent->filerefs;
                    delete[] ptrCurrent->node_childs;
                    delete ptrCurrent;
                    return;
                }

                //***********Checking right side for deleting an element********//
                else if (sibling_ind[1] <= Parent_node->count)
                {
                    Node<T>* node_on_right = Parent_node->node_childs[sibling_ind[1]];
                    int ct1 = ptrCurrent->count, ct2 = 0, right_max = node_on_right->count;
                    while (ct2 < right_max) {
                        ptrCurrent->node_key[ct1] = node_on_right->node_key[ct2];
                        ptrCurrent->filerefs[ct1] = node_on_right->filerefs[ct2];
                        ct1++;
                        ct2++;
                    }
                    
                    ptrCurrent->node_childs[ptrCurrent->count] = NULL;
                    ptrCurrent->count += right_max;

                    ptrCurrent->node_childs[ptrCurrent->count] = node_on_right->node_childs[right_max];

                    cout << "\nMerging nodes" << endl;
                    //delete_non_leaf(Parent_node->node_key[ sibling_ind[1] - 1], Parent_node, node_on_right);
                    delete[] node_on_right->node_key;
                    delete[] node_on_right->filerefs;
                    delete[] node_on_right->node_childs;
                    delete node_on_right;
                }
            }

        }
    }

    //**********Function to check if the current pointer is root**********//
    void check_if_root_is_null(Node<T>* ptrCurrent)
    {
        if (ptrCurrent == Root)
        {
            for (int count = 0; count < m + 1; count++)
            {
                ptrCurrent->node_childs[count] = NULL;
            }
            //***********If the root size has got zero then make its pointer null***********//
            if (ptrCurrent->count == 0)
            {
                Root = NULL;
                delete[] ptrCurrent->node_key;
                delete[] ptrCurrent->node_childs;
                delete ptrCurrent;
                cout << "\nTree is empty now as the last element of data is deleted" << endl;
            }

            return;
        }
        //*Allocating the next pointer memory to the deleted one (in case if the next ptr is not null)**//
        int next = ptrCurrent->count + 1;       //**Storing next index*//

        ptrCurrent->node_childs[next - 1] = ptrCurrent->node_childs[next];
        //*Making the extra memory null**//
        ptrCurrent->node_childs[next] = NULL;


    }



    ///For deleting a non-lead node(i.e., internal node of tree)
    //Call this function.
    void delete_non_leaf(T val, Node<T>* ptrCurrent, Node<T>* child)
    {
        //CASE 1: (Also base case) If the leaf to be deleted is the root  
        //Checking number of items in root
        if (ptrCurrent == Root && ptrCurrent->count == 1) { //If 1 element it must have left/right child or both
            int ref = -1;
            //find which child to be deleted
            if (child == ptrCurrent->node_childs[1]) {
                ref = 1;
            }
            else if (child == ptrCurrent->node_childs[0]) {
                ref = 0;
            }
            //On the basis of the child to be deleted
            //Delete the corresponding child and set the root as equivalent to the other
            // child on the other side.
            if (ref == 1 || ref == 0) {
                delete[] child->node_key;
                delete[] child->node_childs;
                delete child;
                //Re assign the value
                if (ref == 1)
                    Root = ptrCurrent->node_childs[0];
                else if (ref == 0)
                    Root = ptrCurrent->node_childs[1];
                delete[] ptrCurrent->node_key;
                delete[] ptrCurrent->node_childs;
                delete ptrCurrent;
                return;
            }
        }
        //Starting from the beginning find the index till where
        //where the reqired value is
        int index = 0;
        while (index < ptrCurrent->count) {
            if (ptrCurrent->node_key[index] == val) {
                break;
            }
            index++;
        }
        //Now continuing from the specified index
        int counter = index;
        while (counter < ptrCurrent->count) {
            //pushing forward
            ptrCurrent->node_key[counter] = ptrCurrent->node_key[counter + 1];
            counter++;
        }

        //Resetting the index
        index = 0;
        while (index < (ptrCurrent->count + 1)) {
            if (ptrCurrent->node_childs[index] == child) { break; }
            index++;
        }

        //We have to adjust the childs position to make room for the new (shifted) child.
        counter = index;//resetting the counter
        while (counter < ptrCurrent->count + 1) {
            ptrCurrent->node_childs[counter] = ptrCurrent->node_childs[counter + 1];//Adjusting the child pointers
            counter++;
        }

        //Deletion will reduce num of items
        ptrCurrent->count -= 1;

        //In these 2 cases deletion process is complete
        int min = (((m + 1) / 2) - 1);// minkeys-1 
        if (ptrCurrent == Root || ptrCurrent->count >= min) {
            return;
        }

        // Else case
        // We need to borrow
        //Calculating the parent through previously defined function
        Node<T>* parent = find_the_parent_of_current_node(Root, ptrCurrent);

        //Now that we found the parent
        //Find the sibling indexes
        int l_index, r_index;
        l_index = -1, r_index = -1;//Arbitary values
        index = 0;
        Node<T>* node_on_right = NULL, node_on_left = NULL;
        //Traverse the children of the current node's parent node
        while (index < parent->count + 1) { //traversing all siblings
            if (ptrCurrent == parent->node_childs[index]) {
                //Index now marks the current position of the current node With respect to its other siblings

                l_index = index - 1;

                //If left<0 it means current index was the leftmost.
                //We only check for left node if thats NOT the case.
                if (!(l_index < 0)) {
                    //Accessing left node using the parent ptr
                    node_on_left = parent->node_childs[l_index];
                }

                r_index = index + 1;

                //If right> parent's num items that means the current node was the rightmost.
                if (!(r_index > parent->count)) {
                    node_on_right = parent->node_childs[r_index];
                }

                break; //stop checking indexes as left and right childs are found
            }
            index++;//checking next index
        }

        //If left sibling has been found
        if (node_on_left != NULL) {
            //Check number of items in left sibling
            int minkeys = (m + 1) / 2;

            if (node_on_left->count >= minkeys) { //No of keys inside it is greater than/equal to min keys
                //*****BORROWING********//

                //making room for the new key to be inserted after borrowing.
                for (int ct = ptrCurrent->count; ct > 0; ct--) {
                    ptrCurrent->node_key[ct] = ptrCurrent->node_key[ct - 1];
                    //shifting keys
                }
                //Borrowing the key of left index from parent
                ptrCurrent->node_key[0] = parent->node_key[l_index];
                //Replacing parent's key with left sibling's  MAXIMUM key
                parent->node_key[l_index] = node_on_left->node_key[node_on_left->count - 1];

                //now adjusting childs
                for (int j = ptrCurrent->count + 1; j > 0; j--) {
                    ptrCurrent->node_childs[j] = ptrCurrent->node_childs[j - 1];
                    //shifting child pointers
                }
                //Adjusting the current node's smallest child with the MAXIMUM child of Left
                ptrCurrent->node_childs[0] = node_on_left->node_childs[node_on_left->count];

                ptrCurrent->count++; //A key has been added to current node
                node_on_left->count--; //a key has been removed from left sibling
                return;
                //*****BORROWING COMPLETED!!****//
            }
        }

        //If no availability of left sibling
        //check if right sibling has been found
        else if (node_on_right != NULL) {
            //Check number of items in right sibling
            int minkeys = (m + 1) / 2;

            if (node_on_right->count >= minkeys) {//Borrowing is possible!!
                //*****BORROWING********//

                //maximum key of current goes to parent's required node
                ptrCurrent->node_key[ptrCurrent->count] = parent->node_key[index];
                //parent gets the MINIMUM of right child
                parent->node_key[index] = node_on_right->node_key[0];
                for (int ct = 0; ct < node_on_right->count - 1; ct++) {
                    node_on_right->node_key[ct] = node_on_right->node_key[ct + 1];
                }
                //adjusting the last child ptr with right sibling's MINIMUM child
                ptrCurrent->node_childs[ptrCurrent->count + 1] = node_on_right->node_childs[0];

                //Adjusting right sibling's child ptrs
                for (int ct = 0; ct < node_on_right->count; ct++) {
                    node_on_right->node_childs[ct] = node_on_right->node_childs[ct + 1];
                }

                ptrCurrent->count++;//A key has been Added to current node
                node_on_right->count--;//a key has been removed from right sibling
                return;
                //*****BORROWING COMPLETED!!****//
            }
        }

        //Now is the case where borrowing was not possible from either siblings due to lack of keys!

        if (node_on_left != NULL) {

            //Add the parent's "left" index key (i.e. the key above left sibling) to left node's maximum
            node_on_left->node_key[node_on_left->count] = parent->node_key[l_index];

            int ct = node_on_left->count + 1;
            //Copying the values of current node into its left sibling (emptying the current node)
            int i = 0;
            while (i < ptrCurrent->count) {
                node_on_left->node_key[ct] = ptrCurrent->node_key[i];
                i++;
            }
            //Reset value of loop variable
            i = 0;
            while (i < ptrCurrent->count + 1) {
                //copying the child pointers to left child
                node_on_left->node_childs[ct] = ptrCurrent->node_childs[i];
                //Making the  pointer null(removing the child)
                ptrCurrent->node_childs[i] = NULL;
                i++;
            }
            //Number of keys that have been added in the left child:(update)
            node_on_left->count += ptrCurrent->count + 1;
            //emptied the current node
            ptrCurrent->count = 0;
            //Recursively call the function
            delete_non_leaf(parent->node_key[l_index], parent, ptrCurrent);
        }
        else if (node_on_right != NULL) {
            //Maximum key of current node replaced with  the corresponding parent key of right sibling
            ptrCurrent->node_key[ptrCurrent->count] = parent->node_key[r_index - 1];
            int ct = ptrCurrent->count + 1;
            //loop variable
            int k = 0;

            //copying all values into current node
            while (k < node_on_right->count) {
                ptrCurrent->node_key[ct] = node_on_right->node_key[k];
                k++;
            }

            //To adjust the childs
            ct = ptrCurrent->count + 1;
            k = 0;
            while (k < node_on_right->count + 1) {//Emptying childs of right into current
                ptrCurrent->node_childs[ct] = node_on_right->node_childs[k];
                node_on_right->node_childs[k] = NULL;
                k++;
            }
            //Updated number of keys into the current node:
            ptrCurrent->count += node_on_right->count + 1;
            //Right sibling has been emptied
            node_on_right->count = 0;

            //Recursive call
            delete_non_leaf(parent->node_key[r_index - 1], parent, node_on_right);
        }
    }

    //******************************* Deletion part Ends *****************************************//

 /*Displays the record of all names beginning with this string*/
    void searchingBystring(string search_item, Node<T>* ptrCurrent)
    {
        if (Root == NULL) {
            cout << "\n\t\t(!) Tree not populated"
                << endl;
        }
        else
        {

            int i = 0;
            if (!ptrCurrent->leaf_node)
            {
                while (i <= ptrCurrent->count)
                {
                    // if (ptrCurrent->node_key > search_item)
                    {
                        searchingBystring(search_item, ptrCurrent->node_childs[i]);
                    }
                    i++;
                }
            }
            else
            {
                for (int i = 0; i <= ptrCurrent->count; i++)
                {
                    if (ptrCurrent->node_key[i] == search_item )
                    {
                        //cout << ptrCurrent->node_key[i] << endl;
                        if (queryNo == 1) {
                            query1.add(ptrCurrent->filerefs[i]);
                        } else  if (queryNo == 2) {
                            query2.add(ptrCurrent->filerefs[i]);
                        }
                        /*cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
                        cout << getRecord(ptrCurrent->filerefs[i]) << endl;
                        cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
                        */counter++;
                    }
                }
            }

        }
    }

    void searchByString(T search_item)
    {
        counter = 0;
        
        //cout << "\nFollowing records have been retrieved: " << endl;
        searchingBystring(search_item, Root);

        cout << "\n\n\t\t***    Total Number of records returned for your query = " << counter << "    *** " << endl;
    }

    /*Shows if search_item exists or not in the tree*/
    void searching(T search_item) {
        bool search = false;
        if (Root == NULL) {
            cout << "\nCannot find the element searched as the tree is empty"
                << endl;
        }
        else {
            int i = 0;
            Node<T>* ptrCurrent = Root;
            while (ptrCurrent->leaf_node != true) {
                while (i < ptrCurrent->count) {
                    if (search_item < ptrCurrent->node_key[i]) {
                        ptrCurrent = ptrCurrent->node_childs[i];
                        break;
                    }
                    if (i == ptrCurrent->count - 1) {
                        ptrCurrent = ptrCurrent->node_childs[i + 1];
                        break;
                    }
                    i++;
                }
            }
            i = 0;
            while (i < ptrCurrent->count) {
                if (ptrCurrent->node_key[i] == search_item) {
                    search = true;
                    break;
                }
                i++;
            }

            if (search) {
                cout << "\nElement found in data" << endl;
            }
            else {
                cout << "Element not found in the data" << endl;
            }
        }
    }

    /*Displays the record of all record beginning with this letter*/
    void searchingBycharacter(T search_item, Node<T>* ptrCurrent)
    {
        if (Root == NULL)
        {
            cout << "\n\t\t(!) Tree not populated"
                << endl;
        }
        else
        {
            int i = 0;
            if (!ptrCurrent->leaf_node)
            {
                while (i <= ptrCurrent->count)
                {
                    // if (ptrCurrent->node_key > search_item)
                    {
                        searchingBycharacter(search_item, ptrCurrent->node_childs[i]);
                    }
                    i++;
                }
            }
            else
            {
                //cout << "\nFollowing records have been retrieved: " << endl;
                for (int i = 0; i <= ptrCurrent->count; i++)
                {
                    if (ptrCurrent->node_key[i] == search_item)
                    {
                        if (queryNo == 1) {
                            query1.add(ptrCurrent->filerefs[i]);
                        }
                        else  if (queryNo == 2) {
                            query2.add(ptrCurrent->filerefs[i]);
                        }
                        /*cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
                        cout << getRecord(ptrCurrent->filerefs[i]) << endl;
                        cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
                        */counter++;


                    }
                }
            }

        }
    }

    void searchBychar(T search_item)
    {
        counter = 0;
        
        searchingBycharacter(search_item, Root);
        cout << "\t\t***    Total Number of records returned for your query = " << counter << "    *** " << endl;
    }

    //*Enter roll no to see its record
    //*Only for specific record
    void searchingNum(int search_num) {
        if (Root == NULL) {
            cout << "\n\t\t(!) Tree not populated"
                << endl;
        }
        else {
            int i = 0;
            Node<T>* ptrCurrent = Root;
            while (!ptrCurrent->leaf_node) {
                while (i < ptrCurrent->count) {
                    if (search_num <= ptrCurrent->node_key[i]) {//comparing first letters
                        ptrCurrent = ptrCurrent->node_childs[i];
                        break;
                    }
                    if (i == ptrCurrent->count - 1) {
                        ptrCurrent = ptrCurrent->node_childs[i + 1];
                        break;
                    }
                    i++;
                }
            }
            i = 0;

            cout << "\n\tRequired record is:  " << endl;
            while (i < ptrCurrent->count) {
                /*cout << "PTR CURRENT -> NODE_KEY[I][0]: " << (ptrCurrent->node_key[i][0]) << endl;

                cout << "PTR CURRENT -> NODE_KEY[I]  : " << (ptrCurrent->node_key[i] ) << endl;
                cout << "SEARCH_ITEM[0] Is:: " << search_item[0] << endl<<endl;

                */

                if (ptrCurrent->node_key[i] == search_num) {
                    //finds the record stored at the file reference and couts it.
                    if (queryNo == 1) {
                        query1.add(ptrCurrent->filerefs[i]);
                    }
                    else  if (queryNo == 2) {
                        query2.add(ptrCurrent->filerefs[i]);
                    }
                    counter++;
                    /*cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
                    cout << getRecord(ptrCurrent->filerefs[i]) << endl;
                    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
                    */break;
                    
                }

                i++;
            }
        }
    }

    void searchDateB(Node<T>* ptrCurrent, Date& date) {
        if (ptrCurrent != NULL) {
            if (ptrCurrent->leaf_node) {
                for (int i = 0; i < ptrCurrent->count; i++) {
                    if (ptrCurrent->node_key[i] < date) {
                        if (queryNo == 1) {
                            query1.add(ptrCurrent->filerefs[i]);
                        }
                        else  if (queryNo == 2) {
                            query2.add(ptrCurrent->filerefs[i]);
                        }
                        //cout << getRecord(ptrCurrent->filerefs[i]) << endl;
                        counter++;
                    }
                    else
                        break;
                }
            }

            if (ptrCurrent->leaf_node != true) {
                for (int i = 0; i < ptrCurrent->count + 1; i++) {
                    if (ptrCurrent->node_key[i] < date) {
                        searchDateB(ptrCurrent->node_childs[i], date);
                    }
                    else /*if (ptrCurrent->node_key[i] > date)*/ {
                        return;
                    }
                }
            }
        }
        return;
    }
    void searchDateA(Node<T>* ptrCurrent, Date& date) {
        if (ptrCurrent != NULL) {
            if (ptrCurrent->leaf_node) {
                //Traversing keys
                for (int i = ptrCurrent->count - 1; i >= 0; i--) {
                    if (ptrCurrent->node_key[i] > date) {
                        if (queryNo == 1) {
                            query1.add(ptrCurrent->filerefs[i]);
                        }
                        else  if (queryNo == 2) {
                            query2.add(ptrCurrent->filerefs[i]);
                        }
                        //cout << getRecord(ptrCurrent->filerefs[i]) << endl;
                        counter++;
                    }
                    else
                        break;
                }
            }

            if (ptrCurrent->leaf_node != true) {
                //Traversing children
                for (int i = ptrCurrent->count; i >= 0; i--) {
                    if (ptrCurrent->node_key[i] > date) {
                        searchDateA(ptrCurrent->node_childs[i], date);
                    }
                    else /*if (ptrCurrent->node_key[i] < date)*/ {
                        return;
                    }

                }
            }
        }
        return;
    }
    void searchDateAfter(Date& date) {
        counter = 0;
        searchDateA(Root, date);
        cout << "\n\n\t\t***    Total Number of records returned for your query = " << counter << "    *** " << endl;

    }
    void searchDateBefore(Date d) {
        searchDateB(Root, d);
    }


    void haadiyaSearchingBystring(string search_item, Node<T>* ptrCurrent)
    {
        if (Root == NULL) {
            cout << "\n\t\t(!) Tree not populated"
                << endl;
        }
        else
        {

            int i = 0;
            if (!ptrCurrent->leaf_node)
            {
                while (i <= ptrCurrent->count)
                {
                     if (ptrCurrent->node_key[i] > search_item)
                    {
                        haadiyaSearchingBystring(search_item, ptrCurrent->node_childs[i]);
                    }
                    i++;
                }
            }
            else
            {
                for (int i = 0; i < ptrCurrent->count; i++)
                {
                    if (ptrCurrent->node_key[i].find(search_item) != string::npos)
                    {
                        //cout << ptrCurrent->node_key[i] << endl;
                        if (queryNo == 1) {
                            query1.add(ptrCurrent->filerefs[i]);
                        }
                        else  if (queryNo == 2) {
                            query2.add(ptrCurrent->filerefs[i]);
                        }
                        /*cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
                        cout << getRecord(ptrCurrent->filerefs[i]) << endl;
                        cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
                        */counter++;
                    }
                }
            }

        }
    }
    void haadiyaSearchByString(string search_item)
    {
        counter = 0;
        //cout << "\nFollowing records have been retrieved: " << endl;
        haadiyaSearchingBystring(search_item, Root);
        cout << "\n\n\t\t***    Total Number of records returned for your query = " << counter << "    *** " << endl;
    }

    void displayNot(Node<T>* ptrCurrent, list<string> &queryRefs) {
        if (ptrCurrent != NULL) {
            //If it is a leafnode
            if (ptrCurrent->leaf_node) {
                //Traverse the keys
                for (int i = 0; i < ptrCurrent->count; i++) {
                    bool check = true;
                    //Check the key against the whole not-linked-list
                    for (LLnode<string>* temp = queryRefs.head; temp != NULL; temp = temp->next) {
                        if (ptrCurrent->filerefs[i] == temp->data) {
                            check = false;
                            break;
                        }
                        
                    }
                    if (check) {
                        counter++;
                        query2.add(ptrCurrent->filerefs[i]);
                    }
                }
            }
            
            //If it is not  a leaf node
            if (ptrCurrent->leaf_node != true) {
                //Traverse the childs
                for (int i = 0; i < ptrCurrent->count + 1; i++) {
                    displayNot(ptrCurrent->node_childs[i], queryRefs);
                }
            }
        }
        return;
    }

    void searchNot(list<string> &queryRefs) {
        counter = 0;
        query2.clear();
        displayNot(Root, queryRefs);
        cout << "\n\n\t\t***    Total Number of records returned for your query (AFTER NOT) = " << counter << "    *** " << endl;
        cout << "\n\tPress any key to view the results of NOT query ...";
        system("PAUSE");
        query2.disp();
    }


};


/************************************* GLOBAL VARIABLES ********************************/
/******/                    B_tree<int> btRollNos;                               /******/
/******/                    B_tree<char> btGenders;                              /******/
/******/                    B_tree<string> btNames;                              /******/
/******/                    B_tree<string> btQualifications;                     /******/
/******/                    B_tree<string> btAddresses;                          /******/
/******/                    B_tree<Date> btDOBs;                                 /******/
/******/                    B_tree<Date> btRegDates;                             /******/
/********************************** GLOBAL VARIABLES ***********************************/


string getRecord(string fref) {
    int lineNum = 0, fileNum = 0;
    string fileName = "Fall2022DSDataFile";
    for (int i = 6; i <= 8; i++) {
        fileName += fref[i];
    }
    fileName += ".txt";
    //*****Syntax = L____F___************
    for (int i = 4, mul = 1; i > 0; i--, mul *= 10) {
        lineNum += ((fref[i] - '0') * mul);
    }

    for (int i = 8, mul = 1; i > 5; i--, mul *= 10) {
        fileNum += ((fref[i] - '0') * mul);
    }

    string data = "";
    fstream inputFile;
    inputFile.open(fileName, ios::in);

    for (int i = 0; i <= lineNum; i++) {
        data = "";
        getline(inputFile, data);
    }
    inputFile.close();
    return data;

}
void file_reading() {
    string Roll_Num = "", Name = "", Dateofbirth = "", Gender = "",
        Registration_Date = "", Address = "", Last_Qualification = "";
    string data = "";
    string fref = "";
    fstream file_data;
    string filename = "Fall2022DSDataFile";
    Date datevar;
    int numDigs, cols, lineNumber, fileNumber;

    for (int i = 0, fileNumber = 1; i < 9; i++, fileNumber++) {

        //*****Setting file name ************
        filename = "Fall2022DSDataFile";
        numDigs = int(log10(fileNumber) + 1);
        for (int i = 0; i < (3 - numDigs); i++) {
            filename += "0";
        }
        filename += to_string(fileNumber);
        filename += ".txt";

        cout << "\n\t > Reading from " << filename;
        //*****Opening file************
        file_data.open(filename, ios::in);

        //*****Initializing variables for new file************
        cols = 0;
        lineNumber = 0;

        //*****Reading 1 file************
        while (getline(file_data, data))
        {

            //If readin a deleted record
            //if (data[0] == '-') {
            //    cout << "reading data " << data << endl;
            //    //*****Reset variables for next line************
            //    lineNumber++;//next line will come
            //    cols = 0;
            //    continue; 
            //}
            //else{
                //********Breaking down one line of the data*******
            for (int i = 0; i < data.size(); i++) {
                if (data[i] == '-' && cols == 0)
                {
                    break;
                }
                if (cols == 0)
                {

                    if (data[i] >= '0' && data[i] <= '9') {
                        Roll_Num += data[i];
                    }
                    else {
                        cols++;
                    }
                }
                if (cols == 1) {
                    if (data[i] == ' ' || data[i] == '\t')
                    {
                        if (data[i + 1] >= 'a' && data[i + 1] <= 'z' ||
                            data[i + 1] >= 'A' && data[i + 1] <= 'Z') {
                            if (data[i] == '\t')
                            {
                                i++;
                            }

                            Name += data[i];


                        }
                        else if (data[i + 1] >= '0' && data[i + 1] <= '9') {
                            cols++;
                        }
                    }
                    else if (data[i] >= 'a' && data[i] <= 'z' ||
                        data[i] >= 'A' && data[i] <= 'Z') {
                        Name += data[i];
                    }
                }
                if (cols == 2) {
                    if (data[i] == ' ' || data[i] == '\t')
                    {
                        if ((data[i + 1] != 'M' && data[i + 2] != ' ' &&
                            data[i + 2] != '\t') ||
                            (data[i + 1] != 'F' && data[i + 2] != ' ' &&
                                data[i + 2] != '\t')) {
                            if (data[i] == '\t')
                            {
                                i++;
                            }
                            Dateofbirth += data[i];
                        }
                        else {
                            cols++;
                        }
                    }
                    else {
                        Dateofbirth += data[i];
                    }
                }
                if (cols == 3) {
                    if (data[i] == ' ' || data[i] == '\t') {
                        if ((data[i + 1] == 'M') ||
                            (data[i + 1] == 'F') &&
                            (data[i + 2] == ' ' || data[i + 2] == '\t')) {
                            Gender += data[i + 1];

                            cols++;
                        }
                    }
                }
                if (cols == 4)
                {
                    if (data[i] == ' ' || data[i] == '\t')
                    {
                        if ((data[i + 1] != 'H') && (data[i + 1] != 'h'))
                        {
                            i = i + 3;
                            Registration_Date += data[i];
                        }
                        else
                        {
                            cols++;
                            i++;
                        }
                    }
                    else {
                        Registration_Date += data[i];
                    }
                }
                if (cols == 5)
                {
                    if (data[i] == ' ' || data[i] == '\t')
                    {
                        if (((data[i + 1] == 'F') &&
                            ((data[i + 2] == 's') || (data[i + 3] == 'S') ||
                                (data[i + 2] == 'S'))) ||
                            ((data[i + 1] == 'A') && ((data[i + 3] == 'l') ||
                                (data[i + 3] == 'L')) ||
                                ((data[i + 1] == 'H') && (data[i + 2] == 'S')))) {

                            cols++;
                            i++;
                        }
                        else {
                            Address += data[i];
                        }
                    }
                    else {
                        Address += data[i];
                    }
                }
                if (cols == 6) {
                    if (data[i] != ' ' || data[i] != '\t') {
                        Last_Qualification += data[i];
                    }
                    else {
                        cols++;
                    }
                }
            }

            //*****Creating FREF (fileref) string ID************
            //*****Syntax = L____F___************

            fref += "L";
            if (lineNumber == 0) {
                fref += "0000";
            }
            else {
                numDigs = int(log10(lineNumber) + 1);
                for (int i = 0; i < (4 - numDigs); i++) {
                    fref += "0";
                }
                fref += to_string(lineNumber);
            }
            fref += "F";
            numDigs = int(log10(fileNumber) + 1);
            for (int i = 0; i < (3 - numDigs); i++) {
                fref += "0";
            }
            fref += to_string(fileNumber);

            //***********Adding to the Btrees**************
            if (cols != 0)
            {
                btRollNos.insert(stoi(Roll_Num), fref);

                btGenders.insert(Gender[0], fref);

                btNames.insert(Name, fref);

                btAddresses.insert(Address, fref);

                datevar.set(Dateofbirth);
                btDOBs.insert(datevar, fref);

                datevar.set(Registration_Date);
                btRegDates.insert(datevar, fref);

                btQualifications.insert(Last_Qualification, fref);
            }



            //*****Reset variables for next line************
            lineNumber++;//next line will come
            fref = "";
            Roll_Num = "";
            Name = "";
            Dateofbirth = "";
            Gender = "";
            Address = "";
            Registration_Date = "";
            Last_Qualification = "";
            cols = 0;

        }

        //*****Going to open next file************
        file_data.close();
    }
}

void insertingRecord() {
    static int rollNoTracker = 6601;
    string name, address, qualification;
    char gender;
    Date dt1, dt2;
    cin.ignore();
    cout << "\n\tEnter the person's name: ";

    getline(cin, name);
    cout << "\n\tEnter the person's gender: ";
    cin >> gender;
    while (gender != 'F' && gender != 'M' && gender!='f' && gender !='m') {
        cout << "\n\tThere are only two genders M/F, please enter valid gender: ";
        cin >> gender;
    }
    cout << "\n\tEnter the person's date of birth: ";
    cin >> dt1;
    cout << "\n\tEnter the person's date of registration: ";
    cin >> dt2;

    cout << "\n\tEnter the person's address: ";
    cin.ignore();
    getline(cin, address);

    cout << "\n\tEnter the person's qualification ALevel/HSSC/FSc: ";
    cin.ignore();
    getline(cin, qualification);

    /*********Creating file reference*********/
    static int lineNoTracker = 101;
    string fref = "L0";
    fref += to_string(lineNoTracker++);//incrementing for next time
    fref += "F001";

    //**Opening file*****
    fstream file_data;
    file_data.open("Fall2022DSDataFile001.txt", ios::app);
    //Writing data into file's end
    file_data << endl << to_string(rollNoTracker) << "\t" << name << "\t" << dt1.date << "\t" << gender << "\t" << dt2.date << "\t" << address << "\t" << qualification;

    ///Writing data into all the trees
    btRollNos.insert(rollNoTracker++, fref);
    btNames.insert(name, fref);
    btAddresses.insert(address, fref);
    btGenders.insert(gender, fref);
    btDOBs.insert(dt1, fref);
    btQualifications.insert(qualification, fref);
    btRegDates.insert(dt2, fref);
    cout << "\n\n\t\t\t Data has been inputted in file as well as updated in the trees." << endl;
    cout << "\n\n\t\t\t Data's file reference is " << fref << endl;
    //Closing file
    file_data.close();
}



//L----F---
void deleteFromFile(string fref) {
    cout << "\n\tDELETING FREF ====  " << fref << endl;
    int lineNum = 0, fileNum = 0;
    string fileName = "Fall2022DSDataFile";
    for (int i = 6; i <= 8; i++) {
        fileName += fref[i];
    }
    fileName += ".txt";
    //*****Syntax = L____F___************
    for (int i = 4, mul = 1; i > 0; i--, mul *= 10) {
        lineNum += ((fref[i] - '0') * mul);
    }
    string data = "";
    //////// /*fstream inputFile;
    //////// inputFile.open(fileName, ios::out);

    //////// for (int i = 0; i < lineNum; i++) {
    ////////     data = "";
    ////////     getline(inputFile, data);
    //////// }

    //////// inputFile << "---------------------------" << endl;
    ////////
    //////// inputFile.close();*/

    string toReplace = getRecord(fref);//identifies the record to replace
    string deleted = "----------------------------";
    ifstream inFile;
    inFile.open(fileName, ios::in);
    ofstream outFile;
    outFile.open(fileName, ios::out || ios::app);
    //string data;
    int replaceLen = toReplace.length();

    while (getline(inFile, data)) {
        for (int i = 0; i < 1; ) {
            int pos = data.find(toReplace);
            if (pos != string::npos)
                data.replace(pos, replaceLen, deleted);
            else
                break;
        }

        outFile << data << endl;
    }

}

string menu = "\n\n\n\t(1). Search Record by Specific Name   \t\t(2). Search Record by Name Contained. \n\t(3). Search Birth dates BEFORE given date\t(4). Search Birth dates AFTER a given date \n\t(5).Search records by qualification     \t(6).Search record by roll no \n\t(7).Search by gender(M or F)           \t\t(8).Search by address \n\t(9).Search reg.dates BEFORE given date \t\t(10) Search reg.date AFTER given date\n\t";

void chooseOperation() {
    char opt = '\0';
    cout << "\n\tWhat operation do you want to perform  ? \n\n\t(A) AND && operation \n\t(O) OR || operation \t>";
    inputChar(opt, 'A', 'O');
    if (opt == 'A') {
        query1 && query2;
    }
    else {
        query1 || query2;
    }
}

void queries2() {
    int ans2;
    string data = "";
    Date det;
    char opt = '\0';
    /*Now store in query2*/
    queryNo = 2;
    /*To make sure no older values are present*/
    query2.clear();
    cout << "\n\t\t\t ****QUERY 2****" << endl;
    cout << menu;
    inputInt(ans2, 1, 10);
    switch (ans2) {
    case 1:
        cout << "\n\tEnter the name to search exact record. ";
        cin.ignore();
        getline(cin, data);
        btNames.searchByString(data);
        break;
    case 2:
        cout << "\n\tEnter the name to search records containing that name. ";
        cin.ignore();
        getline(cin, data);
        btNames.haadiyaSearchByString(data);
        break;
    case 3:
        cout << "\n\tEnter the date to search records of people born before: ";
        cin >> det;
        btDOBs.searchDateBefore(det);
        break;
    case 4:
        cout << "\n\tEnter the date to search records of people born after: ";
        cin >> det;
        btDOBs.searchDateAfter(det);
        break;
    case 5:
        cout << "\n\tEnter the qualification to search. ";
        cin.ignore();
        getline(cin, data);
        btQualifications.searchByString(data);
        break;
    case 6:
        cout << "\n\tEnter the roll no. to search. ";
        inputInt(ans2, 0);
        btRollNos.searchingNum(ans2);
        break;
    case 7:
        cout << "\n\tEnter a Gender (M or F) to search. ";
        inputChar(opt, 'M', 'F');
        btGenders.searchBychar(opt);
        break;
    case 8:
        cout << "\n\tEnter an address or part of it, to search. ";
        cin.ignore();
        getline(cin, data);
        btAddresses.haadiyaSearchByString(data);  
        break;
    case 9:
        cout << "\n\tEnter the date to search records of people registered before: ";
        cin >> det;
        btRegDates.searchDateBefore(det);
        break;
    case 10:
        cout << "\n\tEnter the date to search records of people registered after: ";
        cin >> det;
        btRegDates.searchDateAfter(det);
        break;

    }
    chooseOperation();
    //return;
}

void queries() {
    char opt = '\0';
    int ans, ans2, ans3;
    Date det;
    char gender = '\0';
    string data = "";
    string divider = "\n\t><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>";
    do {
        system("cls");

        cout << divider;
        cout << "\n\t*\t\t\t\tWelcome to\t\t\t\t*"
            << "\n\t*\t\t\tFatima & Haadiya's Queries\t\t\t*"
            << divider;

       cout << menu << "(0).Quit \t\t > ";

        inputInt(ans, 0, 10);

        cout << divider;
        queryNo = 1;
        query1.clear();
        switch (ans) {
        case 1:
            cout << "\n\tEnter the name to search exact record. ";
            cin.ignore();
            getline(cin, data);
            cout << "\n\tDo you want to AND/OR with another query? Y/N: ";
            cin >> opt;
            if (opt == 'Y' || opt== 'y') {
                btNames.searchByString(data);
                queries2();
            }
            else { 
                btNames.searchByString(data);
                cout << "\n\tPress any key to display the results \n\t" ;
                system("PAUSE");
                query1.disp();
            }
            break;
        case 2:
            cout << "\n\tEnter the name to search records containing that name. ";
            cin.ignore();
            getline(cin, data);
            btNames.haadiyaSearchByString(data);
            cout << "\n\tDo you want to AND/OR with another query? Y/N ";
            inputChar(opt, 'Y', 'N');
            if (opt == 'Y') {
                queries2();
            }
            else {
                cout << "\n\tDo you want to NOT this query? Y/N ";
                inputChar(opt, 'Y', 'N');
                if (opt == 'N') { //NORMAL SEARCH HAS BEEN DONE 
                    cout << "\n\tPress any key to display the results \n\t";
                    system("PAUSE");
                    query1.disp();
                }
                else {
                    cout << "\n\tAfter NOT the records are:- " << endl << endl;
                    btNames.searchNot(query1);
                }
            }
            break;
        case 3:
            cout << "\n\tEnter the date to search records of people born before: ";
            cin >> det;
            btDOBs.searchDateBefore(det);
            cout << "\n\tDo you want to AND/OR with another query? Y/N ";
            inputChar(opt, 'Y', 'N');
            if (opt == 'Y') {
                queries2();
            }
            else {
                
                    cout << "\n\tPress any key to display the results \n\t";
                    system("PAUSE");
                    query1.disp();
                
            }
            break;
        case 4:
            cout << "\n\tEnter the date to search records of people born after: ";
            cin >> det;
            btDOBs.searchDateAfter(det);

            cout << "\n\tDo you want to AND/OR with another query? Y/N ";
            inputChar(opt, 'Y', 'N');
            if (opt == 'Y') {
                queries2();
            }
            else {
                
                    cout << "\n\tPress any key to display the results \n\t";
                    system("PAUSE");
                    query1.disp();
                
            }
            break;
        case 5:
            cout << "\n\tEnter the qualification to search. ";
            cin.ignore();
            getline(cin, data);
            btQualifications.searchByString(data);
            cout << "\n\tDo you want to AND/OR with another query? Y/N ";
            inputChar(opt, 'Y', 'N');
            if (opt == 'Y') {
                queries2();
            }
            else {
                cout << "\n\tDo you want to NOT this query? Y/N ";
                inputChar(opt, 'Y', 'N');
                if (opt == 'N') { //NORMAL SEARCH HAS BEEN DONE 
                    cout << "\n\tPress any key to display the results \n\t";
                    system("PAUSE");
                    query1.disp();
                }
                else {
                    cout << "\n\tAfter NOT the records are:- " << endl << endl;
                    btQualifications.searchNot(query1);
                }
            }
            break;
        case 6:
            cout << "\n\tEnter the roll no. to search. ";
            inputInt(ans2, 0);
            btRollNos.searchingNum(ans2);

            cout << "\n\tDo you want to AND/OR with another query? Y/N " ;
            inputChar(opt, 'Y', 'N');
            if (opt == 'Y') {
                queries2();
            }
            else {
                cout << "\n\tDo you want to NOT this query? Y/N ";
                inputChar(opt, 'Y', 'N');
                if (opt == 'N') { //NORMAL SEARCH HAS BEEN DONE 
                    cout << "\n\tPress any key to display the results \n\t";
                    system("PAUSE");
                    query1.disp();
                }
                else {
                    cout << "\n\tAfter NOT the records are:- " << endl << endl;
                    btRollNos.searchNot(query1);
                }
            }
           
            break;
        case 7:
            cout << "\n\tEnter a Gender (M or F) to search. ";
            inputChar(gender, 'M', 'F');
            btGenders.searchBychar(gender);
            cout << "\n\tDo you want to AND/OR with another query? Y/N ";
            inputChar(opt, 'Y', 'N');
            if (opt == 'Y') {
                queries2();
            }
            else {
                cout << "\n\tDo you want to NOT this query? Y/N ";
                inputChar(opt, 'Y', 'N');
                if (opt == 'N') { //NORMAL SEARCH HAS BEEN DONE 
                    cout << "\n\tPress any key to display the results \n\t";
                    system("PAUSE");
                    query1.disp();
                }
                else {
                    cout << "\n\tAfter NOT the records are:- " << endl << endl;
                    btGenders.searchNot(query1);
                }
            }
            break;
        case 8:
            cout << "\n\tEnter the Address to find relevant Addresses ";
            cin.ignore();
            getline(cin, data);
            btAddresses.haadiyaSearchByString(data);
            cout << "\n\tDo you want to AND/OR with another query? Y/N ";
            inputChar(opt, 'Y', 'N');
            if (opt == 'Y') {
                queries2();
            }
            else {
                cout << "\n\tDo you want to NOT this query? Y/N ";
                inputChar(opt, 'Y', 'N');
                if (opt == 'N') { //NORMAL SEARCH
                    cout << "\n\tPress any key to display the results \n\t" ;
                    system("PAUSE");
                    query1.disp();
                }
                else {
                    cout << "\n\tAfter NOT the records are:- " << endl << endl;
                    btAddresses.searchNot(query1);
                }
            }
            break;
        case 9:
            cout << "\n\tEnter the date to search records of people registered before: ";
            cin >> det;
            btRegDates.searchDateBefore(det);
            cout << "\n\tDo you want to AND/OR with another query? Y/N " << endl;
            inputChar(opt, 'Y', 'N');
            if (opt == 'Y') {
                queries2();
            }
            else {
                cout << "\n\tPress any key to display the results \n\t";
                system("PAUSE");
                query1.disp();
            }
            break;
        case 10:
            cout << "\n\tEnter the date to search records of people born after: ";
            cin >> det;
            btRegDates.searchDateAfter(det);
            cout << "\n\tDo you want to AND/OR with another query? Y/N " << endl;
            inputChar(opt, 'Y', 'N');

            if (opt == 'Y') {
                queries2();
            }
            else {
                cout << "\n\tPress any key to display the results \n\t";
                system("PAUSE");
                query1.disp();
            }
            break;
        case 0:
            queryNo = -1;
            return;
        }
        queryNo = -1;
        data = "";
        cout << divider
            << "\n\t Press 1 to continue, 0 to quit ...";
        inputInt(ans2, 0, 1);
       

    } while (ans2 != 0);
}

void mainMenu() {
    int ans, ans2, ans3;
    string data = "";
    string divider = "\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    do {
        system("cls");

        cout << divider;
        cout << "\n\t*\t\t\t\tWelcome to\t\t\t\t*"
            << "\n\t*\t\t\tFatima And Haadiya's Proj\t\t\t*"
            << divider;

        cout << "\n\n\t(1). Populate B+ Trees  \t (2). Print B+ Tree "
            << "  \n\t(3). Insert new record   \t (4). Delete Record "
            << "  \n\t(5) Queries (Searching)  \t (0). Quit \t\t> ";

        inputInt(ans, 0, 5);

        cout << divider;

        switch (ans) {
        case 1:
            file_reading();
            break;
        case 2: {
            cout << "\n\t\tChoose which tree to print";
            cout << "\n\t(1) RollNo's   \t(2) Names       \t(3)Qualifications"
                << "\n\t(4) Gender      \t(5) Date(Birth) \t(6) Date(Registration)"
                << "\n\t(7) Addresses  \t > ";
            inputInt(ans2, 1, 7);
            switch (ans2) {
            case 1:
                btRollNos.display_public();
                break;
            case 2:
                btNames.display_public();
                break;
            case 3:
                btQualifications.display_public();
                break;
            case 4:
                btGenders.display_public();
                break;
            case 5:
                btDOBs.display_public();
                break;
            case 6:
                btRegDates.display_public();
                break;
            }
        }

              break;
        case 3:
            insertingRecord();
            break;
        case 4: {
            cout << "\n\t\tChoose how to delete";
            cout << "\n\t(1) By RollNo   \t(2) By Name  \t > ";
            inputInt(ans2, 1, 2);
            switch (ans2) {
            case 1:
                cout << "\nEnter the roll no:";
                inputInt(ans3, 0);
                btRollNos.deleting_node(ans3);
                break;
            case 2:
                cout << "\nEnter the Name:";
                cin.ignore();
                getline(cin, data);
                btNames.deleting_node(data);
                break;
            }
        }  break;
        case 5:
            queries();
            break;
        case 0:
            return;

        }
        cout << divider
            << "\n\t Press 1 to continue, 0 to quit ...";
        inputInt(ans2, 0, 1);

    } while (ans2 != 0);

}