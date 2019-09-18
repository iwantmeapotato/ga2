#include<iostream>
#include<string>
#include<fstream>
#include<ctime>
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif
using namespace std;

int NUMBER = 0, AGE = 1, MINUTES = 2, RATING = 3;
enum player{};

void cls() { system(CLEAR); }

class Player {
public:
  int number, age, minutes, rating, session;
  char status;
  string pos;
  bool subbed;
  Player *next, *prev;
  Player(char s = 'c', int n = 0, string p = "Center") { status = s; number = n; pos = p; next = NULL; prev = NULL; minutes = 0; session = 0; age = (rand() % 19) + 20; rating = (rand() % 51) + 45;}
};

class Roster {
public:
  Player *head, *tail, *tail_ref;
  int players;
  bool court;
  Roster(bool court) {
    this->court = court;
    players = 0;
    head = NULL;
    tail = NULL;
  }
  bool Swap(Player *a, Player *b) { // a < b
    //hell nah fix this shit

    /*
    */ // move me!
    swap(a->number, b->number);
    swap(a->age, b->age);
    swap(a->minutes, b->minutes);
    swap(a->rating, b->rating);
    swap(a->pos, b->pos);
    //
    // a->prev->next = b;
    // b->next->prev = a;
    // b->prev = a->prev;
    // a->prev = b;
    // a->next = b->next;
    // b->next = a;

    return true;
  }


  bool isempty() { if (head == NULL) return true; return false;}

  void add_beg(Player *p) {
    if (isempty()) {
      head = p;
      tail = p;
      players++;
      return;
    }
    head->prev = p;
    p->next = head;
    head = p;
    if (court) { head->prev = tail; tail->next = head; }
    players++;
  }
  void add_end(Player *p) {
    if (isempty()) { add_beg(p); return; }
    tail->next = p;
    p->prev = tail;
    tail = p;
    tail_ref = p;
    if (court) { tail->next = head; head->prev = tail; }
    players++;
  }

  bool sub(Player *p, Roster l, bool init = false) { // subs with the highest rated bench player
    int c = 0;
    Player *cu = l.head;
    Player *swap = 0;
    if (init) swap = p;
    while (c <= 6) {
      if (cu->pos == p->pos && swap == 0) {
        swap = cu;
      }
      if (cu->pos == p->pos && ((swap != 0 && cu->rating > swap->rating))) {
        swap = cu;
      }
      cu = cu->next;
      c++; // no, python!
    }
    if (swap == 0) return false;
    Swap(p, swap);
    return true;
  }

  void sort(int data) {
    bool greater = false;
    for (int i = 0; i < players - 1; i++) {
      for (int j = 0; j < players - 1; j++) {
        Player *x = get(j);
        Player *y =get(j+1);

        Player *tmp = head;

        ///make this less ugly
        if (data == NUMBER) {
          if (x->number > y->number) greater = true;
        }
        if (data == AGE) {
          if (x->age > y->age) greater = true;
        }
        if (data == MINUTES) {
          if (x->minutes < y->minutes) greater = true;
        }
        if (data == RATING) {
          if (x->rating < y->rating) greater = true;
        }

        if (greater) {
          Swap(x, y);

          //test changes
          /*
          for (int i = 0; i < 5; i++) {
            cout << tmp->number << "->";
            tmp = tmp->next;
          }
          */
          cout << '\n';
          greater = false;
        }

      }
    }
  }

  Player *get(int index) {
    if (isempty()) return 0;
    if (index < 0 || index >= players) return 0;
    Player *tmp = head;
    int c = 0;
    while (tmp != NULL) {
      if (c == index) return tmp;
      c++;
      tmp = tmp->next;
    }
    return 0;
  }

  void print() {
    Player *tmp = head;
    bool started = false;
    while (tmp != NULL) {
      if (tmp->prev == tail && started) break; //specifically for court players
      started = true;
      cout << "[" << tmp->number << "] age: " << tmp->age << ", rating: " << tmp->rating;
      if (tmp->status == 'c') {
        cout << " | playing for " << tmp->minutes << " minutes.";
      }
      else {
        cout << " || played for " << tmp->minutes << " minutes.";
      }
      cout << "\t " << tmp->pos << endl;
      tmp = tmp->next;
    }
  }
};

