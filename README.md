# Food_Delivery_application
It is a food delivery application\n
Firstly in the main method the user is asked to eneter a choice(a number out of 1,2,3) according to his/her needs
CASE 1
is for registering a restaurant
CASE 2
is for creating a new customer account if he/she has logged in for the first time
CASE 3 
is for placing the order(the user already has an account)
If the user selects 1 
Method register_restaurant is called
In register_restaurant()
Inputs taken from user=name of restaurant,number of items
Input stored in name,limit variable respectively
Then fstream object created fout
Restaurant.csv file opened
Store the restaurant name stored in"name" in the csv file
Then create a csv file with the name same as the restaurant name
Start a loop from i=0 to i<limit
Take the name and price of each item and store in "itemname","price" respectively
Close the file
Fout.close();
A message is displayed on screen-"do you wish to continue"
You can type either T or F for yes/no
Like this you can register many restaurants and all the restaurant name will be saved in restaurant.csv
The menu of a particular restaurant will be saved it its seperate csv file
I have alredy registered 4 restaurants-kfc,dominos,keventers,baskin as can be seen in restaurant.csv file uploaded here
The menu of a particular restaurant can be viewed in the csv file of tha particular restaurant
Tf the user selects 2
Method register_customer() is called
In this method
fstream object f created
customer_Login_Details.csv file opened
Inputs take-name,password,phone number
Inputs stored in variable=name,password,ph
Then is_registered method called
Tn is_registered(long long ph)
ph in long long is converted to sting and stored in "num" using stream.str()
ifstream object ip created
Open file customer_Login_Details.csv
Start a while loop
Each phone number in this csv file is stored in phone
Compare phone and num and store the result in x
x=0 if the number matches
if x=0
The users has alresdy registered with this number
return 1
else
return 0
Now in register_customer()
if (!(is_registered(ph)))
Store the name,phone no,.password in customer_Login_Details.csv
If the user selects 3
login() method called
Inputs taken=phone,password
Inputs stored in =ph,pass
customer_login() method is called to get the name for this particular phone number
In customer_login(long long ph,string pass)
ph converted to string and stored in"num"
ifstream object ip created
Open file customer_Login_Details.csv
Read name,phone and password from file and store in "nm","phone","password"
Compare each ph no. and password with the entered ph no. and password
if (num.compare(phone) == 0 && pass.compare(password) == 0)
return nm
else
return"\0"
in login()
The name retured by customer_login is stored in "name"
User is asked to eneter a choice(a number out of 1,2,3) according to his/her needs
CASE1
is for viewing order history
CASE2
is for placing order
If 2 is selected 
Method place_order(ph,name) is called
In place_order(long long ph,string name)
Select_restuarent () is called
In select_restaurent()
ifstream object fout created
open file restaurents.csv
Display all the restaurant
Store the restaurant eneterd by the user in "res_name"
ifstream object fout created
Open file order.csv
Start a while loop for reading this file
int ctr;//ctr is acounter variable for tracking live orders are not more than 10
while (ff.good())
Store restauarant name of each order in "rest" and status in "status"
Compare "res_name"with"status" and increas ctr by everytime it matches
Finally check if (ctr>10)
Ff yes return "NULL"
else return res_name to place_order()
In place_order()
Returned string from select_restaurent() is stored in rest_name
if (rest_name.compare("NULL") == 0)
    The below message is printed
        cout << "SORRY !!! THIS RESTAURANT IS NOT ACCEPTING ORDERS FOR NOW " << endl;
        else
        ifstream object fout created
Open csv file of that particular restaurant
Display menu of that file
Input form the use= number of items(stored in varuable sizee),name of items(stored in array arr of size "size"
All items are then stores in array using while loop
str=string which is combination of all the items in one seperated by'-'
generte_bill () method called
In genertare_bill(string arr[], string name, int size)
Inputs taken are
1-an array consisting of all the items ordered by the user 
2-name of the restaurant
 3-size of the array
 for loop form int i=0 to size
 ifstream object fout created
Open file of this restaurant
Read this file using while loop
 while (fout.good())
 Store each item on menu and its price in"item"and "price"
 variable food_name stores element of the arra at index i
 Compare item and food_name
 item.compare(food_name) == 0
 if matched
  bill = bill + stof(price);
  return bill;
The retured amount is stored in"bill"
fstream object fin created
open file order.csv
Store name,phone,restaurant,order,bill,status in order.csv
close fin
fin.close();
if 1 is selected
order_history() method called
fstream object f created
open file order.csv
Print  "DISPLAYING ORDER HISTORY "
Compare each number of order.csv with enterd number
if match found
Store resataurant ,order,bil in variables "rest","order_name","bill"
Display detaiils in format
restaurant name:
items orders:
total bill:
close f
If the user gives a wrong input 
"wrong choice " printed






    















