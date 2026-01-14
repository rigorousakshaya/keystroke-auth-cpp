#include<iostream>
#include<string>
#include<vector>
#include<chrono>
#include<cmath>
#include<fstream>
using namespace std;
using namespace chrono;
double similarity(vector<double>a,vector<double>b){
    double diff=0;
     for(int i=0;i<a.size();i++){
            diff+=abs(a[i]-b[i]);
    }
    if(a.size()==0) return 999;
    return diff/a.size();
}
vector<double> recordpattern(string &pass){
    vector<double> t;
    char ch;
    auto start=high_resolution_clock::now();
    while((ch=getchar())!='\n'){
        auto now=high_resolution_clock::now();
       double gap= duration<double>(now-start).count();
       t.push_back(gap);
       start=now;
       if(ch!='\n')
       pass.push_back(ch);
    }
    return t;
}
void registeruser(){
    string user,pass;
    vector<double>timing;
    cout<<"enter user name:\n";
    cin>>user;
    cin.ignore();
    cout<<"enter password";
    timing=recordpattern(pass);
    ofstream f("database.txt");
    f<<user<<endl;
    f<<pass<<endl;
    for(double x:timing){
        f<<x<<" ";
    }
    f.close();
    cout<<"registration completed successfully!\n";
}
void storemarks(){
    string marks;
    cin.ignore();
    cout<<"enter your marks:(enter end to stop)";
   
    ofstream f("secure.txt",ios::app);
    while(true){
         getline(cin,marks);
         if(marks=="end")
         break;
         f<<marks<<endl;
    }
        
    f.close();
    cout<<"marks stored successfully\n";
}
void viewmarks(){
    string data;
    ifstream f("secure.txt");
    cout<<"Your stored marks\n";
    while(getline(f,data)){
        cout<<data<<endl;
    }
    f.close();
}
void securemenu(){
    int ch;
    do{
        cout << "\n--- SECURE DASHBOARD ---";
        cout << "\n1. Store Marks";
        cout << "\n2. View Marks";
        cout << "\n3. Logout";
        cout << "\nChoice: ";
        cin >> ch;

        if(ch==1){
            storemarks();
        }
        else if(ch==2){
            viewmarks();
        }
    }while(ch!=3);
}
void login(){
    string user,pass;
    string saveduser,savedpass;
    vector<double>savedtiming,inputtiming;
    double x;
    ifstream f("database.txt");
    f>>saveduser;
    f>>savedpass;
    while(f>>x){
        savedtiming.push_back(x);
    }
    f.close();
    cout<<"enter user name:\n";
    cin>>user;

    cin.ignore();
    cout<<"enter password\n";
    inputtiming=recordpattern(pass);
    if(saveduser!=user || savedpass!=pass){
        cout<<"Invalid username or password\n";
        return;
    }
    double diff=similarity(savedtiming,inputtiming);
    if(diff<0.3){
        cout<<"\n access granted to user\n";
        securemenu();
    }
    else{
        cout<<"typing pattern mismatch(suspected hacker)";
    }

}
int main(){
    int ch;
    cout<<"1.register 2.login\n Enter your choice";
    cin>>ch;
    if(ch==1){
        registeruser();
    }
    else if(ch==2){
        login();
    }
}