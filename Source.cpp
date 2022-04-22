#include"Tree.h"
#include<array>
int main() {
	std::array<Product, 7> Elements;
	bSearchTreeType<Product> Tree;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	/*Elements[0].changeProductCode(56);
	Elements[1].changeProductCode(96);
	Elements[2].changeProductCode(60);
	Elements[3].changeProductCode(22);
	Elements[4].changeProductCode(85);*/

	bool tmpFlag = true;
	int ActiveMenu = 8;
	while (tmpFlag == true) {
		system("cls");
		menu(ActiveMenu);
		tmpFlag = pointer(Tree, ActiveMenu);
	}
	/*for (int i = 0; i<Elements.size(); i++) {
		Tree.insert(Elements[i]);
	}
	std::cout<<Tree.treeLeavesCount();
	std::seek()*/
	//Tree.FindMiddleElement(PrintProduct);
	return 0;
}