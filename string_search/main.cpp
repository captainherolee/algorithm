#include <iostream>
#include <string>

using namespace std;
void find_pattern(const string &, const string &);
int main(const int argc, const char **argv)
{
    const string haystack = "hello hello hello hellchosun";
    const string needle = "hell";

    find_pattern(haystack, needle);

    return 0;
}

void find_pattern(const string &haystack, const string &needle)
{
    const auto haystack_size = haystack.size();
    const auto needle_size = needle.size();
    int i, j;
    bool unmatched_flag = true;

    cout << "Begin to find pattern \"" << needle << "\" at target string \"" << haystack << "\"" << endl;
    for (i = 0; i < haystack_size - needle_size; ++i) {
        for (j = 0; j < needle_size; ++j) {
            if (haystack[i + j] == needle[j]) {
                continue;
            }
            break;
        }

        if (j == needle_size) {
            cout << "pattern \"" << needle << "\" matched at " << i + 1 << " ~ " << i + 1 + needle_size << endl;
            unmatched_flag = false;
        }
    }

    if (unmatched_flag) {
        cout << "Pattern unmatched" << endl;
    }
}

//상태전이함수 생성
void kmp(char *pat) {
    int n = strlen(pat);
    int i = -1, j = 0;
    pi[j] = i;
    while(j < n) {
        if(i == -1 || pat[i] == pat[j])
            pi[++j] = ++i;
        else 
            i = pi[i];
    }
}

//문자열 비교
void find_pattern(char *arr, char *pat) {
    int n = strlen(arr);
    int m = strlen(pat);
    int i = j = 0;
    while(i < n) {
        if(j == -1 || arr[i] == pat[j]) 
            i++, j++;
        else
            j = pi[j];
        
        if(j == m) {
            printf("The matching %d\n",i-m+1);
            j = pi[j];
        }
    }