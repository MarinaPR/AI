#include <Windows.h>
#include <list>
#include <iostream>
#include<iomanip>

using namespace std;

class State {
public:
	bool boat;              //положення човна
	bool people[3];         //положення людей(масив з 3 людей)
	bool bigMonkey;         //положення великої мавпи
	bool littleMonkeys[2];  //положення маленьких (масив з 2 мавп)
	int cost;

	State() {
	}
	State(bool b, bool* p, bool bm, bool* lm, int c) {
		this->boat = b;

		for (int i = 0; i < 3; i++) {
			this->people[i] = p[i];
		}

		this->bigMonkey = bm;
		for (int i = 0; i < 2; i++) {
			this->littleMonkeys[i] = lm[i];
		}
		this->cost = c;
	}
};

bool AnyHuman(State state) { //перевірка чи є люди для ведення човна на березі
	for (int i = 0; i < 3; i++) {
		if (state.boat == state.people[i]) {
			return true;
		}

	}
	return false;
}

list<int> LittleMonkeysOnTheSide(State state) { //рахування скільки мавп на березі (для умов)
	list<int> res;
	for (int i = 0; i < 2; i++) {
		if (state.littleMonkeys[i] == state.boat)
			res.push_back(i);
	}
	return res;
}
list<int> PeopleOnTheSide(State state) {   //скільки людей на березі (для умов)
	list<int> res;
	for (int i = 0; i < 3; i++) {
		if (state.people[i] == state.boat)
			res.push_back(i);
	}
	return res;
}

