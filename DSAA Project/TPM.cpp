#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<stdlib.h>
#include<iomanip>
#include<sstream>

using namespace std;
class Student{
	public:
		string StudentName;
		int marks,attendence;
		int roll_no,enrollment_no;
	public:
		Student (){
			marks=0;
			attendence=0;
			
		}
		Student(Student &obj){
			obj.enrollment_no=enrollment_no;
			obj.roll_no=roll_no;
			obj.StudentName=StudentName;
			obj.marks=marks;
			obj.attendence=attendence;
		}
		void setData(string s1){
			
			string record[5];
			string word;
			stringstream s(s1);
			short i=0;
			while (getline(s, word, ',')) {
            	record[i]=word;
            	i++;
        	}
        	StudentName=record[0];
        	roll_no=stoi(record[1]);
        	enrollment_no=stoi(record[2]);
        	marks=stoi(record[3]);
        	attendence=stoi(record[4]);
		}
		
		void getStudentData(){
			cout<<"Enter Student name :";cin>>StudentName;
			cout<<"Enter Roll no. of Student";cin>>roll_no;
			cout<<"Enter Enrollment no. of Student";cin>>enrollment_no;
		}
		void CheckStudentData(){
			system("cls");
			cout<<"\n\n\n";
			cout<<"====================// Student Details \\\\=================="<<endl;
			cout<<"Student name              :"<<StudentName<<endl;
			cout<<"Roll no. of Student       :"<<roll_no<<endl;
			cout<<"Enrollment no. of Student :"<<enrollment_no<<endl;
			cout<<"Attendence                :"<<attendence<<"%"<<endl;
			cout<<"Marks                     :"<<marks<<endl;
			cout<<"\n\n";
			int choice;
			cout<<"press<1> To change marks"<<endl;
			cout<<"press<2> To change attendence"<<endl;
			cout<<"press<3> To return"<<endl;
			cout<<"Enter your Choice (Enter Number with no spaces) : ";cin>>choice;
			if(choice==1){
				changeMarks();
			}
			if(choice==2){
				changeAttendence();
			}
			return;
			
		}
		void changeMarks(){
			int newmarks;
			cout<<"Enter new Marks";cin>>newmarks;
			marks=newmarks;
			CheckStudentData();
		}
		void changeAttendence(){
			int a;
			cout<<"Enter new Attendence (in percentage) :";cin>>a;
			attendence=a;
			CheckStudentData();
		}
};


class Classroom{
	public:
		Student* classStudent;
		string subjectName,year;
		string courseCode,dept;
		char section;
		string classId;
		int capacity;
		
	public:
		Classroom(){
			classStudent = new Student[50];
			capacity=0;
		}
		void setData(string s1){
			string record[6];
			string word;
			stringstream s(s1);
			short i=0;
			while (getline(s, word, ',')) {
            	record[i]=word;
            	i++;
        	}
        	classId=record[0];
        	subjectName=record[1];
        	year=record[2];
        	courseCode=record[3];
        	dept=record[4];
        	section=char(record[5][0]);
        	
        	fstream fin;
    		fin.open(record[0]+".csv", ios::in);
    		string line;
    		if (fin.peek() == EOF){
				return;
			}
  			i=0;
    		while (fin.peek() != EOF) {
  
        	// read an entire row and
        	// store it in a string variable 'line'
        	fin>>line;
        	classStudent[i].setData(line);
        	capacity++;
        	i++;
			}
			capacity--;
			
			fin.close();
		}
		void getData(){
			string SN,CC,D,y;
			char S;
			string id;
			cout<<"Enter the Subject name: ";cin>>SN;
			subjectName=SN;
			cout<<"Enter the Course code: ";cin>>CC;
			courseCode=CC;
			cout<<"Enter the section:";cin>>S;
			section=S;
			cout<<"Enter the Dept. Name:";cin>>D;
			dept=D;
			cout<<"Enter Classroom ID:";cin>>id;
			classId=id;
			cout<<"Enter year of Study:";cin>>y;
			year=y;

		}
		
