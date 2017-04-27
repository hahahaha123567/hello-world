/*
backtrack: dfs + prun
first use of cpp = = ugly code
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int infinity = 65535;

class problem {
public:
	problem(const string & name, int solveTime, int debugTime);
	bool equal(problem i);
	string name;
	int solveTime;
	int debugTime;
	bool searched;
};

problem::problem(const string & name, int solveTime, int debugTime) 
	: name(""), solveTime(0), debugTime(0), searched(false)
{
	this->name = name;
	this->solveTime = solveTime;
	this->debugTime = debugTime;
}

inline bool problem::equal(problem i)
{
	if (name == i.name)
		return true;
	else {
		return false;
	}
}

class problemSequence {
public:
	problemSequence();
	problemSequence(int totalTime, int problemNum, int readTime);
	vector<problem> sequence;
	void addProblem(problem i);
	void deleteProblem();
	void calc();
	void print();
	bool find(problem p);
	int scoreTime, solveNum, problemNum, size;
private:
	int totalTime, readTime;
	int usedTime;
};

problemSequence::problemSequence()
	: totalTime(0), problemNum(0), readTime(0), size(0){}

problemSequence::problemSequence(int totalTime, int problemNum, int readTime)
	: totalTime(0), problemNum(0), readTime(0), size(0)
{
	this->totalTime = totalTime * 60;
	this->problemNum = problemNum;
	this->readTime = readTime;
}

inline void problemSequence::addProblem(problem i)
{
	size++;
	sequence.push_back(i);
}

inline void problemSequence::deleteProblem()
{
	size--;
	sequence.pop_back();
}

void problemSequence::calc()
{
	int debugNum = 0;
	solveNum = 0;
	usedTime = readTime;
	scoreTime = 0;
	vector<problem>::iterator it = sequence.begin();

	while (it != sequence.end()) {
		debugNum = (usedTime + it->solveTime) / 60;
		if ((usedTime + it->solveTime) % 60 == 0) {
			debugNum--;
		}
		int thisTime = it->solveTime + it->debugTime * debugNum;
		if (usedTime + thisTime <= totalTime) {
			it++;
			solveNum++;
			usedTime += thisTime;
			scoreTime += usedTime;
			scoreTime += 20 * debugNum;
		}
		else {
			break;
		}
	}
}

inline void problemSequence::print()
{
	vector<problem>::iterator it = sequence.begin();
	cout << "Total Time = " << scoreTime << endl;
	for (int i = 0; i < solveNum; ++i, ++it) {
		cout << it->name << endl;
	}
}

inline bool problemSequence::find(problem p)
{
	for (auto it : sequence) {
		if (it.equal(p))
			return true;
	}
	return false;
}

problemSequence answer;

void backTrack(problemSequence & input, problemSequence now, int level)
{
	if (level > input.problemNum + 1)
		return;
	//calculate current sequence
	now.calc();
	if (now.solveNum < now.size)
		return;
	if ((now.solveNum > answer.solveNum) || (now.solveNum == answer.solveNum && now.scoreTime < answer.scoreTime)) {
		answer = now;
	}
	//depth first search
	vector<problem>::iterator it;
	for (it = input.sequence.begin(); it != input.sequence.end(); it++) {
		if (now.find(*it)) {
			//cout << "In level " << level << ": " << it->name << " is rejected" << endl;
			continue;
		}
		else {
			//cout << "In level " << level << ": " << it->name << " is accepted" << endl;
			now.addProblem(*it);
			backTrack(input, now, level+1);
			now.deleteProblem();
		}
	}
}

int main()
{
	int totalTime, problemNum, readTime;

	cin >> totalTime;
	while (totalTime >= 0) {
		cin >> problemNum >> readTime;
		//build a sequence, store the input
		problemSequence input(totalTime, problemNum, readTime);
		for (int i = 0; i < problemNum; i++) {
			string name;
			int solveTime, debugTime;
			cin >> name >> solveTime >> debugTime;
			problem temp(name, solveTime, debugTime);
			input.addProblem(temp);
		}
		//execute
		problemSequence now(totalTime, problemNum, readTime);
		answer.solveNum = 0, answer.scoreTime = infinity;
		backTrack(input, now, 1);
		answer.print();
		cin >> totalTime;
	}

	return 0;
}