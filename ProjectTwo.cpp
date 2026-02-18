//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Matthew Marsh
// Version     : 2.0
// Description : ABCU Course Planner (Project Two) using a Binary Search Tree
//============================================================================
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// Use the standard namespace
using namespace std;

// Declare the course structure
struct Course {
	string courseNumber;
	string courseTitle;
	vector<string> prerequisites;
};

// Declare the internal structure for tree node
struct Node {
	Course course;
	Node* left;
	Node* right;

	// Default constructor for node
	Node() {
		left = nullptr;
		right = nullptr;
	}

	// Node initialized with a course
	Node(Course aCourse) :
		Node() {
		course = aCourse;
	}
};

// Declare the binary search tree class
class BinarySearchTree {
private:
	Node* root;
	void addNode(Node* node, Course course);
	void inOrder(Node* node);
	void postOrder(Node* node);
	void preOrder(Node* node);
	Node* removeNode(Node* node, string courseNumber);
	void destroyTree(Node* node);

public:
	BinarySearchTree();
	virtual ~BinarySearchTree();
	void insert(Course aCourse);
	void inOrder();
	void PostOrder();
	void PreOrder();
	void Remove(string courseNumber);
	Course Search(string courseNumber);
};

// Binary Search Tree method implementations
BinarySearchTree::BinarySearchTree() {
	this->root = nullptr;
}

// Destructor implementation to free memory
BinarySearchTree::~BinarySearchTree() {
	destroyTree(root);
	root = nullptr;
}

// Public traversal method implementations
void BinarySearchTree::inOrder() {
	inOrder(root);
}

// Public traversal method implementations
void BinarySearchTree::PostOrder() {
	postOrder(root);
}

// Public traveral method implementations
void BinarySearchTree::PreOrder() {
	preOrder(root);
}

// Insert method implementation

void BinarySearchTree::insert(Course aCourse) {

	// Initialize current node to root prior to traversal
	Node* currentNode = root;

	// If the root is empty, set the root to a new node with the passed course
	if (root == nullptr) {
		root = new Node(aCourse);
	}

    //Keep looping downwards until the bottom of the tree is reached
    while (currentNode != nullptr) {

        //If the passed course number is smaller than current node course number
        if (aCourse.courseNumber < currentNode->course.courseNumber) {

            //If the current node's left node is equal to null ptr
            if (currentNode->left == nullptr) {

                //Set the current node's left node to a new course node
                currentNode->left = new Node(aCourse);
                return;
            }

            else {

                //Traverse to the left node to continue searching
                currentNode = currentNode->left;
            }
        }
        else {

            //If the right node is empty
            if (currentNode->right == nullptr) {

                //Set the current node's right node to a new course node
                currentNode->right = new Node(aCourse);
                return;
            }

            else {

                //Traverse to the right node to continue searching
                currentNode = currentNode->right;
            }
        }
    }
}

//Remove method implementation (Not implemented in main program)
//Used for testing purposes only
void BinarySearchTree::Remove(string courseNumber) {

    //Set the parent node to null ptr and current node to root as housekeeping prior to traversal
    Node* parentNode = NULL;
    Node* currentNode = root;

    //While not at the bottom of the tree
    while (currentNode != nullptr) {

        //If the current node's courseNumber matches the passed courseNumber
        if (currentNode->course.courseNumber == courseNumber) {

            //Found the node to be deleted
            if (currentNode->left == NULL && currentNode->right == NULL) {

                //Node has no children
                if (parentNode == NULL) {

                    //Delete the root node
                    root = NULL;
                }

                //If the current node is the left child of the parent node
                else if (parentNode->left == currentNode) {

                    //Empty the left child of the parent node
                    parentNode->left = NULL;
                }

                else {

                    //Empty the right child of the parent node
                    parentNode->right = NULL;
                }
            }

            //If the current node has no left child
            else if (currentNode->left == NULL) {

                //If the current node is the root node
                if (parentNode == NULL) {

                    //Set the root to the right child of the current node
                    root = currentNode->right;
                }

                //If the current node is the left child of the parent node
                else if (parentNode->left == currentNode) {

                    //Set the left child of the parent node to the right child of the current node
                    parentNode->left = currentNode->right;
                }

                else {

                    //Set the right child of the parent node to the right child of the current node
                    parentNode->right = currentNode->right;
                }
            }

            //If the current node has no right child
            else if (currentNode->right == NULL) {

                //If the current node is the root node
                if (parentNode == NULL) {

                    //Set the root to the left child of the current node
                    root = currentNode->left;
                }

                //If the current node is the left child of the parent node
                else if (parentNode->left == currentNode) {

                    //Set the left child of the parent node to the left child of the current node
                    parentNode->left = currentNode->left;
                }

                else {

                    //Set the right child of the parent node to the left child of the current node
                    parentNode->right = currentNode->left;
                }
            }

            else {
                //Node has two children
                //Find the successor (smallest node on the right subtree)
                Node* successorNode = currentNode->right;

                //While the successor node has a left child
                while (successorNode->left != NULL) {

                    //Traverse to the left child
                    successorNode = successorNode->left;
                }

                //Copy the successor's course to the current node
                Course successorCourse = successorNode->course;
                //Delete the successor node
                Remove(successorCourse.courseNumber);
                //Assign the successor course to the current node
                currentNode->course = successorCourse;
            }

            //Node successfully deleted
            return;
        }

        //If the passed courseNumber is smaller than the current node's courseNumber
        else if (courseNumber < currentNode->course.courseNumber) {

            //Traverse to the left child
            parentNode = currentNode;
            currentNode = currentNode->left;
        }

        else {

            //Traverse to the right child
            parentNode = currentNode;
            currentNode = currentNode->right;
        }
    }

    //Node not found
    cout << "/n" << "Value not found." << endl;
    return;
}

