#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class product{
public:
    string Product_ID,Expiration_date;
    string name;
    string price,number;
    void add_product()
    {
        cout<<"name :";
        cin>> this->name;
        cout<<"quantity :";
        cin>>this->number;
        cout<<"ID :";
        cin>>this->Product_ID;
        cout<<"price :";
        cin>>this->price;
        cout<<"exp date :";
        cin>>this->Expiration_date;
        ofstream product(name + ".txt",ios_base::app);
        product<<this->name<<endl<<this->number<<endl<<this->Product_ID<<endl<<this->price<<endl<<this->Expiration_date<<endl;
        product.close();
        ofstream products("products.txt",ios_base::app);
        products<< this->name<<endl<< this->Product_ID<<endl;
        products.close();
    }

    void updatequantity(int newnum,const string& namee)
    {
        ifstream product((namee + ".txt"));
        ofstream temp("temp.txt",ios_base::app);

        string line;
        getline(product,line);
        temp<<line<<endl;
        getline(product,line);
        temp<<stoi(line)-newnum<<endl;
        getline(product,line);
        temp<<line<<endl;
        getline(product,line);
        temp<<line<<endl;
        getline(product,line);
        temp<<line;
        product.close();
        temp.close();

        remove((namee + ".txt").c_str());
        rename("temp.txt",(namee + ".txt").c_str());
    }

    void deleteproduct()
    {
        cout<<"Enter the product name :";
        cin>>name;
        remove((name+(".txt")).c_str());
        ofstream temp("temp.txt");
        ifstream product("products.txt");
        string line;
        while (getline(product,line)){
            if(line!=name)
            {
                temp<<line<<endl;
                getline(product,line);
                temp<<line<<endl;
            }
            else
                getline(product,line);
        }
        product.close();
        temp.close();

        remove("products.txt");
        rename("temp.txt","products.txt");
    }





};
