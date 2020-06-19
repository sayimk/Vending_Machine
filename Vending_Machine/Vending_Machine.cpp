// Vending_Machine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;


//represents an item from the vending machine
class VItem {
public:

    VItem() {

        itemName = "";
        itemAmount = 0;
        itemPrice = 0.0f;

    }

    //constructor
    VItem(string item_name, float item_price, int item_amount) {
        itemName = item_name;
        itemAmount = item_amount;
        itemPrice = item_price;
    }

    //methods
    string getName() {
        return itemName;
    }

    int getAmount() {
        return itemAmount;
    }

    float getPrice() {
        return itemPrice;
    }

    void setName(string item_name) {
        itemName = item_name;
    }

    void setAmount(int item_amount) {
        itemAmount = item_amount;
    }

    void setPrice(float item_price) {
        itemPrice = item_price;
    }

private:
    string itemName;
    int itemAmount;
    float itemPrice;

};

vector<VItem> add_Item(vector<VItem> current_inventory, string item_name, float price, int total_amount) {
    
    VItem temp(item_name,price,total_amount);
    current_inventory.push_back(temp);

    return current_inventory;
}

//adding money via float method
float add_inserted_money(float current_total, float inserted_to_add) {

    current_total = current_total + inserted_to_add;
    cout << "Balance:  "; cout << setprecision(3) << current_total; cout << "\n";
    return current_total;
}

//adding money via string method
float add_inserted_money(float current_total, string inserted_to_add) {
    
    //add exception handling here
    current_total = current_total + stof(inserted_to_add);
    cout << "Balance:  "; cout << setprecision(3) << current_total; cout << "\n";
    return current_total;
}

//returns all the input coins
void coins_out(vector<string> coins_in, float total) {

    string temp_out = "";
    
    for (int i = 0; i < coins_in.size(); i++){

        if (!i==0){
            temp_out = temp_out + ", " + coins_in.at(i);
        }
        else {
            temp_out = coins_in.at(0);
        }
    }

    cout << "\nReturning coins: " + temp_out+"\n";
    cout << setprecision(3) << total;
    cout << "\n";
}

//displays balance, options, available items list
void display_menu(vector<VItem> current_inventory, float balance_total) {

    cout << "\n";
    cout << "Hi there, Welcome to a vending machine \n";
    cout << "\n";
    cout << "Available Items : \n";
    cout << "Item Name - Quantity - Price\n";

    for (int i = 0; i < current_inventory.size(); i++) {
        cout << to_string(i) + " - " + current_inventory.at(i).getName() + " - " + to_string(current_inventory.at(i).getAmount()) + " - "; cout << setprecision(3) << current_inventory.at(i).getPrice();
        cout << "\n";
    }

    cout << "\nYour Balance is: "; cout << setprecision(3) << (balance_total); cout << "\n";
    cout << "Options available are: \n";
    cout << "- Insert Money (POUND, TWO POUNDS, 1, 2, 5, 10, 20, 50)\n";
    cout << "- COIN RETURN \n";
    cout << "- BUY <Item Number> \n";
    cout << "- SERVICE \n";
    cout << "- exit \n";
}

//recursive password barrier, requires number of attempts and correct password
bool password_barrier(string password, int attempts) {
    bool granted = false;
    string enteredPass;

    if (attempts <= 0) {
        cout << "Access Denied";
        granted = false;
        return granted;
    }
    else {
        cout << "\nEnter Service Password: ";
        cin >> enteredPass;


        if (enteredPass == password) {
            granted = true;
            return granted;

        }else {
            cout << "\n";
            cout << (attempts - 1);
            cout << "left";
            return password_barrier(password, (attempts - 1));
        }
    }
}

//displays service menu options
void display_service_menu() {

    cout << "\n Service Menu:\n";
    cout << "1. Add Items\n";
    cout << "2. Remove Items\n";
    cout << "3. Exit";

}

//basic string splitter/parser, uses ',' as a regex for splitting as well as string end i.e. hi,hello, howdy >> vector(3)
vector<string> input_parser(string input_regex_comma) {
    
    string buffer = "";
    vector<string> outputs;

    for (int i = 0; i < input_regex_comma.size(); i++) {
        
        if ((input_regex_comma.at(i)==',')){
            outputs.push_back(buffer);
            buffer = "";

        } else if (i >= (input_regex_comma.size()-1)){
            buffer = buffer + input_regex_comma.at(i);
            outputs.push_back(buffer);

        }else {
            if(isspace(input_regex_comma.at(i))==0)
                buffer = buffer + input_regex_comma.at(i);
        }
    }
    return outputs;
}