Course BinarySearchTree::Search(string courseNumber) {

    //Initialize current node to root prior to traversal
    Node* currentNode = root;

    //Keep looping downwards until the bottom of the tree is reached
    while (currentNode != nullptr) {

        //If the current node's course number matches the passed course number
        if (currentNode->course.courseNumber == courseNumber) {

            //Return the found course
            return currentNode->course;
        }

        //If the passed course number is smaller than current node course number
        else if (courseNumber < currentNode->course.courseNumber) {

            //Traverse to the left node to continue searching
            currentNode = currentNode->left;
        }

        else {

            //Traverse to the right node to continue searching
            currentNode = currentNode->right;
        }
    }

    //Course not found, return empty course
    Course emptyCourse;
    return emptyCourse;
}

//Recursive function to add a node
void BinarySearchTree::addNode(Node* node, Course course) {

    //If the node is empty
    if (node == nullptr) {

        //Assign the node with the new course
        node = new Node(course);
    }

    //If the courseNumber is smaller than the passed node's courseNumber 
    if (course.courseNumber < node->course.courseNumber) {

        //If the node's left node is empty
        if (node->left == nullptr) {

            //Assign the left node with the new course
            node->left = new Node(course);
        }

        else {

            //Recursively add the course down the left side using the addNode function
            addNode(node->left, course);
        }
    }

    else {

        //If the right node is empty
        if (node->right == nullptr) {

            //Assign the right node with the new course
            node->right = new Node(course);
        }

        else {

            //Recursively add the course down the right side using the addNode function
            addNode(node->right, course);
        }
    }
}

//Recursive traversal functions implementations to go from lowest to highest
void BinarySearchTree::inOrder(Node* node) {

    //If the node is empty
    if (node == nullptr) {

        return;
    }

    //Use inOrder to traverse left
    inOrder(node->left);

    //Output courseNumber, courseTitle
    cout << node->course.courseNumber << ", " << node->course.courseTitle << endl;

    //Use inOrder to traverse right
    inOrder(node->right);
}

//Recursive traversal functions implementations (Not used in main program)
void BinarySearchTree::postOrder(Node* node) {

    //If the node is empty
    if (node == nullptr) {

        return;
    }

    //Use postOrder to traverse left
    postOrder(node->left);

    //Use postOrder to traverse right
    postOrder(node->right);

    //Output courseNumber, courseTitle
    cout << node->course.courseNumber << ", " << node->course.courseTitle << endl;
}

//Recursive traversal functions implementations (Not used in main program)
void BinarySearchTree::preOrder(Node* node) {

    //If the node is empty
    if (node == nullptr) {

        return;
    }

    //Output courseNumber, courseTitle
    cout << node->course.courseNumber << ", " << node->course.courseTitle << endl;

    //Use preOrder to traverse left
    preOrder(node->left);

    //Use preOrder to traverse right
    preOrder(node->right);
}

