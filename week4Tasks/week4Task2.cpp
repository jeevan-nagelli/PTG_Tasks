#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
using namespace std;

void callerFuntion(vector<string> dynamicWidgets,set<string> staticWidgets){
    //use of Iterators: Print all dynamic widgets using an iterator.
    cout<<"use of Iterators: Print all\n";
    for(auto it1=dynamicWidgets.begin();it1!=dynamicWidgets.end();it1++){
        cout<<*it1<<" ";
    };

    //Checking if a specific widget (e.g., "WarningLights") is in the std::set using std::set::find.
    cout<<"\n\nChecking if a specific widge s in the std::set\n";
    auto it2=staticWidgets.find("WarningLights");
    if(it2!=staticWidgets.end()){
        cout<<"WarningLights is in the set"<<endl;
    }else{
        cout<<"WarningLights is not in the set"<<endl;
    }

    //Combining both containers into a std::vector<std::string> using std::copy.
    cout<<"\nCombining both containers\n";
    vector<string> newVec;
    copy(dynamicWidgets.begin(),dynamicWidgets.end(),back_inserter(newVec));
    copy(staticWidgets.begin(),staticWidgets.end(),back_inserter(newVec));
    for(string s:newVec){
        cout<<s<<" ";
    }

    //Using std::find to locate a specific widget in the combined container.
    cout<<"\n\nUsing std::find\n";
    auto it3=find(newVec.begin(),newVec.end(),"Tachometer");
    if(it3!=newVec.end()){
        cout<<"Tachometer is in the combined container\n"<<endl;
    }else{
        cout<<"Tachometer is not in the combined container\n"<<endl;
    }
}

int main(){
    vector<string> dwidgets={"Speedometer","Tachometer","Temperature","FuelGauge"};
    set<string> swidgets={"Logo","WarningLights","HomeButton"};

    callerFuntion(dwidgets,swidgets);

}