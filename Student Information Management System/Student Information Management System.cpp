#include <bits/stdc++.h>
#include <windows.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;

#define int long long

/*      Hello Developers!
        We are developing a Student's Information Management System using C & C++ programming languages.
        Some basic operations that we can do in this systemare:
                *Add new student's information
                *Search specific student's information by ID no.
                *View all student's information
                *Edit/Update any student's information
                *Delete a single student's information by ID no.
                *Delete all Student's information.
                *You can also restore last 10 deleted student's indormation from Recycle Bin
        
        We are implimenting Student's information in student type structured data and storing it bt Linked List.
        We are storing 
                *Student ID
                *Name
                *Phone
                *E-mail
                *Enrolled Courses
                    *Course Code
                    *Course Name
            Storing course information in map(C++ STL Property) where Course Code is the key and course name is the value

            ******A lot more to go****
        
        9th Nov, 2023
*/

/*structure type data to hold Student's information. Including his assigned courses*/
typedef struct students{
    string ID, name, email, phone;
    int courseNum;
    map<string,string> course; //to store all his courses where key is course code and value is course name
    struct students *next;
}students;

students *start = NULL;
students *queStart = NULL, *queEnd = NULL; //stores deleted students information to restore
int queEle = 0;

void landing();
void menu();
void display();
void exitProgram();
void addNew();
bool exists(string SID, string type, string ID);
void SearchByID();
void returnlanding();
void slowTxt(string s);
void viewDevelopers();
void updateStud();
string scanName();
string scanPhone();
string scanEmail();
string scanID();
string scanCCode();
string scanCName();
void deleteRandom();
void deleteAll();
void restore();
void queDisplay();
bool isValidName(const string & name);
bool isValidPhone(const string & Phone);
bool foundAtr(const string & s);

signed main(){
    while(true){
        system("cls"); //Cleares previous output
        landing();
        int ope;
        cin>>ope;
        switch(ope){
            case 0:
                exitProgram();
                break;
            case 1:
                menu();

                break;

            case 2:
                queDisplay();
                break;

            case 3:
                viewDevelopers();
                break;

            default:
                string invalid = "\n\tInvalid Choise...";
                slowTxt(invalid);
                Sleep(300);
                break;
        }
    }
}

void landing(){
    system("cls");
    cout<<"\n\n";
    cout<<"\t=============================================\n"; Sleep(10);
    cout<<"\n\t    Student Information Management System"<<endl<<endl; Sleep(10);
    cout<<"\t=============================================\n"; Sleep(10);
    cout<<"\n\t\t\t   Home"<<endl; Sleep(10);
    cout<<"\n\t[1] Main Menu"<<endl; Sleep(10);
    cout<<"\t[2] Open recycle bin."<<endl; Sleep(10);
    cout<<"\t[3] Meet The Developer's"<<endl; Sleep(10);
    cout<<"\t[0] Exit the Program."<<endl; Sleep(10);
    cout<<"\t=============================================\n"; Sleep(10);
    cout<<"\tEnter your Choise: ";
}

