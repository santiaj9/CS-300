//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Jordan Santiago
// Version     : 1.0
// Copyright   : Copyright © 2023 SNHU COCE
// Description : ABCU Advising Program Course Planner
//============================================================================

//Pulls in the required headers
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

//============================================================================
// Creation of Vector and Course object Data Scructures
//============================================================================

// Initializes the Course object structure
struct Course {
    string courseNumber;
    string title;
    string preRequisite1;
    string preRequisite2;
};

// Initializes the vector courseLibrary
vector<Course> courseLibrary;

//============================================================================
// Functions to search, load, and print the Course Library
//============================================================================

//Searches courseLibrary for a specific course number and prints the details
void searchCourse(string courseNumber) {
    bool found = false; //Creates a boolean to hold if the course was found
    //Transform changes the input to be uppercase, making the case of the input not matter
    transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);

    for (int i = 0; i < courseLibrary.size(); i++) { //Iterates through courseLibrary
        if (courseLibrary[i].courseNumber == courseNumber) { //Sets search parameter to the course number
            found = true; //Changes found to true to avoid printing course not found
            //Next four lines print the course's information
            cout << "\n" << courseLibrary[i].courseNumber << " | "
                << courseLibrary[i].title << " | "
                << courseLibrary[i].preRequisite1 << " | "
                << courseLibrary[i].preRequisite2 << "\n" << endl;
            break; //Breaks the for loop
        }
    }
    //If the course is not found, tell the user
    if (found == false) {
        cout << "\nCourse not found.\n" << endl;
    }
}

//Loads all course information into the courseLibrary
void loadCourseLibrary() {
    
    //Gets the file with the course information opened
    cout << "\nLoading Course Information" << "\n" << endl; //Prompts the user to wait for the course data to be loaded into the system
    std::ifstream courseDoc("CS 300 ABCU_Advising_Program_Input.csv"); //Opens the csv with the course information
   
    //Reads the csv loads each row into a Course object
    Course course; //Creates course object to store data before it is added to the courseLibrary
    std::string line; //Creates string to hold each line from the CSV
    char delimiter = ','; //Creates the delimiter that will remove the "," from the string
    std::vector<string> temp; //Creates a temporary vector to store the line before parsing
    //Ensures the document is open before parsing
    if(courseDoc.is_open()){
        //Ensures the document is good
        while (courseDoc.good()) {
            //Iterates through file to read and record the data
            for (int i = 0; getline(courseDoc, line, delimiter); i++) {
                size_t pos = line.find('\n'); //Checks for a new line within the string to handle properly
                //if statement catches a new line a parses the information between what is before and after it
                if (pos != std::string::npos) {
                    std::string beforeNewLine; //Creates string to hold the string before a new line
                    beforeNewLine = line.substr(0, pos); //Takes the string data before the new line
                    line = line.substr(pos+1); //Resets the line data to everything after the new line
                    temp.push_back(beforeNewLine); //Adds string before new line to the temp vector
                    temp.push_back(line); //Adds the string after the new line to the temp vector
                    i++; //iterates i to reposition getline() correctly
                }
                //If no new line is found, the string is added to the temp vector
                else {
                    temp.push_back(line); //Adds the line to the temp vector
                }
          
            }
         }
        //Parses through the temp vector to add course information into the courseLibrary
        for (int i = 0; i < temp.size(); i++) {
            //Logic to tell the system where each piece of data needs to be placed
            if (i % 4 == 0) {
                course.courseNumber = temp[i]; //Adds the courseNumber to the temp vector
            }
            else if (i % 4 == 1) {
                course.title = temp[i]; //Adds the courseNumber to the temp vector
            }
            else if (i % 4 == 2) {
                if (temp[i] == "") { //If there is no first prerequisite
                    course.preRequisite1 = "N/A"; //Put N/A as a placeholder and add it to the temp vector
                }
                else {
                    course.preRequisite1 = temp[i]; //Adds the courseNumber to the temp vector
                }
            }
            else if (i % 4 == 3) {
                if (temp[i] == "") { //If there is no second prerequisite
                    course.preRequisite2 = "N/A"; //Put N/A as a placeholder and add it to the temp vector
                    courseLibrary.push_back(course); //Adds the newly finished course object to the courseLibrary
                }
                else {
                    course.preRequisite2 = temp[i]; //Adds the second prerequisite to the temp vector
                    courseLibrary.push_back(course); //Adds the newly finished course object to the courseLibrary
                }
            }
        }

        //Puts the courseLibrary in alphanumeric order using the sort() function
        sort(courseLibrary.begin(), courseLibrary.end(), [](const Course& a, const Course& b) {
            return a.courseNumber < b.courseNumber; //provides logic to determine when a course number is less than another
            });

        //Creates a header line identify the columns and adds to courseLibrary
        Course courseHeaders = { "Course Number", "Title", "Pre-Requisite 1", "Pre-Requisite 2" }; //Creates a Course object for the headers
        courseLibrary.insert(courseLibrary.begin(), courseHeaders); //Inserts the course headers at the beginning of the courseLibrary
    }
}

