#include <iostream>
#include <vector>
using namespace std;

struct Person {
  int id;
  vector<int> milkTypes;
  vector<int> timesD;
  int timeS = -1;
};

int main() {
  //n is for number of lines, m is for types of milk, d is for number of lines with pmt, s is for number of lines with sick people pt
  int n,m,d,s;
  cin >> n >> m >> d >> s;
  vector <Person> people;

  //receiving and saving data for each person - id, types of milk drunk, times the types of milk were drunk
  for(int i = 0; i < d; i++) {
    int id, milk, timeD;
    cin >> id >> milk >> timeD;
    bool found = false;
    for(int j = 0; j < people.size(); j++) {
      //if already existing, just add new milk type and type to preexisting person's vectors
      if(people[j].id == id) {
        people[j].milkTypes.push_back(milk);
        people[j].timesD.push_back(timeD);
        found = true;
        break;
      }

    }
    //if the person is not found, create a new person and save info into the new person
    if(!found){
        Person temp;
        temp.id = id;
        temp.milkTypes.push_back(milk);
        temp.timesD.push_back(timeD);
        people.push_back(temp);
    }
  }

  //cout << people.size() << endl;
  
  //receive input for sick people
  for(int i = 0; i < s; i++) {
    int id, timeS;
    cin >> id >> timeS;

    //find person who is sick using id and then save the time they became sick into the preexisting person's data
    for(int j = 0; j < people.size(); j++) {
      if(people[j].id == id) {
        //cout << ",";
        people[j].timeS = timeS;
        break;
      }
    }
    
  }

  vector<int> peopleSick;
  for(int i = 0; i < people.size(); i++) {
    if(people[i].timeS != -1) {
      peopleSick.push_back(i);
    }
  }
  
  vector <int> possibleContMilk;
  for(int i = 0; i < people.size(); i++) {
    for(int j = 0; j < people[i].milkTypes.size(); j++) {
      //if the person got sick after drinking the milk, save into array of possible types of contaminated milk
      if(people[i].timesD[j] < people[i].timeS && people[i].timeS != -1) {
        bool allDrunk = true;
        for(int k = 0; k < peopleSick.size(); k++) {
          bool drunkMilk = false;
          for(int l = 0; l < people[k].milkTypes.size(); l++) {
            if(people[k].milkTypes[l] == people[i].milkTypes[j]) {
              drunkMilk = true;
              break;
            }
          }
          if(!drunkMilk) {
            allDrunk = false;
            break;
          }
        } 
        if(allDrunk) {
          possibleContMilk.push_back(people[i].milkTypes[j]);
        }
      }
    }
  }

  // for(int i = 0; i < possibleContMilk.size(); i++) {
  //   cout << possibleContMilk[i] << " ";
  // }
  // cout << endl;

  
  //create new array containing only unique types of milk
  
  vector<int> filteredPossContMilk;
  for(int i = 0; i < possibleContMilk.size(); i++) {
    bool reoccur = false;
    for(int j = 0; j < filteredPossContMilk.size(); j++) {
      if(possibleContMilk[i] == filteredPossContMilk[j]) {
        reoccur = true;
        break;
      }
    }
    
    if(!reoccur) {
      filteredPossContMilk.push_back(possibleContMilk[i]);
    }
  }

   for(int i = 0; i < filteredPossContMilk.size(); i++) {
      cout << filteredPossContMilk[i] << " ";
   }
  
  //find which type of milk caused the most people to become sick
  vector<int> countForConMilk;
  for(int i = 0; i < filteredPossContMilk.size(); i++) {
    countForConMilk.push_back(0);
  }
  
  for(int i = 0; i < people.size(); i++) {
    for(int j = 0; j < people[i].milkTypes.size(); j++) {
      for(int k = 0; k < filteredPossContMilk.size(); k++) {
        if(people[i].milkTypes[j] == filteredPossContMilk[k]) {
          countForConMilk[k]++;
        }
      }
    }
  }

  int treatments = 0;
  for(int i = 0; i < countForConMilk.size(); i++) {
    if(countForConMilk[i] > treatments) {
      treatments = countForConMilk[i];
    }
  }
  
  cout << treatments;
  
}