void menu(){
    system("cls");
    cout<<"\n\n";
    cout<<"\t=============================================\n"; Sleep(10);
    cout<<"\n\t    Student Information Management System"<<endl<<endl; Sleep(10);
    cout<<"\t=============================================\n"; Sleep(10);
    cout<<"\n\t\t\t  Main Menu"<<endl; Sleep(10);
    cout<<"\n\t[1] Add a new Student."<<endl; Sleep(10);
    cout<<"\t[2] Search a Student by ID."<<endl; Sleep(10);
    cout<<"\t[3] View all Student's Info."<<endl; Sleep(10);
    cout<<"\t[4] Update any Students Info."<<endl; Sleep(10);
    cout<<"\t[5] Delete any Student's Info."<<endl; Sleep(10);
    cout<<"\t[6] Delete All Student's Info."<<endl; Sleep(10);
    cout<<"\t[7] Restore deleted Info."<<endl; Sleep(10);
    cout<<"\t[9] Return to Home."<<endl; Sleep(10);
    cout<<"\t[0] Exit The program."<<endl; Sleep(10);
    cout<<"\t=============================================\n"; Sleep(10);
    cout<<"\tEnter your Choise: ";
    int ope;
    cin>>ope;
    switch(ope){
        case 0:
            exitProgram();
            break;

        case 1:
            addNew();
            break;

        case 2:
            SearchByID();
            break;
        case 3:
            display();
            break;
        case 4:
            updateStud();
            break;
        case 5:
            deleteRandom();
            break;
        case 6:
            deleteAll();
            break;
        case 7:
            restore();
            break;
        case 9:
            return;
            break;

        default:
            string invalid = "\n\tInvalid Choise...";
            for(auto it : invalid){
                cout<<it;
                Sleep(20);
            }
            cout<<"\n\n";
            Sleep(300);
            break;
    }
}

void SearchByID(){
    string s = "To search a student, please Enter following\n\tinformation. ";
    slowTxt(s);
    cout<<"\tStident ID: ";
    string ID;
    cin>>ID;
    students *st = start;
    bool found = false;
    while(st!=NULL){
        if(st->ID==ID){
            //cout<<"\tStudent ID: "<<st->ID<<endl;
            cout<<"\tName: "<<st->name<<endl;
            cout<<"\tPhone: "<<st->phone<<endl;
            cout<<"\tE-mail: "<<st->email<<endl;
            cout<<"\tEnrolled courses: "<<st->course.size()<<endl;
            int c = 1; //course counter
            for(auto it : st->course){
                cout<<"\t\tCourse-";if(c<10){cout<<"0";}cout<<c<<": "<<endl;
                cout<<"\t\t\tCourse Name: "<<it.second<<endl;
                cout<<"\t\t\tCourse Code: "<<it.first<<endl;
                c++;
            }
            found = true;
        }
        st = st->next;
    }
    if(found==false){
        string p = "There is no information of student holding ID ";
        p+=ID;
        slowTxt(p);
    }
    returnlanding();
}

bool exists(string tocmp, string type, string ID){
    bool ide = false;
    bool phn = false;
    bool email = false;
    students *st = start;
    while(st!=NULL){
        if(st->ID==tocmp && st->ID==ID){
            ide = true;
        }
        if(st->phone==tocmp && st->ID==ID){
            phn = true;
        }
        if(st->email==tocmp && st->ID==ID){
            email = true;
        }
        st = st->next;
    }

    if(type == "id"){
        return ide;
    }
    else if(type == "phn"){
        return phn;
    }
    else if(type == "mail"){
        return email;
    }
    else{
        return false;
    }
}

void addNew(){
    cout<<"\n\n"<<endl;
    string s = "You wanted to add a new student. \n\tPlease enter his/her detailed information";
    slowTxt(s);

    string ID = scanID();
    string name = scanName();
    string phone = scanPhone();
    string email = scanEmail();

    //Node creation and vallue Assiging
    students *student = new students();
    student->ID = ID;
    student->name = name;
    student->email = email;
    student->phone = phone;

    cout<<"\tEnter The Number of Courses: ";
    cin>>student->courseNum;

    for(int i = 1;i<=student->courseNum;i++){
        cout<<"\tCourse-"<<i<<": \n";
        string cCode = scanCCode();
        string cName = scanCName();

        student->course[cCode] = cName; //assigning map value
    }

    if(start == NULL){
        start = student;
    }
    else{
        students *p = start;
        while(p->next!=NULL){
            p = p->next;
        }
        p->next = student;
    }
    //display();
    cout<<"\n\tStudent added successfully! \n";
    returnlanding();

}