list<State> NewStates(State state) { //умови

	list<State> states;

	if (state.boat == state.bigMonkey || AnyHuman(state)) // якщо є кому везти човна 
	{
		if (state.boat == state.bigMonkey) { //якщо на березі є велика мавпа
			if (LittleMonkeysOnTheSide(state).size() != 0 && LittleMonkeysOnTheSide(state).size() >= (PeopleOnTheSide(state).size())) {//якщо є маленькі мавпи і умова дозволяє їх перевезти
				for (int i = 0; i < 2; i++) {
					if (state.littleMonkeys[i] == state.boat) {
						bool tmplMonkeys[2];
						for (int j = 0; j < 2; j++) {
							tmplMonkeys[j] = state.littleMonkeys[j];
						}
						tmplMonkeys[i] = !state.boat;

						int tmpcost = 0;
						for (int x = 0; x < 2; x++) {
							tmpcost += tmplMonkeys[x];
						}

						states.push_back(State(!state.boat, state.people, !state.bigMonkey, tmplMonkeys, 6 - (state.people[0] + state.people[1] + state.people[2] + !state.bigMonkey + tmpcost)));//наступний стан (на інший берег переїхала велика мавпа та одна маленька
					}
				}
			}

			if (PeopleOnTheSide(state).size() != 0 && (PeopleOnTheSide(state).size()) > LittleMonkeysOnTheSide(state).size()) { //якщо є люди і умова дозволяє їх перевезти
				for (int i = 0; i < 3; i++) {
					if (state.people[i] == state.boat) {
						bool tmpPeople[3];
						for (int j = 0; j < 3; j++) {
							tmpPeople[j] = state.people[j];
						}
						tmpPeople[i] = !state.boat;

						int tmpcost = 0;
						for (int x = 0; x < 2; x++) {
							tmpcost += tmpPeople[x];
						}

						states.push_back(State(!state.boat, tmpPeople, !state.bigMonkey, state.littleMonkeys, 6 - (tmpcost + !state.bigMonkey + state.littleMonkeys[0] + state.littleMonkeys[1]))); //наступний стан (на інший берег переїхала велика мавпа з людиною)
					}
				}
			}

			states.push_back(State(!state.boat, state.people, !state.bigMonkey, state.littleMonkeys, 6 - (state.people[0] + state.people[1] + state.people[2] + !state.bigMonkey + state.littleMonkeys[0] + state.littleMonkeys[1]))); //наступний стан (велика мавпа поїхала сама)
		}

		if (AnyHuman(state)) { //якщо на березі є людина
			for (int k = 0; k < 3; k++) {
				//перебір варіантів хто може поїхати з К-ю людиною
				if (LittleMonkeysOnTheSide(state).size() != 0 && LittleMonkeysOnTheSide(state).size() >= (PeopleOnTheSide(state).size())) {//якщо на цьому березі є маленькі мавпи яких можна перевезти людині
					for (int i = 0; i < 2; i++) {
						if (state.littleMonkeys[i] == state.boat && state.people[k] == state.boat) {
							bool tmplMonkeys[2];
							for (int j = 0; j < 2; j++) {
								tmplMonkeys[j] = state.littleMonkeys[j];
							}
							tmplMonkeys[i] = !state.boat;

							int tmpMcost = 0;
							for (int x = 0; x < 2; x++) {
								tmpMcost += tmplMonkeys[x];
							}

							bool tmpPeople[3];
							for (int j = 0; j < 3; j++) {
								tmpPeople[j] = state.people[j];
							}
							tmpPeople[k] = !state.boat;

							int tmpcost = 0;
							for (int x = 0; x < 2; x++) {
								tmpcost += tmpPeople[x];
							}

							states.push_back(State(!state.boat, tmpPeople, state.bigMonkey, tmplMonkeys, 6 - (tmpcost + state.bigMonkey + tmpMcost)));//наступний стан, коли людина перевозить малу мавпу на наступний берег
						}
					}
				}
				if (PeopleOnTheSide(state).size() != 0 && (PeopleOnTheSide(state).size() - 1) >= LittleMonkeysOnTheSide(state).size()) { //якщо на березі є люди які можуть поїхати на інший берег
					for (int i = 0; i < 3; i++) {
						if (state.people[i] == state.boat) {
							if (i == k) {
								if (state.people[k] == state.boat) {
									bool tmpMainPeople[3]; //людина, що сидить у човні - поїде сама
									for (int j = 0; j < 3; j++) {
										tmpMainPeople[j] = state.people[j];
									}
									tmpMainPeople[i] = !state.boat;

									int tmpcost = 0;
									for (int x = 0; x < 2; x++) {
										tmpcost += tmpMainPeople[x];
									}

									states.push_back(State(!state.boat, tmpMainPeople, state.bigMonkey, state.littleMonkeys, 6 - (tmpcost + state.bigMonkey + state.littleMonkeys[0] + state.littleMonkeys[1]))); //наступний стан, коли людина поїхала сама
								}
							}
							else {
								if ((PeopleOnTheSide(state).size() - 2) >= LittleMonkeysOnTheSide(state).size()) {
									bool tmpPeople[3];
									for (int j = 0; j < 3; j++) {
										tmpPeople[j] = state.people[j];
									}
									tmpPeople[i] = !state.boat;
									tmpPeople[k] = !state.boat;
									int tmpcost = 0;
									for (int x = 0; x < 2; x++) {
										tmpcost += tmpPeople[x];
									}

									states.push_back(State(!state.boat, tmpPeople, state.bigMonkey, state.littleMonkeys, 6 - (tmpcost + state.bigMonkey + state.littleMonkeys[0] + state.littleMonkeys[1]))); //наступний стан, коли люди поїхали вдвох
								}
							}
						}
					}
				}
				if (state.bigMonkey == state.boat) {  //якщо на березі є велика мавпа
					if (state.people[k] == state.boat) {
						bool tmpPeople[3];
						for (int j = 0; j < 3; j++) {
							tmpPeople[j] = state.people[j];
						}
						tmpPeople[k] = !state.boat;

						int tmpcost = 0;
						for (int x = 0; x < 2; x++) {
							tmpcost += tmpPeople[x];
						}

						states.push_back(State(!state.boat, tmpPeople, !state.bigMonkey, state.littleMonkeys, 6 - (tmpcost + !state.bigMonkey + state.littleMonkeys[0] + state.littleMonkeys[1])));// людина поїхала з великою мавпою
					}
				}
			}
		}

	}
	return states;
}

