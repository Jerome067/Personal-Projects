#include <iostream>
#include <string>
#include <cctype>
#include <map>
#include <ctime>
#include <iomanip>
#include <vector>
#include <limits>

using namespace std;

struct userDate {
    int day;
    int month;
    int year;
};

struct userPlans {
    int status;
    string namePlan;
    string note;
    int taskPrio;
};

struct userData {
    string username;
    string password;
    vector<userPlans> plans;
    vector<userDate> deadline;
};

map<string, userData> users;

int homepage();
bool creatingAccount(map<string, userData>& users);
bool logIn(map<string, userData>& users, userData& activeUser);
void schedulePlanner(userData& activeUser);
void printOutput(int i, userData& activeUser);

int main() {
    system("color E6");

    userData activeUser;
    int option;

    // A welcome message (Start)

    cout << "\n\t\t\t ___________________________________________________________________________________";
    cout << "\n\t\t\t|                                                                                  |";
    cout << "\n\t\t\t|                                                                                  |";
    cout << "\n\t\t\t|                                     WELCOME TO                                   |";
    cout << "\n\t\t\t|                                                                                  |";
    cout << "\n\t\t\t|8 8888888888       ,o888888o.         ,o888888o.    8 8888      88    d888888o.   |";
    cout << "\n\t\t\t|8 8888          . 8888     `88.      8888     `88.  8 8888      88  .`8888:' `88. |";
    cout << "\n\t\t\t|8 8888         ,8 8888       `8b  ,8 8888       `8. 8 8888      88  8.`8888.   Y8 |";
    cout << "\n\t\t\t|8 8888         88 8888        `8b 88 8888           8 8888      88  `8.`8888.     |";
    cout << "\n\t\t\t|8 888888888888 88 8888         88 88 8888           8 8888      88   `8.`8888.    |";
    cout << "\n\t\t\t|8 8888         88 8888         88 88 8888           8 8888      88    `8.`8888.   |";
    cout << "\n\t\t\t|8 8888         88 8888        ,8P 88 8888           8 8888      88     `8.`8888.  |";
    cout << "\n\t\t\t|8 8888         `8 8888       ,8P  `8 8888       .8' ` 8888     ,8P 8b   `8.`8888. |";
    cout << "\n\t\t\t|8 8888          ` 8888     ,88'      8888     ,88'    8888   ,d8P  `8b.  ;8.`8888 |";
    cout << "\n\t\t\t|8 8888             `8888888P'         `8888888P'       `Y88888P'    `Y8888P ,88P' |";
    cout << "\n\t\t\t|                                                                                  |";
    cout << "\n\t\t\t|                          YOUR PERSONAL PRODUCTIVITY APP                          |";
    cout << "\n\t\t\t|                                                                                  |";
    cout << "\n\t\t\t|__________________________________________________________________________________|";
    cout << "\n\t\t\t: : : : : : : : For a first time user let's now set up your account!: : : :  : : : :" << endl;
    bool choice = creatingAccount(users);

    do {

        // Option if the user wants to continue logging in or going to home page
        if (choice == true) {
            option = 1;
        }
        else {
            option = homepage();
        }

        // Functions and options
        switch (option) {

            // Log in page
            case 1: if (logIn(users, activeUser) == true) {
            // If the user choose to continue to program 
            schedulePlanner(activeUser);
            break;
            }
              else {
            // If the user choose to go back to home page
            break;
        }

              // Create Account page
        case 2: if (creatingAccount(users) == true) { 
                        if (!logIn(users, activeUser)) {
                            // If the user wants to back to home page
                            break; 
                        } else {
                            // Else continue to main program
                            schedulePlanner(activeUser);
                            break;
                        }
                    } else {
                        // After creating account, if the user wants to go back to home page, this will break
                        break;
                    }   

        case 3: cout << "\n\t\t\tExiting program...\n";
                break;

        default: break;

        }

        // Resets the option to go back to home page
        choice = false;

    } while (option != 3);

    return 0;
}