		void CheckClassRoomData(){
			system("cls");
			cout<<"\n\n\n";
			cout<<"==================// Classroom details \\\\====================="<<endl;
			cout<<"\n\n\n";
			cout<<"Class name          :"<<subjectName<<endl;
			cout<<"Course code         :"<<courseCode<<endl;
			cout<<"Enter the Dept.Name :"<<dept<<endl;
			cout<<"Section             :"<<section<<endl;
			cout<<"Class Room id       :"<<classId<<endl;
			cout<<"Students in Class   :"<<capacity<<endl;
			cout<<"\n\n";
			int choice;
			cout<<"press<1> To Add student in class"<<endl;
			cout<<"press<2> To Remove student from class "<<endl;
			cout<<"press<3> To view all the students in class"<<endl;
			cout<<"press<4> To search an student of class"<<endl;
			cout<<"press<5> To return"<<endl;
			cout<<"Enter your Choice (Enter Number with no spaces) : ";cin>>choice;
			if(choice==1){
				addStudent();
			}
			if(choice==2){
				removeStudentFromName();
			}
			if(choice==3){
				printAllClassDetail();
			}
			if(choice==4){
				searchAnyStudentByName();
			}
			return;
		}
		
		void addStudent(){
			if (capacity==50){
				cout<<"Class is AlreadyFull you can't add more student";
				CheckClassRoomData();
			}
			Student s1;
			s1.getStudentData();
			classStudent[capacity]=s1;
			capacity++;
			
			string filename= classId+".csv";
			string record=s1.StudentName+","+to_string(s1.roll_no)+","+to_string(s1.enrollment_no)+","+to_string(s1.marks)+","+to_string(s1.attendence);
			ofstream csvFile(filename, ios::app);
  			csvFile<< record<<endl ;
  			csvFile.close(); 
  			CheckClassRoomData();
		}
		void removeStudentFromName(){
			string name;
			cout<<"Enter the Name of Student to find";cin>>name;
			int i;
			for(i=0;i<capacity;i++){
				if(classStudent[i].StudentName==name){
					for(int j=i;j<capacity-1;j++){
						classStudent[j]=classStudent[j+1];
					}
					break;
				}
			}
			capacity--;
			
			string filename= classId+".csv";
			ofstream csvFileOut(filename);
  			for (i=0;i<capacity;i++){
  			string record=classStudent[i].StudentName+","+to_string(classStudent[i].roll_no)+","+to_string(classStudent[i].enrollment_no)+","+to_string(classStudent[i].marks)+","+to_string(classStudent[i].attendence);
    		csvFileOut << record << endl;
  			}
  			csvFileOut.close();
			CheckClassRoomData();
		}
		void printAllClassDetail(){
			system("cls");
			
			cout<<"//=====================class Detail=================\\\\\n\n\n"<<endl;
			
			cout<<"Enrollment-no"<<setw(4)<<"||"<<"Name"<<setw(16)<<"||"<<"Roll-no"<<setw(5)<<"||"<<"Attendence(%)"<<"||"<<setw(3)<<"Marks"<<endl;
			for(int i=0;i<capacity;i++){
				cout<<classStudent[i].enrollment_no<<setw(13)<<"||"<<classStudent[i].StudentName<<setw(20-classStudent[i].StudentName.size())<<"||"<<classStudent[i].roll_no<<setw(10)<<"||"<<classStudent[i].attendence<<setw(13)<<"||"<<classStudent[i].marks<<endl;	
			}
		}
		void searchAnyStudentByName(){
			string name;
			cout<<"Enter the Name of Student to find: ";cin>>name;
			int i;
			for(i=0;i<capacity;i++){
				if(classStudent[i].StudentName==name){
					classStudent[i].CheckStudentData();
					break;
				}
			}
			
			
			string filename=classId+".csv";
			ofstream csvFileOut(filename);
  			for (i=0;i<capacity;i++){
  			string record=classStudent[i].StudentName+","+to_string(classStudent[i].roll_no)+","+to_string(classStudent[i].enrollment_no)+","+to_string(classStudent[i].marks)+","+to_string(classStudent[i].attendence);
    		csvFileOut << record << endl;
  			}
  			csvFileOut.close();
		}
			
};



struct node {
        int time;
        string class_;
        node* left;
        node* right;
    };
