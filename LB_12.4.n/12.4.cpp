#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <limits>  // For numeric_limits
#include <algorithm>

using namespace std;

struct Employee {
    string last_name;  // Last name
    string initials;   // Initials
    string position;   // Position
    int hire_year;     // Hire year
    double salary;     // Salary
};

// Function prototypes
void AddEmployee(Employee*& employees, int& N);
void EditEmployee(Employee* employees, int N);
void DeleteEmployee(Employee*& employees, int& N);
void PrintEmployees(const Employee* employees, int N);
void SortByLastName(Employee* employees, int N);
void SortBySalary(Employee* employees, int N);
void SortByHireYear(Employee* employees, int N);
bool SaveToFile(const Employee* employees, int N, const string& filename);
bool LoadFromFile(Employee*& employees, int& N, const string& filename);
void Menu();

// Function to get valid integer input
bool GetValidInt(int& input) {
    cin >> input;
    if (cin.fail() || input <= 0) {
        cin.clear();  // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
        return false;
    }
    return true;
}

// Function to get valid double input
bool GetValidDouble(double& input) {
    cin >> input;
    if (cin.fail() || input <= 0.0) {
        cin.clear();  // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
        return false;
    }
    return true;
}

int main() {
    int N = 0;  // Number of employees
    Employee* employees = nullptr;
    int menuItem;
    string filename;

    while (true) {
        Menu();
        cout << "Enter action number: ";
        cin >> menuItem;

        switch (menuItem) {
        case 1:
            AddEmployee(employees, N);
            break;
        case 2:
            EditEmployee(employees, N);
            break;
        case 3:
            DeleteEmployee(employees, N);
            break;
        case 4:
            PrintEmployees(employees, N);
            break;
        case 5:
            SortByLastName(employees, N);
            break;
        case 6:
            SortBySalary(employees, N);
            break;
        case 7:
            SortByHireYear(employees, N);
            break;
        case 8:
            cout << "Enter filename to save: ";
            cin >> filename;
            if (SaveToFile(employees, N, filename))
                cout << "Data successfully saved to file." << endl;
            else
                cout << "Error saving data to file." << endl;
            break;
        case 9:
            cout << "Enter filename to load: ";
            cin >> filename;
            if (LoadFromFile(employees, N, filename))
                cout << "Data successfully loaded from file." << endl;
            else
                cout << "Error loading data from file." << endl;
            break;
        case 0:
            delete[] employees;
            return 0;
        default:
            cout << "Invalid selection! Please try again." << endl;
        }
    }
}

void Menu() {
    cout << "\nSelect action:" << endl;
    cout << "1 - Add employee" << endl;
    cout << "2 - Edit employee" << endl;
    cout << "3 - Delete employee" << endl;
    cout << "4 - Print employee information" << endl;
    cout << "5 - Sort by last name" << endl;
    cout << "6 - Sort by salary" << endl;
    cout << "7 - Sort by hire year" << endl;
    cout << "8 - Save records to file" << endl;
    cout << "9 - Load records from file" << endl;
    cout << "0 - Exit program" << endl;
}

void AddEmployee(Employee*& employees, int& N) {
    Employee* new_employees = new Employee[N + 1];
    for (int i = 0; i < N; i++) {
        new_employees[i] = employees[i];
    }
    delete[] employees;
    employees = new_employees;

    cout << "Enter last name: ";
    cin >> employees[N].last_name;
    cout << "Enter initials: ";
    cin >> employees[N].initials;
    cout << "Enter position: ";
    cin >> employees[N].position;
    cout << "Enter hire year: ";
    while (!GetValidInt(employees[N].hire_year)) {
        cout << "Invalid input. Enter a valid year: ";
    }
    cout << "Enter salary: ";
    while (!GetValidDouble(employees[N].salary)) {
        cout << "Invalid input. Enter a valid salary: ";
    }
    N++;
}

void EditEmployee(Employee* employees, int N) {
    int index;
    cout << "Enter employee number to edit (1 - " << N << "): ";
    cin >> index;
    if (index < 1 || index > N) {
        cout << "Invalid number!" << endl;
        return;
    }
    index--;

    cout << "Editing employee #" << index + 1 << ":" << endl;
    cout << "Last name: ";
    cin >> employees[index].last_name;
    cout << "Initials: ";
    cin >> employees[index].initials;
    cout << "Position: ";
    cin >> employees[index].position;
    cout << "Hire year: ";
    while (!GetValidInt(employees[index].hire_year)) {
        cout << "Invalid input. Enter a valid year: ";
    }
    cout << "Salary: ";
    while (!GetValidDouble(employees[index].salary)) {
        cout << "Invalid input. Enter a valid salary: ";
    }
}

void DeleteEmployee(Employee*& employees, int& N) {
    int index;
    cout << "Enter employee number to delete (1 - " << N << "): ";
    cin >> index;
    if (index < 1 || index > N) {
        cout << "Invalid number!" << endl;
        return;
    }
    index--;

    Employee* new_employees = new Employee[N - 1];
    for (int i = 0, j = 0; i < N; i++) {
        if (i != index) {
            new_employees[j++] = employees[i];
        }
    }
    delete[] employees;
    employees = new_employees;
    N--;
}

void PrintEmployees(const Employee* employees, int N) {
    cout << "===============================================================================" << endl;
    cout << "| # | Last Name | Initials | Position | Hire Year | Salary |" << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "|" << setw(2) << i + 1 << " ";
        cout << "|" << setw(12) << left << employees[i].last_name;
        cout << "|" << setw(11) << employees[i].initials;
        cout << "|" << setw(13) << employees[i].position;
        cout << "|" << setw(11) << employees[i].hire_year;
        cout << "|" << setw(16) << employees[i].salary << "|" << endl;
    }
    cout << "===============================================================================" << endl;
}

void SortByLastName(Employee* employees, int N) {
    sort(employees, employees + N, [](const Employee& a, const Employee& b) {
        return a.last_name < b.last_name;
        });
}

void SortBySalary(Employee* employees, int N) {
    sort(employees, employees + N, [](const Employee& a, const Employee& b) {
        return a.salary < b.salary;
        });
}

void SortByHireYear(Employee* employees, int N) {
    sort(employees, employees + N, [](const Employee& a, const Employee& b) {
        return a.hire_year < b.hire_year;
        });
}

bool SaveToFile(const Employee* employees, int N, const string& filename) {
    ofstream file(filename);
    if (!file) return false;

    file << "No | Last Name    | Initials    | Position      | Hire Year   | Salary" << endl;
    file << "--------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        file << setw(2) << i + 1 << " | ";
        file << setw(12) << left << employees[i].last_name << " | ";
        file << setw(11) << employees[i].initials << " | ";
        file << setw(13) << employees[i].position << " | ";
        file << setw(11) << employees[i].hire_year << " | ";
        file << setw(16) << employees[i].salary << endl;
    }

    return true;
}

bool LoadFromFile(Employee*& employees, int& N, const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) return false;

    file.read((char*)&N, sizeof(N));
    delete[] employees;
    employees = new Employee[N];
    for (int i = 0; i < N; i++) {
        file.read((char*)&employees[i], sizeof(Employee));
    }

    return true;
}