void jm_report(Roster r) {
  Player *cu = r.head;
  cout << "\n\tNumber\tMinutes played\n\t" + string(22, '=') + "\n";
  for (int i = 0; i < 12; i++) {
    cout << "\t" << cu->number << "\t" << cu->minutes << '\n';
    cu = cu->next;
  }
  cout << '\n';
  system("pause");
}

void jam_report(Roster r) {
  Player *cu = r.head;
  cout << "\n\tAge\tNumber\tMinutes played\n\t" + string(30, '=') + "\n";
  for (int i = 0; i < 12; i++) {
    cout << '\t' << cu->age << '\t' << cu->number << "\t" << cu->minutes << '\n';
    cu = cu->next;
  }
  cout << '\n';
  system("pause");
}

void r_report(Roster r) {
  Player *cu = r.head;
  cout << "\n\tAge\tNumber\tRating\tMinutes played\n\t" + string(38, '=') + "\n";
  for (int i = 0; i < 12; i++) {
    cout << '\t' << cu->age << '\t' << cu->number << '\t' << cu->rating << "\t" << cu->minutes << '\n';
    cu = cu->next;
  }
  cout << '\n';
  system("pause");
}

void full_report(Roster r) {
  Player *cu = r.head;
  cout << "\n\tAge\tNumber\tRating\tPosition\t\tMinutes played\n\t" + string(62, '=') + "\n";
  for (int i = 0; i < 12; i++) {
    cout << '\t' << cu->age << '\t' << cu->number << '\t' << cu->rating << '\t' << cu->pos << "\t\t";  if (cu->pos.length() < 8) cout << '\t'; cout << cu->minutes << '\n';
    cu = cu->next;
  }
  cout << '\n';
  system("pause");
}

void make_report(Roster r, int criteria) {
  Player *cu = r.head;
  if (criteria == MINUTES) { r.sort(MINUTES); cout << "\n\tNumber\tMinutes played\n\t" + string(22, '=') + "\n"; } //oops wait this is pythonic
  if (criteria == AGE) { r.sort(AGE); cout << "\n\tAge\tNumber\tMinutes played\n\t" + string(30, '=') + "\n"; } //lol whatever python is better anyway
  if (criteria == RATING) { r.sort(RATING); cout << "\n\tAge\tNumber\tRating\tMinutes played\n\t" + string(38, '=') + "\n"; } // print > cout
  if (criteria == NUMBER) { r.sort(NUMBER); cout << "\n\tAge\tNumber\tRating\tPosition\t\tMinutes played\n\t" + string(62, '=') + "\n"; } // or should i say cout << print
  for (int i = 0; i < 12; i++) {
    if (criteria == MINUTES) cout << "\t" << cu->number << "\t" << cu->minutes << '\n';
    if (criteria == AGE) cout << '\t' << cu->age << '\t' << cu->number << "\t" << cu->minutes << '\n';
    if (criteria == RATING) cout << '\t' << cu->age << '\t' << cu->number << '\t' << cu->rating << "\t" << cu->minutes << '\n';
    if (criteria == NUMBER) { cout << '\t' << cu->age << '\t' << cu->number << '\t' << cu->rating << '\t' << cu->pos << "\t\t";  if (cu->pos.length() < 8) cout << '\t'; cout << cu->minutes << '\n'; }
    cu = cu->next;
  }
  cout << '\n';
  system("pause");
}

void sub_report() {
  ifstream log("sub_log.txt");
  string line;
  cout << "\n\tSub In\tSub Out\tTime\n\t" << string(23, '=') << '\n';
  while(!log.eof()) {
    getline(log, line);
    cout << line << '\n';
  }
  log.close();
  system("pause");
}

void print_ros(Roster c, Roster b, string title = "Current") {
  cout << "\n" << title << " roster\n====================\nCourt:\n";
  c.print();
  cout << "\nBench: \n";
  b.print();
}

//I LOVE YOU 3000
//SETH + MEGAN 2019
//GOTTA GO TO MOODY