string scanID(){
    bool valid = false;
    string ID;
    cin.ignore();
    while(!valid){
        cout<<"\tStudent ID: ";
        getline(cin, ID);
        if(exists(ID,"id", ID)){
            cout<<"\tID "<<ID<<" already exists.\n\n";
        }
        else if(ID.size()==0){
            cout<<"\tInvalid! ID can not be empty\n\n";
        }
        else{
            valid = true;
        }
    }
    return ID;
}

string scanName(){
    string name;
    bool valid = false;
    //cin.ignore();
    while(!valid){
        cout<<"\tStudent Name: ";
        getline(cin, name);
        if(name.size()==0){
            cout<<"\t\tInvalid! Name can not be empty\n\n";
        }
        else if(isValidName(name) != true){
            cout<<"\t\tInvalid Name\n\n";
        }
        else{
            valid = true;
        }
    }
    return name;
}

string scanPhone(){
    bool valid = false;
    string phone;
    //cin.ignore();
    while(!valid){
        cout<<"\tThe Phone Number: ";
        getline(cin, phone);
        if(phone.size() != 11){
            cout<<"\t\tPhone number should be 11 character\n\n";
        }
        else if(phone.size() == 0){
            cout<<"\t\tPhone nummber can not be empty\n\n";
        }
        else if(isValidPhone(phone) != true){
            cout<<"\t\tInvalid Phone Number\n\n";
        }
        else{
            valid = true;
        }
    }
    return phone;
}

string scanEmail(){
    string email;
    bool valid = false;
    //cin.ignore();
    while(!valid){
        cout<<"\tE-mail Address: ";
        getline(cin, email);
        if(email.size()==0){
            cout<<"\t\tE-mail can not be empty\n\n";
        }
        else if(foundAtr(email) != true){
            cout<<"\t\tInvalid E-mail\n\n";
        }
        else{
            valid = true;
        }
    }
    return email;
}

string scanCCode(){
    bool valid = false;
    string cCode;
    //cin.ignore();
    while(!valid){
        cout<<"\tCourse Code: ";
        //getline(cin, Ccode);
        cin>>cCode;
        if(cCode.size()==0){
            cout<<"\t\tCourse code can not be empty\n";
        }
        else{
            valid = true;
        }
    }
    return cCode;
}

string scanCName(){
    bool valid = false;
    string cName;
    //cin.ignore();
    while(!valid){
        cin.ignore();
        cout<<"\tCourse Name: ";
        getline(cin, cName);
        if(cName.size()==0){
            cout<<"\t\tCourse name can not be empty\n";
        }
        else{
            valid = true;
        }
    }
    return cName;
}

