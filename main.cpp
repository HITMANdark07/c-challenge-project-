#include<iostream>
using namespace std;

class Fruit{
    private:
    string name;
    double weight;
    double unit_price;
    public:
    static const string NAME;
    static const double WEIGHT;
    static const double UNIT_PRICE;
    Fruit(){
        name= NAME;
        weight= WEIGHT;
        unit_price=UNIT_PRICE;
    }
    Fruit(string st, double wt,double up){
        name=st;
        weight=wt;
        unit_price=up;
    }
    string getName(){
        return name;
    }
    void setName(string st){
        name = st;
    }
    double getWeigth(){
        return weight;
    }
    void setWeight(double wt){
        weight= wt;
    }
    double getunit_price(){
        return unit_price;
    }
    void setunit_price(double up){
        unit_price=up;
    }
    bool Order(double rw, double *oc){
        if(rw>weight){
            *oc=0.0;
            return false;
        }else{
            weight=weight-rw;
            *oc= rw*unit_price;
            return true;
        }
    }
    void display(){
        cout<<"-------------------------------------------------------------------"<<endl;
        cout<<"Fruit Name: "<<name<<"\tWeight: "<<weight<<"\tUnit Price: "<<unit_price<<endl;
        // cout<<name;
        // cout.precision(3);
        // cout<<"\t\t"<<weight<<"\t"<<unit_price<<endl;
        cout<<"-------------------------------------------------------------------"<<endl;
        // cout.precision(3);
        // cout<<"Weigth: "<<setw(5);
        // cout<<fixed<<weight<<" ";
        // cout<<"Unit Price"<<setw(5);
        // cout<<fixed<<unit_price<<" ";
    }
};
const string Fruit::NAME = "A Fruit";
const double Fruit::WEIGHT = 0.0;
const double Fruit::UNIT_PRICE = 0.0;
class OnlineSuperMarket{
    private:
    Fruit fruits[8];
    string market_name;
    string web_address;
    int find(string mn);
    void quit();
    public:
    static const Fruit fruit_list[8];
    static const double sales_tax_rate;
    static const string MARKET_NAME;
    static const string WEB_ADDRESS;
    OnlineSuperMarket(){
        market_name=MARKET_NAME;
        web_address=WEB_ADDRESS;
    }
    OnlineSuperMarket(string mn, string wa){
        market_name=mn;
        web_address=wa;
    }
    ~OnlineSuperMarket(){
        cout<<"Online super market "<<market_name<<" at "<<web_address<<" is already closed."<<endl;
    }
    string getMarketName(){
        return market_name;
    }
    string getWebAddress(){
        return web_address;
    }
    void init(){
        string fruist_name[8]={"Banana","Strawberry","Orange","Grapes","Watermelon","Apple","Blueberry","Mango"};
        double up[8]={0.85,3.50,3.50,4.50,1.45,3.20,4.50,3.25};
        for(int i=0;i<8;i++){
            Fruit f= fruits[i];
            f.setName(fruist_name[i]);
            f.setunit_price(up[i]);
            double range = 50.0-10.0+1;
            double wt= rand() % int(range) + 10.0;
            f.setWeight(wt);
            fruits[i]=f;
        }

    }
    void sort(){
        for(int i=0;i<8;i++){
            for(int j=0;j<8-i-1;j++){
                if(fruits[j].getName()>fruits[j+1].getName()){
                    const string temp= fruits[j].getName();
                    fruits[j].setName(fruits[j+1].getName());
                    fruits[j+1].setName(temp);
                }
            }
        }
    }
    void run(){
        char ch;
        while(ch!='q' || ch!='Q'){
            string fName;
            double wt;
            int found;
            double oc;
            bool od;
            cout<<"------------"<<market_name<<"------------ "<<endl;
            cout<<"------------"<<web_address<<"------------"<<endl;
            cout<<"Select from above options: "<<endl;
            cout<<"1. Food Ordering"<<endl;
            cout<<"2. show Fruits "<<endl;
            cout<<"Enter 'q' or 'Q' to Quit"<<endl;
            cin>>ch;
            switch(ch)
            {
            case '1':
                cout<<"Enter Fruit Name: ";
                cin>>fName;
                cout<<"Enter weight required: ";
                cin>>wt;
                found = find(fName);
                if(found!=-1){
                    od = fruits[found].Order(wt,&oc);
                    if(od){
                        oc = oc*(1+sales_tax_rate);
                        cout<<"Total Order Cost: "<<oc<<endl;
                    }else{
                        cout<<"Weight Exceed the Available Fruits weight"<<endl;
                    }
                }else{
                    cout<<"Entered Fruit is Not present"<<endl;
                }
                break;
            case '2':
                showFruits();
                break;
            case 'q':
                quit();
                exit(1);
                break;
            case 'Q':
                quit();
                exit(1);
                break;
            default:
                cout<<"Enter Valid Input"<<endl;
                break;
            }
        }
    }

    void showFruits(){
        for(int i=0;i<8;i++){
            fruits[i].display();
        }
    }

};
const double OnlineSuperMarket::sales_tax_rate=0.095;
const string OnlineSuperMarket::MARKET_NAME="Foothill Super Market";
const string OnlineSuperMarket::WEB_ADDRESS="http://www.foothillmarket.com";
int OnlineSuperMarket::find(string mn){
    for(int i=0;i<8;i++){
        string gn=fruits[i].getName();
        if(gn==mn){
            return i;
        }
    }
    return -1;
}
void OnlineSuperMarket::quit(){
    cout<<"Thanks for your visit and come again."<<endl;
}
int main(){
    OnlineSuperMarket *ptr = NULL;
    OnlineSuperMarket obj = OnlineSuperMarket("Super Market","https://supermarket.com");
    ptr = &obj;
    ptr->showFruits();
    ptr->init();
    ptr->showFruits();
    ptr->sort();
    ptr->showFruits();
    ptr->run();
    return 0;
}