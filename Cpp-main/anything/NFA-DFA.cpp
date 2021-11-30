#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

#ifndef _NFA_DFA
// the common of NFA ans DFA
class FA {
public:
  // state char to state ID
  unordered_map<char, int> state;
  // state ID to state char
  unordered_map<int, char> restate;
  // allow all of this DFA
  unordered_set<char> wordList;
  // all end state
  unordered_set<char> end;
  // begin state
  unordered_set<char> start;
  // matrix of path
  vector<vector<vector<char>>> matrix;
  /**
   * return all of this state's length
   * @return length of state
   */
  int getStateSize();
  /**
   * return all of the end state's length
   * @return length of end state
   */
  int getEndSize();
  /**
   * return all of this wordlist's size
   * @return length of word list
   */
  int getWordListSize();
  /**
   * if this state set have this ID,return false,
   * else insert this state SID and state char,then return true
   * @param ins want to insert char
   * @param SID ID of state
   * @return success of worst
   */
  bool insertState(const char &ins, int SID);
  /**
   * if this word list have the char that named ins,return false,
   * else input this char in wordlist
   * @param ins want insert char
   * @return success of worst
   */
  bool insertWordList(const char &ins);
  /**
   * if char that named ins in the end list, return false
   * else input this char in end list
   * @param ins want insert char
   * @return success of worst
   */
  bool insertEnd(const char &ins);
  /**
   * if test in the state, return true,else return false;
   * @param state max list
   * @param test test list
   * @return true or false
   */
  bool isSameSatate(vector<vector<char>> &_state, vector<char> &test);

  /**
   * return test in state's index
   * @param state max state list
   * @param test test list
   * @return index of test in state
   */
  int getIndexInVectorOfState(vector<vector<char>> &_state, vector<char> &test);
  /**
   * used x,y,char,to input the vector of matrix.
   * @param x the first value of matrix
   * @param y the second value of matrix
   * @param ch char
   * @param matrix path of state to state, ans show read a what char to go
   * @param state_size length of state
   * @return if input success,return true,else return false;
   */
  bool setMatrixValue(const int &x, const int &y, const char &ch);
  /**
   * show the matrix ,and show state input a char and go a new state
   * @param matrix save this path's matrix
   * @param stateSize size of state in this matrix
   * @param restate map<int,char>
   */
  void showMatrixValue();
  /**
   * if char that named ins in the start list, return false
   * else input this char in start list
   * @param ins want insert char
   * @return success of worst
   */
  bool insertStart(const char &ins);
  /**
   * read a char, then return go new state set
   * @param ans input state set
   * @param read input char
   * @return read this char to go a new state set
   */
  vector<char> readAChar(vector<char> &ans, const char &read);
};
class DFA : public FA {
public:
  /**
   * initialize of DFA
   * @param start start state
   * @param state a map to show [symbol,SID]
   * @param wordList wordlist set
   * @param end end set
   * @param matrix this matrix save all path can arrive
   */
  DFA(char start, unordered_map<char, int> &state,
      unordered_set<char> &wordList, unordered_set<char> &end,
      vector<vector<vector<char>>> &matrix);
  /**
   * initialize of DFA
   * @param test used a old DFA to copy the new DFA
   */
  DFA(const DFA &test);
  /**
   * initialize of DFA
   * @param test FA object
   * @param start a start state symbol
   */
  DFA(const FA &test, char start);
};
class NFA : public FA {

