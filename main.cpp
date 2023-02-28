#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <conio.h>
#include <vector>

#include <ctime>

using namespace std;

void order_history(long long ph)
//this method takes a phone number as input and displays all the orders of this particular user 

{

    stringstream stream;
    stream << ph;
    string num;

    num = stream.str();
    string phone;
    string nm;
    string rest;

    
    ifstream f;
    f.open("order.csv");
    
    cout << "DISPLAYING ORDER HISTORY " << endl;
    while (f.good())
    {

        getline(f, nm, ',');
        getline(f, phone, ',');
        getline(f, rest, ',');
        

        string order_name;
        string bill;
        if (num.compare(phone) == 0)
        {

            cout << "RESTAURENT"
                 << ":" << rest << endl;
            cout << "items ordered :";
            getline(f, order_name, ',');
            cout << order_name << endl;
            getline(f, bill, ',');
            cout << "total bill" << bill << endl;
            cout << "==================================================" << endl;
        }
    }
    f.close();
}

float generate_bill(string arr[], string name, int size)
// this method takes three inputs form the user
// 1-an array consisting of all the items ordered by the user 
// 2-name of the restaurant
// 3-size of the array
// it then takes the price of all the items ordered by the user from the csv file of that particular restaurant and genertaes the total bill 
{

    float bill;
    bill = 0;
    string item;
    string price;
   
    for (int i = 0; i < size; i++)
    {

        
        string food_name;
        food_name = arr[i];
        ifstream fout;
        fout.open(name + ".csv");
        while (fout.good())
        {
    

            getline(fout, item, ',');
            getline(fout, price, '\n');
           
            if (item.compare(food_name) == 0)
            {
                

                bill = bill + stof(price);
            }
        }
    }
    return bill;
}
string select_restaurent()
{
    // this method displays the list of all the restaurants and returns the restaurant selected by the user to plac_order method
    string res_name;
    ifstream fout;
    cout << "SELECT A RESTAURENT FORM THE LIST" << endl;
    fout.open("restaurents.csv");
    
    while (fout.good())

    {

        string line;
        getline(fout, line);
        cout << line << endl;
    }

    cin >> res_name;
    ifstream ff;
    ff.open("order.csv");
    string nm;
    string ph;
    string rest;
    string order;
    string bill;
    string status;
    int ctr;
    ctr = 0;
    while (ff.good())
    {
        
        getline(ff, nm, ',');
        getline(ff, ph, ',');
        getline(ff, rest, ',');
        getline(ff, order, ',');
        getline(ff, bill, ',');
        getline(ff, status, '\n');

        if (res_name.compare(rest) == 0 && status.compare("LIVE") == 0)

            ctr++;
    }
    if (ctr > 10)
    {

        return "NULL";
    }

    return res_name;
}
void place_order(long long ph, string name)
{
    // this method takes 2 inputs
    // 1-phone number
    // 2-user name 
    // the user is asked to select a restaurant and the n enetr the number of items he/she has to order 
    // the user is then asked to enter the items 
    // all the details entered by the user is stored in order.csv file
    // then finally by callin generate_bill method the bill is displayed
    int size;
    string rest_name = select_restaurent();
    if (rest_name.compare("NULL") == 0)
    {
        cout << "SORRY !!! THIS RESTAURANT IS NOT ACCEPTING ORDERS FOR NOW " << endl;
    }
    else
    {
        
        ifstream fout;
        fout.open(rest_name + ".csv");
        
        while (fout.good())
        {
            
            string line;
            getline(fout, line);
            cout << line << endl;
        }
        fout.close();
        cout << "enter the number of items you want to order" << endl;
        cin >> size;

        cout << "enter the names of items you want to order" << endl;
        string arr[size];

        int ctr = 0;
        string str;
        while (ctr != size)
        {
            string item;
            cin >> item;
            arr[ctr] = item;
            ctr++;
            str = str + "-" + item;
        }
        int len = str.length();
        str = str.substr(1, len);

        float bill = generate_bill(arr, rest_name, size);
        cout << "the total bill is" << bill <<"Rs"<< endl;
        fstream fin;

        fin.open("order.csv", ios::out | ios::app);
       

        fin << name << "," << ph << "," << rest_name << "," << str << "," << bill << ","
             "LIVE"
            << "\n";

        fin.close();
    }
}