class Schedule {
public:
    node* root;
    node* Add_Class(int time, node* t,string class_)
    {
        if(t == NULL)
        {
            t = new node;
            t->time = time;
            t->class_ = class_;
            t->left = t->right = NULL;
        }
        else if(time < t->time)
            t->left = Add_Class(time, t->left,class_);
        else if(time > t->time)
            t->right = Add_Class(time, t->right,class_);
        return t;
    }

    node* Find_ClassMin(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->left == NULL)
            return t;
        else
            return Find_ClassMin(t->left);
    }
    node* Remove_Class(int time, node* t,string class_) {
        node* temp;
        if(t == NULL)
            return NULL;
        else if(time < t->time)
            t->left = Remove_Class(time, t->left, class_);
        else if(time > t->time)
            t->right = Remove_Class(time, t->right,class_);
        else if(t->left && t->right)
        {
            temp = Find_ClassMin(t->right);
            t->time = temp->time;
            t->class_ = temp->class_;
            t->right = Remove_Class(t->time, t->right, class_);
        }
        else
        {
            temp = t;
            if(t->left == NULL)
                t = t->right;
            else if(t->right == NULL)
                t = t->left;
            delete temp;
        }

        return t;
    }

    void Get_List(node* t) {
        if(t == NULL)
            return;
        Get_List(t->left);
        cout << t->time << ":00 :  " << t->class_ << endl;
        Get_List(t->right);
    }

    node* Find_Class(node* t, int time) {
        if(t == NULL)
            return NULL;
        else if(time < t->time)
            return Find_Class(t->left, time);
        else if(time > t->time)
            return Find_Class(t->right, time);
        else
            return t;
    }

public:
    Schedule() {
        root = NULL;
    }
    void Add_Class(int time,string class_) {
        root = Add_Class(time, root, class_);
    }

    void Remove_Class(int time,string class_) {
        root = Remove_Class(time, root,class_);
    }

    void Class_list() {
        Get_List(root);
        cout << endl;
    }

    void find_class(int time) {
        root = Find_Class(root, time);
        if(root==NULL){
            cout << "no class is scheduled at this time";
        }
        else{
        cout << root->time << ":00 " << root->class_;
        }
    }
};

//int main() {
//    Schedule t;
//    t.Add_Class(8,"math");
//    t.Add_Class(9,"english");
//    t.Add_Class(10,"urdu");
//    t.Add_Class(11, "dsa");
//    t.Add_Class(12, "physics");
//    t.Class_list();
//    t.Remove_Class(8,"math");
//    t.Class_list();
//    t.find_class(8);
////    t.Remove_Class(25);
////    t.Class_list();
////    t.Remove_Class(30);
////    t.Class_list();
//    return 0;
//}

class ClassroomNode{
	public:
		Classroom data;
		ClassroomNode* next;
	public:
		ClassroomNode(){
		}
		ClassroomNode(ClassroomNode &obj){
			data=obj.data;
			next=obj.next;
		}
		ClassroomNode(Classroom class1){
			data=class1;
			next=NULL;
		}
		ClassroomNode(string s1){
			data.setData(s1);
			next=NULL;
		}
		
};