  /**
   * only read '~' can go to state
   * @param ans input state set
   * @return a new vector
   */
  vector<char> E_closer(vector<char> ans);

public:
  /**
   * NFA to DFA
   */
  DFA toDFA();
  /**
   * initialize NFA
   */
  NFA();
};
int FA::getStateSize() { return state.size(); }
int FA::getEndSize() { return end.size(); }
int FA::getWordListSize() { return wordList.size(); }
bool FA::insertState(const char &ins, int SID) {
  if (this->state.count(ins)) // if have this char that named ins
    return false;
  this->restate[SID] = ins; // put (SID,ins) input restate
  this->state[ins] = SID;   // put (ins,SID) input state
  return true;
}
bool FA::insertWordList(const char &ins) {
  if (this->wordList.count(ins))
    return false;
  this->wordList.insert(ins);
  return true;
}
bool FA::insertStart(const char &ins) {
  if (this->start.count(ins))
    return false;
  this->start.insert(ins);
  return true;
}
bool FA::insertEnd(const char &ins) {
  if (this->end.count(ins))
    return false;
  this->end.insert(ins);
  return true;
}
vector<char> NFA::E_closer(vector<char> ans) {
  unordered_set<char> s;
  for (const char &ch : ans) {
    s.insert(ch); // save yourself
    unordered_set<char> hashset;
    queue<char> chQue;
    hashset.insert(ch);
    chQue.push(ch);
    while (!chQue.empty()) {                   // queue is empty ?
      int number = this->state[chQue.front()]; // index of ch in this state
      for (int a = 0; a < this->getStateSize(); ++a) { // hight
        for (char ch : this->matrix[number][a]) {      // path
          if (ch == '~') {
            if (!hashset.count(this->restate[a])) {
              hashset.insert(this->restate[a]);
              chQue.push(this->restate[a]);
            }
            s.insert(this->restate[a]);
          }
        }
      }
      chQue.pop();
    }
  }
  vector<char> ret;
  for (auto begin = s.begin(), end = s.end(); begin != end;
       ++begin) // set to vector
    ret.push_back(*begin);
  return ret;
}
vector<char> FA::readAChar(vector<char> &ans, const char &read) {
  unordered_set<char> s;
  for (const char &ch : ans) {
    int number = this->state[ch]; // index of ch in this state
    for (int a = 0; a < this->getStateSize(); ++a) {  
      for (char ch : this->matrix[number][a]) {
        if (ch == read || ch == '~') {
          s.insert(this->restate[a]);
          break;
        }
      }
    }
  }
  vector<char> ret;
  for (auto begin = s.begin(), end = s.end(); begin != end; ++begin)
    ret.push_back(*begin);
  return ret;
}
bool FA::isSameSatate(vector<vector<char>> &_state, vector<char> &test) {
  for (auto &state : _state) {
    if (test == state)
      return true;
  }
  return false;
}
int FA::getIndexInVectorOfState(vector<vector<char>> &_state,
                                vector<char> &test) {
  int size = _state.size();
  for (int a = 0; a < size; ++a)
    if (_state[a] == test)
      return a;
  return -1;
}
NFA::NFA() {
  int stap = 0;
  char a;
  cout << "输入NFA要求：\n1.所有状态和字符表均为单个字符。\n2.空串用符号'~'"
          "表示。\n请输入开始符号"
       << endl;
  while (cin >> a)
    this->insertStart(a);
  cin.clear();
  clearerr(stdin);
  cout << "请输入字符表" << endl;
  while (cin >> a)
    this->insertWordList(a);
  cin.clear();
  clearerr(stdin);
  cout << "请输入状态表内容" << endl;
  while (cin >> a)
    this->insertState(a, stap++);
  cin.clear();
  clearerr(stdin);
  cout << "请输入结束符号" << endl;
  while (cin >> a)
    this->insertEnd(a);
  cin.clear();
  clearerr(stdin);
  //'!'表示无法到达，'~'表示输入空可到达
  this->matrix = *(new vector<vector<vector<char>>>(
      state.size(), vector<vector<char>>(state.size(), vector<char>())));
  cout << "请输入状态转换函数\n,格式：状态A 状态B 连接字符"
          "\n状态转换函数的要求：\n1:"
          "状态必须是状态表中的一个状态。\n2:"
          "连接字符必须是字符表中字符或者是'~'表示空字符\n";
  char A, B, C;
  while (cin >> A >> B >> C) {
    try {
      if (!state.count(A) || !state.count(B))
        throw('A');
      else if (!wordList.count(C) && C != '~')
        throw('B');
    } catch (char A) {
      if (A == 'A')
        cout << "输入状态错误\n请重新输入" << endl;
      else if (A == 'B')
        cout << "连接字符错误\n请重新输入" << endl;
    }
    setMatrixValue(this->state[A], this->state[B], C);
  }
}
bool FA::setMatrixValue(const int &x, const int &y, const char &ch) {
  if (x >= this->getStateSize() || y >= this->getStateSize())
    return false;
  matrix[x][y].push_back(ch);
  return true;
}
void FA::showMatrixValue() {
  cout << "不可达使用字符'!'表示" << endl;
  cout << "begin state :=  ";
  for (char ch : this->start)
    cout << ch << " ";
  cout << endl << "end state ：= ";
  for (char ch : this->end)
    cout << ch << " ";
  cout << endl << "路径矩阵为:\n";
  int stateSize = this->getStateSize();
  cout << "\t";
  for (int a = 0; a < stateSize; ++a) {
    cout << this->restate[a] << "\t";
  }
  cout << endl;
  for (int a = 0; a < stateSize; ++a) {
    cout << restate[a] << "\t";
    for (int b = 0; b < stateSize; ++b) {
      int stap = matrix[a][b].size();
      if (stap > 0) {
        cout << matrix[a][b][0];
        for (int c = 1; c < stap; ++c) {
          cout << "|" << matrix[a][b][c];
        }
      } else
        cout << '!';
      cout << '\t';
    }
    cout << endl;
  }
}
DFA NFA::toDFA() {
  vector<vector<char>> _state;
  vector<vector<char>> path;
  FA f;   
  queue<vector<char>> queu; //save the new state
  char _char = 'A';
  int stap = 0;
  vector<char> vec; // list -> E_closer can uesd vector
  for (auto begin = this->start.begin(), end = this->start.end(); begin != end;
       ++begin) { // using start state initialization this vector
    vec.emplace_back(*begin);
  }
  vec = E_closer(vec);          // compute the start state E-closer
  sort(vec.begin(), vec.end()); // remove the same vector
  queu.push(vec);
  _state.emplace_back(vec);
  f.state[_char] = stap;
  f.restate[stap] = _char;
  ++stap;
  ++_char;
  vector<char> Test;  //readAChar latter, have a new vector
  while (!queu.empty()) {  //queue is empty?
    vec = queu.front();
    int begin_state = f.getIndexInVectorOfState(_state, vec);
    for (auto begin = wordList.begin(), end = wordList.end(); begin != end;
         ++begin) {
      Test = this->E_closer(readAChar(vec, *begin));  // new vector
      if (Test.empty())  //if vector is empty, it mean a state read a char cann't go a new state
        continue;
      sort(Test.begin(), Test.end());  // objective is have a easy remove the same one
      if (!isSameSatate(_state, Test)) {
        queu.push(Test);
        _state.push_back(Test);
        f.state[_char] = stap;
        f.restate[stap] = _char;
        ++stap;
        ++_char;
      }
      int end_state = f.getIndexInVectorOfState(_state, Test);
      path.push_back({f.restate[begin_state], *begin, f.restate[end_state]});
    }
    queu.pop();
  }
  f.matrix = vector<vector<vector<char>>>(
      state.size(), vector<vector<char>>(state.size(), vector<char>()));
  for (vector<char> &vec : path) {
    f.setMatrixValue(f.state[vec[0]], f.state[vec[2]], vec[1]);
  }
  int size = _state.size();
  for (int a = 0; a < size; ++a) {
    for (char &ch : _state[a])
      if (this->end.count(ch))
        f.end.insert(f.restate[a]);
  }
  for (auto ch : this->wordList)
    f.wordList.insert(ch);
  DFA ret(f, 'A');
  return ret;
}
DFA::DFA(const FA &test, char start) {
  for (auto en : test.end)
    this->end.insert(en);
  for (auto mat : test.matrix)
    this->matrix.push_back(mat);
  this->start.insert(start);
  for (auto stat : test.state) {
    this->state[stat.first] = stat.second;
    this->restate[stat.second] = stat.first;
  }
  for (auto word : test.wordList)
    this->wordList.insert(word);
}
DFA::DFA(char start, unordered_map<char, int> &state,
         unordered_set<char> &wordList, unordered_set<char> &end,
         vector<vector<vector<char>>> &matrix) {
  this->start.insert(start);
  for (auto stat : state) {
    this->state[stat.first] = stat.second;
    this->restate[stat.second] = stat.first;
  }
  for (auto word : wordList)
    this->wordList.insert(word);
  for (auto endchar : end)
    this->end.insert(endchar);
  this->matrix = matrix;
}
DFA::DFA(const DFA &test) {
  for (auto en : test.end)
    this->end.insert(en);
  for (auto mat : test.matrix)
    this->matrix.push_back(mat);
  this->start = test.start;
  for (auto stat : test.state) {
    this->state[stat.first] = stat.second;
    this->restate[stat.second] = stat.first;
  }
  for (auto word : test.wordList)
    this->wordList.insert(word);
}

#endif

int main() {
  NFA a;
  cout << "NFA:" << endl;
  a.showMatrixValue();
  cout << endl << endl;
  DFA b(a.toDFA());
  cout << "DFA:" << endl;
  b.showMatrixValue();
  return 0;
}
// test
/**
x
a b
x y 1 2 3 4 5 6 
y

x 5 ~
5 5 a
5 5 b
5 1 ~
1 3 a
1 4 b
3 2 a
4 2 b
2 6 ~
6 6 a
6 6 b
6 y ~
*/
