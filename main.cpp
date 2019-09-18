#include"roster.h"
using namespace std;

// while (megan);
// do { seth; }

int main() {
  Roster court(1), bench(0);
  string positions[5] = {"Point Guard", "Shooting Guard", "Small Forward", "Power Forward", "Center"};

  for (int i = 1; i <= 5; i++) {
    Player *p = new Player('c', i, positions[i % 5]);
    court.add_end(p);
  }
  for (int i = 1; i <= 7; i++) {
    Player *p = new Player('b', i + 5, positions[i % 5]);
    bench.add_end(p);
  }

  print_ros(court, bench, "Initial");
  court.sort(NUMBER);

  Player *cu = court.head;
  for (int i = 0; i < 5; i++) {
    court.sub(cu, bench, true); //select starters
    cu = cu->next;
  }
  print_ros(court, bench, "Sorted");


//check link health
/*
  cout << endl; // delete after fixing Swap function
  Player *tmp = court.head;
  for (int i = 0; i < 5; i++) {
    cout << tmp->number << "->";
    tmp = tmp->next;
  }
*/ /////////////////////////////////////////



// 2K20 Rizk Edition

  int minute = 1, quarter = 1, tmp;
  string quarters[4] = { "First", "Second", "Third", "Fourth" };
  ofstream ofs("sub_log.txt");

  while(quarter <= 4) {
    cout << '\n' << quarters[quarter - 1] << " quarter ====================================\n";
    while (minute <= 12) {
      cout << "[" << quarter << "] " << minute << ":\n";
      minute++;

      // evaluate player & times
      Player *cu = court.head;
      for (int p = 0; p < 12; p++) {
        if (p < 5) { // court players
          if (cu->session > cu->rating / 15) {
            cout << '\t' << cu->number << " subbed out after playing " << cu->session << " minutes.\n";
            tmp = cu->number;
            cu->session = 0;
            court.sub(cu, bench);
            ofs << '\t' << cu->number << '\t' << tmp << '\t' << "Q" << quarter << ":" << minute - 1<< '\n';
          }
          cu->minutes++;
        }
        else { // bench players
          if (cu->session > 10 ) {
            cout << '\t' << cu->number << " subbed back in for ";
            tmp = cu->number;
            cu->session = 0; // current bench player
            bench.sub(cu,court);
            cout << cu->number << '\n'; // court player
            ofs << '\t' << cu->number << '\t' << tmp << '\t' << "Q" << quarter << ":" << minute - 1<< '\n';
          }
        }
        cu->session++;
        cu = cu->next;
        if (p == 4) cu = bench.head; // switch over to bench at end of court
      }

      system("timeout -t 1 >NUL");
    }
    minute = 1;
    quarter++;
  }
  ofs.close();
  cout << "\n\tGame over! Go Coogs!\n\n";

  print_ros(court, bench, "Ending");
  cout << string(2, '\n');
  Roster merged(false);
  for (int i = 0; i < 5; i++) {
    merged.add_end(court.get(i));
  }
  for (int i = 0; i < 7; i++) {
    merged.add_end(bench.get(i));
  }

  system("pause");

  while(1) {
    cls();
    int choice;
    string line;
    ifstream ifs("menu.txt");
    while(!ifs.eof()) {
      getline(ifs, line);
      cout << line << '\n';
    }
    cout << "|     Enter your choice: ";
    cin >> choice;

  switch (choice) {
    case 1:
      cls();
      make_report(merged, MINUTES);
      break;
    case 2:
      cls();
      make_report(merged, AGE);
      break;

    case 3:
      cls();
      make_report(merged, RATING);
      break;
    case 4:
      cls();
      make_report(merged, NUMBER);
      break;
    case 5:
      cls();
      sub_report();
      break;
    case 6: //done
      return 0;
    default:
      break;
  }


  }



  merged.sort(NUMBER);

  return 0;
}