//Prints out courseLibrary in an easy to read format
void printCourseLibrary() {
    //Next four lines create variables to represent the longest input for each column
    int longestCourseNumber = 0;
    int longestTitle = 0;
    int longestPreRequisite1 = 0;
    int longestPreRequisite2 = 0;
    //Next four lines create spacers to represent blank space needed to format the columns print out in a way that is easily readable
    string spacerCourseNumber;
    string spacerTitle;
    string spacerPreRequisite1;
    string spacerPreRequisite2;
    //Temporary int to store the difference between the longest input and the current input needed to create the blank spaces
    int temp = 0;

    //Iterates through the courseLibrary to determine which input in each column is the longest
    for (int i = 0; i < courseLibrary.size(); i++) {
        if (courseLibrary[i].courseNumber.length() > longestCourseNumber) { //Checks the current course number to see if it is the longest in the vector
            longestCourseNumber = courseLibrary[i].courseNumber.length(); //If the current course number is the longest, sets longestCourseNumber to its length
        }
        if (courseLibrary[i].title.length() > longestTitle) { //Checks the current title to see if it is the longest in the vector
            longestTitle = courseLibrary[i].title.length(); //If the current title is the longest, sets longestTitle to its length
        }
        if (courseLibrary[i].preRequisite1.length() > longestPreRequisite1) { //Checks the current prerequisite1 to see if it is the longest in the vector
            longestPreRequisite1 = courseLibrary[i].preRequisite1.length(); //If the current prerequisite1 is the longest, sets longestPreRequisite1 to its length
        }
        if (courseLibrary[i].preRequisite2.length() > longestPreRequisite2) { //Checks the current prerequisite2 to see if it is the longest in the vector
            longestPreRequisite2 = courseLibrary[i].preRequisite2.length(); //If the current prerequisite2 is the longest, sets longestPreRequisite2 to its length
        }
    }

    cout << endl; //Adds blank space between the output and the menu within the program screen

    //Iterates through the courseLibrary vector
    for (int i = 0; i < courseLibrary.size(); i++) {
        //Dynamically creates a blank space variable for each course number
        if (courseLibrary[i].courseNumber.length() < longestCourseNumber) { //Checks the current course number to see if it is shorter than longestCourseNumber
            temp = longestCourseNumber - courseLibrary[i].courseNumber.length(); //If the current course number is shorter, set temp to the difference
            for (int j = 0; j < temp; j++) { //Iterates a number of times equal to temp's length
                spacerCourseNumber += " "; //Adds a " " to spacerCourseNumber each time the for loop runs
            }
        }
        //Dynamically creates a blank space variable for each title
        if (courseLibrary[i].title.length() < longestTitle) { //Checks the current title to see if it is shorter than longestTitle
            temp = longestTitle - courseLibrary[i].title.length(); //If the current title is shorter, set temp to the difference
            for (int j = 0; j < temp; j++) { //Iterates a number of times equal to temp's length
                spacerTitle += " "; //Adds a " " to spacerTitle each time the for loop runs
            }
        }
        //Dynamically creates a blank space variable for each prerequisite1
        if (courseLibrary[i].preRequisite1.length() < longestPreRequisite1) { //Checks the current prerequisite1 to see if it is shorter than longestPreRequisite1
            temp = longestPreRequisite1 - courseLibrary[i].preRequisite1.length(); //If the current prerequisite1 is shorter, set temp to the difference
            for (int j = 0; j < temp; j++) { //Iterates a number of times equal to temp's length
                spacerPreRequisite1 += " "; //Adds a " " to spacerPreRequisite1 each time the for loop runs
            }
        }
        //Dynamically creates a blank space variable for each prerequisite2
        if (courseLibrary[i].preRequisite2.length() < longestPreRequisite2) { //Checks the current prerequisite2 to see if it is shorter than longestPreRequisite2
            temp = longestPreRequisite2 - courseLibrary[i].preRequisite2.length(); //If the current prerequisite2 is shorter, set temp to the difference
            for (int j = 0; j < temp; j++) { //Iterates a number of times equal to temp's length
                spacerPreRequisite2 += " "; //Adds a " " to spacerPreRequisite2 each time the for loop runs
            }
        }
        cout << courseLibrary[i].courseNumber << spacerCourseNumber << " | " //Prints the course number with the formatting spaces
            << courseLibrary[i].title << spacerTitle << " | "  //Prints the title with the formatting spaces
            << courseLibrary[i].preRequisite1 << spacerPreRequisite1 << " | " //Prints the first pre-requisite or "N/A" with the formatting spaces
            << courseLibrary[i].preRequisite2 << spacerPreRequisite2 << endl; //Prints the second pre-requisite or "N/A" with the formatting spaces

        //Next four lines reset the spacers to prepare for the next vector element
        spacerCourseNumber = "";
        spacerTitle = "";
        spacerPreRequisite1 = "";
        spacerPreRequisite2 = "";
    }
    cout << endl; //Adds blank space between the output and the menu within the program screen
}

