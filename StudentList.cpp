#include "StudentList.h"

// Define a constructor to initialize the list. The list starts with no Students
StudentList::StudentList() {
    head = nullptr; 
    tail = nullptr; 
    numStudents = 0; 
}

// Return the number of students currently in the list
int StudentList::listSize() {
    return numStudents; 
}

// Add a Node with a student to the front (head) of the list.
void StudentList::addFront(Student s) {
    Node* newNode = new Node(s); 

    if (head == nullptr) {
        head = newNode; 
        tail = newNode; 
    } else { 
        newNode->next = head; 
        head->prev = newNode; 
        head = newNode; 
    }
    numStudents++; 
}

// Add a Node with a student to the back (tail) of the list.
void StudentList::addBack(Student s) {
    Node* newNode = new Node(s); 

    if (tail == nullptr) { 
        head = newNode; 
        tail = newNode; 
    } else { 
        tail->next = newNode; 
        newNode->prev = tail; 
        tail = newNode; 
    }
    numStudents++; 
} // <-- Closing brace added here

// Print out the names of each student in the list.
void StudentList::printList() {
    Node* current = head; 
    while (current != nullptr) { 
        cout << current->data.name << endl; 
        current = current->next; 
    }
}

// Remove the Node with the student at the back (tail) of the list
void StudentList::popBack() {
    if (tail == nullptr) { 
        cout << "Error: List is empty, cannot pop from back." << endl;
        return; 
    }

    Node* temp = tail; 
    if (tail->prev != nullptr) { 
        tail = tail->prev; 
        tail->next = nullptr; 
    } else { 
        head = nullptr; 
        tail = nullptr; 
    }
    delete temp; 
    numStudents--; 
}

// Remove the Node with the student at the front (head) of the list
void StudentList::popFront() {
    if (head == nullptr) { 
        cout << "Error: List is empty, cannot pop from front." << endl;
        return; 
    }

    Node* temp = head; 
    if (head->next != nullptr) { 
        head = head->next; 
        head->prev = nullptr; 
    } else { 
        head = nullptr; 
        tail = nullptr; 
    }
    delete temp; 
    numStudents--;
}

// Insert a student at the position "index".
void StudentList::insertStudent(Student s, int index) {
    if (index < 0 || index > numStudents) { 
        cout << "Invalid index. Adding student to the back." << endl;
        addBack(s); 
        return;
    }

    if (index == 0) { 
        addFront(s); 
        return;
    }

    Node* newNode = new Node(s); 
    Node* current = head; 

    for (int i = 0; i < index - 1; ++i) { 
        current = current->next;
    }

    newNode->next = current->next; 
    newNode->prev = current; 

    if (current->next != nullptr) { 
        current->next->prev = newNode; 
    } else { 
        tail = newNode; 
    }
    current->next = newNode; 
    numStudents++; 
}

// Find the student with the given id number and return them
Student StudentList::retrieveStudent(int idNum) {
    Node* current = head; 

    while (current != nullptr) { 
        if (current->data.id == idNum) { 
            return current->data; 
        }
        current = current->next; 
    }

    cout << "Student with ID " << idNum << " not found." << endl;
    return Student(); 
}

// Remove a Node with a student from the list with a given id number
void StudentList::removeStudentById(int idNum) {
    Node* current = head; 

    while (current != nullptr) { 
        if (current->data.id == idNum) { 
            if (current->prev != nullptr) {
                current->prev->next = current->next; 
            } else {
                head = current->next; 
            }
            if (current->next != nullptr) {
                current->next->prev = current->prev; 
            } else {
                tail = current->prev; 
            }
            delete current; 
            numStudents--; 
            return; 
        }
        current = current->next; 
    }

    cout << "Student with ID " << idNum << " not found. Cannot remove." << endl;
}

// Change the GPA of the student with given id number to newGPA
void StudentList::updateGPA(int idNum, float newGPA) {
    Node* current = head; 

    while (current != nullptr) { 
        if (current->data.id == idNum) { 
            current->data.GPA = newGPA; 
            return; 
        }
        current = current->next; 
    }

    cout << "Student with ID " << idNum << " not found. Cannot update GPA." << endl;
}

// Add all students from otherList to this list.
void StudentList::mergeList(StudentList &otherList) {
    if (otherList.head == nullptr) return; 

    if (head == nullptr) { 
        head = otherList.head; 
        tail = otherList.tail; 
    } else { 
        tail->next = otherList.head; 
        otherList.head->prev = tail; 
        tail = otherList.tail; 
    }

    numStudents += otherList.numStudents; 
    otherList.head = nullptr; 
    otherList.tail = nullptr; 
    otherList.numStudents = 0; 
}

// Create a StudentList of students whose GPA is at least minGPA.
StudentList StudentList::honorRoll(float minGPA) {
    StudentList honorList; 
    Node* current = head; 

    while (current != nullptr) {
        if (current->data.GPA >= minGPA) { 
            honorList.addBack(current->data); 
        }
        current = current->next; 
    }

    return honorList; 
}