//basic bubble style search, I know its not efficient for really large lists, but it works
int vector_vitem_search(vector<VItem> item_list,string name) {

    for (int i = 0; i < item_list.size(); i++){

        if (item_list.at(i).getName() == name) {
            return i;
        }
    }
    return -1;
}

//use to verify functions work
void self_function_test() {
    cout << "-- Self-check --\nlog:\n";

    if (add_inserted_money(4.0f,2.5f)==6.5f)
        cout << " - Adding money via float - Test Successful\n";
    else 
        cout << " - Adding money via float - Test Failed\n";

    if (add_inserted_money(4.0f, "2.5") == 6.5f)
        cout << " - Adding money via text - Test Successful\n";
    else
        cout << " - Adding money via text - Test Failed\n";

    if (input_parser("test1,test2,test3").size() == 3)
        cout << " - Input text parser - Test Successful\n";
    else
        cout << " - Input text parser - Test Failed\n";

    VItem test1("test1", 1.0, 1);
    VItem test2("test2", 2.0, 2);
    VItem test3("test3", 3.0, 3);

    vector<VItem> items;
    items.push_back(test1);
    items.push_back(test2);
    items.push_back(test3);

    cout << items.size();
    vector<VItem> temp = add_Item(items, "test4", 4, 4.0f);
    if (temp.size() == 4)
        cout << " - Service Add Item - Test Successful\n";
    else
        cout << " - Service Add Item - Test Failed\n";

    int i = vector_vitem_search(items, "test3");
    if (items.at(i).getName() == "test3")
        cout << " - Vector Items Search - Test Successful\n";
    else
        cout << " - Vector Items Search - Test Failed\n";

    cout << "-- Self-Check Completed --\n";
}

