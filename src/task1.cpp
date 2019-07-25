#include <iostream>
#include <string>
#include <vector>
#include <fstream> 
#include <jsoncpp/json/json.h>

using namespace std; 

int main() {  
	clock_t start,end;
	ifstream file; 
	char word;
	string line, filename;
	int record = 0;
	double sum = 0.00, cost, maxCostComponent = 0.00;
	std::vector<int> costMoreThanNintyFive, maxCostComponentGreaterthanFifty;
	std::vector<double> maxCostComponents;
	cout << "Enter filename: ";
	cin >> filename;
	start = clock();
	file.open(filename.c_str());
	while (!file.eof()) {
		file.get(word);
		line += word;
		if(word == '}'){
			file.get(word);
			Json::Reader reader;
			Json::Value obj;
			reader.parse(line,obj);
			line = "";

			//query 1			
			record++;
			cost = obj["cost"].asDouble();
			sum += cost;

			//query 2
			for(int i = 0; i < obj["cost_components"].size(); i++) {
				if(obj["cost_components"][i].asDouble() > maxCostComponent)
					maxCostComponent = obj["cost_components"][i].asDouble();
			}

			//query 3
			if(cost > 95.00){
				costMoreThanNintyFive.push_back(obj["id"].asInt());
			}
			
			//query 4
			if(maxCostComponent > 50.00) {
				maxCostComponentGreaterthanFifty.push_back(obj["id"].asInt());		
			}
		}
	}

	cout<< "Query 1: the average value of the cost field of all objects: " << (sum/record) << endl;

	cout<< "Query 2: the maximum of the maximum value in each of the array of values in the cost_components field: " << maxCostComponent << endl;

	cout << "Query 3: the list of the id values of all of the objects that have their cost larger than 95: " ;
	for(vector<int>::iterator it = costMoreThanNintyFive.begin(); it != costMoreThanNintyFive.end(); ++it)
		cout << " " << *it;
	cout << endl;

	cout << "Query 4: the list of the id values of all of the objects that have the maximum value in their cost_components array larger than 50: ";
	for(vector<int>::iterator it = maxCostComponentGreaterthanFifty.begin(); it != maxCostComponentGreaterthanFifty.end(); ++it)
		cout << " " << *it;
	cout << endl;

	file.close();


	end = clock();
	cout << "Time taken for execution: " << (end-start)/double(CLOCKS_PER_SEC) << " seconds." <<endl;
	return 0; 
}