class Teacher{
	public:
		string teacherName, email,password;
		ClassroomNode* head;
		ClassroomNode* tail;
		Schedule s;
	public:
		Teacher(){
			head=NULL;
			tail=NULL;
		}
		void setData(string s1){
			string record[3];
			stringstream s(s1);
			string word;
			short i=0;
			while (getline(s, word, ',')) {
            	record[i]=word;
            	i++;
        	}
        	
        	teacherName=record[0];
        	email=record[1];
        	password=record[2];

        	
        	fstream fin;
    		fin.open(record[0]+"classrooms.csv", ios::in);

			if (fin.peek() == EOF){
				return;
			}
    		string line;
  			i=0;
    		while (!fin.eof()) {
  
	        		// read an entire row and
	        		// store it in a string variable 'line'
		        	fin>>line;
		        	ClassroomNode* c1=new ClassroomNode(line);
		        	if(head==NULL){
		        		head=tail=c1;
					}
					else{
						tail->next=c1;
						tail=tail->next;
						
					}
	        		i++;
				}
			
		}
		void DisplayTeacherPortal(){
			system("cls");
			cout<<"\n\n\n";
			cout<<"-------------------------// Teacher Portal \\\\-----------------------"<<endl;
			cout<<"Teacher name :"<<teacherName<<endl;

			cout<<"\n\n";
			int choice;
			cout<<"press<1> To create new class"<<endl;
			cout<<"press<2> To remove a existing class "<<endl;
			cout<<"press<3> To view all the classes detail"<<endl;
			cout<<"press<4> To search for any class details"<<endl;
			cout<<"press<5> To schedule any class "<<endl;
			cout<<"press<6> To see the schedule of classes"<<endl;
			cout<<"press<7> To remove any class from shedule"<<endl;
			cout<<"press<8> To search for any class from schedule"<<endl;
			cout<<"press<9> To return"<<endl;
			cout<<"Enter your Choice(Enter Number with no spaces) : ";cin>>choice;
			if(choice==1){
				createNewClassRoom();
				DisplayTeacherPortal();
			}
			if(choice==2){
				removeClassroomById();
				DisplayTeacherPortal();
			}
			if(choice==3){
				viewAllClassRoomsDetail();
			}
			if(choice==4){
				selectClassroomDetail();
			}
			if(choice==5){
				int t;
				cout<<"Enter the time:";
				cin>>t;
				cout<<"Enter the class name:";
				string c;
				cin>>c;
				cout<<"\n\n";
				s.Add_Class(t,c);
				DisplayTeacherPortal();
				
			}
			if(choice==6){
				s.Class_list();
				int choice;
				cout<<"Enter any number to go back:";cin>>choice;
				DisplayTeacherPortal();
			}
			if(choice==7){
				int t;
				cout<<"Enter the time:";
				cin>>t;
				cout<<"Enter the class name:";
				string c;
				cin>>c;
				s.Remove_Class(t,c);
				DisplayTeacherPortal();
			}
			if(choice==8){
				int t;
				cout<<"Enter the time:";
				cin>>t;
				s.find_class(t);
				DisplayTeacherPortal();
			}
		
			return;
			
		}
		void createNewClassRoom(){
			system("cls");
			cout<<"Creating classroom.................\n\n\n";
			Classroom c1;
			c1.getData();
			ClassroomNode* newClass= new ClassroomNode(c1);
			if(head==NULL){
				head==newClass;
			}
			else{
			
				ClassroomNode* temp=head;
				while(temp->next!=NULL){
					temp=temp->next;
				}
				temp->next=newClass;
			}
			string filename= teacherName+"classrooms.csv";
			string record=c1.classId+","+c1.subjectName+","+c1.year+","+c1.courseCode+","+c1.dept+","+c1.section;
			ofstream csvFile(filename, ios::app);
  			csvFile<< record<<endl ;
  			csvFile.close(); 
  			
  			ofstream file;
  			file.open(c1.classId+".csv");
  			file.close();
			
		}
		
		void removeClassroomById(){
			system("cls");
			cout<<"Removing class...................\n\n";
			string key;
			cout<<"Enter class ID :";cin>>key;
			string x =key +".csv";
			if( remove( x.c_str()) != 0 )
    			perror( "Error deleting file" );
  			else
    			puts( "File successfully deleted" );
			
    		ClassroomNode* temp = head;
    		ClassroomNode* prev = NULL;
    		if (temp != NULL && temp->data.classId == key) {
    			
        		head = temp->next;
        		delete temp;
        		return;
    		}
 
    		else {
        		while (temp != NULL && temp->data.classId != key) {
            		prev = temp;
            		temp = temp->next;
        		}
        	
        		if (temp == NULL)
            	return;
            
        		prev->next = temp->next;
        		delete temp;
			}
			
			temp =head;
			string filename= teacherName+"classrooms.csv";
			ofstream csvFileOut(filename);
  			while(temp!=NULL){
			  
  				string record=temp->data.classId+","+temp->data.subjectName+","+temp->data.year+","+temp->data.courseCode+","+temp->data.dept+","+temp->data.section;
    			csvFileOut << record << endl;
    			temp=temp->next;
  			}
  			csvFileOut.close();
			
			DisplayTeacherPortal();
		}
		
