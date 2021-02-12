// compile: g++ -std=c++11 -o pointers pointers.cpp
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

typedef struct Student {
    int id;
    char *f_name;
    char *l_name;
    int n_assignments;
    double *grades;
} Student;

int promptInt(std::string message, int min, int max);
double promptDouble(std::string message, double min, double max);
void calculateStudentAverage(void *object, double *avg);

int main(int argc, char **argv)
{
    Student student;
    double average;

    //Sequence of user input -> store in fields of `student`
    student.id = promptInt("Please enter the student's id number: ", 0 ,999999999);

    std::cout << "Please enter the student's first name: ";
    char first_name[128];
    scanf("%s", first_name);
    student.f_name = first_name;

    std::cout << "Please enter the student's last name: ";
    char last_name[128];
    scanf("%s", last_name);
    student.l_name = last_name;

    std::cin.ignore(1); //The consequences of using scanf.

    student.n_assignments = promptInt("Please enter how many assignments were graded: ", 0 ,134217728);

    std::cout << "\n";
    double grades[student.n_assignments];
    for(int i=0; i<student.n_assignments; i++) {
        //Format message for "promptDouble()" into a single string.
        std::string message0 = "Please enter grade for assignment ";
        std::string message1 = std::to_string(i);
        std::string message2 = ": ";
        std::string message = message0 + message1 + message2;

        grades[i] = promptDouble(message, 0, 100);
    }
    student.grades = grades;
    
    average = student.n_assignments;    //Temporarily set the average to the number of assignments so the size of the grades array is known in "calculateStudentAverage()"
    calculateStudentAverage(student.grades, &average);
    
    std::cout << "Student: " << student.f_name << " " << student.l_name << " [" << student.id << "]\n";
    std::cout << std::fixed;
    std::cout << std::setprecision(1);
    std::cout << "  Average grade: " << average;

    return 0;
}


/*
   message: text to output as the prompt
   min: minimum value to accept as a valid int
   max: maximum value to accept as a valid int
*/
int promptInt(std::string message, int min, int max) {
    int value = 0;
    std::string user_input;
    bool valid_input = true;
    do {
        valid_input = true;
        std::cout << message;
        getline(std::cin, user_input);
        //Manually goes through the user's string checking for anything that isn't a number.
        for(int i=0; i<user_input.length(); i++) {
            if(user_input[i] < 48 || user_input[i] > 57 ) {
                std::cout << "Sorry, I cannot understand your answer\n";
                valid_input = false;
                break;
            }
        }
        //The above test does not catch an empty input array so this IF does.
        if(user_input.length() == 0) {
            std::cout << "Sorry, I cannot understand your answer\n";
            valid_input = false;
        }
        if(valid_input) {
            value = std::stoi(user_input);
            if(value < min || value > max) {
                std::cout << "Sorry, I cannot understand your answer\n";
                valid_input = false;
            }
        }
    } while (valid_input == false);
    return value;
}


/*
   message: text to output as the prompt
   min: minimum value to accept as a valid double
   max: maximum value to accept as a valid double
*/
double promptDouble(std::string message, double min, double max) {
    double value = 0;
    std::string user_input;
    bool valid_input = true;
    do {
        valid_input = true;
        std::cout << message;
        getline(std::cin, user_input);

        //Manually goes through the user's string checking for anything that isn't a number or if there is more than one "."
        int periods_seen = 0;
        for(int i=0; i<user_input.length(); i++) {
            if(user_input[i] == 46) {
                periods_seen++;
            }
            if(periods_seen > 1 || (user_input[i] < 48 && user_input[i] != 46) || user_input[i] > 57 ) {
                std::cout << "Sorry, I cannot understand your answer\n";
                valid_input = false;
                break;
            }
        }
        //The above test does not catch an empty input array so this IF does. It also catches the case of a single "." being entered.
        if(user_input.length() == 0 || (periods_seen == 1 && user_input[1] == 0)) {
            std::cout << "Sorry, I cannot understand your answer\n";
            valid_input = false;
        }
        if(valid_input) {
            value = std::stod(user_input);  //Converts the string to a double.
            if(value < min || value > max) {
                std::cout << "Sorry, I cannot understand your answer\n";
                valid_input = false;
            }
        }
    } while(valid_input == false);
    return value; 
}


/*
   object: pointer to anything - your choice! (but choose something that will be helpful)
   avg: pointer to a double (can store a value here)
*/
void calculateStudentAverage(void *object, double *avg) {
    double *grades = (double*)object;
    int assignments = *avg;   //Gets the size of "grades[]" from average
    double sum = 0.0;
    for(int i=0; i<assignments; i++) {
        sum += grades[i];
    }
    *avg = sum/assignments;
}
