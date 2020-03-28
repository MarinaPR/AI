#include <Windows.h>
#include <list>
#include <iostream>


using namespace std;


class Node {
public:
	bool lion;
	bool fox;
	bool goose;
	bool corn;
	bool boat;
	double fCost;
	Node() {

	}
	Node(bool l, bool f, bool g, bool c, bool boat, double cost) {
		this->lion = l;
		this->fox = f;
		this->goose = g;
		this->corn = c;
		this->boat = boat;
		this->fCost = cost;
	}
};

list<Node> closeList;

bool goalSucc = false;


double Min(double a, double b) {
	return a < b ? a : b;
}

list<Node> Sort(list<Node> list) {
	Node min = Node(list.front().lion, list.front().fox, list.front().goose, list.front().corn, list.front().boat, list.front().fCost);
	auto iter = list.cbegin();
	auto itermin = list.cbegin();
	int i = 0;

	for (Node n : list) {
		if (min.fCost > n.fCost) {
			min = n;
		}
	}

	for (Node n : list) {

		i++;

		if (min.fCost == n.fCost) {
			break;
		}

		iter++;
	}

	if (iter != list.cbegin()) {
		if (list.size() > 1) {
			if (iter != list.cend()) {
				list.erase(iter);
				list.push_front(min);
			}
			else {
				list.pop_back();
				list.push_front(min);
			}
		}
	}

	return list;
}

list<Node> RemoveFirstNode(list<Node> list) {
	list.pop_front();
	return list;
}

boolean isDublicate(Node node) {

	for (Node n : closeList) {
		if (n.lion == node.lion && n.fox == node.fox && n.goose == node.goose && n.corn == node.corn && n.boat == node.boat) {
			return true;
		}
	}

	return false;
}

