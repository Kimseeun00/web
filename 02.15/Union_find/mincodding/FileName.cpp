#include<set>
#include<multiset>
#include<map>
#include<unordered_map>
#include<unordered_set>
#include<string>
using namespace std;

set<int> st;
map<string, int> mp;

int main() {
	mp.insert({ "123132" ,1});
	mp["123123"]; // 1;
	st.insert(1);

	unordered_set<int> unset;
	
	auto it = unset.find(10000)

}