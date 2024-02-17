#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <cstring>
#define MAXL 10
#define piu pair<int, User*>
#define pim pair<int, Message*>
using namespace std;

struct User {
  char name[MAXL + 1];
  int total;
 
  void init(char* str) {
    strcpy(name, str);
    total = 0;
  }
};
 
struct Comp4User {
  bool operator() (const piu &a, const piu &b) {
    // 총합포인트가 높은 사용자를 기준으로 내림차순
    // 총합포인트가 같을 경우, 이름이 사전순으로 앞선 사용자를 우선배치
    // 우선순위 큐에서의 연산은 원래의 연산과 반대로 설정
    return a.first != b.first ? a.first < b.first : strcmp(a.second->name, b.second->name) > 0;
  }
};
 
priority_queue<piu, vector<piu>, Comp4User> pqu;
int userCnt;
 
// 사용자 수는 10000명 이하
User userlist[10000];
 
// 주소값 리턴을 통해 속도개선 및 불필요한 임시공간 할당 방지
User* getUser() { return &userlist[userCnt++]; }
 
// User 이름에 해당하는 User(이름, 총합포인트)의 주소를 해싱
unordered_map<string, User*> cdb;
 
struct Message {
  int id, point, total;
  bool alive;
  User* user;
  Message* parent;
  vector<Message*> comments;
  Message* main;
 
  void init(int _id, int _point, User* _user, Message* _parent = nullptr) {
    id = _id;
    point = total = _point;
    user = _user;
    user->total += point;
 
    comments.clear();
    parent = _parent;
    if (parent != nullptr) {
      parent->add(this, point);
      main = parent->main;
    }
    else {
      main = this;
    }
    alive = true;
  }
 
  void add(Message* comment, int addpoint) {
    comments.push_back(comment);
    Message* ptr = this;
    while (ptr != nullptr) {
      ptr->total += addpoint;
      ptr = ptr->parent;
    }
  }
 
  void remove() {
    if (!alive) return;
    alive = false;
    user->total -= point;
    pqu.push({ user->total, user });
    for (auto p : comments) p->remove();
  }
 
  void erase() {
    remove();
    int delpoint = total;
    Message* ptr = this;
    while (ptr != nullptr) {
      ptr->total -= delpoint;
      ptr = ptr->parent;
    }
  }
};
 
struct Comp4Message {
  bool operator() (const pim &a, const pim &b) {
    return a.first != b.first ? a.first < b.first : a.second->id > b.second->id;
  }
};
 
priority_queue<pim, vector<pim>, Comp4Message> pqm;
 
int messageCnt;
Message messagelist[50001];
 
Message* getMessage() { return &messagelist[messageCnt++]; }
 
unordered_map<int, Message*> mdb;
 
User* findUser(char user[]) {
  string str(user);
  User* obj = cdb[str];
  if (obj == nullptr) {
    obj = getUser();
    obj->init(user);
    cdb[str] = obj;
  }
  return obj;
}
 
void init() {
  userCnt = messageCnt = 0;
  pqu = {}; pqm = {};
  cdb.clear(); mdb.clear();
}
 
int writeMessage(char mUser[], int mID, int mPoint) {
  User* obj = findUser(mUser);
  Message* ptr = getMessage();
 
  ptr->init(mID, mPoint, obj);
  mdb[mID] = ptr;
 
  pqu.push({ obj->total, obj });
  pqm.push({ ptr->total, ptr });
 
  return obj->total;
}
 
int commentTo(char mUser[], int mID, int mTargetID, int mPoint)
{
  User* obj = findUser(mUser);
  Message* ptr = getMessage();
  Message* par = mdb[mTargetID];
 
  ptr->init(mID, mPoint, obj, par);
  mdb[mID] = ptr;
 
  ptr = ptr->main;
  pqu.push({ obj->total, obj });
  pqm.push({ ptr->total, ptr });
 
  return ptr->total;
}
 
int erase(int mID) {
  Message* ptr = mdb[mID];
  ptr->erase();
  pqm.push({ ptr->main->total, ptr->main });
  return ptr->parent == nullptr ? ptr->user->total : ptr->main->total;
}
 
void getBestMessages(int mBestMessageList[]) {
  int cnt = 0;
  Message* msglist[5];
  while (cnt < 5) {
    int total = pqm.top().first;
    Message* ptr = pqm.top().second;
    pqm.pop();
 
    if (!ptr->alive || ptr->total != total || (cnt > 0 && msglist[cnt - 1] == ptr)) continue;
    msglist[cnt] = ptr;
    mBestMessageList[cnt++] = ptr->id;
  }
  for (int i = 0; i < 5; i++) pqm.push({ msglist[i]->total, msglist[i] });
}
 
void getBestUsers(char mBestUserList[][MAXL + 1]) {
  int cnt = 0;
  User* userlist[5];
  while (cnt < 5) {
    int total = pqu.top().first;
    User* obj = pqu.top().second;
    pqu.pop();
 
    if (obj->total != total || (cnt > 0 && userlist[cnt - 1] == obj)) continue;
    userlist[cnt] = obj;
    strcpy(mBestUserList[cnt++], obj->name);
  }
  for (int i = 0; i < 5; i++) pqu.push({ userlist[i]->total, userlist[i] });
}