list<Node> ExpandNode(Node node)
{
	list<Node> succ;

	if (node.boat == node.lion) {//лев
		if (node.boat == node.fox) { //лев + лиса 
			if (node.boat == node.goose) { //лев + лиса + гусь
				if (node.boat == node.corn) {////лев + лиса + гусь + кукуруза
					//отправить лису + кукурузу на другой берег
					succ.push_back(Node(node.lion, !node.fox, node.goose, !node.corn, !node.boat, 4 - (node.lion + !node.fox + node.goose + !node.corn)));
				}
				//лев + гусь + кукуруза
				else {
					//sотправить лису на другой берег
					succ.push_back(Node(node.lion, !node.fox, node.goose, node.corn, !node.boat, 4 - (node.lion, !node.fox + node.goose, node.corn)));
				}
			}
			else {
				//лев + лиса + кукуруза 
				if (node.boat == node.corn) {
					//отправить льва на другой берег
					succ.push_back(Node(!node.lion, node.fox, node.goose, node.corn, !node.boat, 4 - (!node.lion + node.fox + node.goose + node.corn)));
					//отправить лису на другой берег
					succ.push_back(Node(node.lion, !node.fox, node.goose, node.corn, !node.boat, 4 - (node.lion + !node.fox + node.goose + node.corn)));
					//отправить лису + кукурузу на другой берег
					succ.push_back(Node(node.lion, !node.fox, node.goose, !node.corn, !node.boat, 4 - (node.lion + !node.fox + node.goose + !node.corn)));
				}
				//лев + лиса
				else {
					//отправить льва на другой берег
					succ.push_back(Node(!node.lion, node.fox, node.goose, node.corn, !node.boat, 4 - (!node.lion + node.fox + node.goose + node.corn)));
					//отправить лису на другой берег
					succ.push_back(Node(node.lion, !node.fox, node.goose, node.corn, !node.boat, 4 - (node.lion + !node.fox + node.goose + node.corn)));
				}
			}
		}
		else {
			if (node.boat == node.goose) {
				//лев + гусь + кукуруза
				if (node.boat == node.corn) {
					//отправить гуся и кукурузу на другой берег
					succ.push_back(Node(node.lion, node.fox, !node.goose, !node.corn, !node.boat, 4 - (node.lion + node.fox + !node.goose + !node.corn)));
					//отправить гуся на другой берег
					succ.push_back(Node(node.lion, node.fox, !node.goose, node.corn, !node.boat, 4 - (node.lion + node.fox + !node.goose + node.corn)));
					//отправить кукурузу на другой берег
					succ.push_back(Node(node.lion, node.fox, node.goose, !node.corn, !node.boat, 4 - (node.lion + node.fox + node.goose + !node.corn)));
				}
				//лев + гусь
				else {
					//отправить льва на другой берег
					succ.push_back(Node(!node.lion, node.fox, node.goose, node.corn, !node.boat, 4 - (!node.lion + node.fox + node.goose + node.corn)));
					//отправить гуся на другой берег 
					succ.push_back(Node(node.lion, node.fox, !node.goose, node.corn, !node.boat, 4 - (node.lion + node.fox + !node.goose + node.corn)));
					//отправить лодку 
					succ.push_back(Node(node.lion, node.fox, node.goose, node.corn, !node.boat, 4 - (node.lion + node.fox + node.goose + node.corn)));
				}
			}
			else {
				//лев + кукуруза
				if (node.boat == node.corn) {
					//отправить льва на другой берег
					succ.push_back(Node(!node.lion, node.fox, node.goose, node.corn, !node.boat, 4 - (!node.lion + node.fox + node.goose + node.corn)));
					//отправить кукурузу на другой берег
					succ.push_back(Node(node.lion, node.fox, node.goose, !node.corn, !node.boat, 4 - (node.lion + node.fox + node.goose + !node.corn)));
					//отправить лодку
					succ.push_back(Node(node.lion, node.fox, node.goose, node.corn, !node.boat, 4 - (node.lion + node.fox + node.goose + node.corn)));
				}
				//лев
				else {
					//отправить льва на другой берег
					succ.push_back(Node(!node.lion, node.fox, node.goose, node.corn, !node.boat, 4 - (!node.lion + node.fox + node.goose + node.corn)));
					//отправить лодку
					succ.push_back(Node(node.lion, node.fox, node.goose, node.corn, !node.boat, 4 - (node.lion + node.fox + node.goose + node.corn)));
				}
			}
		}
	}
	else {
		if (node.boat == node.fox) {
			if (node.boat == node.goose) {
				//лиса + гусь + кукуруза 
				if (node.boat == node.corn) {
					//отправить лису и кукурузу на другой берег
					succ.push_back(Node(node.lion, !node.fox, node.goose, !node.corn, !node.boat, 4 - (node.lion + !node.fox + node.goose + !node.corn)));
					//отправить гуся  на другой берег
					succ.push_back(Node(node.lion, node.fox, !node.goose, node.corn, !node.boat, 4 - (node.lion + node.fox + !node.goose + node.corn)));
					//отправить гуся и кукурузу на другой берег
					succ.push_back(Node(node.lion, node.fox, !node.goose, !node.corn, !node.boat, 4 - (node.lion + node.fox + !node.goose + !node.corn)));
				}
				//лиса + гусь
				else {
					//отправить лису на другой берег
					succ.push_back(Node(node.lion, !node.fox, node.goose, node.corn, !node.boat, 4 - (node.lion + !node.fox + node.goose + node.corn)));
					//отправить гуся  на другой берег
					succ.push_back(Node(node.lion, node.fox, !node.goose, node.corn, !node.boat, 4 - (node.lion + node.fox + !node.goose + node.corn)));
				}
			}
			else {
				//лиса + кукуруза
				if (node.boat == node.corn) {
					//отправить лису на другой берег
					succ.push_back(Node(node.lion, !node.fox, node.goose, node.corn, !node.boat, 4 - (node.lion + !node.fox + node.goose + node.corn)));
					//отправить кукурузу на другой берег
					succ.push_back(Node(node.lion, node.fox, node.goose, !node.corn, !node.boat, 4 - (node.lion + node.fox + node.goose + !node.corn)));
					//отправить лису и кукурузу на другой берег
					succ.push_back(Node(node.lion, !node.fox, node.goose, !node.corn, !node.boat, 4 - (node.lion + !node.fox + node.goose + !node.corn)));
					//отправить лодку на другой берег
					succ.push_back(Node(node.lion, node.fox, node.goose, node.corn, !node.boat, 4 - (node.lion + node.fox + node.goose + node.corn)));
				}
				//лиса
				else {
					//отправить лису на другой берег
					succ.push_back(Node(node.lion, !node.fox, node.goose, node.corn, !node.boat, 4 - (node.lion + !node.fox + node.goose + node.corn)));
					//отправить лодку
					succ.push_back(Node(node.lion, node.fox, node.goose, node.corn, !node.boat, 4 - (node.lion + node.fox + node.goose + node.corn)));
				}
			}
		}
		else {
			if (node.boat == node.goose) {
				//гусь + кукуруза
				if (node.boat == node.corn) {
					//отправить гуся и кукурузу на другой берег
					succ.push_back(Node(node.lion, node.fox, !node.goose, !node.corn, !node.boat, 4 - (node.lion + node.fox + !node.goose + !node.corn)));
					//отправить гуся на другой берег
					succ.push_back(Node(node.lion, node.fox, !node.goose, node.corn, !node.boat, 4 - (node.lion + node.fox + !node.goose + node.corn)));
					//отправить  кукурузу на другой берег
					succ.push_back(Node(node.lion, node.fox, node.goose, !node.corn, !node.boat, 4 - (node.lion + node.fox + node.goose + !node.corn)));
				}
				//гусь
				else {
					//отправить гуся  на другой берег
					succ.push_back(Node(node.lion, node.fox, !node.goose, node.corn, !node.boat, 4 - (node.lion + node.fox + !node.goose + node.corn)));
					//отправить лодку
					succ.push_back(Node(node.lion, node.fox, node.goose, node.corn, !node.boat, 4 - (node.lion + node.fox + node.goose + node.corn)));
				}
			}
			else {
				//кукуруза
				if (node.boat == node.corn) {
					//отправить  кукурузу на другой берег
					succ.push_back(Node(node.lion, node.fox, node.goose, !node.corn, !node.boat, 4 - (node.lion + node.fox + node.goose + !node.corn)));
					//отправить лодку
					succ.push_back(Node(node.lion, node.fox, node.goose, node.corn, !node.boat, 4 - (node.lion + node.fox + node.goose + node.corn)));
				}
				//конец
				else {
					cout << "WWWWWWWW" << endl;
				}
			}
		}
	}

	return succ;
}