int homepage() {
    // Home page for Logging in and Creating Account 
    int choice;
    while (true) {
        cout << endl;
        cout << "\t\t\t=== FOCUS ===\n" << endl;
        cout << "\t\t\t  Home page  \n" << endl;
        cout << "\t\t\t[1] Log-in " << endl;
        cout << "\t\t\t[2] Create Account " << endl;
        cout << "\t\t\t[3] Exit    " << endl;
        cout << "\t\t\tEnter: ";
        cin >> choice;

        if (choice == 1 || choice == 2 || choice == 3) {
            break;
        }
        else {
            cout << "\t\t\tError: Invalid option. Please try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        }
    }

    return choice;
}

bool creatingAccount(map<string, userData>& users) {
    string username, password, schedule;
    userData newUser;

    // For Creating Username & Password
    while (true) {

        // Creating a new account -> For username 
        while (true) {
            cout << "\n\t\t\t=== CREATING ACCOUNT === Type (back) to go to home page";
            cout << "\n\t\t\tUsername Requirements: (At least 6 characters, containing both Letters and Numbers)\n";

            // Validators
            bool length = false;
            bool containsLetter = false;
            bool containsDigit = false;

            cout << "\n\t\t\tEnter username: ";
            cin >> username;

            if (username == "back") { // To go to home page
                cout << "\t\t\tGoing to home page..." << endl;
                return false;
            }

            // Username Validators
            // For length (number of characters)
            if (username.length() >= 6) {
                length = true;
            }
            // For letters and Digits (if included in the username)
            for (char ch : username) { // To check each string using char
                if (isalpha(ch)) {
                    containsLetter = true;
                }
                else if (isdigit(ch)) {
                    containsDigit = true;
                }
            }

            // Error message for invalid username
            if (!length) {
                cout << "\t\t\tError: (At least 6 characters)" << endl;
            }
            if (!containsLetter) {
                cout << "\t\t\tError: (Needs to contain a Letter)" << endl;
            }
            if (!containsDigit) {
                cout << "\t\t\tError: (Needs to contain a Number)" << endl;
            }
            // break if the username is valid
            if (length == true && containsLetter == true && containsDigit == true) {
                // Finding if there if the Username already exists or not
                if (users.find(username) != users.end()) {
                    cout << "\t\t\tUsername already exists. Please choose a different one. " << endl;
                }
                else {
                    cout << "\t\t\t √ (Valid Username)" << endl;
                    break;
                }
                break;
            }
        }

        // Creating a new account -> For password
        while (true) {
            cout << "\n\t\t\tPassword Requirements: (at least 8 characters, containing 1 lowercase, 1 uppercase, 1 numbers, and 1 symbol)" << endl;
            cout << "\n\t\t\tEnter password: ";
            cin >> password;

            // Validators
            bool length = false;
            bool containsLower = false;
            bool containsUpper = false;
            bool containsDigit = false;
            bool containsSymbol = false;

            // Password validator
            // For length
            if (password.length() >= 8) {
                length = true;
            }
            // For other requirements
            for (char ch : password) {
                if (islower(ch)) {
                    containsLower = true;
                }
                else if (isupper(ch)) {
                    containsUpper = true;
                }
                else if (isdigit(ch)) {
                    containsDigit = true;
                }
                else if (ispunct(ch)) {
                    containsSymbol = true;
                }
            }

            // Error messages
            if (!length) {
                cout << "\t\t\tError: (At least 8 characters)" << endl;
            }
            if (!containsDigit) {
                cout << "\t\t\tError: (Needs to contain a Number)" << endl;
            }
            if (!containsUpper) {
                cout << "\t\t\tError: (Needs to contain at least 1 Uppercase)" << endl;
            }
            if (!containsLower) {
                cout << "\t\t\tError: (Needs to contain at least 1 Lowercase)" << endl;
            }
            if (!containsSymbol) {
                cout << "\t\t\tError: (Needs to contain at least 1 symbol)" << endl;
            }

            // break if the password is valid
            if (containsLower == true && containsUpper == true && containsDigit == true && containsSymbol == true) {
                cout << "\t\t\t √ (Valid Password)" << endl;
                break;
            }
        }

        // For Finalizing of creating Account
        char userChoice;
        while (true) {
            cout << "\n\t\t\t== Are you sure you're ready to finalize your account creation? ==\n" << endl;
            cout << "\t\t\t[y] Yes" << endl;
            cout << "\t\t\t[n] No" << endl;
            cout << "\t\t\tEnter: ";
            cin >> userChoice;

            if (tolower(userChoice) == 'y') {
                // If Yes , create user and save it 
                newUser.password = password;
                newUser.username = username;
                users[newUser.username] = newUser;
                cout << "\n\t\t\tCreating account successful! " << endl;
                break;
            }
            else if (tolower(userChoice) == 'n') {
                // If No, goes back to the start of creating account
                break;
            }
            else {
                cout << "\t\t\tError: Invalid Choice. Try again. " << endl;
            }
        }

        if (tolower(userChoice) == 'y') {
            break;
        }
        else {
            // If No, goes back to the start of creating account
            continue;
        }

    }

    // For Continuation to the Schedule Planner or going to home page
    while (true) {
        char choice;
        cout << "\n\t\t\t== Continue Logging In? ==\n" << endl;
        cout << "\t\t\t[y] Yes" << endl;
        cout << "\t\t\t[n] No" << endl;
        cout << "\t\t\tEnter: ";
        cin >> choice;
        if (tolower(choice) == 'y') {
            cout << "\t\t\tGoing to log in page...\n";
            return true;
        }
        else if (tolower(choice) == 'n') {
            cout << "\t\t\tGoing back to home page...\n";
            return false;
        }
        else {
            cout << "\t\t\tError: Invalid Choice. Try again." << endl;
        }
    }

}

bool logIn(map<string, userData>& users, userData& activeUser) {
    string username, password;
    cout << "\n\t\t\t=== LOG-IN === Type (back) to go to home page" << endl;

    while (true) {
        cout << "\n\t\t\tEnter username: ";
        cin >> username;

        if (username == "back") { // To go to home page
            cout << "\t\t\tGoing back to home page..." << endl;
            return false;
            break;
        }

        cout << "\t\t\tEnter password: ";
        cin >> password;

        // Finds if there is a username and password that matches in the database
        auto find = users.find(username);
        if (find != users.end() && find->second.password == password) {
            cout << "\t\t\tLogin successful! " << endl;
            activeUser = find->second;
            break;
        }
        else {
            cout << "\t\t\tError: Invalid username and password. " << endl;
            continue;
        }
    }

    return true;
}

void schedulePlanner(userData& activeUser) {
    int count, menuChoice;
    cout << "\n\t\t\t=== WELCOME " << activeUser.username << " TO SCHEDULE PLANNER! ===\n";

    // User inputs the details for each task
    while (true) {
        char choice;
        cout << "\n\t\t\t== Is this your first time using schedule planner? ==\n";
        cout << "\t\t\t[y] Yes\n";
        cout << "\t\t\t[n] No\n";
        cout << "\t\t\tEnter choice: ";
        cin >> choice;
        if (tolower(choice) == 'y') {
            // If new user, get the datas' first before going to home page of sched planner
            cout << "\n\t\t\t== For first time user, we now set up your schedule =\n";
            cout << "\n\t\t\t=== SETTING UP ===\n";
            cout << "\t\t\tHow many plans do you have? : \n";
            cout << "\t\t\tEnter: ";
            cin >> count;

            // Setting up the information for plans
            for (int i = 0; i < count; i++) {
                // Making a struct for user input
                userDate inputDeadline;
                userPlans inputPlan;

                // For name of the plan
                cout << "\n\t\t\t=== Naming Plan " << i + 1 << " ===\n";
                cout << "\t\t\tEnter name of the plan: ";
                cin.ignore();
                getline(cin, inputPlan.namePlan);

                // For status of plan
                while(true) {
                    cout << "\n\t\t\t=== Status of Plan " << inputPlan.namePlan << " ===\n";
                    cout << "\t\t\t[1] Not started\n";
                    cout << "\t\t\t[2] In Progress\n";
                    cout << "\t\t\t[3] Completed\n";
                    cout << "\t\t\t[4] Overdue\n";
                    cout << "\t\t\t[5] Cancelled\n";
                    cout << "\t\t\tEnter status number (1-5): ";
                    cin >> inputPlan.status;

                    if (inputPlan.status >= 1 && inputPlan.status <= 5){
                        break;
                    } else {
                        cout << "\t\t\tError: Invalid input. Please enter a valid integer.\n";
                        cin.clear(); // Clear error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    }
                }

                // For deadline
                while (true){
                    cout << "\n\t\t\t=== Due Date for Plan " << inputPlan.namePlan << " ===\n";
                    cout << "\t\t\tEnter month [1-12]: ";
                    cin >> inputDeadline.month;

                    if (inputDeadline.month >= 1 && inputDeadline.month <= 12){
                        break;
                    } else {
                        cout << "\t\t\tError: Invalid input. Please enter a valid integer.\n";
                        cin.clear(); // Clear error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    }
                }

                while (true) {
                    cout << "\t\t\tEnter day [1-31]: ";
                    cin >> inputDeadline.day;

                    if (inputDeadline.day >= 1 && inputDeadline.day <= 31){
                        break;
                    } else {
                        cout << "\t\t\tError: Invalid input. Please enter a valid integer.\n";
                        cin.clear(); // Clear error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    }
                }

                while (true) {
                    cout << "\t\t\tEnter year: ";
                    cin >> inputDeadline.year;

                    if (inputDeadline.year >= 999 && inputDeadline.year <= 9999){
                        break;
                    } else {
                        cout << "\t\t\tError: Invalid input. Please enter a valid integer.\n";
                        cin.clear(); // Clear error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    }
                }

                // For note

                cout << "\n\t\t\t=== Note for Plan " << inputPlan.namePlan << " ===\n";
                cout << "\t\t\tEnter note: ";
                cin.ignore(); // Clear the input buffer
                getline(cin, inputPlan.note);



                while (true) {
                    // Task prioritization
                    cout << "\n\t\t\t=== Task Prioritization for Plan " << inputPlan.namePlan << " ===\n";
                    cout << "\t\t\t[1] High priority task\n";
                    cout << "\t\t\t[2] Medium priority task\n";
                    cout << "\t\t\t[3] Low priority task\n";
                    cout << "\t\t\tEnter priority number: ";
                    cin >> inputPlan.taskPrio;
                    // Saving the data from user input


                    if (inputPlan.taskPrio >= 1 && inputPlan.taskPrio <= 3){
                                break;
                    } else {
                        cout << "\t\t\tError: Invalid input. Please enter a valid integer.\n";
                        cin.clear(); // Clear error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    }
                }

                activeUser.plans.push_back(inputPlan);
                activeUser.deadline.push_back(inputDeadline);
            }
            break;
        }
        else if (tolower(choice) == 'n') {
            break;
        }
        else {
            cout << "\n\t\t\tError: Invalid choice. Try again.\n";
        }

    }

    while (true) {

        // Home page for sched planner
        cout << "\n\t\t\t============================= SCHEDULE PLANNER ==================================== " << endl;
        cout << "\t\t\tActive User: " << activeUser.username << endl;

        // Display sorted plans
        cout << "\n\t\t\t===================== PLANS DASHBOARD ============================" << endl;
        cout << "\t\t\t| ";
        cout << "\n\t\t\t== High Priority Tasks \n";
        for (int i = 0; i < activeUser.plans.size(); i++) {
            if (activeUser.plans[i].taskPrio == 1) {
                printOutput(i, activeUser);
            }
        }
        cout << "\n\t\t\t==================================================================\n";
        cout << "\t\t\t| ";
        cout << "\n\t\t\t== Medium Priority Tasks \n";
        for (int i = 0; i < activeUser.plans.size(); i++) {
            if (activeUser.plans[i].taskPrio == 2) {
                printOutput(i, activeUser);
            }
        }
        cout << "\n\t\t\t==================================================================\n";
        cout << "\t\t\t| ";
        cout << "\n\t\t\t== Low Priority Tasks \n";
        for (int i = 0; i < activeUser.plans.size(); i++) {
            if (activeUser.plans[i].taskPrio == 3) {
                printOutput(i, activeUser);
            }
        }
        cout << "\n\t\t\t==================================================================\n";
        while (true) {
            cout << "\n\t\t\t\t===== MENU =====" << endl;
            cout << "\t\t\t\t[1] Add a new plan " << endl;
            cout << "\t\t\t\t[2] Edit an existing plan" << endl;
            cout << "\t\t\t\t[3] Log out " << endl;
            cout << "\t\t\t\tEnter choice: ";
            cin >> menuChoice;


            if (menuChoice == 1 || menuChoice == 2 || menuChoice == 3) {
                break;
            }
            else {
                cout << "\t\t\tError: Invalid option. Please try again." << endl;
                cin.clear(); // Clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            }
        }

        switch (menuChoice) {
            case 1: cout << "\n\t\t\t=== Add a new plan ===\n";
                    cout << "\t\t\tHow many plans do you want to Add? : \n";
                    cout << "\t\t\tEnter: ";
                    cin >> count;

                    // Setting up the information for plans
                    for (int i = 0; i < count; i++) {
                        // Making a struct for user input
                        userDate inputDeadline;
                        userPlans inputPlan;

                        // For name of the plan
                        cout << "\n\t\t\t=== Naming Plan " << i + 1 << " ===\n";
                        cout << "\t\t\tEnter name of the plan: ";
                        cin.ignore(); // Clear the input buffer
                        getline(cin, inputPlan.namePlan);


                        // For status

                        while (true) {
                            cout << "\n\t\t\t=== Status of Plan " << inputPlan.namePlan << " ===\n";
                            cout << "\t\t\t[1] Not started\n";
                            cout << "\t\t\t[2] In Progress\n";
                            cout << "\t\t\t[3] Completed\n";
                            cout << "\t\t\t[4] Overdue\n";
                            cout << "\t\t\t[5] Cancelled\n";
                            cout << "\t\t\tEnter status number (1-5): ";
                            cin >> inputPlan.status;

                            if (inputPlan.status >= 1 && inputPlan.status <= 5){
                                break;
                            } else {
                                cout << "\t\t\tError: Invalid input. Please enter a valid integer.\n";
                                cin.clear(); // Clear error flag
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                            }
                        }

                        while (true) {
                            // For deadline
                            cout << "\n\t\t\t=== Due Date for Plan " << inputPlan.namePlan << " ===\n";
                            cout << "\t\t\tEnter month [1-12]: ";
                            cin >> inputDeadline.month;

                            if (inputDeadline.month >= 1 && inputDeadline.month <= 12){
                                break;
                            } else {
                                cout << "\t\t\tError: Invalid input. Please enter a valid integer.\n";
                                cin.clear(); // Clear error flag
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                            }                   
                        }

                        while (true) {
                            cout << "\t\t\tEnter day [1-31]: ";
                            cin >> inputDeadline.day;
                            if (inputDeadline.day >= 1 && inputDeadline.day <= 31){
                                break;
                            } else {
                                cout << "\t\t\tError: Invalid input. Please enter a valid integer.\n";
                                cin.clear(); // Clear error flag
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                            }
                        }

                        while (true) {
                            cout << "\t\t\tEnter year: ";
                            cin >> inputDeadline.year;

                            if (inputDeadline.year >= 1 && inputDeadline.year <= 9999){
                                break;
                            } else {
                                cout << "\t\t\tError: Invalid input. Please enter a valid integer.\n";
                                cin.clear(); // Clear error flag
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                            }
                        }

                        // For note
                        cout << "\n\t\t\t=== Note for Plan " << inputPlan.namePlan << " ===\n";
                        cout << "\t\t\tEnter note: ";
                        cin.ignore(); // Clear the input buffer
                        getline(cin, inputPlan.note);

                        // Task prioritization
                        cout << "\n\t\t\t=== Task Prioritization for Plan " << inputPlan.namePlan << " ===\n";
                        cout << "\t\t\t[1] High priority task\n";
                        cout << "\t\t\t[2] Medium priority task\n";
                        cout << "\t\t\t[3] Low priority task\n";
                        cout << "\t\t\tEnter priority number: ";
                        cin >> inputPlan.taskPrio;
                        // Saving the data from user input
                        activeUser.plans.push_back(inputPlan);
                        activeUser.deadline.push_back(inputDeadline);
                    }
                    break;

        case 2: cout << "\n\t\t\t=== Edit plan ===\n";
                while (true) {
                    string planName;
                    int menuChoice;
                    bool found = false;

                    // First find the task name
                    while (true) {
                        cout << "\t\t\tEnter the name of the plan you want to edit. Type (back) to go back \n";
                        cout << "\t\t\tEnter: ";
                        cin.ignore();
                        getline(cin, planName);

                        if (planName == "back") { // To go to previous page
                            cout << "\t\t\tGoing to schedule planner..." << endl;
                            break; // Break out of the inner loop
                        }

                        for (int i = 0; i < activeUser.plans.size(); i++) {
                            if (activeUser.plans[i].namePlan == planName) {
                                found = true;
                                cout << "\t\t\tFound!" << endl;
                                break; // Break out of the inner loop
                            } else {
                                cout << "\t\t\tError: Plan not found. Please check the name and try again." << endl;
                            }
                        }
                        
                    }

                    if (planName == "back") { // To go to previous page
                        break; // Break out of the outer loop
                    }

                    while (true) {
                        cout << endl;
                        cout << "\t\t\tWhat do you want to edit in your plan? \n";
                        cout << "\t\t\t[1] Title\n";
                        cout << "\t\t\t[2] Status\n";
                        cout << "\t\t\t[3] Deadline\n";
                        cout << "\t\t\t[4] Note\n";
                        cout << "\t\t\t[5] Prioritization\n";
                        cout << "\t\t\t[6] All\n";
                        cout << "\t\t\t[7] Exit\n";
                        cout << "\t\t\tEnter: ";
                        cin >> menuChoice;

                        if (menuChoice >= 1 && menuChoice <= 7) {
                            break;
                        }
                    }

                    if (menuChoice == 7) {
                        break; // Break out of the outer loop
                    }

                    for (int i = 0; i < activeUser.plans.size(); i++) {
                        if (activeUser.plans[i].namePlan == planName) {
                            if (menuChoice == 1 || menuChoice == 6) {
                                cout << endl;
                                cout << "\t\t\tEnter new title: ";
                                cin.ignore();
                                getline(cin, activeUser.plans[i].namePlan);
                            }
                            else if (menuChoice == 2 || menuChoice == 6) {
                                // Update plan details
                                cout << endl;
                                cout << "\t\t\tEnter new status [1-5]\n";
                                cout << "\t\t\t[1] Not started\n";
                                cout << "\t\t\t[2] In Progress\n";
                                cout << "\t\t\t[3] Completed\n";
                                cout << "\t\t\t[4] Overdue\n";
                                cout << "\t\t\t[5] Cancelled\n";
                                cout << "\t\t\tEnter: ";
                                cin >> activeUser.plans[i].status;
                            }
                            else if (menuChoice == 3 || menuChoice == 6) {
                                cout << endl;
                                cout << "\t\t\tEnter new deadline (month-day-year) \n";

                                while (true) {
                                    cout << "\t\t\tEnter month [1-12]: ";
                                    cin >> activeUser.deadline[i].month;

                                    if (activeUser.deadline[i].month >= 999 && activeUser.deadline[i].month <= 9999){
                                        break;
                                    } else {
                                        cout << "\t\t\tError: Invalid input. Please enter a valid integer.\n";
                                        cin.clear(); // Clear error flag
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                                    }                            
                                }

                                while (true) {
                                    cout << "\t\t\tEnter day [1-31]: ";
                                    cin >> activeUser.deadline[i].day;

                                    if (activeUser.deadline[i].day >= 1 && activeUser.deadline[i].day <= 31){
                                        break;
                                    } else {
                                        cout << "\t\t\tError: Invalid input. Please enter a valid integer.\n";
                                        cin.clear(); // Clear error flag
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                                    }
                                }

                                while (true) {
                                    cout << "\t\t\tEnter year: ";
                                    cin >> activeUser.deadline[i].year;

                                    if (activeUser.deadline[i].year >= 999 && activeUser.deadline[i].year <= 9999){
                                        break;
                                    } else {
                                        cout << "\t\t\tError: Invalid input. Please enter a valid integer.\n";
                                        cin.clear(); // Clear error flag
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                                    }
                                }

                            } 
                            else if (menuChoice == 4 || menuChoice == 6) {
                                    cout << endl;
                                    cout << "\t\t\tEnter new note: ";
                                    cin.ignore();
                                    getline(cin, activeUser.plans[i].note);
                            }
                            else if (menuChoice == 5 || menuChoice == 6) {
                                cout << endl;
                                cout << "\t\t\tEnter new task prioritization [1-3]: ";
                                cin >> activeUser.plans[i].taskPrio;
                            }
                        }

                        cout << "\t\t\tPlan updated successfully!" << endl;
                        break;
                    }
                    break;
                }
                break;
        case 3: break; // Exit loop when user selects option 3

        }
        if (menuChoice == 3) {
            cout << "\n\t\t\tLogging out...\n";
            // Save the user data before logging out
            users[activeUser.username] = activeUser;
            activeUser = userData(); // Reset activeUser
            cout << "\t\t\tLogged out successfully.\n";
            break;
        }
    }
}

void printOutput(int i, userData& activeUser) {
    cout << endl;
    cout << "\t\t\t| Task name: " << activeUser.plans[i].namePlan << " | ";

    int statusIndex = activeUser.plans[i].status;
    string statName[5] = { "Not started", "In Progress", "Completed", "Overdue", "Cancelled" };
    cout << "Status: " << statName[statusIndex - 1] << " | ";

    int monthIndex = activeUser.deadline[i].month;
    string monthsOutput[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
    cout << "Deadline: " << monthsOutput[monthIndex - 1] << " " << activeUser.deadline[i].day << ", " << activeUser.deadline[i].year << " | ";

    cout << "Note: " << activeUser.plans[i].note << " | " << endl;
}
