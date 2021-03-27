#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<iostream>
using namespace std;

void menu();
void addNumber();
void displayRecords();
void searchBySrNo();
void deleteRecords();
void modifyRecords();

class PhoneBook {
    int srno;
    char name[25];
    char mobile[15];
    char email[30];
    char group[20];

    public:
        int getSrNo() {
            return srno;
        }

        void storeData() {
            cout << "\n........................CREATE NEW PHONE RECORD....................\n";
            
            cout << "Enter Serial Number: ";
            cin >> srno;
            cin.ignore();

            cout << "Enter Record Name: ";
            cin.getline(name, 25);

            cout << "Enter Mobile Number: ";
            cin.getline(mobile, 15);

            cout << "Enter e-mail ID: ";
            cin.getline(email, 30);

            cout << "Enter Group Record: ";
            cin.getline(group, 20);

            cout << endl;
        }

        void showData() {
            cout << "\n..............PHONE BOOK RECORD......................\n";

            cout << "Sr. No.: " << srno << endl;
            cout << "Name: " << name << endl;
            cout << "Mobile No.: " << mobile << endl;
            cout << "Email ID: " << email << endl;
            cout << "Group: " << group << endl;
        }
}b;

void addNumber() {
    ofstream fout;
    fout.open("PhoneBook.dat", ios :: out | ios :: binary | ios :: app);
    b.storeData();
    fout.write((char*)&b, sizeof(b));
    fout.close();
    cout << "\nRecord Saved to File.....\n";
}

void displayRecords() {
    ifstream fin;
    fin.open("PhoneBook.dat", ios :: out | ios :: binary | ios :: app);
    while(fin.read((char*)&b, sizeof(b)))
    {
        b.showData();
    }
    fin.close();
    cout << "\nReading of Data File Completed............";
}

void searchBySrNo() {
    ifstream fin;
    int n, flag = 0;
    fin.open("PhoneBook.dat", ios :: out | ios :: binary | ios :: app);
    cout << "Enter Serial Number of Record To Display: ";
    cin >> n;

    while(fin.read((char*)&b, sizeof(b)))
    {
        if(n == b.getSrNo()) {
            b.showData();
            flag++;
            cout << "\n\n.........Record Found and Displayed.........\n";
        }
    }
    fin.close();
    if(flag == 0)
        cout << "\nThe Record of Serial Number " << n << " is not in file....\n";
    cout << "\nReading of Data File Completed.....\n";
}

void deleteRecords() {
    ifstream fin;
    ofstream fout;
    int n, flag = 0;
    fin.open("PhoneBook.dat", ios :: out | ios :: binary);
    cout << "Enter Serial Number of Record To Delete: ";
    cin >> n;

    while(fin.read((char*)&b, sizeof(b))) {
        if(n == b.getSrNo()) {
            cout << "\nThe Following record is deleted......";
            b.showData();
            flag++;
        }
        else {
            fout.write((char*)&b, sizeof(b));
        }
    }
    fin.close();
    fout.close();
    if(flag == 0) 
        cout << "\nThe Record of Serial Number " << n << " is not in file....";
    cout << "\nReading of data file completed....";
    remove("PhoneBook.dat");
    rename("temp.dat", "PhoneBook.dat");
}

void modifyRecords() {
    fstream fio;
    int n, flag=0, pos;
    fio.open("PhoneBook.dat", ios :: out | ios :: binary | ios :: in);

    cout << "Enter Serial Number of Record to Modify: ";
    cin >> n;

    while(fio.read((char*)&b, sizeof(b))) {
        pos = fio.tellg();
        if(n == b.getSrNo()) {
            cout << "\nThe Following record will be modified....\n";
            b.showData();
            flag++;
            cout << "\nRe-Enter the New Details.....\n";
            b.storeData();
            fio.seekg(pos-sizeof(b));
            cout << "\n....Data Modified Successfully....\n";
        }
    }
    fio.close();
    if(flag == 0) 
        cout << "\nThe Record of Serial Number " << n << " is not in file....";
    cout << "\nReading of Data File Completed......\n";
}

void menu() {
    int ch;
    do {
        cout << ".........................................................\n";
        cout << "               PHONEBOOK MANAGEMENT                       ";
        cout << "\n.........................................................\n\n";
        cout << "::::::::::::::::::: PROGRAM MENU ::::::::::::::::::::::::::\n";

        cout << "0. Exit\n";
        cout << "1. Save New Phone Record\n";
        cout << "2. Display All Saved Records\n";
        cout << "3. Search Specific Record\n";
        cout << "4. Delete Specific Record\n";
        cout << "5. Modify Existing Record\n";
        cout << "Enter Your Choice: ";
        cin >> ch;

        switch(ch) {
            case 1:
                addNumber();
                break;
            case 2:
                displayRecords();
                break;
            case 3:
                searchBySrNo();
                break;
            case 4:
                deleteRecords();
                break;
            case 5:
                modifyRecords();
                break;
        }
    } while(ch != 0);
}

int main() {
    menu();
}