list<State> Sort(list<State> state) {   //сортування списку станів за вартістю, щоб підняти кращі та опустити гірші стани.
	State min_cost = State(state.front().boat, state.front().people, state.front().bigMonkey, state.front().littleMonkeys, state.front().cost);
	for (State s : state) {
		if (s.cost < min_cost.cost) {
			min_cost = s;
		}
	}

	auto iter = state.cbegin();
	auto itermin = state.cbegin();
	int i = 0;

	for (State s : state) {
		i++;
		if (min_cost.cost == s.cost) {
			break;
		}
		iter++;
	}

	if (iter != state.cbegin()) {
		if (state.size() > 1) {
			if (iter != state.cend()) {
				state.erase(iter);
				state.push_front(min_cost);
			}
			else {
				state.pop_back();
				state.push_front(min_cost);
			}
		}
	}

	return state;
}
void print(State state) {
	cout << setw(17) << "ЛОДКА" << setw(15) << "[ЧЕЛОВЕК 1]" << setw(15) << "[ЧЕЛОВЕК 2]" << setw(15) << "[ЧЕЛОВЕК 3]" << setw(10) << "МАВПА" << setw(15) << "[мавпа 1]" << setw(15) << "[мавпа 2]" << setw(10) << "ВЕС" << endl;
	cout << setw(15) << state.boat << setw(12) << state.people[0] << setw(15) << state.people[1] << setw(15) << state.people[2] << setw(13) << state.bigMonkey << setw(13) << state.littleMonkeys[0] << setw(15) << state.littleMonkeys[1] << setw(13) << state.cost << endl;

}
bool goal(State state) { //всі опинилися на іншому березі
	if (state.people[0] == true && state.people[1] == true && state.people[2] == true && state.bigMonkey == true && state.littleMonkeys[0] == true && state.littleMonkeys[1] == true) {
		return true;
	}
	else return false;
}
bool Beam(State state) {
	int beamwidth = 1;  //для цієї задачі вистачає ширини променя 1
	cout << endl << "= = = = = = = = = = = = = = = = = = = = = = = = = = [ Ш А Г ]  = = = = = = = = = = = = = = = = = = = = = = = = = " << endl;  //одна ітерація

	cout << endl << " Один Берег: " << endl;
	print(state);  //стан, який обробляється
	list<State> list = NewStates(state);
	list = Sort(list);
	while (list.size() > beamwidth) { //видалення всіх станів, що виходять за межі ширини променя
		list.pop_back();
	}
	cout << " Другой Берег: " << endl; //можливі наступні стани
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		cout << setw(15) << (*iter).boat << setw(12) << (*iter).people[0] << setw(15) << (*iter).people[1] << setw(15) << (*iter).people[2]
			<< setw(13) << (*iter).bigMonkey << setw(13) << (*iter).littleMonkeys[0] << setw(15) << (*iter).littleMonkeys[1] << setw(13) << (*iter).cost << endl;
	}
	State decision = State(list.front().boat, list.front().people, list.front().bigMonkey, list.front().littleMonkeys, list.front().cost); //найвигідніший стан для переходу

	while (!goal(decision)) { //якщо не всі переїхали на інший берег

		if (Beam(decision)) { // переходимо до наступного стану
			break; //якщо всі переїхали - виходимо з алгоритму
		}
	}
	return true;
}

int main() {
	setlocale(LC_ALL, "Russian");
	State start;   //перший стан. Всі на лівому березі.
	start.boat = false;
	start.people[0] = false;
	start.people[1] = false;
	start.people[2] = false;
	start.bigMonkey = false;
	start.littleMonkeys[0] = false;
	start.littleMonkeys[1] = false;
	start.cost = 6;
	Beam(start);
	return 0;
}
