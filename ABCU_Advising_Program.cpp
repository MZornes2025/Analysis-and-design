/*******************************************************************************
* ABCU Advising Program
*
* Description: This program helps academic advisors manage and view course
*              information for the Computer Science department at ABCU.
*              It loads course data from a file into a binary search tree (BST),
*              allows printing all courses in alphanumeric order, and searching
*              for specific course information including prerequisites.
*
* Author: Mariana Zornes
* Date: 6/22/2025
* Version: 1
*******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

/*******************************************************************************
* Course Structure
*******************************************************************************/
struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;
};

/*******************************************************************************
* Binary Search Tree Node Structure
*******************************************************************************/
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course aCourse) : course(aCourse), left(nullptr), right(nullptr) {}
};

/*******************************************************************************
* Binary Search Tree Class
*******************************************************************************/
class BinarySearchTree {
private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void destroyTree(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void Insert(Course course);
    Course Search(string courseNumber);
    void InOrder();
};

BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

BinarySearchTree::~BinarySearchTree() {
    destroyTree(root);
}

void BinarySearchTree::Insert(Course course) {
    if (root == nullptr) {
        root = new Node(course);
    }
    else {
        addNode(root, course);
    }
}

void BinarySearchTree::addNode(Node* node, Course course) {
    if (course.courseNumber < node->course.courseNumber) {
        if (node->left == nullptr) {
            node->left = new Node(course);
        }
        else {
            addNode(node->left, course);
        }
    }
    else {
        if (node->right == nullptr) {
            node->right = new Node(course);
        }
        else {
            addNode(node->right, course);
        }
    }
}

Course BinarySearchTree::Search(string courseNumber) {
    // Convert input to uppercase for case-insensitive comparison
    transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);

    Node* current = root;

    while (current != nullptr) {
        string currentCourseNumber = current->course.courseNumber;
        transform(currentCourseNumber.begin(), currentCourseNumber.end(), currentCourseNumber.begin(), ::toupper);

        if (currentCourseNumber == courseNumber) {
            return current->course;
        }
        else if (courseNumber < currentCourseNumber) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    return Course();
}

void BinarySearchTree::InOrder() {
    inOrder(root);
}

void BinarySearchTree::inOrder(Node* node) {
    if (node != nullptr) {
        inOrder(node->left);
        cout << node->course.courseNumber << ", " << node->course.title << endl;
        inOrder(node->right);
    }
}

void BinarySearchTree::destroyTree(Node* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

/*******************************************************************************
* Helper function to trim whitespace
*******************************************************************************/
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (string::npos == first) {
        return "";
    }
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

/*******************************************************************************
* Load Courses Function
*******************************************************************************/
void loadCourses(string filename, BinarySearchTree* bst) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file '" << filename << "'." << endl;
        return;
    }

    cout << "Loading courses from file..." << endl;

    string line;
    int lineNumber = 0;
    int coursesLoaded = 0;

    while (getline(file, line)) {
        lineNumber++;
        line = trim(line);

        if (line.empty()) continue;

        vector<string> tokens;
        size_t start = 0;
        size_t end = line.find(',');

        while (end != string::npos) {
            string token = trim(line.substr(start, end - start));
            if (!token.empty()) {
                tokens.push_back(token);
            }
            start = end + 1;
            end = line.find(',', start);
        }

        string lastToken = trim(line.substr(start));
        if (!lastToken.empty()) {
            tokens.push_back(lastToken);
        }

        if (tokens.size() < 2) {
            cout << "Warning: Line " << lineNumber << " skipped - invalid format: " << line << endl;
            continue;
        }

        Course course;
        course.courseNumber = tokens[0];
        course.title = tokens[1];

        for (size_t i = 2; i < tokens.size(); ++i) {
            if (!tokens[i].empty()) {
                course.prerequisites.push_back(tokens[i]);
            }
        }

        bst->Insert(course);
        coursesLoaded++;
    }

    file.close();
    cout << "Successfully loaded " << coursesLoaded << " courses." << endl;
}

/*******************************************************************************
* Display Course Function
*******************************************************************************/
void displayCourse(Course course, BinarySearchTree* bst) {
    if (course.courseNumber.empty()) {
        cout << "Course not found." << endl;
        return;
    }

    cout << "\nCourse Details:" << endl;
    cout << "---------------" << endl;
    cout << "Number: " << course.courseNumber << endl;
    cout << "Title: " << course.title << endl;

    if (!course.prerequisites.empty()) {
        cout << "\nPrerequisites:" << endl;
        for (string prereq : course.prerequisites) {
            Course prereqCourse = bst->Search(prereq);
            if (!prereqCourse.courseNumber.empty()) {
                cout << "  " << prereqCourse.courseNumber << " - " << prereqCourse.title << endl;
            }
            else {
                cout << "  " << prereq << " (prerequisite not found in system)" << endl;
            }
        }
    }
    else {
        cout << "\nNo prerequisites required." << endl;
    }
    cout << endl;
}

/*******************************************************************************
* Display Menu Function
*******************************************************************************/
void displayMenu() {
    cout << "\nABCU Advising Program Menu" << endl;
    cout << "-------------------------" << endl;
    cout << "1. Load Courses from File" << endl;
    cout << "2. Print Course List" << endl;
    cout << "3. Search for Course" << endl;
    cout << "9. Exit Program" << endl;
    cout << "Enter your choice (1-3 or 9): ";
}

/*******************************************************************************
* Main Function
*******************************************************************************/
int main() {
    BinarySearchTree* bst = new BinarySearchTree();
    string filename;
    string courseNumber;
    int choice = 0;

    cout << "Welcome to the ABCU Advising Program" << endl;
    cout << "----------------------------------" << endl;

    while (choice != 9) {
        displayMenu();

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input. Please enter a number (1-3 or 9).\n";
            continue;
        }

        switch (choice) {
        case 1:
            cout << "\nEnter filename (or full path): ";
            cin.ignore();
            getline(cin, filename);
            loadCourses(filename, bst);
            break;

        case 2:
            cout << "\nCourse List (Alphanumeric Order):" << endl;
            cout << "--------------------------------" << endl;
            bst->InOrder();
            break;

        case 3:
            cout << "\nEnter course number (e.g., CSCI101): ";
            cin.ignore();
            getline(cin, courseNumber);
            displayCourse(bst->Search(courseNumber), bst);
            break;

        case 9:
            cout << "\nThank you for using the ABCU Advising Program!\n" << endl;
            break;

        default:
            cout << "\nInvalid option. Please choose 1-3 or 9.\n";
            break;
        }
    }

    delete bst;
    return 0;
}