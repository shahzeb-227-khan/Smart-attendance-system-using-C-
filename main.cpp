#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <iomanip>
using namespace std;

class link {
private:
    int b, x, i, choice, n, a;
    char cont;

    struct node {
        int data;
        string name;
        string email;
        string home;
        string off;
        string tell;
        string cell;
        string sec;
        string gender;
        struct node* link;
    } *head, * temp, * temp1, * temp2;

    struct Attendance {
        int studentId;
        bool isPresent; // true for present, false for absent
        Attendance* next;
    } *attendanceHead;

    struct Queue {
        node* records[100];
        int front, rear;

        Queue() : front(0), rear(0) {}

        void enqueue(node* record) {
            if (rear < 100) {
                records[rear++] = record; // Add record to the queue
            }
        }

        node* dequeue() {
            if (front < rear) {
                return records[front++];
            }
            return NULL;
        }

        bool isEmpty() {
            return front == rear;
        }
    };

    Queue attendanceQueue;

public:
    link() : head(NULL), attendanceHead(NULL) {}

    void typewriter(const string& text, int delay = 50) {
        for (char c : text) {
            cout << c;
            cout.flush();
            Sleep(delay);
        }
    }

    void start() {
        system("cls");
        Sleep(800);

        // Set text color to light aqua on a black background
        system("color 0b");

        // Title with typewriter effect
        gotoxy(35, 8);
        typewriter("==========================================", 30);
        gotoxy(35, 9);
        typewriter("||                                      ||", 30);
        gotoxy(35, 10);
        typewriter("||     SMART STUDENT RECORD MANAGEMENT  ||", 30);
        gotoxy(35, 11);
        typewriter("||                 SYSTEM               ||", 30);
        gotoxy(35, 12);
        typewriter("||                                      ||", 30);
        gotoxy(35, 13);
        typewriter("==========================================", 30);

        // Animated welcome message
        gotoxy(35, 15);
        typewriter("   \tWELCOME TO THE SYSTEM!", 50);

        Sleep(600); // Pause for effect

        // Loading bar animation
        gotoxy(35, 18);
        paint(10); // Set text color to green
        cout << "Loading: ";
        Sleep(500);

        gotoxy(40, 20);
        paint(14); // Set text color to yellow
        cout << "[";
        for (int i = 0; i < 35; ++i) {
            cout << "\xDB"; // Block character for loading bar
            Sleep(100);     // Speed of animation
        }
        cout << "]";

        Sleep(500); // Pause after loading bar completes

        // Transition effect and proceed to the main menu
        effect();    // Optional custom effect function
        main_menu(); // Navigate to the main menu
    }


    void printByClassAndSection() {
        effect(); // Assuming it's a screen effect
        system("cls");

        paint(11); // Light cyan for border
        cout << "\n\t\t===============================================\n";
        cout << "\t\t||     Display Records by Class & Section    ||\n";
        cout << "\t\t===============================================\n";

        string className, section;
        char sectionFilter;

        paint(14); // Yellow for input prompts
        cout << "\n\tEnter the class to display records for: ";
        paint(15); // White for user input
        cin >> className;

        paint(14);
        cout << "\n\tWould you like to filter by section? (y/n): ";
        paint(15);
        cin >> sectionFilter;

        if (sectionFilter == 'y' || sectionFilter == 'Y') {
            paint(14);
            cout << "\n\tEnter the section to display records for: ";
            paint(15);
            cin >> section;
        }

        bool found = false;
        temp1 = head;

        while (temp1 != NULL) {
            if (temp1->off == className) {
                if ((sectionFilter == 'y' || sectionFilter == 'Y') && temp1->sec != section) {
                    temp1 = temp1->link;
                    continue;
                }

                // Display student record
                paint(10); // Green for record found header
                cout << "\n\t-----------------------------------------------";
                paint(14); // Yellow for field labels
                cout << "\n\t# ID: ";
                paint(15); // White for values
                cout << temp1->data;

                paint(14);
                cout << "\n\t# Name: ";
                paint(15);
                cout << temp1->name;

                paint(14);
                cout << "\n\t# Class: ";
                paint(15);
                cout << temp1->off;

                paint(14);
                cout << "\n\t# Section: ";
                paint(15);
                cout << temp1->sec;

                paint(14);
                cout << "\n\t# Gender: ";
                paint(15);
                cout << temp1->gender;

                paint(14);
                cout << "\n\t# Telephone Number: ";
                paint(15);
                cout << temp1->tell;

                paint(14);
                cout << "\n\t# Cell-Phone Number: ";
                paint(15);
                cout << temp1->cell;

                paint(14);
                cout << "\n\t# Email Address: ";
                paint(15);
                cout << temp1->email;

                paint(14);
                cout << "\n\t# Home Address: ";
                paint(15);
                cout << temp1->home << endl;

                found = true;
            }
            temp1 = temp1->link;
        }

        if (!found) {
            paint(12); // Red for no records message
            cout << "\n\tNo records found for the specified class and section.\n";
        }

        paint(14); // Yellow for prompt
        cout << "\n\tPress any key to return to the main menu...";
        _getch();
        main_menu();
    }