int main(){

    //vars
    vector<VItem> items_list;
    float total_inserted = 0.0f;
    float last_total_logged = 0.0f;
    vector<string> inserted_order;
    string input = "";
    bool exit = false;
    string pass = "1234abc";

    //checks if most of the core functions are working through basic automated test
    self_function_test();

    //using while to keep prog running, use 'exit' to exit
    while (!exit){

        display_menu(items_list,total_inserted);

        cout << "\nEnter Option: ";

        //easiest way to get a sentense input i.e. buy 1, but it is slightly buggy, registers 'Enter' as an input and goes through one display 
        //menu cycle. if more time, could find a solution
        getline(cin, input);

        //check for 'buy' keyword
        int selection = -1;;

        if (input.find("Buy") < input.size()) {
            selection = input.find("Buy");
        }
        else if (input.find("buy") < input.size()) {
            selection = input.find("buy");
        }
        else if (input.find("BUY") < input.size()) {
            selection = input.find("BUY");
        }

       //start of option selection clause
        if (selection != -1){
            try {
                selection = stoi(input.substr(selection + 3, input.size()));

                if (items_list.at(selection).getPrice() <= total_inserted) {
                    if (items_list.at(selection).getAmount() >= 1) {

                        //process the transaction
                        cout << "\n Processing Transaction...";

                        total_inserted = total_inserted - items_list.at(selection).getPrice();
                        items_list.at(selection).setAmount(items_list.at(selection).getAmount() - 1);

                        cout << "\nComplete, please take item\n";
                    }
                    else
                        cout << "\nInsufficient items available, please select an alternative\n";
                }
                else
                    cout << "\nInsufficient Balance, please insert the correct amount\n";

            }catch (out_of_range e) {
                cout << "\nInvalid Item ID, Please try again\n";
            }
            catch (exception e) {
                cout << "\n Whoops, something went wrong, please verify input and try again";
                cout << e.what();
                cout << "\n";
            }

            //least efficient, but easiest option for de-case-sensitivety, if had time, could standardize string to all lowercase
        }else if ((input=="POUND")||(input=="pound")||(input=="Pound")){
            
            total_inserted = add_inserted_money(total_inserted, 1.0f);
            inserted_order.push_back(input);
            last_total_logged = total_inserted;

        } else if ((input == "TWO POUNDS") || (input == "two pounds") || (input == "Two Pounds")) {
            
            total_inserted = add_inserted_money(total_inserted, 2.0f);
            inserted_order.push_back(input);
            last_total_logged = total_inserted;

        } else if ((input == to_string(1)) || (input == to_string(2)) || (input == to_string(5)) || (input == to_string(10)) || (input == to_string(20)) || (input == to_string(50))) {

            total_inserted = add_inserted_money(total_inserted, input);
            inserted_order.push_back(input);
            last_total_logged = total_inserted;

        } else if ((input == "COIN RETURN") || (input == "Coin Return") || (input == "coin return")) {
            
            try{
                if (last_total_logged != total_inserted)
                    throw exception("balance not same as inserted coins, balance has changed");

                coins_out(inserted_order, total_inserted);

            }catch (exception e){
                cout << "Coins cannot be returned after using 'Buy' selection\n";
                cout << "Change can be returned in a future update, please come again!";
            }
       
        }else if ((input == "SERVICE") || (input == "Service") || (input == "service")) {

            cout << "Entered Service \n";

            bool exit_service = false;
            bool auth = false;

            auth = password_barrier(pass, 3);

            //only entering service while user hasnt entered exit command and is authorized via password_barrier, defaulted to 3 attempts
            while (!exit_service && auth) {
                string selection = "";
                vector<string> add_vals;
                int exists = -1;

                display_service_menu();
                cout << "\nEnter Option No: ";
                cin >> selection;

                if (selection == "1"){
                    string item_to_add = "";

                    cout << "\n Enter the items name, its price and the quantity (without any spaces):\n";
                    cin >> item_to_add;

                    try {
                        add_vals = input_parser(item_to_add);
                        exists = vector_vitem_search(items_list, add_vals.at(0));

                        if (exists == -1) {
                            
                            if (add_vals.size() < 3)
                                throw invalid_argument("VItem requires 3 data cells, not all data cells available, add_vals < 3");
                            
                            items_list = add_Item(items_list, add_vals.at(0), stof(add_vals.at(1)), stoi(add_vals.at(2)));
                            cout << "\nItem Added\n";

                        }
                        else {
                            
                            items_list.at(exists).setAmount(items_list.at(exists).getAmount() + stoi(add_vals.at(2)));
                            items_list.at(exists).setPrice(stof(add_vals.at(1)));
                            cout << "\nItem Updated\n";
                        }
                    }
                    catch (invalid_argument i){
                        cout << "Insufficient Data provided to perform action, please verify information provided and try again";
                    } catch (exception e) {
                        cout << "Whoops, Something went wrong, please verify input, order and try again";
                        cout << e.what();
                        cout << "\n";
                    
                    }
                }else if (selection == "2") {
                    string item_to_remove = "";
                    vector<string> remove_vals;
                    int index_to_remove = -1;

                    try {
                        cout << "\n Enter the item name, followed by quantity: \n";
                        cin >> item_to_remove;
                        remove_vals = input_parser(item_to_remove);
                        index_to_remove = vector_vitem_search(items_list, remove_vals.at(0));

                        if (index_to_remove == -1)
                            throw invalid_argument("Item index does not exist in items vector");

                        if (items_list.at(index_to_remove).getAmount() < stoi(remove_vals.at(1)))
                            throw out_of_range("unable to remove more items than available in item vector");

                               //if all exception checks are passed deduct the amount from the items list
                                items_list.at(index_to_remove).setAmount(items_list.at(index_to_remove).getAmount() - stoi(remove_vals.at(1)));
                                cout << "Items Removed";

                    }catch (invalid_argument i) {
                        cout << "Invalid item name/does not exist\n";
                    }catch (out_of_range o){
                        cout << "Insufficent quantity available to remove, please verify removal amount";
                    }catch (exception e) {
                        cout << "Whoops something went wrong, please verify input and try again";
                    }
                }
                else if (selection == "3") {
                    exit_service = true;
                }
            }
            cout << "\nExiting Service Menu\n";
        
        } else if (input =="exit"){
            exit = true;
        }
        else {
            cout << "invalid input, try another option";
        }
    }
}


