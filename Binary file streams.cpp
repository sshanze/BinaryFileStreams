#include <stdio.h>

void arrayToFile(const char* fileName, int* arr, int size) 
{
    FILE* file = fopen(fileName, "wb");
    fwrite(arr, sizeof(int), size, file);
    fclose(file);
}

void fileToArray(const char* fileName, int* arr, int size)
{
    FILE* file = fopen(fileName, "rb");
    fread(arr, sizeof(int), size, file);
    fclose(file);
}

int main() 
{
    // Define an array and its size
    int myArray[] = { 1, 2, 3, 4, 5 };
    int size = sizeof(myArray) / sizeof(int);

    // Write the array to a file
    arrayToFile("myFile.dat", myArray, size);

    // Define another array to store the data from the file
    int newArray[size];

    // Read the data from the file into the new array
    fileToArray("myFile.dat", newArray, size);

    // Display the array contents
    for (int i = 0; i < size; i++)
    {
        printf("%d ", newArray[i]);
    }

    return 0;
}



void arrayToFile(const char* fileName, int* arr, int size) 
{
    FILE* file = fopen(fileName, "wb");
    if (file) 
    {
        fwrite(arr, sizeof(int), size, file);
        fclose(file);
    }
}

void fileToArray(const char* fileName, int* arr, int size) 
{
    FILE* file = fopen(fileName, "rb");
    if (file)
    {
        fread(arr, sizeof(int), size, file);
        fclose(file);
    }
}

int main() 
{
    int myArray[] = { 1, 2, 3, 4, 5 };
    int size = sizeof(myArray) / sizeof(int);

    arrayToFile("myFile.dat", myArray, size);

    int newArray[size];
    fileToArray("myFile.dat", newArray, size);

    for (int i = 0; i < size; i++)
    {
        printf("%d ", newArray[i]);
    }

    return 0;
}


#include <iostream>
#include <fstream>
using namespace std;

void arrayToFile(const char* fileName, int* arr, int size) 
{
    ofstream file(fileName, ios::binary);
    if (file) 
    {
        file.write(reinterpret_cast<char*>(arr), size * sizeof(int));
    }
}

void fileToArray(const char* fileName, int* arr, int size) 
{
    ifstream file(fileName, ios::binary);
    if (file) 
    {
        file.read(reinterpret_cast<char*>(arr), size * sizeof(int));
    }
}

int main()
{
    int myArray[] = { 1, 2, 3, 4, 5 };
    int size = sizeof(myArray) / sizeof(int);

    arrayToFile("myFile.dat", myArray, size);

    int newArray[size];
    fileToArray("myFile.dat", newArray, size);

    for (int i = 0; i < size; i++) 
    {
        cout << newArray[i] << " ";
    }

    return 0;
}


#include <iostream>
#include <fstream>
using namespace std;

class Student {
private:
    int id;
    float marks;

public:
    Student(int id = 0, float marks = 0.0f) : id(id), marks(marks) {}

    friend istream& operator>>(istream& in, Student& student) 
    {
        cout << "Enter ID: ";
        in >> student.id;
        cout << "Enter Marks: ";
        in >> student.marks;
        return in;
    }

    friend ostream& operator<<(ostream& out, const Student& student) 
    {
        out << "ID: " << student.id << ", Marks: " << student.marks;
        return out;
    }

    void addStudent(ofstream& file) 
    {
        file.write(reinterpret_cast<char*>(this), sizeof(*this));
        cout << "Student added successfully!" << endl;
    }

    static void displayAllStudents(ifstream& file) 
    {
        Student student;
        file.seekg(0, ios::end);
        int size = file.tellg() / sizeof(Student);

        if (size == 0)
        {
            cout << "No records found." << endl;
            return;
        }

        file.seekg(0, ios::beg);

        for (int i = 0; i < size; i++) 
        {
            file.read(reinterpret_cast<char*>(&student), sizeof(Student));
            cout << student << endl;
        }
    }