//Recursive remove node function implementation (Not used in main program)
Node* BinarySearchTree::removeNode(Node* node, string courseNumber) {

    //If node = nullptr return node
    if (node == nullptr) {

        return node;
    }

    //If the passed courseNumber is smaller than the current node's courseNumber
    if (courseNumber < node->course.courseNumber) {

        //Check for match and if so, remove left node using recursive call 
        node->left = removeNode(node->left, courseNumber);
    }

    //If the passed courseNumber is larger than the current node's courseNumber
    else if (courseNumber > node->course.courseNumber) {

        //Check for match and if so, remove right node using recursive call
        node->right = removeNode(node->right, courseNumber);
    }

    else {

        //If match found proceed to remove node
        if (node->left == nullptr && node->right == nullptr) {

            //Node has no children so delete node
            delete node;
            node = nullptr;
        }

        //If the left node has a child but the right node does not
        else if (node->left != nullptr && node->right == nullptr) {

            //Delete node and make left node the new node
            Node* temp = node;
            node = node->left;
            delete temp;
        }

        //If the right node has a child but the left node does not
        else if (node->left == nullptr && node->right != nullptr) {

            //Delete node and make right node the new node
            Node* temp = node;
            node = node->right;
            delete temp;
        }

        //If the node has two children
        else {

            //Create temp node to right
            Node* temp = node->right;

            //While left node is not empty keep moving temp left
            while (temp->left != nullptr) {

                temp = temp->left;
            }

            //Make the node's course (right) equal to temp course (left)
            node->course = temp->course;

            //Remove the right node using recursive call
            node->right = removeNode(node->right, temp->course.courseNumber);
        }
    }
}

//Recursive destroy tree function implementation
void BinarySearchTree::destroyTree(Node* node) {

    //If the node is not empty
    if (node != nullptr) {

        //Recursively destroy left and right subtrees
        destroyTree(node->left);
        destroyTree(node->right);

        //Delete the current node
        delete node;
    }
}

//Convert string to uppercase for consistent searching
void convertCase(string& toConvert) {

    //Loop through each character in the string
    for (unsigned int i = 0; i < toConvert.length(); i++) {

        //If the character is an alphabetic character
        if (isalpha(toConvert[i])) {

            //Convert the character to uppercase
            toConvert[i] = toupper(toConvert[i]);
        }
    }
}

//Tokenizes a line based on the comma delimiter into a vector of strings
vector<string> Tokens(string lineFeed) {

    //Define the delimiter as a comma
    char delim = ',';

    //Includes a delimiter at the end so last word is also read
    lineFeed += delim;

    //Initialize variables
    vector<string> lineTokens;
    string temp = "";

    //Loop through each character in the line
    for (int i = 0; i < lineFeed.length(); i++) {

        //If the character is the delimiter
        if (lineFeed[i] == delim) {

            //Store the current token, reset temp and increment i to next character
            lineTokens.push_back(temp);
            temp = "";
            i++;
        }

        //Else keep adding characters to the current token
        temp += lineFeed[i];
    }

    //Return the vector of tokens
    return lineTokens;
}

//Creates the data structure and adds to the collection of courses
void loadCourses(string csvPath, BinarySearchTree* courseList) {

    //ifstream to read file & initialize variables
    ifstream inFS;
    string line;
    vector<string> stringTokens;

    //Open the read file
    inFS.open(csvPath);

    //When the file can not open using the provided csvPath, prompt user for correct file path
    //Meant for both initial load and any re-attempts
    while (!inFS.is_open()) {

        cout << "Could not open file. Please check inputs and press ENTER to try again." << endl;
        //Clears the input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Please enter the csv path to the course file: " << endl;
        //Gets the full line including spaces
        getline(cin, csvPath);

        //Try to open the file again
        inFS.open(csvPath);
    }

    //Read the file line by line until the end of the file
    while (!inFS.eof()) {

        //Create a new struct for each line of the file
        Course course;

        //Gets the full line including spaces
        getline(inFS, line);

        //Split the line into tokens via the comma
        stringTokens = Tokens(line);

        //If there aren't at least 2 tokens, the line is misformatted and skipped
        if (stringTokens.size() < 2) {

            cout << "\nFormat Error! Please verify the format of the csv file. Skipping line." << endl;
            break;
        }

        //Else populate the course struct with the tokens
        else {

            //Assign the first two tokens to courseNumber and courseTitle
            course.courseNumber = stringTokens.at(0);
            course.courseTitle = stringTokens.at(1);

            //Any remaining tokens are prerequisites
            for (unsigned int i = 2; i < stringTokens.size(); i++) {

                course.prerequisites.push_back(stringTokens.at(i));
            }

            //Push this course to the end of the course list
            courseList->insert(course);
        }
    }

    //Close the file
    inFS.close();
}

//Displays the course information
void displayCourse(Course course) {

    //Output course number and title followed by prerequisites preface
    cout << course.courseNumber << ", " << course.courseTitle << endl;
    cout << "Prerequisites: ";

    //Check if there are any prerequisites and output none if empty
    if (course.prerequisites.empty()) {

        cout << "none" << endl;
    }

    //Else output all prerequisites
    else {

        //Loop through each prerequisite
        for (unsigned int i = 0; i < course.prerequisites.size(); i++) {

            //Output the prerequisite
            cout << course.prerequisites.at(i);

            //If there are multiple prerequisites, put a comma between them
            if (course.prerequisites.size() > 1 && i < course.prerequisites.size() - 1) {

                cout << ", ";
            }
        }
    }

    //Output a new line at the end
    cout << endl;
}

