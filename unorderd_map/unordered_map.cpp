#include <unordered_map>
#include <iostream>

using namespace std;

int main(void)
{
    std::unordered_map<std::string, int> umap;
    
    if (umap.empty())
        printf("umap is empty.\n");
        
    umap.insert(std::make_pair("Hi", 1));
    umap.insert(std::make_pair("Hello", 3));
    umap.insert(std::make_pair("World", 4));
    umap.insert(std::make_pair("!!!", 6));
    
    auto it = umap.begin();

    while(it != umap.end()) {
        cout << it->first << endl;
        it++;
    }
    if (umap.empty() == false) 
        printf("umap count: %d\n", umap.size());

    
    return 0;
}