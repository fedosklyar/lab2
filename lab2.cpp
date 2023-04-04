#include "lab2.h"

struct time
{
    int start_hours;
    int start_minutes;
    int end_hours;
    int end_minutes;
};

struct clients
{
    char name[100];
    time session;
};

string create_file(){
    string name;
    cout<<"Enter the name of file: ";
    getline(cin, name);
    name += ".dat";

    ofstream FILE (name, ios::binary);
    FILE.close();
    return name;
}


int fill_the_file(string name_of_file){
    int quantity, hours, minutes;
    string num;
    int i = 0, quan = 0;
    clients user;
    int size;
    bool check1, check2, check_start_end;
    char pick;

    
    do{
        pick = create_user(user.name, user.session.start_hours, user.session.start_minutes, user.session.end_hours, user.session.end_minutes, i, name_of_file);
        i++;
    }while(tolower(pick) != 'n');
    return i;

}

void get_info_from_file(string name){
    ifstream inFile(name, ios::binary);

    clients user;
    cout<<"\n\n==========The list of clients==========\n";
    while(inFile.read((char*) &user, sizeof(clients))) {
        cout<<"\n";
        cout<<user.name; user.session.start_hours < 10? cout<<"0" : cout<<""; cout<< user.session.start_hours<<":";
        user.session.start_minutes < 10 ? cout<<"0" : cout<<""; cout<< user.session.start_minutes<<" -- ";
        user.session.end_hours < 10 ? cout<<"0" : cout<<""; cout<<user.session.end_hours<<":";
        user.session.end_minutes < 10 ? cout<<"0" : cout<<""; cout<<user.session.end_minutes;
    }
    inFile.close();
}



int time_to_minutes(int hours, int minutes){
    int time = hours * 60 + minutes;
    return time;
}

bool check_time(int hours, int minutes, string name, int quantity){
    clients user[quantity + 1];
    ifstream fromFile(name, ios::binary);
    int curr_start_time, curr_finish_time, compare, i = 0;
    bool flag = true; //ця змінна щоб витягувати проміжки з файлу й потім порівнювати

    compare = time_to_minutes(hours, minutes);
    if(compare > 1020 || compare  < 540) {
        if(compare  < 540) cout<<"\n======Sorry, but the manager starts working at 9 a.m======\nPlease, try again:\n"<<endl;
        else cout<<"======Sorry, but the manager finishes working at 5 p.m======\nPlease, try again:\n"<<endl;
        flag = false;
        return flag;
    }

    else {

    while(fromFile.read((char*) &user[i], sizeof(clients))){
        curr_start_time = time_to_minutes(user[i].session.start_hours, user[i].session.start_minutes);      
        curr_finish_time = time_to_minutes(user[i].session.end_hours, user[i].session.end_minutes);         
        compare = time_to_minutes(hours, minutes);                                                          
        if ((compare >= curr_start_time && compare <= curr_finish_time) || (curr_start_time >= compare && curr_finish_time <= compare)){
            cout<<"\n======Sorry, but this time is already taken======\nPlease, try again:\n"<<endl;          
            flag = false;
            break;
        }
        i++; 
    }
    fromFile.close();
    return flag;
    }
}

bool check_start_and_end (int start_hours, int start_minutes, int end_hours, int end_minutes, string name, int quan){
    bool flag = true;
    clients user[quan];
    int start = time_to_minutes(start_hours, start_minutes);           
    int end = time_to_minutes(end_hours, end_minutes);       
    int i = 0, curr_start_time, curr_finish_time;
    if(start >= end){
        cout<<"======Sorry, the end of the session can`t be beforehand the the start of it======\n\nPlease, try again: "<<endl;
        flag = false;
    }

    ifstream fromFile(name, ios::binary);
    while(fromFile.read((char*) &user[i], sizeof(clients))){
        curr_start_time = time_to_minutes(user[i].session.start_hours, user[i].session.start_minutes);      
        curr_finish_time = time_to_minutes(user[i].session.end_hours, user[i].session.end_minutes);      
        if(start <= curr_start_time && end >= curr_finish_time){
            cout<<"\n======Sorry, but this time is already taken======\nPlease, try again:\n"<<endl;
            flag = false;
        } 
    }
    fromFile.close();
    return flag;
}


