#include <unordered_map>
#include <iostream>

using namespace std;
struct Pos {
    int row;
    int col;
};

int main(void)
{
    unordered_map<string, int> umap;
    unordered_map<Pos, int> um;    
    if (umap.empty())
        printf("umap is empty.\n");
        
    umap.insert(make_pair("Hi", 1));
    umap.insert(make_pair("Hello", 3));
    umap.insert(make_pair("World", 4));
    umap.insert(make_pair("!!!", 6));
    
    auto it = umap.begin();

    while(it != umap.end()) {
        cout << it->first << endl;
        it++;
    }
    if (umap.empty() == false) 
        printf("umap count: %d\n", umap.size());

    Pos cur;
    cur.col = 1;
    cur.row = 2;
    int id = 1;
    um.insert(make_pair(cur, id));

    unordered_map<Pos, int>::iterator findIter;

    findIter = um.find(cur);

    if (findIter != um.end())
	{
		printf("%d %d\n", findIter->second);
        um.erase(cur);
	}
	else
	{
		printf("not found\n");
	}
   
    if (um.empty())
        printf("um is empty.\n");
    
    return 0;
}