string customer_login(long long ph, string pass)
{
    // this method takes 2 inputs
    // 1-phone number
    // 2-password
    // it then matches the phone number with all the numbers in custome_Login_Detail.csv file and returns the appropriate name accordingly to login() method


    stringstream stream;
    stream << ph;
    string num;

    num = stream.str();
    string nm;
    string password;

    ifstream ip("customer_Login_Details.csv");
    string phone;
    while (ip.good())
    {
        getline(ip, nm, ',');
        getline(ip, phone, ',');
        getline(ip, password, '\n');

        if (num.compare(phone) == 0 && pass.compare(password) == 0)

            return nm;
    }
    return "\0";
}
void login()
{
    // this method allows a user to login to his account and then he/she can either view his order history or place a order
    long long ph;
    string pass;
    cout << "enter your phone number" << endl;
    cin >> ph;
    cout << "enter your password" << endl;
    cin >> pass;
    string name = customer_login(ph, pass);
    
    if (name.compare("\0") != 0)
    {
        cout <<"Hello "<<name<<"!"<<endl;
        int ch;
        cout << "select one of the following :" << endl;
        cout << "1-TO VIEW ORDER HISTORY" << endl
             << "2-TO PLACE ORDER" << endl;
             
        cin >> ch;
        if (ch == 1)
        {
            order_history(ph);
        }
        else if (ch == 2)
            place_order(ph, name);


        else
        {
            cout << "WRONG CREDENTIALS" << endl;
        }
    }
}

bool is_registered(long long ph)
{
    // this method takes in phone number as input and matched it with numbers in custome_Login_Details.csv file
    // it returns 1 if the customer has already registered with this inputted number else 0
    stringstream stream;
    stream << ph;
    string num;

    num = stream.str();
    string nm;
    ifstream ip("customer_Login_Details.csv");
    string phone;
    while (ip.good())
    {
        getline(ip, nm, ',');
        getline(ip, phone, ',');
        int x = num.compare(phone);
        if (x == 0)
        {
            cout << "you already have registered with this number" << endl;
            return 1;
        }
    }
    return 0;
}

void register_restaurant()
{
    // this method takes in the restaurant details and stores it in the csv file of that particular restaurant

    int limit;
    string name;
    cout << "enter name of your restaurant : ";
    cin >> name;
    cout << "enter the number of items in your menu";
    cin >> limit;
    fstream fout;
    
    fout.open("restaurents.csv", ios::out | ios::app);
    // fout<<"LIST OF ALL RESTAURENTS OPEN NOW"<<endl; 

    fout << name << "\n";
    fout.close();
    fout.open(name + ".csv", ios::out | ios::app);
    fout << "foodname"
         << ","
         << "price"
         << "\n";
    for (int i = 0; i < limit; i++)
    {
        string itemname;
        float price;
        cout << "enter the name and price  of itme number" <<" "<<(i + 1)<<endl;
        cin >> itemname;
        cin >> price;
        fout << itemname << "," << price << "\n";
    }
    fout.close();
}
void register_customer()
{
    // this method takes in the customer details and stores them in a csv file
    // it also checks if a customer is already registered or not
    string name;
    string password;
    long long ph;
    fstream f;
    f.open("customer_Login_Details.csv", ios::out | ios::app);
    cout << "enter your name"<<endl;
    cin >> name;
    cout << "enter your password"<<endl;
    cin >> password;
    cout << "enter your phone number"<<endl;
    cin >> ph;
    if (!(is_registered(ph)))
    {

        f << name
          << ","
          << ph
          << "," << password << "\n";
        f.close();
    }
}
int main()
{
    int choice;
    char ch;
    ;
    cout << "select one of the following"<<endl;
    cout << "1-register a restaurant  \n 2-open customer account\n 3-order food"<<endl;
    cin >> choice;
    while (true)
    {

        switch (choice)
        {
        case 1:

            register_restaurant();
            break;
        case 2:
            register_customer();
            break;
        case 3:
            login();
            break;
        default:
            cout << "WRONG CHOICE";
        }
        cout << "do you wish to continue?";
        cin >> ch;
        if (ch == 'F')
            break;

        cout << "1-register a restaurant  \n 2-open customer account\n 3-order food";
        cin >> choice;
    }

    return 0;
}
