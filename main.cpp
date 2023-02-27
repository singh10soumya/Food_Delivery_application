#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
void order_history(long long ph)

{
    // ifstream fout;
    // fout.open("customer_Login_Details.csv");
    stringstream stream;
    stream << ph;
    string num;

    num = stream.str();
    string phone;
    string nm;
    string rest;

    // string pass;
    ifstream f;
    f.open("order.csv");
    // cout<<"RESTAURENT"<<"ORDER"<<"PRICE"<<endl;
    cout << "DISPLAYING ORDER HISTORY " << endl;
    while (f.good())
    {

        getline(f, nm, ',');
        getline(f, phone, ',');
        getline(f, rest, ',');
        // getline(fout,pass,'\n');

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
}

float generate_bill(string arr[], string name, int size)
{

    float bill;
    bill = 0;
    string item;
    string price;
    // cout << "sally";
    // arr = litti,dal,momo
    // cout<<sizeof(arr)<<endl;
    for (int i = 0; i < size; i++)
    {

        // cout << "sally1";
        string food_name;
        food_name = arr[i];
        ifstream fout;
        fout.open(name + ".csv");
        while (fout.good())
        {
            // cout << "sally2";

            getline(fout, item, ',');
            getline(fout, price, '\n');
            // cout<<item<<endl;
            // cout<<price<<endl;
            // cout<<food_name<<endl;
            if (item.compare(food_name) == 0)
            {
                cout << "matched" << endl;

                bill = bill + stof(price);
            }
        }
    }
    return bill;
}
string select_restaurent()
{
    string res_name;
    ifstream fout;
    cout << "select a restaurent from the list" << endl;
    fout.open("restaurents.csv");
    // cout<<"soumya";
    while (fout.good())

    {
        // cout<<"soumyasingh";
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
        // cout<<"apple"<<endl;
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
    int size;
    string rest_name = select_restaurent();
    if (rest_name.compare("NULL") == 0)
    {
        cout << "this restaurent is no longer accepting orders for now" << endl;
    }
    else
    {
        // cout<<rest_name<<endl;
        ifstream fout;
        fout.open(rest_name + ".csv");
        // cout << fout.rdbuf();
        while (fout.good())
        {
            // cout<<"soumya";
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
        cout << "the total bill is" << bill << endl;
        fstream fin;
        fin.open("order.csv", ios::out | ios::app);
        fin << name << "," << ph << "," << rest_name << "," << str << "," << bill << ","
            << "LIVE"
            << "\n";

        fout.close();
    }
}

string customer_login(long long ph, string pass)
{

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
    long long ph;
    string pass;
    cout << "enter your phone number" << endl;
    cin >> ph;
    cout << "enter your password" << endl;
    cin >> pass;
    string name = customer_login(ph, pass);
    // cout<<name<<endl;
    if (name.compare("\0") != 0)
    {
        cout << name << endl;
        int ch;
        cout << "type 1 for order history and 2 to place a new order";
        cin >> ch;
        if (ch == 1)
        {
            order_history(ph);
        }
        else
            place_order(ph, name);
    }

    else
    {
        cout << "WRONG CREDENTIALS" << endl;
    }
}

bool is_registered(long long ph)
{
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

    int limit;
    string name;
    cout << "enter name of your restaurant";
    cin >> name;
    cout << "enter the number of items in your menu";
    cin >> limit;
    fstream fout;
    fout.open("restaurents.csv", ios::out | ios::app);

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
        cout << "enter the name and price  of" << (i + 1) << "th item";
        cin >> itemname;
        cin >> price;
        fout << itemname << "," << price << "\n";
    }
    fout.close();
}
void register_customer()
{
    string name;
    string password;
    long long ph;
    fstream f;
    f.open("customer_Login_Details.csv", ios::out | ios::app);
    cout << "enter your name";
    cin >> name;
    cout << "enter your password";
    cin >> password;
    cout << "enter your phone number";
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
    cout << "select one of the following";
    cout << "1-register a restaurant  \n 2-open customer account\n 3-order food";
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