    bool findStudent(ifstream& file) 
    {
        Student student;
        bool found = false;

        while (file.read(reinterpret_cast<char*>(&student), sizeof(Student)))
        {
            if (student.id == this->id && student.marks == this->marks) 
            {
                found = true;
                break;
            }
        }

        return found;
    }

    bool deleteStudent(ifstream& inFile, ofstream& outFile) 
    {
        Student student;
        bool found = false;

        while (inFile.read(reinterpret_cast<char*>(&student), sizeof(Student)))
        {
            if (student.id == this->id && student.marks == this->marks)
            {
                found = true;
            }
            else 
            {
                outFile.write(reinterpret_cast<char*>(&student), sizeof(Student));
            }
        }

        return found;
    }
};

int main()
{
    ofstream outFile("student.dat", ios::binary | ios::app);
    ifstream inFile("student.dat", ios::binary);

    if (!outFile || !inFile) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    int choice;
    Student student;
    bool found;

    do {
        cout << "\nMenu:\n1. Add Student\n2. Find Student\n3. Delete Student\n4. Display All Students\n5. Exit\n";
        cin >> choice;

        switch (choice) 
        {
        case 1:
            cin >> student;
            student.addStudent(outFile);
            break;
        case 2:
            cout << "Enter student information to find:\n";
            cin >> student;
            found = student.findStudent(inFile);
            if (found)
            {
                cout << "Student found!" << endl;
            }
            else 
            {
                cout << "Student not found." << endl;
            }
            break;
        case 3:
            cout << "Enter student information to delete:\n";
            cin >> student;
            found = student.deleteStudent(inFile, outFile);
            if (found) 
            {
                cout << "Student deleted successfully!" << endl;
            }
            else
            {
                cout << "Student not found." << endl;
            }
            break;
        case 4:
            Student::displayAllStudents(inFile);
            break;
        case 5:
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }

    }
    while (choice != 5);

    outFile.close();
    inFile.close();

    return 0;
}



int main()
{
    ofstream outFile("student.dat", ios::binary | ios::app);
    ifstream inFile("student.dat", ios::binary);

    if (!outFile || !inFile) 
    {
        cerr << "Error opening file." << endl;
        return 1;
    }

    int choice;
    Student student;
    bool found;

    cout << "\nMenu:\n";
    cout << "1. Add Student\n";
    cout << "2. Find Student\n";
    cout << "3. Delete Student\n";
    cout << "4. Display All Students\n";
    cout << "5. Exit\n";

    cin >> choice;

    if (choice == 1) 
    {
        cin >> student;
        student.addStudent(outFile);
    }
    else if (choice == 2) 
    {
        cout << "Enter student information to find:\n";
        cin >> student;
        found = student.findStudent(inFile);
        if (found)
        {
            cout << "Student found!" << endl;
        }
        else 
        {
            cout << "Student not found." << endl;
        }
    }
    else if (choice == 3) 
    {
        cout << "Enter student information to delete:\n";
        cin >> student;
        found = student.deleteStudent(inFile, outFile);
        if (found)
        {
            cout << "Student deleted successfully!" << endl;
        }
        else 
        {
            cout << "Student not found." << endl;
        }
    }
    else if (choice == 4) 
    {
        Student::displayAllStudents(inFile);
    }
    else if (choice == 5)
    {
        // Exit the program
    }
    else 
    {
        cout << "Invalid choice. Please try again." << endl;
    }

    outFile.close();
    inFile.close();

    return 0;
}



bool deleteStudent(ifstream& inFile) 
{
    ofstream tempFile("temp.dat", ios::binary);  // Create a temporary file

    if (!tempFile) {
        cerr << "Error creating temporary file." << endl;
        return false;
    }

    Student student;
    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        if (student.id == this->id && student.marks == this->marks) {
            found = true;
        }
        else {
            tempFile.write(reinterpret_cast<char*>(&student), sizeof(Student));
        }
    }

    tempFile.close();
    inFile.close();

    remove("student.dat");  // Delete the original file
    rename("temp.dat", "student.dat");  // Rename the temporary file to the original file name

    return found;
}