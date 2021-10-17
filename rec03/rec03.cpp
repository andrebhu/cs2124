/*
Andre Hu
2/12/2021
Chemistry Program for Checking Similar Hydrocarbons
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Hydrocarbon{
    vector<string> names;
    size_t carbon;
    size_t hydrogen;
};

void open_file(ifstream& file); 
void fill_vector(vector<Hydrocarbon>& data, ifstream& file);
size_t find_hydrocarbon(const vector<Hydrocarbon>& data, size_t c, size_t h);
void display_hydrocarbons(const vector<Hydrocarbon>& data);
void sort_hydrocarbons(vector<Hydrocarbon>& data);
void swap_hydrocarbons(vector<Hydrocarbon>& data, size_t i, size_t j);
void add(vector<Hydrocarbon>& data,const string& name, size_t carbons, size_t hydrogens);

int main(){
    ifstream input;
    open_file(input);

    vector<Hydrocarbon> data;

    fill_vector(data, input);
    input.close();
    sort_hydrocarbons(data);
    display_hydrocarbons(data);
    return 0;
}

//swaps hydrocarbons
void swap_hydrocarbons(vector<Hydrocarbon>& data, size_t i, size_t j){
    Hydrocarbon hc = data[i];
    data[i] = data[j];
    data[j] = hc; 
}

//implementing selection sort
void sort_hydrocarbons(vector<Hydrocarbon>& data){
    size_t sorted;
    for (size_t i = 0; i < data.size() - 1; ++i){
        //keeps track of sorted/unsorted
        sorted = i;
        for (size_t j = i + 1; j < data.size(); ++j){
            if(data[j].carbon < data[sorted].carbon){
                swap_hydrocarbons(data, i, j);
            }
            else if(data[j].carbon == data[sorted].carbon){
                if(data[j].hydrogen < data[sorted].hydrogen){
                    swap_hydrocarbons(data, i, j);
                }
            }
        }
    }
}

//displays hydrocarbons in data
void display_hydrocarbons(const vector<Hydrocarbon>& data){
    for (size_t i = 0; i < data.size(); ++i){
        cout << "C" << data[i].carbon << "H" << data[i].hydrogen << " ";
        for (size_t j = 0; j < data[i].names.size(); ++j){
            cout << data[i].names[j] << " ";
        }
        cout << endl;
    }
}

//finds if hydrocarbon already exists with same carbons/hydrogens
size_t find_hydrocarbon(const vector<Hydrocarbon>& data, size_t carbons, size_t hydrogens){
    for (size_t i = 0; i < data.size(); ++i){
        if (data[i].carbon == carbons && data[i].hydrogen == hydrogens){
            return i;
        }
    }
    return data.size();
}

//adds hydrocarbon to data
void add(vector<Hydrocarbon>& data,const string& name, size_t carbons, size_t hydrogens){
    size_t index = find_hydrocarbon(data, carbons, hydrogens);
            //if not found will return size of data
            if (index == data.size()){
                Hydrocarbon hc{vector<string>{name}, carbons, hydrogens};
                data.push_back(hc);
            }
            //add name to existing hydrocarbon
            else{
                data[index].names.push_back(name);
            }
}

//fills data vector with hydrocarbons
void fill_vector(vector<Hydrocarbon>& data, ifstream& input){
    string name;
    char c;
    size_t carbons;
    size_t hydrogens;

    while(input >> name >> c >> carbons >> c >> hydrogens){
        add(data, name, carbons, hydrogens);        
    }
}

//asks and reads in input file
void open_file(ifstream& input){
    string name;

    cout << "File name? ";
    cin >> name;
    input.open(name);

    //loops if can not open file
    while (!input){
        input.clear();
        cout << "File name? ";
        cin >> name;
        input.open(name);
    }
}