void updateStud(){
    string s = "You have requested to edit a student's \n\tinformation. Please Enter his/her ID.";
    slowTxt(s);
    string ID;
    bool valid = false;
    //cin.ignore();
    while(!valid){
        cout<<"\tStudent ID: ";
        cin>>ID;
        if(!exists(ID, "id",ID)){
            cout<<"\n\tNo student found holding ID: "<<ID<<endl;
        }
        else{
            valid = true;
        }
    }
    students *st = start, *toEdit;
    while(st!=NULL){
        if(st->ID==ID){
            toEdit = st;
            break;
        }
        st = st->next;
    }
    if(toEdit!=NULL){
        cout<<"\t[Note: You can Edit Student's Name, Phone] \n\t[Number, Email. You also can add or delete]\n\t[courses from Enrolled course list.]\n";
        int edit = true;
        while(edit){
            cout<<"\t===========================================\n";
            cout<<"\t[1] Edit Name"<<endl;
            cout<<"\t[2] Edit Phone Number"<<endl;
            cout<<"\t[3] Edit E-mail Address"<<endl;
            cout<<"\t[4] Add new course"<<endl;
            cout<<"\t[5] Delete a course"<<endl;
            cout<<"\t===========================================\n";
            cout<<"\tEnter your choise: ";
            int ope;
            cin>>ope;
            switch(ope){
                case 0:
                {
                    landing();
                }
                break;
                case 1:
                {
                    cin.ignore();
                    string name = scanName();
                    toEdit->name = name;
                }
                break;
                case 2:
                {
                    cin.ignore();
                    string phone = scanPhone();
                    toEdit->phone = phone;
                }
                break;
                case 3:
                {
                    cin.ignore();
                    string email = scanEmail();
                    toEdit->email = email;
                }
                break;
                case 4:
                {
                    cin.ignore();
                    string cCode = scanCCode();
                    if(toEdit->course.find(cCode)!=toEdit->course.end()){
                        cout<<"\n\tAlready Enrolled..."<<endl;
                    }
                    else{
                        string cName = scanCName();
                        toEdit->course[cCode] = cName;
                        cout<<"\tCourse added successfully...\n";
                        toEdit->courseNum++;
                    }
                }
                break;
                case 5:
                {
                    cin.ignore();
                    string cCode = scanCCode();
                    if(toEdit->course.find(cCode)==toEdit->course.end()){
                        cout<<"\n\t"<<toEdit->name<<" is not enrolled in this course."<<endl<<endl;
                    }
                    else{
                        toEdit->course.erase(cCode);
                        toEdit->courseNum--;
                    }
                }
                break;
                default:
                {
                    string invalid = "\n\tInvalid Choise...";
                    for(auto it : invalid){
                        cout<<it;
                        Sleep(20);
                    }
                    cout<<"\n\n";
                    Sleep(300);
                }
                break;
            }
            char x;
            cout<<"\n\tEdit anything else[y/n]: ";
            cin>>x;
            if(x=='n')
                edit = false;
        }
    }
}

void display(){
    /*MyFile stores Displaying data externally each time Display function is called*/
    ofstream MyFile("current_student_list.txt");
    string s = "Viewing All the Student Information: ";
    MyFile<<"\t"<<s<<endl;
    slowTxt(s);
    students *st = start;
    int p = 0;
    while(st!=NULL){
        p++;
        cout<<"\t\t        Student-"; if(p<10){cout<<"0";}cout<<p<<endl;
        cout<<"\t=============================================\n";
        cout<<"\tStudent ID: "<<st->ID<<endl;
        cout<<"\tName: "<<st->name<<endl;
        cout<<"\tPhone: "<<st->phone<<endl;
        cout<<"\tE-mail: "<<st->email<<endl;
        cout<<"\tEnrolled courses: "<<st->course.size()<<endl;

        MyFile<<"\t\t        Student-"; if(p<10){MyFile<<"0";}MyFile<<p<<endl;
        MyFile<<"\t=============================================\n";
        MyFile<<"\tStudent ID: "<<st->ID<<endl;
        MyFile<<"\tName: "<<st->name<<endl;
        MyFile<<"\tPhone: "<<st->phone<<endl;
        MyFile<<"\tE-mail: "<<st->email<<endl;
        MyFile<<"\tEnrolled courses: "<<st->course.size()<<endl;

        if(st->course.size()!=0){
            int c = 1; //course counter
            for(auto it : st->course){
                cout<<"\t\tCourse-";if(c<10){cout<<"0";}cout<<c<<": "<<endl;
                cout<<"\t\t\tCourse Name: "<<it.second<<endl;
                cout<<"\t\t\tCourse Code: "<<it.first<<endl;
                c++;

                MyFile<<"\t\tCourse-";if(c<10){MyFile<<"0";}MyFile<<c<<": "<<endl;
                MyFile<<"\t\t\tCourse Name: "<<it.second<<endl;
                MyFile<<"\t\t\tCourse Code: "<<it.first<<endl;
            }
        }
        cout<<"\t=============================================\n";
        MyFile<<"\t=============================================\n";
        st = st->next;
    }

    MyFile.close();
    returnlanding();
}