    void markAttendance() {
        effect(); // Optional: Assuming this creates a visual effect
        system("cls");

        paint(11); // Light cyan for border
        cout << "\n\t\t===============================================\n";
        cout << "\t\t||             Mark Attendance                ||\n";
        cout << "\t\t===============================================\n";

        int studentId;
        string studentName;

        // Input prompts
        paint(14); // Yellow for prompts
        cout << "\n\tEnter Student ID: ";
        paint(15); // White for user input
        cin >> studentId;

        paint(14);
        cout << "\n\tEnter Student Name: ";
        paint(15);
        cin.ignore(); // Clear the newline character from the input buffer
        getline(cin, studentName);

        // Search for the student
        temp1 = head;
        bool found = false;

        while (temp1 != NULL) {
            if (temp1->data == studentId && temp1->name == studentName) {
                // Mark attendance
                Attendance* newAttendance = new Attendance;
                newAttendance->studentId = studentId;
                newAttendance->isPresent = true; // Mark as present
                newAttendance->next = attendanceHead; // Add to the front of the list
                attendanceHead = newAttendance;

                paint(10); // Green for success message
                cout << "\n\tAttendance of student ID: " << studentId << " marked successfully!\n";
                found = true;
                break;
            }
            temp1 = temp1->link; // Move to the next student
        }

        // If student not found
        if (!found) {
            paint(12); // Red for error message
            cout << "\n\tError: Student ID or Name not found!\n";
        }

        // Return to main menu
        paint(14); // Yellow for prompt
        cout << "\n\tPress any key to return to the main menu...";
        _getch();
        main_menu();
    }


