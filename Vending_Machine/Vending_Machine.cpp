// Vending_Machine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;


//represents an item from the vending machine
class VItem {


public:

    VItem() {

        itemName = "";
        itemAmount = 0;
        itemPrice = 0.0f;

    }

    VItem(string item_name, float item_price, int item_amount) {
        itemName = item_name;
        itemAmount = item_amount;
        itemPrice = item_price;
    }

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

vector<VItem> add_Item(vector<VItem> current_inventory, string item_name, int total_amount, float price) {
    
    return current_inventory;
}

float add_inserted_money(float current_total, float inserted_to_add) {

    current_total = current_total + inserted_to_add;
    cout << "Accepted: " + to_string(inserted_to_add)+"\n";
    cout << "Balance:  " + to_string(current_total)+"\n";
    return current_total;
}

float add_inserted_money(float current_total, string inserted_to_add) {
    
    //add exception handling here
    current_total = current_total + stof(inserted_to_add);
    cout << "Accepted: " + inserted_to_add + "\n";
    cout << "Balance:  " + to_string(current_total) + "\n";
    return current_total;
}

void coins_out(vector<string> coins_in) {

    string temp_out = "";
    
    for (int i = 0; i < coins_in.size(); i++){

        if (!i==0){
            temp_out = temp_out + ", " + coins_in.at(i);
        }
        else {
            temp_out = coins_in.at(0);
        }
    }

    cout << "Returning coins: " + temp_out;
}

void display_menu(vector<VItem> current_inventory, float balance_total) {

    cout << "\n";
    cout << "Hi there, Welcome to a vending machine \n";
    cout << "\n";
    cout << "Available Items : \n";
    cout << "Item Name - Quantity - Price\n";

    for (int i = 0; i < current_inventory.size(); i++) {
        cout <<to_string(i)+" - "+ current_inventory.at(i).getName() + " - " + to_string(current_inventory.at(i).getAmount()) + " - " + to_string(current_inventory.at(i).getPrice()) + "\n";
    }

    cout << "\nYour Balance is: " + to_string(balance_total)+"\n";
    cout << "Options available are: \n";
    cout << "- Insert Money (POUND, TWO POUNDS, 1, 2, 5, 10, 20, 50)\n";
    cout << "- COIN RETURN \n";
    cout << "- BUY <Item Number> \n";
    cout << "- SERVICE \n";
    cout << "- exit \n";
}

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

void display_service_menu() {

    cout << "\n Service Menu:\n";
    cout << "1. Add Items\n";
    cout << "2. Remove Items\n";
    cout << "3. Exit";

}

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

}

int main(){

    vector<VItem> items_list;
    float total_inserted = 0.0f;
    vector<string> inserted_order;
    string input = "";
    bool exit = false;
    string pass = "1234abc";

    while (!exit){

        display_menu(items_list,total_inserted);

        cout << "\nEnter Option: ";

        getline(cin, input);

        //check for BUY
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


        }else if ((input=="POUND")||(input=="pound")||(input=="Pound")){
            
            total_inserted = add_inserted_money(total_inserted, 1.0f);
            inserted_order.push_back(input);

        } else if ((input == "TWO POUNDS") || (input == "two pounds") || (input == "Two Pounds")) {
            
            total_inserted = add_inserted_money(total_inserted, 2.0f);
            inserted_order.push_back(input);

        } else if ((input == to_string(1)) || (input == to_string(2)) || (input == to_string(5)) || (input == to_string(10)) || (input == to_string(20)) || (input == to_string(50))) {

            total_inserted = add_inserted_money(total_inserted, input);
            inserted_order.push_back(input);

        } else if ((input == "COIN RETURN") || (input == "Coin Return") || (input == "coin return")) {
            //lock the coins in after a transaction, by checking logged_total and total inserted-----
            coins_out(inserted_order);
       
        }else if ((input == "SERVICE") || (input == "Service") || (input == "service")) {

            cout << "Entered Service \n";

            bool exit_service = false;
            bool auth = false;

            auth = password_barrier(pass, 3);

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

                            VItem new_item(add_vals.at(0), stof(add_vals.at(1)), stoi(add_vals.at(2)));
                            items_list.push_back(new_item);
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

    }


    
}