//============================================================================
// Main Method
//============================================================================

int main()
{
    //Initilizes variables for user inputs
    int userChoice = 0;
    string courseNumber = "";
    
    //Creates while loop that initializes the menu
    while (userChoice != 9) {
        //Prints instruction to the user
        cout << "Please choose from the following options:\n" << endl;
        //Next four lines print the user's choices to the screen
        cout << "1 - Load the course library from the data file." << endl;
        cout << "2 - Print out the course library." << endl;
        cout << "3 - Search for a specific course's information." << endl;
        cout << "9 - Exit the program\n" << endl;

        cin >> userChoice; //Takes the user's choice as an input
        
        //Error handling to ensure that the user gives a legitimate input
        while (userChoice != 1 && userChoice != 2 && userChoice != 3 && userChoice != 9) { //while the user's choice is invalid
            cout << "\nInvalid input. Please choose valid menu option (1, 2, 3, 9).\n" << endl; //Repeats instructions
            //Next four lines print the user's choices to the screen
            cout << "1 - Load the course library from the data file." << endl;
            cout << "2 - Print out the course library." << endl;
            cout << "3 - Search for a specific course's information." << endl;
            cout << "9 - Exit the program\n" << endl;
            cin.clear(); //Clears the error state that cin is in if applicable
            cin.ignore(1000, '\n'); //Discards the remaining characters in con
            cin >> userChoice; //Retakes the user's choice as an input
        }

        //When the input is valid, the program moves to the next stage

        //Switch case to detemine what the program will do based on user input
        switch (userChoice) {
        case 1: //Loads the courseLibrary with the data from the given file
            loadCourseLibrary(); //Conducts the loading function
            break; //exits the switch case

        case 2: //Prints the entire courseLibrary in alphanumeric order
            printCourseLibrary(); //Conducts the printing function
            break; //exits the switch case

        case 3: //Searches the courseLibrary for a specific course and returns it
            cout << "\nWhat is the Course Number that you would like to find? (e.g. MATH201)\n" << endl;
            cin >> courseNumber; //Takes the user's choice of Course Numbers as an input
            while (courseNumber.length() != 7) { //ensures the input is the correct length
                cout << "\nThere's an issue with the input! Please reenter the Course Number\n" << endl;
                cin >> courseNumber; //retakes the user's choice of Course Numbers as an input
            }
            searchCourse(courseNumber); //Conducts the searching function
            break; //exits the switch case

        case 9: //Exits the program, printing a goodbye message
            cout << "\nThank you for using this program! Have a great day!\n" << endl;
            cout << "Program terminated" << endl;
            break; //exits the switch case
        }
    }
}

