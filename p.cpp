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


};