void slowTxt(string s){
    system("cls");
    cout<<"\n\n";
    cout<<"\t=============================================\n"; Sleep(10);
    cout<<"\n\t    Student Information Management System"<<endl<<endl; Sleep(10);
    cout<<"\t=============================================\n"; Sleep(10);
    cout<<"\n"<<endl;
    cout<<"\t";
    for(auto it : s){
        cout<<it;
        Sleep(20);
    }
    cout<<"\n\n";
}

void returnlanding(){
    cout<<"\n\tTo return Home[H]\n\tTo return to Main Menu[M]\n\tTo Close the Programme[0]\n\tEnter your choice: ";
    char x;
    cin>>x;
    if(x=='0'){
        exitProgram();
    }
    else if(x=='M' || x=='m'){
        menu();
    }
}

void exitProgram(){
    string thank = "Thank Your for using our service... We hope \n\tto see you soon.. Have a good day..";
    slowTxt(thank);
    Sleep(500);
    exit(0);
}

void deleteRandom(){
    string s = "You are about to delete an students \n\tinformation. Please enter his/her ID.\n";
    slowTxt(s);
    cout<<"\tEnter Student ID: ";
    string ID;
    cin>>ID;
    students *st = start, *prev = NULL;
    bool found = false;
    while(st!=NULL){
        if(st->ID==ID){
            found = true;
            break;
        }
        prev = st;
        st = st->next;
    }
    if(found==false){
        string noInfo = "There is no information of student holding ID ";
        noInfo+=ID;
        slowTxt(noInfo);
    }
    else{
        int x;
        cout<<"\n\tDo you really want to delete "<<ID<<"'s info?"<<endl;
        cout<<"\n\t[1] Confirm Deletion."<<endl;
        cout<<"\t[0] Cancel Deletion."<<endl;
        cout<<"\tYour choice: "; cin>>x;
        if(x==1){
            if(st == start){
                start = start->next;
            }
            else{
                prev->next = st->next;
            }
            //st->course.clear();
            //delete tmp;
            st->next = NULL;
            if(queEle==10){
                students *queTmp = queStart;
                queStart = queStart->next;
                delete queTmp;
                queEle--;
            }
            if(queEle==0){
                queStart = st;
                queEnd = st;
            }
            else{
                queEnd->next = st;
                queEnd = st;
            }
            queEle++;
            cout<<"\n\tInformation Moved to recycle bin."<<endl;
        }
        else{
            cout<<"\n\tDeletion cancelled."<<endl;
        }
    }
    returnlanding();
}

void deleteAll(){
    int x;
    cout<<"\n\tDo you really want to delete all Student's \n\tinformation?"<<endl;
    cout<<"\n\t[1] Confirm Deletion."<<endl;
    cout<<"\t[0] Cancel Deletion."<<endl;
    cout<<"\tYour choice: "; cin>>x;
    students *tmp,*ptr = start;
    if(x==1){
        while(start != NULL){
            tmp = start;
            start = start->next;
            tmp->next = NULL;
            if(queEle==10){
                students *queTmp = queStart;
                queStart = queStart->next;
                delete queTmp;
                queEle--;
            }
            if(queEle==0){
                queStart = tmp;
                queEnd = tmp;
            }
            else{
                queEnd->next = tmp;
                queEnd = tmp;
            }
            queEle++;
        }
        cout<<"\n\tAll Information Deleted Successfully!."<<endl;
    }
    else{
        cout<<"\n\tDeletion canceled."<<endl;
    }
    returnlanding();
}

void queDisplay(){
    cout<<"\n\tRecycle Bin: ";
    students *p = queStart;
    if(p!=NULL){
        cout<<p->ID; p = p->next;
        while(p!=NULL){
            cout<<", "<<p->ID;
            p = p->next;
        }
        cout<<endl;
    }
    else{
        cout<<"Empty!"<<endl;
    }
    returnlanding();
}

