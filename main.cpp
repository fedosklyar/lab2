#include "lab2.h"



int main(){
    string name_of_file;
    int quantity_of_users, intervals_am = 0, intervals_pm = 0;
    char app;

    name_of_file = create_file();
    quantity_of_users = fill_the_file(name_of_file);
    get_info_from_file(name_of_file);
    count_intervals(name_of_file, intervals_am, intervals_pm, quantity_of_users) ;
    cout<<"\n==Do you want to append the file? (Y - yes, N - no) --> ";
    cin>>app;
    if((tolower(app) != 'n')){
         intervals_am = 0, intervals_pm = 0;
         file_append(name_of_file, quantity_of_users);
         get_info_from_file(name_of_file);
         count_intervals(name_of_file, intervals_am, intervals_pm, quantity_of_users);
        }
    getchar();
    getchar();

    return 0;
}