void count_intervals(string name, int &am, int &pm, int quantity){
    ifstream fromFile(name, ios::binary);
    int start {}, end {}, prev_end {}, prev_start{}, pos;
    clients user, users[quantity], temp;

    for(int i = 0; i < quantity; i++) fromFile.read((char*) &users[i], sizeof(clients));
    fromFile.close();
    for(int i = 0; i < quantity; i++) cout<<users[i].session.start_hours<<":"<<users[i].session.start_minutes<<"   "<<users[i].session.end_hours<<":"<<users[i].session.end_minutes<<endl;

    for(int i = 1; i < quantity; i++){
        temp = users[i];
        int j = i - 1;
        while(j >= 0 && time_to_minutes(users[j].session.start_hours, users[j].session.start_minutes) > time_to_minutes(temp.session.start_hours, temp.session.start_minutes)){
            users[j + 1] = users[j] ;
            j--;
        }
        users[j + 1] = temp;
    }

    for(int i = 0; i < quantity; i++) {
        cout<<"\n";
        cout<<users[i].name; users[i].session.start_hours < 10? cout<<"0" : cout<<""; cout<< users[i].session.start_hours<<":";
        users[i].session.start_minutes < 10 ? cout<<"0" : cout<<""; cout<< users[i].session.start_minutes<<" -- ";
        users[i].session.end_hours < 10 ? cout<<"0" : cout<<""; cout<<users[i].session.end_hours<<":";
        users[i].session.end_minutes < 10 ? cout<<"0" : cout<<""; cout<<users[i].session.end_minutes;
    } 

    for(int i = 0; i < quantity; i++){
        //cout<<"\n\nPochav Chitaty"<<endl;
        //cout<<"Time start  "<<users[i].session.start_hours<<"  "<<users[i].session.start_minutes<<endl;
        start = time_to_minutes(users[i].session.start_hours, users[i].session.start_minutes);
        end = time_to_minutes(users[i].session.end_hours, users[i].session.end_minutes);
        //cout<<"\nStart = "<<start<<endl;
        //cout<<"\nEnd = "<<end<<endl;
        if(start > 540 && start < 720) am++;
        if(start >= 720 && start < 1020 && end > 720 && end < 1020)pm++;
        if(start > 720 && prev_end < 720){ //ось це цікаве, хмммм
            am++;
            pm++;
        }
        if(start < 720 && end > 720 && end < 1020) pm++;
        prev_end = end;
        }

    cout<<"\n=== Intervals for leisure before noon --> "<<am<<endl;
    cout<<"=== Intervals for leisure after noon --> "<<pm<<endl;
}

void file_append(string name_of_file, int &quan){
    clients user;
    string num;
    char check1, check2, check_start_end, pick;

    do{
        pick = create_user(user.name, user.session.start_hours, user.session.start_minutes, user.session.end_hours, user.session.end_minutes, quan, name_of_file);
        quan++;
    }while(tolower(pick) != 'n');
}

char create_user(char *name, int &start_hours, int &start_minutes, int &end_hours, int &end_minutes, int i, string name_of_file){
    clients user;
    string num;
    char check1, check2, check_start_end, pick;


    cin.ignore();
        cout<<"Enter the name of "<< i + 1 <<" client :";
        fgets(user.name, 100, stdin);
        cout<<"NAme --> "<<user.name<<endl;

       do{
        do{cout<<"Enter the time of the start of the session (in format hh:mm) : ";
        getline(cin, num, ':');
        user.session.start_hours = stoi(num);
        getline(cin, num);
        user.session.start_minutes = stoi(num);
        check1 = check_time(user.session.start_hours, user.session.start_minutes, name_of_file, i);
        }while(!check1);

        do{cout<<"Enter the time of the end of the session (in format hh:mm) : ";
        getline(cin, num, ':');
        user.session.end_hours = stoi(num);
        getline(cin, num);
        user.session.end_minutes = stoi(num);
        check2 = check_time(user.session.end_hours, user.session.end_minutes, name_of_file, i);
        }while(!check2);
        check_start_end = check_start_and_end (user.session.start_hours, user.session.start_minutes, user.session.end_hours, user.session.end_minutes, name_of_file, i);
       }while(!check_start_end);

        ofstream outFile (name_of_file, ios::binary | ios::app);
            outFile.write((char*)&user, sizeof(clients));
            outFile.close();
            i++;
            cin.ignore();
            cout<<"Do you want to enter another client? (Y - yes, N - no) --> ";
            cin>>pick;
        
        return pick;
}