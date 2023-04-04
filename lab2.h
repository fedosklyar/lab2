#include<iostream>
#include<fstream>
#include<cstring>
#include<string>

using namespace std;

string create_file();
int fill_the_file(string name);
void get_info_from_file(string name);
int time_to_minutes(int hours, int minutes);
bool check_time(int hours, int minutes, string name, int quantity);
bool check_start_and_end (int start_hours, int start_minutes, int end_hours, int end_minutes, string name, int quan);
void count_intervals(string name, int &am, int &pm, int quantity);
char create_user(char *name, int &start_hours, int &start_minutes, int &end_hours, int &end_minutes, int i, string name_of_file);
void file_append(string name_of_file, int &quan);