Node RBFS(Node root, double limit)
{
	list<Node> openList;

	if (root.lion == true && root.fox == true && root.goose == true && root.corn == true)
	{
		cout << '\n' << "                          [ Начальное условие ]   " << '\n' << endl;
		cout << "Лев:  " << root.lion << "  Лиса:  " << root.fox << "  Гусь:  " << root.goose << "  Кукуруза:  " << root.corn << "  Лодка с Фермером:  " << root.boat << "  Вес:  " << root.fCost << endl;
		goalSucc = true;
		return root;
	}
	else
	{
		list<Node> successors = ExpandNode(root);

		successors = Sort(successors);

		if (successors.front().fCost > limit)
		{
			return successors.front();
		}
		else
		{
			closeList.push_back(root);

			for (Node s : successors)
			{
				if (!isDublicate(s)) {
					openList.push_back(s);
				}
			}

			if (openList.size() >= 1) {
				openList = Sort(openList);
				Node bestNode;
				Node alternativeNode;

				while (goalSucc == false)
				{
					if (openList.size() >= 1) {
						bestNode = Node(openList.front().lion, openList.front().fox, openList.front().goose, openList.front().corn, openList.front().boat, openList.front().fCost);
						//Node(openList.front().goat, openList.front().wolf, openList.front().cabbage, openList.front().boat, openList.front().fCost);
						openList.pop_front();
					}
					else {
						cout << "Failure" << endl;
						break;
					}

					if (openList.size() >= 1) {
						alternativeNode = Node(openList.front().lion, openList.front().fox, openList.front().goose, openList.front().corn, openList.front().boat, openList.front().fCost);
						openList.pop_front();
					}
					else {
						alternativeNode = Node(NULL, NULL, NULL, NULL, NULL, 1000);
					}
					bestNode = RBFS(bestNode, Min(limit, alternativeNode.fCost + 1));

					cout << endl;
					openList.push_back(bestNode);

					openList = Sort(openList);
				}
			}
		}
	}

	if (goalSucc) {
		cout << "= = = = = = = = = = = = = = = = = = Шаг = = = = = = = = = = = = = = = = =" << endl;
		cout << "Лев:  " << root.lion << "  Лиса:  " << root.fox << "  Гусь:  " << root.goose << "  Кукуруза:  " << root.corn << "  Лодка с Фермером:  " << root.boat << "  Вес:  " << root.fCost << endl;
	}

	return root;
}

int main() {
	setlocale(LC_ALL, "Russian"); 
	Node start;
	start.lion = false;
	start.fox = false;
	start.goose = false;
	start.corn = false;
	start.boat = false;
	start.fCost = 4;
	RBFS(start, 1000);
	return 0;
}