//Waits for user to press enter before continuing
void wait_for_enter() {
    cout << "Press ENTER to continue..." << endl;

    // Wait for a new line character (Enter key press)
    cin.get();

}

//Main program execution starts here
int main(int argc, char* argv[]) {

    //Process command line arguments
    string csvPath, courseSearchKey;

    //Initialize all the variables
    Course course;
    bool valid;
    int choice = 0;

    //Process command line arguments to get csvPath and optional courseSearchKey
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    case 3:
        csvPath = argv[1];
        courseSearchKey = argv[2];
        break;
    default:
        //Assigns the default file if not provided or found from user input
        csvPath = "CS 300 ABCU_Advising_Program_Input.csv";
    }

    //Initialize the binary search tree
    BinarySearchTree* courseList = new BinarySearchTree();

    cout << "Welcome to the course planner!" << endl;

    //Main menu loop to continue until user exits
    while (choice != 9) {

        //Display the menu options
        cout << "Menu:" << endl;
        cout << "  1. Load Courses" << endl;
        cout << "  2. Display All Courses" << endl;
        cout << "  3. Find Course" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";

        //Reset variables for each loop
        courseSearchKey = "";
        string anyKey = " ";
        choice = 0;

        //Input validation and menu selection
        try {

            //Get user menu choice
            cin >> choice;

            // If user entered something invalid (like a letter)
            if (cin.fail()) {

                //Clear fail state
                cin.clear();

                //Discard the bad input
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                //Output invalid input message
                cout << "Invalid input. Please enter a number from the menu." << endl;

                //Waits for user to press enter before continuing
                wait_for_enter();

                //Clears the cin operator of extra input or any errors generated by bad input, e.g., 'a'
                cin.ignore();

                //Clears the console to redraw a fresh menu after each operation is completed by the user
                system("cls");

                //Restart the menu loop
                continue;
            }

            //Validate numeric input
            if (!((choice > 0 && choice < 4) || choice == 9)) {

                //Output invalid choice message
                cout << choice << " is not a valid option. Please select one of the available options." << endl;

                //Waits for user to press enter before continuing
                wait_for_enter();

                //Clears the cin operator of extra input or any errors generated by bad input, e.g., 'a'
                cin.ignore();

                //Clears the console to redraw a fresh menu after each operation is completed by the user
                system("cls");

                //Restart the menu loop
                continue;
            }

            //Process the valid menu choice
            switch (choice) {
                //Load Courses based on user provided csvPath
            case 1:

                //Clears the input buffer
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                //Prompts user for csvPath then gets full line including spaces
                cout << "Please enter the csv path to the course file: " << endl;
                getline(cin, csvPath);

                //Complete the method call to load the courses
                loadCourses(csvPath, courseList);
                cout << "Courses loaded." << endl;

                //Waits for user to press enter before continuing
                wait_for_enter();

                //Exit case
                break;

                //Display all courses in order
            case 2:

                //Output preface message
                cout << "Here is a sample schedule:" << endl;

                //Call the inOrder traversal method to display all courses
                courseList->inOrder();

                //Waits for user to press enter before continuing
                wait_for_enter();

                //Exit case
                break;

                //Find a specific course based on user input
            case 3:

                //Prompt user for course to search
                cout << "\nWhat course would you like to search for? " << endl;
                cin >> courseSearchKey;

                //Converts the case of the user input for consistent searching
                convertCase(courseSearchKey);

                //Search for the course in the binary search tree
                course = courseList->Search(courseSearchKey);

                //If the course number is not empty, display the course information
                if (!course.courseNumber.empty()) {
                    displayCourse(course);
                }

                //Else output not found message
                else {
                    cout << "\nCourse ID " << courseSearchKey << " not found." << endl;
                }

                //Waits for user to press enter before continuing
                wait_for_enter();

                //Exit case
                break;

                //Exit the program
            case 9:

                //Exit case
                break;

                //Validation catch for invalid menu choice
            default:

                //Should not reach here due to prior validation, but just in case
                throw 2;
            }
        }

        //Validation
        catch (int err) {

            //Output invalid choice message
            cout << choice << " is not a valid option. Please select one of the available options." << endl;

            //Waits for user to press enter before continuing
            wait_for_enter();
        }

        //Clears the cin operator of extra input or any errors generated by bad input, e.g., 'a'
        cin.ignore();

        //Clears the console to redraw a fresh menu after each operation is completed by the user
        system("cls");
    }

    //Output exit message
    cout << "Thank you for using the course planner!" << endl;

    //Free the memory used by the binary search tree
    return 0;
}