#include "classes.h"
#include <iostream>
using namespace std;
int main() {
	linkedList<string> list;
	list.add("mom");
	list.add("dad");
	list.add("uncle");
	list.add("grandpa");
	list.print();

	return 0;
}