bool isValidName(const string & name){
    bool flag = true;
    for(char c : name){
        if(c >= 'A' && c <= 'Z'){
            flag = true;
        }
        else if(c >= 'a' && c <= 'z'){
            flag = true;
        }
        else if(c==' '){
            flag = true;
        }
        else{
            flag = false;
            break;
        }
    }
    return flag;
}

bool isValidPhone(const string & Phone){
    bool flag = true;
    for(char c : Phone){
        if(c >= '0' && c <= '9'){
            flag = true;
        }
        else{
            flag = false;
            break;
        }
    }
    return flag;
}

bool foundAtr(const string & s){
    for(char c : s){
        if (c == '@'){
            return true;
        }
    }
    return false;
}

void restore(){
    system("cls");
    string s = "You wanted to Restore Information of a \n\tStudent. Please Enter Information Below";
    slowTxt(s);

    //Displays Current Bin
    cout<<"\n\tRecycle Bin: ";
    students *pt = queStart;
    if(pt!=NULL){
        cout<<pt->ID; pt = pt->next;
        while(pt!=NULL){
            cout<<", "<<pt->ID;
            pt = pt->next;
        }
        cout<<endl;
    }
    if(queStart==NULL){
        cout<<"Empty!"<<endl;
        returnlanding();
    }
    else{
        bool found = false;
        string ID;
        students *p = queStart, *q = NULL;
        while(!found){
            p = queStart, q = NULL;
            cout << "\tStudent ID : ";
            cin >> ID;
            while(p != NULL){
                if(p->ID == ID){
                    found = true;
                    break;
                }
                q = p;
                p = p->next;
            }
            if(!found){
                cout<<"\n\tID is not in Recycle Bin."<<endl;
                cout<<"\tRestore another?(y/n): ";
                char x;
                cin>>x;
                if(x=='n'){
                    returnlanding();
                }
            }
        }
        students *tmp;
        if(p == queStart){
            tmp = queStart;
            queStart = queStart->next;
        }
        else{
            tmp = p;
            q->next = p->next;
        }
        p->next = NULL;

        //Adding Information to the main linked list which wants to restore
        students *ptr = start;
        if(start == NULL){
            tmp->next = NULL;
            start = tmp;
        }
        else{
            while(ptr->next != NULL){
                ptr = ptr->next;
            }
            ptr->next = tmp;
            tmp->next = NULL;
        }
        cout << "\n\tInformation Restored Successfully!" << endl;
        returnlanding();
    }
}

void slowDevTxt(string s){
    for(auto it : s){
        cout<<it;
        Sleep(5);
    }
}

void viewDevelopers(){
    string s = "Hello! Meet Our Team Member's";
    slowTxt(s);
    s = "\t1. Name: Md.Sanaullah Shovon\n\t   Student ID: 0242310005101082\n\t   Phone No. 01303091174\n\t   Mail ID: shovon23105101082@diu.edu.bd\n\n";
    slowDevTxt(s);
    s = "\t2. Name: Abdur Rahman\n\t   Student ID: 0242310005101413\n\t   Phone No. 01306661998\n\t   Mail ID: rahman23105101413@diu.edu.bd\n\n";
    slowDevTxt(s);
    s = "\t3. Name: Md.Tanvir Hasan\n\t   Student ID: 024231000510\n\t   Phone No. 01724757410\n\t   Mail ID: hasan23105101461@diu.edu.bd\n\n";
    slowDevTxt(s);
    s = "\t4. Name: Ummay Jubaiya Moushi\n\t   Student ID: 0242310005101887\n\t   Phone No. 01887173670\n\t   Mail ID: moushi2305101887@diu.edu.bd\n\n";
    slowDevTxt(s);
    s = "\t5. Name: Kazi Amir Hamza\n\t   Student ID: 0242310005101895\n\t   Phone No. 01990799148\n\t   Mail ID: hamza2305101895@diu.edu.bd\n\n";
    slowDevTxt(s);
    returnlanding();

}