		void viewAllClassRoomsDetail(){	
			system("cls");
			cout<<"//======================(Classrooms)=================\\\\\n\n\n";
			ClassroomNode* temp = head;
			cout<<"SubjectName"<<setw(29)<<"||"<<"CourseCode"<<setw(3)<<"||"<<"Department"<<setw(3)<<"||"<<"section"<<setw(6)<<"||"<<"classID"<<endl;
			while(temp!=NULL){
				Classroom data=temp->data;
				cout<<data.subjectName<<setw(40-data.subjectName.size())<<"||"<<data.courseCode<<setw(13-data.courseCode.size())<<"||"<<data.dept<<setw(13-data.dept.size())<<"||"<<data.section<<setw(12)<<"||"<<data.classId<<endl;
				temp=temp->next;
			}
		}
		void selectClassroomDetail(){
			system("cls");
			cout<<"Searching of class.......\n\n"<<endl;
			string id;
			cout<<"Enter Class Id: ";
			cin>>id;
			ClassroomNode* temp = head;
			while(temp!=NULL){
				if(temp->data.classId==id){
					temp->data.CheckClassRoomData();
					break;
				}
				
				temp=temp->next;
			}
		}
		
	
};




class teacherNode{
	public:
		Teacher data;
		teacherNode* next;
	public:
		teacherNode(Teacher t1){
			data=t1;
			next=NULL;
		}
		teacherNode(string s1){
			data.setData(s1);
			next=NULL;
		}
};


class Login{
	public:
		string email,password;
		teacherNode* head;
		teacherNode* tail;
	public:
		
		Login(){
			head==NULL;
			tail==NULL;
		}
		
		void gettingDataFromCSV(){
			fstream fin;
    		fin.open("teacher.csv", ios::in);
    		string line, temp;
  			int i=0;
    		while (!fin.eof()) {
  			
 			fin>>line;	
        	teacherNode* t1=new teacherNode(line)  ;
        	if(head==NULL){
        		head=tail=t1;
			}
			else{
				tail->next=t1;
				tail=tail->next;
			}
        	i++;
			}
		
		}
		
		void TeacherLogin(){
			bool checkLogin = true;
			system("cls");
			cout<<"\n"<<endl;
			cout<<"------------------------------// TEACHER LOGIN \\\\-----------------------------"<<"\n\n\n"<<endl;

			cout<<"\nEnter Email(correct no spaces): ";
			cin>>email;
			cout<<"\nEnter Password(no spaces): ";
			cin>>password;
			teacherNode* temp=head;
			while(temp!=NULL){
				if (email == temp->data.email){
					if (password == temp->data.password){
						temp->data.DisplayTeacherPortal();
							checkLogin=true;	
						break;
					}
				}
				
			else{
				checkLogin=false;
			}
				temp=temp->next;
			}
			!checkLogin && cout << "enter correct email";
		
		}
		
		void TeacherSignUp(){
			string n,e,p;
			cout<<"Enter the email: ";
			cin>>e;
			cout<<"Enter the password: ";
			cin>>p;
			cout<<"Enter Name: ";
			cin>>n;
			string filename= "teacher.csv";
			string record=n+","+e+","+p;
			ofstream csvFile(filename, ios::app);
  			csvFile<< record<<endl ;
  			csvFile.close(); 
  			
  			ofstream file;
  			file.open(n+"classrooms.csv");
  			file.close();
			
		}
};

class TeacherPlannerManager{
	public:
	Login l1;
	public:
		void menu(){
			system("cls");
			int choice;
			cout<<"\n\n\n-------------------------//-WELCOME TO TEACHER MANAGER-\\\\--------------------\n\n\n\n"<<endl;
			l1.gettingDataFromCSV();
			cout<<"-----||press<1> (To LOGIN)"<<endl;
			cout<<"-----||press<2> (To SIGN UP) " <<endl;
			cout<<"-----||press<3> (To EXIT) \n\n" <<endl;
			cout<<"-----||Enter your choice(In order to get correct result give correct input in number ): ";cin>>choice;	
			if(choice==1){
				l1.TeacherLogin();
			}
			else if(choice==2){
				l1.TeacherSignUp();
				cout<<"Sucessfully Signed Up"<<endl;
				cout<<"press<1> to go to main menu"<<endl;
				int choice1;cin>>choice1;if(choice1==1)menu();
			}
			else if(choice==3){
				exit(0) ;
			}
			return;
		}
};

int main(){
	TeacherPlannerManager a;
	a.menu();
    
	return 0;
}