    void viewAttendance() {
        system("cls");

        // Display Header
        paint(11); // Light cyan for border
        cout << "\n\t\t\t\t===============================================\n";
        cout << "\t\t\t\t||           ATTENDANCE RECORDS              ||\n";
        cout << "\t\t\t\t===============================================\n";

        paint(15);
        cout << string(60, '-') << endl;

        // Check if student records are available
        if (head == NULL) {
            paint(12); // Red for warning or error message
            cout << "No student records found.\n";
            paint(15); // Reset to default color
            cout << "Press any key to return to the main menu...";
            _getch();
            main_menu();
            return;
        }

        // Count total students
        int count = 0;
        temp1 = head;
        while (temp1 != NULL) {
            count++;
            temp1 = temp1->link;
        }

        // Create an array to hold pointers to student nodes
        node** studentArray = new node * [count];
        temp1 = head;
        for (int i = 0; i < count; i++) {
            studentArray[i] = temp1;
            temp1 = temp1->link;
        }

        // Sort students by ID using bubble sort
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (studentArray[j]->data > studentArray[j + 1]->data) {
                    // Swap pointers
                    node* temp = studentArray[j];
                    studentArray[j] = studentArray[j + 1];
                    studentArray[j + 1] = temp;
                }
            }
        }

        // Print Table Header
        cout << left << setw(15) << "Student ID"
            << left << setw(30) << "Name"
            << left << setw(15) << "Status" << endl;
        cout << string(60, '-') << endl;

        // Display sorted attendance records
        for (int i = 0; i < count; i++) {
            // Find the attendance status
            Attendance* tempAttendance = attendanceHead;
            bool isPresent = false;

            while (tempAttendance != NULL) {
                if (tempAttendance->studentId == studentArray[i]->data) {
                    isPresent = tempAttendance->isPresent;
                    break;
                }
                tempAttendance = tempAttendance->next;
            }

            // Display record with color-coded attendance
            cout << left << setw(15) << studentArray[i]->data
                << left << setw(30) << studentArray[i]->name;

            // Apply color coding for "Present" and "Absent"
            if (isPresent) {
                paint(10); // Green for "Present"
                cout << left << setw(15) << "Present";
            }
            else {
                paint(12); // Red for "Absent"
                cout << left << setw(15) << "Absent";
            }
            paint(15); // Reset to default color
            cout << endl;
        }

        // Cleanup dynamically allocated memory
        delete[] studentArray;

        // Prompt user to return to the main menu
        cout << "\nPress any key to return to the main menu...";
        _getch();
        main_menu();
    }


    void paint(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    void setCursorPosition(int x, int y) {
        COORD position;
        position.X = x;
        position.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
    }

    void main_menu() {
        int choice = 0;
        char key;

        do {
            system("cls");
            int Set[10] = { 7, 7, 7, 7, 7, 7, 7, 7, 7, 7 }; // Default color for all menu options
            int counter = 0;

            do {
                system("cls");

                paint(11); // Light cyan for border
                cout << "\n\n\t\t\t\t\t\t===============================================\n";
                cout << "\t\t\t\t\t\t||                                           ||\n";
                paint(14); // Yellow for the title
                cout << "\t\t\t\t\t\t||   SMART STUDENT RECORD MANAGEMENT         ||\n";
                cout << "\t\t\t\t\t\t||                  SYSTEM                   ||\n";
                paint(11);
                cout << "\t\t\t\t\t\t||                                           ||\n";
                cout << "\t\t\t\t\t\t===============================================\n";

                // Reset all colors for menu options
                for (int i = 0; i < 10; i++) Set[i] = 7; // Default text color
                Set[counter] = 12; // Highlight the current option (red)

                // Menu options
                setCursorPosition(50, 10); paint(Set[0]);
                cout << "1. Add Student Record";
                setCursorPosition(50, 11); paint(Set[1]);
                cout << "2. Delete Specific Record";
                setCursorPosition(50, 12); paint(Set[2]);
                cout << "3. Delete All Records";
                setCursorPosition(50, 13); paint(Set[3]);
                cout << "4. Find A Record";
                setCursorPosition(50, 14); paint(Set[4]);
                cout << "5. Display All Student Records";
                setCursorPosition(50, 15); paint(Set[5]);
                cout << "6. Display Records by Class/Section";
                setCursorPosition(50, 16); paint(Set[6]);
                cout << "7. Mark Attendance";
                setCursorPosition(50, 17); paint(Set[7]);
                cout << "8. View Attendance Records";
                setCursorPosition(50, 18); paint(Set[8]);
                cout << "9. Submitted To";
                setCursorPosition(50, 19); paint(Set[9]);
                cout << "10. Exit";

                // Footer with creator names
                cout << "\n\n\t\t\t\t\t\t===============================================\n";
                cout << "\t\t\t\t\t\t||               Created by:                 ||\n";
                cout << "\t\t\t\t\t\t||         Enayat, Shahzaib & Muneeb         ||\n";
                cout << "\t\t\t\t\t\t||                                           ||\n";
                cout << "\t\t\t\t\t\t||               Version: 1.0                ||\n";
                cout << "\t\t\t\t\t\t===============================================\n";

                // Handle key input for navigation
                key = _getch();

                if (key == 72) { // Up arrow key
                    counter--;
                    if (counter < 0) counter = 9; // Wrap to the last option
                }
                else if (key == 80) { // Down arrow key
                    counter++;
                    if (counter > 9) counter = 0; // Wrap to the first option
                }
                else if (key == '\r') { // Enter key
                    choice = counter + 1;
                    break;
                }
            } while (true);

            system("cls");

            // Perform action based on choice
            switch (choice) {
            case 1:
                insert();
                break;
            case 2:
                del_specify();
                break;
            case 3:
                del();
                break;
            case 4:
                search();
                break;
            case 5:
                print();
                break;
            case 6:
                printByClassAndSection();
                break;
            case 7:
                markAttendance();
                break;
            case 8:
                viewAttendance();
                break;
            case 9:
                About_Dev();
                break;
            case 10:
                cout << "Thanks for using this software";
                exit(0);
            default:
                cout << "\nInvalid Key Pressed.................";
            }

            cout << "\n\n*Press ENTER KEY To <continue>";
            cout << "\n*Press ESC KEY To <exit>";
            char x = _getch();
            if (x == 27) { // ESC key
                exit(0);
            }
        } while (true);
    }

    void About_Dev() {
        effect();
        system("cls");

        // Title
        paint(14); // Yellow for border
        gotoxy(45, 3);
        cout << "\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\ SUBMITTED TO \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n";

        Sleep(1000); // Add suspense effect

        // Developer Details
        paint(13); // Light magenta for labels
        cout << "\n\nName: ";
        paint(15); // White for values
        cout << "Nasar Kamal";

        Sleep(1000); // Delayed display for dramatic effect
        paint(13);
        cout << "\n\nPlatform: ";
        paint(15);
        cout << "Visual Studio OR DEV-C++";

        Sleep(1000); // Another suspense delay
        paint(13);
        cout << "\n\nLanguage: ";
        paint(15);
        cout << "C++";

        // Prompt to Return
        paint(10); // Green for the return prompt
        cout << "\n\nPress ENTER to return to the main menu...";

        // Wait for Enter key (ASCII 13)
        while (_getch() != 13);

        main_menu(); // Return to the main menu
    }


    struct bstNode {
        int id;
        string name, off, sec, gender, tell, cell, email, home;
        bstNode* left;
        bstNode* right;

        bstNode(int id, string name, string off, string sec, string gender, string tell, string cell, string email, string home) {
            this->id = id;
            this->name = name;
            this->off = off;
            this->sec = sec;
            this->gender = gender;
            this->tell = tell;
            this->cell = cell;
            this->email = email;
            this->home = home;
            left = right = NULL;
        }
    };

    bstNode* bstRoot = NULL;

    bstNode* bstInsert(bstNode* root, bstNode* newNode) {
        if (root == NULL) {
            return newNode; // New node becomes the root
        }

        if (newNode->id < root->id) {
            root->left = bstInsert(root->left, newNode); // Insert in the left subtree
        }
        else if (newNode->id > root->id) {
            root->right = bstInsert(root->right, newNode); // Insert in the right subtree
        }
        return root;
    }

    bstNode* bstDelete(bstNode* root, int id) {
        if (root == NULL) return root;

        if (id < root->id) {
            root->left = bstDelete(root->left, id);
        }
        else if (id > root->id) {
            root->right = bstDelete(root->right, id);
        }
        else {
            if (root->left == NULL) {
                bstNode* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == NULL) {
                bstNode* temp = root->left;
                delete root;
                return temp;
            }

            bstNode* temp = root->right;
            while (temp && temp->left != NULL) {
                temp = temp->left;
            }
            root->id = temp->id;
            root->name = temp->name;
            root->off = temp->off;
            root->sec = temp->sec;
            root->gender = temp->gender;
            root->tell = temp->tell;
            root->cell = temp->cell;
            root->email = temp->email;
            root->home = temp->home;
            root->right = bstDelete(root->right, temp->id);
        }
        return root;
    }

    void search() {
        effect(); // Presumably a screen effect
        system("cls");

        paint(11); // Light cyan for border
        cout << "\n\t\t===============================================\n";
        cout << "\t\t||               Search Record                ||\n";
        cout << "\t\t===============================================\n";

        if (bstRoot == NULL) {
            paint(12); // Red for error message
            cout << "\n\tNo records available to search!";
            paint(15); // White for normal text
            cout << "\n\tPress any key to return to the main menu...";
            _getch();
            main_menu();
            return;
        }

        paint(14); // Yellow for input prompt
        cout << "\n\tEnter the ID you want to search: ";
        paint(15); // White for user input
        cin >> a;
        fflush(stdin);

        bstNode* current = bstRoot;
        bool found = false; // Flag to check if record is found
        while (current != NULL) {
            if (current->id == a) {
                paint(10); // Green for success
                cout << "\n\tEntry Found:";
                paint(14); // Yellow for field labels
                cout << "\n\t# ID: ";
                paint(15); // White for values
                cout << current->id;

                paint(14);
                cout << "\n\t# Name: ";
                paint(15);
                cout << current->name;

                paint(14);
                cout << "\n\t# Class: ";
                paint(15);
                cout << current->off;

                paint(14);
                cout << "\n\t# Section: ";
                paint(15);
                cout << current->sec;

                paint(14);
                cout << "\n\t# Gender: ";
                paint(15);
                cout << current->gender;

                paint(14);
                cout << "\n\t# Telephone Number: ";
                paint(15);
                cout << current->tell;

                paint(14);
                cout << "\n\t# Cell-Phone Number: ";
                paint(15);
                cout << current->cell;

                paint(14);
                cout << "\n\t# Email Address: ";
                paint(15);
                cout << current->email;

                paint(14);
                cout << "\n\t# Home Address: ";
                paint(15);
                cout << current->home << endl;

                found = true;
                break;
            }
            else if (a < current->id) {
                current = current->left; // Search in the left subtree
            }
            else {
                current = current->right; // Search in the right subtree
            }
        }

        if (!found) {
            paint(12); // Red for error
            cout << "\n\tRecord Not Found!";
        }

        paint(14); // Yellow for input prompt
        cout << "\n\tDo You Want To Search Another Record? (y / n): ";
        paint(15); // White for user input
        cont = _getch();

        if (cont == 'y' || cont == 'Y') {
            system("cls");
            search();
        }

        Sleep(1000);
        main_menu();
    }


    void insert() {
        effect(); // Assuming this creates a startup effect for the screen.
        system("cls");

        // Header with a stylish border
        paint(11); // Light cyan for border
        cout << "\n\t\t\t\t===============================================\n";
        cout << "\t\t\t\t||           Add Student Record              ||\n";
        cout << "\t\t\t\t===============================================\n";

        char get1[100], get2[100], get3[100], get4[100], get5[100], get6[100], get7[100], get8[100];

        // Check if the list is empty
        if (head == NULL) {
            head = new struct node;
            i = 1; // Initialize ID correctly for the first record
            head->data = i; // Assign ID to the node

            // Show Student ID (pre-assigned)
            paint(14); // Yellow for prompts
            cout << "\n\t# Student ID: ";
            paint(15); // White for user input
            cout << i;

            // Collect Student Details
            cin.ignore(); // Ensure input buffer is clear
            paint(14);
            cout << "\n\t# Name: ";
            paint(15);
            cin.getline(get1, 100);
            head->name = get1;

            paint(14);
            cout << "\t# Class: ";
            paint(15);
            cin.getline(get6, 100);
            head->off = get6;

            paint(14);
            cout << "\t# Section: ";
            paint(15);
            cin.getline(get7, 100);
            head->sec = get7;

            paint(14);
            cout << "\t# Gender: ";
            paint(15);
            cin.getline(get8, 100);
            head->gender = get8;

            paint(14);
            cout << "\t# Telephone Number: ";
            paint(15);
            cin.getline(get2, 100);
            head->tell = get2;

            paint(14);
            cout << "\t# Cell-Phone Number: ";
            paint(15);
            cin.getline(get3, 100);
            head->cell = get3;

            paint(14);
            cout << "\t# Email Address: ";
            paint(15);
            cin.getline(get4, 100);
            head->email = get4;

            paint(14);
            cout << "\t# Home Address: ";
            paint(15);
            cin.getline(get5, 100);
            head->home = get5;

            head->link = NULL;

            // Add record to BST
            bstNode* newNode = new bstNode(i, head->name, head->off, head->sec, head->gender, head->tell, head->cell, head->email, head->home);
            bstRoot = bstInsert(bstRoot, newNode);

            attendanceQueue.enqueue(head); // Add to queue

            paint(10); // Green for success message
            cout << "\n\tYour Record Has Been Successfully Inserted!\n";
        }
        else {
            temp = head;
            head = new struct node;
            i++; // Increment ID for each new record
            head->data = i; // Assign ID to the node

            // Show Student ID
            paint(14);
            cout << "\n\t# Student ID: ";
            paint(15);
            cout << i;

            // Collect Student Details (similar to above)
            cin.ignore(); // Ensure input buffer is clear
            paint(14);
            cout << "\n\t# Name: ";
            paint(15);
            cin.getline(get1, 100);
            head->name = get1;

            paint(14);
            cout << "\t# Class: ";
            paint(15);
            cin.getline(get6, 100);
            head->off = get6;

            paint(14);
            cout << "\t# Section: ";
            paint(15);
            cin.getline(get7, 100);
            head->sec = get7;

            paint(14);
            cout << "\t# Gender: ";
            paint(15);
            cin.getline(get8, 100);
            head->gender = get8;

            paint(14);
            cout << "\t# Telephone Number: ";
            paint(15);
            cin.getline(get2, 100);
            head->tell = get2;

            paint(14);
            cout << "\t# Cell-Phone Number: ";
            paint(15);
            cin.getline(get3, 100);
            head->cell = get3;

            paint(14);
            cout << "\t# Email Address: ";
            paint(15);
            cin.getline(get4, 100);
            head->email = get4;

            paint(14);
            cout << "\t# Home Address: ";
            paint(15);
            cin.getline(get5, 100);
            head->home = get5;

            head->link = temp;

            // Add record to BST
            bstNode* newNode = new bstNode(i, head->name, head->off, head->sec, head->gender, head->tell, head->cell, head->email, head->home);
            bstRoot = bstInsert(bstRoot, newNode);

            attendanceQueue.enqueue(head); // Add to queue

            paint(10); // Green for success message
            cout << "\n\tYour Record Has Been Successfully Inserted!\n";
        }

        // Option to add another record
        paint(14); // Yellow for prompt
        cout << "\n\tDo You Want to Add Another Record? (y/n): ";
        paint(15); // White for user input
        cont = _getch();

        if (cont == 'y' || cont == 'Y') {
            system("cls");
            insert();
        }

        Sleep(1000);
        main_menu();
    }


    void print() {
        if (head == NULL) {
            paint(12); // Red for error
            cout << "\n\n\t===============================================\n";
            cout << "\t||           No Records Found!              ||\n";
            cout << "\t===============================================\n";
            paint(14); // Yellow for prompt
            cout << "\n\tPress any key to return to the main menu...";
            _getch();
            main_menu();
            return;
        }

        temp1 = head;
        paint(11); // Light cyan for header
        cout << "\n\n\t===============================================\n";
        cout << "\t||           Student Records                 ||\n";
        cout << "\t===============================================\n";

        while (temp1 != NULL) {
            paint(13); // Light magenta for borders
            cout << "\n\t-----------------------------------------------\n";
            paint(14); // Yellow for labels
            cout << "\t# ID: ";
            paint(15); // White for values
            cout << temp1->data;

            paint(14);
            cout << "\n\t# Name: ";
            paint(15);
            cout << temp1->name;

            paint(14);
            cout << "\n\t# Class: ";
            paint(15);
            cout << temp1->off;

            paint(14);
            cout << "\n\t# Section: ";
            paint(15);
            cout << temp1->sec;

            paint(14);
            cout << "\n\t# Gender: ";
            paint(15);
            cout << temp1->gender;

            paint(14);
            cout << "\n\t# Telephone Number: ";
            paint(15);
            cout << temp1->tell;

            paint(14);
            cout << "\n\t# Cell-Phone Number: ";
            paint(15);
            cout << temp1->cell;

            paint(14);
            cout << "\n\t# Email Address: ";
            paint(15);
            cout << temp1->email;

            paint(14);
            cout << "\n\t# Home Address: ";
            paint(15);
            cout << temp1->home;

            temp1 = temp1->link; // Move to the next record
        }

        paint(13); // Light magenta for closing border
        cout << "\n\t-----------------------------------------------\n";

        paint(10); // Green for prompt
        cout << "\n\tPress any key to return to the main menu...";
        _getch();
        main_menu();
    }


    void del_specify() {
        effect();
        system("cls");

        paint(11); // Light cyan for border
        cout << "\n\t\t===============================================\n";
        cout << "\t\t||           Delete Specific Record           ||\n";
        cout << "\t\t===============================================\n";

        paint(14); // Yellow for prompt
        cout << "\n\tEnter ID for which you want to delete the record: ";
        paint(15); // White for user input
        cin >> b;

        temp1 = head;
        temp2 = NULL; // Initialize temp2 to keep track of the previous node
        bool found = false;

        while (temp1 != NULL) {
            if (temp1->data == b) {
                if (temp1 == head) {
                    head = head->link; // Update head if the first record is deleted
                }
                else {
                    temp2->link = temp1->link; // Bypass the deleted node
                }
                delete temp1; // Delete the node
                bstRoot = bstDelete(bstRoot, b); // Remove from BST

                paint(10); // Green for success message
                cout << "\n\tYour Record Has Been Deleted Successfully!\n";
                found = true;
                break;
            }
            else {
                temp2 = temp1; // Move temp2 to current node
                temp1 = temp1->link; // Move to the next node
            }
        }

        if (!found) {
            paint(12); // Red for error message
            cout << "\n\tError: Record Not Found!\n";
        }

        paint(14); // Yellow for prompt
        cout << "\n\tPress any key to return to the main menu...";
        _getch(); // Wait for a key press
        main_menu(); // Return to the main menu
    }


    void del() {
        effect();
        system("cls");

        paint(11); // Light cyan for border
        cout << "\n\t\t===============================================\n";
        cout << "\t\t||              Delete All Records            ||\n";
        cout << "\t\t===============================================\n";

        temp1 = head;
        while (temp1 != NULL) {
            temp2 = temp1;
            temp1 = temp1->link;
            delete temp2; // Free memory of each node
        }
        head = NULL;

        paint(10); // Green for success message
        cout << "\n\tAll Records Have Been Deleted Successfully!\n";

        paint(14); // Yellow for prompt
        cout << "\n\tPress any key to return to the main menu...";
        _getch(); // Wait for a key press
        main_menu(); // Return to the main menu
    }


    void effect() {
        for (int i = 0; i < 3; i++) {
            cout << " . ";
            Sleep(500);
        }
    }

    void gotoxy(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
};

int main() {
    link l;
    l.start();
    return 0;
}