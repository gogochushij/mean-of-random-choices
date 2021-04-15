#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <fstream>
#include <map>
using namespace std;

long long factorial(int n)
{
	if (n == 0) return 1;
	return 1ll*n*factorial(n-1);
}

set<string> vertices;
vector<vector<string>> clauses;

int random_choices(vector<string> perm)
{
	enum var_value {no, zero, one};
	map<string, var_value> values;
	for (string v : vertices) values[v] = no;
	//vector<vector<string>> cur_evaluation (clauses.size(), {no, no, no});
	
	bool propagation_made = true;
	int random_choices = 0;
	for (string v : perm)
	{
		if (values[v] == no)
		{
			propagation_made = true;
			while (propagation_made == true)
			{
				propagation_made = false;
				for (vector<string> cl : clauses)
				{	if (values[cl[2]] == one) continue;
					if (values[cl[0]] == one and values[cl[1]] == one and values[cl[2]] == no)
					{
						propagation_made = true;
						values[cl[2]] = one;
					}						
				}
			}
			if (values[v] == no)
			{
				values[v] = one;
				random_choices++;
			}
		}
	}	
	
	for (string var : perm)
	{
		cout << var << " ";
	}
	cout << " : " << random_choices << endl;
	return random_choices;
}

int main()
{
	ifstream in("input.txt");
	vector<string> input;
	string t;
	while (in >> t)
	{
		input.push_back(t);
		vertices.insert(t);
	}
	cout << "Vertices: ";
	for (string v : vertices)
	{
		cout << v << " ";
	}
	
	assert(input.size() % 3 == 0);
	for (int i = 0; 3*i < input.size(); i++)
	{
		clauses.push_back({input[3*i], input[3*i+1], input[3*i+2]});
	}
	cout << endl;
	
	cout << "Clauses: " << endl;
	for (vector<string> cl : clauses)
	{
		cout << "-" << cl[0] << " OR -" << cl[1] << " OR " << cl[2] << endl;
	}
	
	vector<string> perm(vertices.begin(), vertices.end());
	long long all_random_choices = 0;
	do
	{
		long long k = random_choices(perm);
		all_random_choices += k;
	} while (next_permutation(perm.begin(), perm.end()));
	
	cout << endl;
	cout << "Total random choices: " << all_random_choices << endl;
	cout << "Mean over " << factorial(vertices.size()) << " permutations is:" << endl;
	cout << (long double)(all_random_choices)/factorial(vertices.size());
	
	
	
}
