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

    void editproduct()
    {
        cout<<"Name :";
        cin>>name;
        string N=name;
        remove((name + ".txt").c_str());
        ofstream temp(("temp.txt"));
        cout<<"New Name :";
        cin>>name;
        temp<<name<<endl;
        cout<<"New Number :";
        cin>>number;
        temp<<number<<endl;
        cout<<"New Product ID :";
        cin>>Product_ID;
        temp<<Product_ID<<endl;
        cout<<"New Price :";
        cin>>price;
        temp<<price<<endl;
        cout<<"New Exp date :";
        cin>>Expiration_date;
        temp<<Expiration_date<<endl;
        temp.close();
        rename("temp.txt",(name + ".txt").c_str());

        ofstream temp2("temp.txt");
        ifstream p("products.txt");
        string line;
        while(getline(p,line))
        {
            if(line!=N)
            {
                temp2<<line<<endl;
                getline(p,line);
                temp2<<line<<endl;
            }
            else
            {
                ifstream edif(name+".txt");
                getline(edif,line);
                temp2<<line<<endl;
                getline(edif,line);
                getline(edif,line);
                temp2<<line<<endl;
                edif.close();
                getline(p,line);
            }

        }p.close();
        temp2.close();

        remove("products.txt");
        rename("temp.txt","products.txt");
    }

    void show_product(){
        ifstream products("products.txt");
        string line;
        cout<<"Name--------Qantity\n";
        while (getline(products,line))
        {
            if(!line.empty())
                cout<<line<<"----------";
            ifstream quantity(line+".txt");
            getline(quantity,line);
            getline(quantity,line);
            if(!line.empty())
                cout<<line<<endl;
            quantity.close();
            getline(products,line);
        }products.close();
    }
};

class employee :public product{
    friend class manager;
private:
    string name,employee_iD,email,password;
public:
    void add_factor()
    {
        ifstream factornum("factornumber.txt");
        string line_num;
        getline(factornum,line_num);
        factornum.close();
        line_num= to_string(stoi(line_num)+1);
        ofstream factnum("factornumber.txt");
        factnum<<line_num;
        factnum.close();
        long int sum=0;
        ofstream factor("factor"+ line_num+".csv");
        factor<<"Name,Number,Id,Price\n";
        cout<<"Enter zero ID to finish\n";
        while(true)
        {
            cout<<"ID :";
            string line_name,line_id;
            cin>>Product_ID;
            ifstream file("products.txt");
            if(Product_ID=="0")
            {
                file.close();
                break;
            }
            while(getline(file,line_name))
            {
                getline(file,line_id);
                if(line_id==Product_ID)
                {
                    ifstream product(line_name+".txt");
                    string line;
                    getline(product,line);//name
                    factor<<line<<",";
                    cout<<"number :";
                    getline(product,line);//num


                    product.close();
                    string lp;
                    cin>>lp;//quantity
                    factor<<lp<<",";
                    updatequantity(stoi(lp),line_name);
                    ifstream product2(line_name+".txt");
                    getline(product2,line);
                    getline(product2,line);


                    getline(product2,line);//id
                    factor<<line<<",";
                    getline(product2,line);//price
                    sum+=stoi(line)* stoi(lp);
                    factor<<line<<",\n";
                    product2.close();
                    break;
                }
            }
        }

        factor<<"Total price :,"<<sum<<",";
        factor.close();
    }
};

class manager :employee ,currency {
private:
    string name="_MANAGER_";
    string email="MAnageSTore@gmail.com";
    string password="FTYHb345vgjkd254";
public:
    void add(){
        cout<<"Name :";
        cin>> this->name;
        cout<<"Employee Id :";
        cin>> this->employee_iD;
        cout<<"Email :";
        cin>> this->email;
        cout<<"Password :";
        cin>> this->password;
        ofstream employee(this->employee_iD+".txt",ios_base::app);
        ofstream employees("empinfo.txt",ios_base::app);
        employee<< this->name<<endl<< this->employee_iD<<endl<< this->email<<endl<< this->password<<endl;
        employees<< this->name<<endl<< this->employee_iD<<endl<< this->email<<endl<< this->password<<endl;
        employee.close();
        employees.close();
    }

    void print_employee_info() {
        ifstream employees("empinfo.txt");
        string line;
        while (getline(employees, line)) {
            cout << line << endl;
        }
        employees.close();
    }
};