#ifndef TREE_H
#define TREE_H


#include<iostream>
#include<string>
#include<fstream>
#include<stack>
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#define UP 72
#define DOWN 80
#define ENTRY 13
#define ESC 27
#define CLEAN system("cls"); // отчистка консоли
#define PAUSE system("pause");
#define ClEANCONSOLE std::cin.clear(); std::cin.ignore(32767, '\n');
////////Prototype fuction////////
extern void menu(int ActiveMenu);

////////End Prototype/////////
class Product {
private:
	int ProductCode;//ключ(номер товара)
	std::string Name;//название товара
	int Count;//количество товара
	float PriseForOne;//цена за 1 ед
	static std::streampos readPos;
	static std::streampos writePos;
public:
	static void SetReadPos(std::streampos pos) { readPos = pos; }
	static void SetWritePos(std::streampos pos) { writePos = pos; }
	Product(int productCode = 0, std::string name = "none", int Count = 0, float prise = 0) : ProductCode(productCode), Name(name), Count(Count), PriseForOne(prise) {
	}
	bool ReadInfoProduct();
	void WriteInfoProduct();
	void changeName(std::string NewName) { this->Name = NewName; }
	void changeCount(int NewCount) { this->Count = NewCount; }
	void changePriseForOne(float NewPrise) { this->PriseForOne = NewPrise; }
	bool changeProductCode(int code) { if (IsCanAdd()) { this->ProductCode = code; return true; }return false; }
	bool IsCanAdd() { if (ProductCode == 0) return true; return false; }
	friend void PrintProduct(Product& pd);
	friend void WriteInFile(Product& pd);
	bool operator==(Product& pd) { if (this->ProductCode == pd.ProductCode) return true; return false; }
	bool operator>(Product& pd) { if (this->ProductCode > pd.ProductCode) return true; return false; }
	bool operator>(int pd) { if (this->ProductCode > pd) return true; return false; }
	Product& operator/(int x) { this->ProductCode /= x; return *this; }
	Product& operator*(int x){ this->ProductCode= ProductCode*x; return *this; }
	Product(const Product& pd) {
		this->Count = pd.Count;
		this->Name = pd.Name;
		this->PriseForOne = pd.PriseForOne;
		this->ProductCode = pd.ProductCode;
	}
	Product& operator=(const Product& pd) {
		this->Count = pd.Count;
		this->Name = pd.Name;
		this->PriseForOne = pd.PriseForOne;
		this->ProductCode = pd.ProductCode;
		return *this;
	}
	Product& operator+(const Product& pd) {
		this->ProductCode += pd.ProductCode;
		return *this;
	}
	Product& operator-(const Product& pd) {
		this->ProductCode -= pd.ProductCode;
		return *this;
	}
};
void PrintProduct(Product& pd);
void WriteInFile(Product& pd);

template<typename Type>
struct Node
{
	Type info;//информация в узле
	Node<Type>* lLink;//ссылка на левое поддерево
	Node<Type>* rLink;//ссылка на правое поддерево
	Node(Type inf = Type(), Node<Type>* l = nullptr, Node<Type>* r = nullptr) : info(inf), lLink(l), rLink(r) {};

};
template<typename Type>
class binaryTreeType
{
private:

	void copyTree(Node<Type>*& copiedNode, Node<Type>*& otherNode);//копирование одного узла
	void destroy(Node<Type>*& destryNode);// удаление всей ветвей под определённых элементом
	void inorder(Node<Type>*& p);// левый, сам элемент, правый
	//void preorder(Node<Type>*& p);// сам элемент, левый,правый
	void postorder(Node<Type>*& p);// левый, правый, сам элемент
	int height(Node<Type>*& p);//высота элемента до Node
	int Max(int x, int y) const;
	int NodeCount(Node<Type>*& p);//количество нодов в P
	int leavesCount(Node<Type>* p);//количесвто листоков в Р
protected:
	Node<Type>* root;//указатель на вершину дерева
public:
	binaryTreeType<Type> operator=(binaryTreeType<Type>& p);
	bool isEmpty() const;
	void inorderTraversal();
	
	void postorderTraversal();
	int treeHeight();
	int treeNodeCount();
	int treeLeavesCount();
	void destroyTree();
	virtual bool search(Type& searchItem, void(*visit)(Type&), void(*menu)()) const = 0;// при необходимисти изменить Type
	virtual bool insert(Type& insertItem) = 0;
	virtual void deleteNode(Type& deleteItem) = 0;
	binaryTreeType();
	binaryTreeType(binaryTreeType<Type>& copiedNode);
	virtual ~binaryTreeType();
	//////////////Binary tree traversal algoritm
	void inorderTraversal(void (*visit)(Type&));
	void preorderTraversal(void(*visit)(Type&));
private:
	void inorder(Node<Type>* p, void (*visit)(Type&));
	void preorder(Node<Type>*& p, void(*visit)(Type&));// сам элемент, левый,правый

};

/////////////////////Implementation////////////////////
template<typename Type>
inline void binaryTreeType<Type>::preorder(Node<Type>*& p, void(*visit)(Type&))
{
	if (p != nullptr) {
		visit(p->info);
		preorder(p->lLink, visit);
		preorder(p->rLink, visit);
	}
}

template<typename Type>
inline binaryTreeType<Type> binaryTreeType<Type>::operator=(binaryTreeType<Type>& p)
{
	copyTree(root, p.root);
	return *this();
}

template<typename Type>
inline bool binaryTreeType<Type>::isEmpty() const
{
	if (root == nullptr) {
		return true;
	}
	else return false;
}

template<typename Type>
inline void binaryTreeType<Type>::inorderTraversal()
{
	inorder(this->root);
}

template<typename Type>
inline void binaryTreeType<Type>::preorderTraversal(void(*visit)(Type&))
{
	preorder(root,visit);
}

template<typename Type>
inline void binaryTreeType<Type>::postorderTraversal()
{
	postorder(root);
}

template<typename Type>
inline binaryTreeType<Type>::binaryTreeType()
{
	root = nullptr;
}

template<typename Type>
inline binaryTreeType<Type>::binaryTreeType(binaryTreeType<Type>& copiedNode)
{
	if (copiedNode.root == nullptr) {
		this->root = nullptr;
	}
	else {
		this->copyTree(root, copiedNode.root);
	}
}

template<typename Type>
inline binaryTreeType<Type>::~binaryTreeType()
{
	destroyTree();
}

template<typename Type>
inline void binaryTreeType<Type>::inorderTraversal(void(*visit)(Type&))
{
	this->inorder(this->root, *visit);
}

template<typename Type>
inline void binaryTreeType<Type>::inorder(Node<Type>* p, void(*visit)(Type&))
{
	if (p != nullptr) {
		inorder(p->lLink, *visit);
		visit(p->info);
		inorder(p->rLink, *visit);
	}
}

template<typename Type>
inline void binaryTreeType<Type>::copyTree(Node<Type>*& copiedNode, Node<Type>*& otherNode)
{
	if (otherNode == nullptr) {
		copiedNode = nullptr;
	}
	else {
		copiedNode = new Node<Type>;
		copiedNode->info = otherNode->info;
		copyTree(copiedNode->lLink, otherNode->lLink);
		copyTree(copiedNode->rLink, otherNode->lLink);
	}

}

template<typename Type>
inline void binaryTreeType<Type>::destroy(Node<Type>*& destryNode)
{
	if (destryNode != nullptr) {
		destroy(destryNode->rLink);
		destroy(destryNode->lLink);
		delete destryNode;
		destryNode = nullptr;
	}
}

template<typename Type>
inline void binaryTreeType<Type>::inorder(Node<Type>*& p)
{
	if (p != nullptr) {
		inorder(p->lLink);
		std::cout << p->info << " ";
		inorder(p->rLink);
	}
}

//template<typename Type>
//inline void binaryTreeType<Type>::preorder(Node<Type>*& p)
//{
//	if (p != nullptr) {
//		std::cout << p->info << " ";
//		preorder(p->lLink);
//		preorder(p->rLink);
//	}
//}

template<typename Type>
inline void binaryTreeType<Type>::postorder(Node<Type>*& p)
{
	if (p != nullptr) {
		postorder(p->lLink);
		postorder(p->rLink);
		std::cout << p->info << " ";
	}
}

template<typename Type>
inline int binaryTreeType<Type>::height(Node<Type>*& p)
{
	if (p == nullptr)
		return 0;
	else {
		return 1 + Max(height(p->lLink), height(p->rLink));
	}
}

template<typename Type>
inline int binaryTreeType<Type>::Max(int x, int y) const
{
	if (x >= y) {
		return x;
	}
	else return y;
}

template<typename Type>
inline int binaryTreeType<Type>::NodeCount(Node<Type>*& p)
{
	if (p == nullptr) {
		return 0;
	}
	else return 1 + NodeCount(p->lLink) + NodeCount(p->rLink);
}

template<typename Type>
inline int binaryTreeType<Type>::leavesCount(Node<Type>* p)
{
	if (p == nullptr) {
		return 0;
	}

	else return leavesCount(p->lLink) + leavesCount(p->rLink)+1;
}

template<typename Type>
inline int binaryTreeType<Type>::treeHeight()
{
	return height(this->root);
}

template<typename Type>
inline int binaryTreeType<Type>::treeNodeCount()
{
	return NodeCount(this->root);
}

template<typename Type>
inline int binaryTreeType<Type>::treeLeavesCount()
{
	return leavesCount(this->root);
}

template<typename Type>
inline void binaryTreeType<Type>::destroyTree()
{
	destroy(this->root);

}




///////////Class bSearchTreeType/////////////////

template<class Type>
class bSearchTreeType :public binaryTreeType<Type> {
public:
	bSearchTreeType<Type>() :binaryTreeType<Type>() {}
	bool search(Type& searchItem, void(*visit)(Type&), void(*menu)()) const override;
	bool insert(Type& insertItem) override;
	void deleteNode(Type& deleteItem) override;
	~bSearchTreeType() {}
private:
	void deleteFromTree(Node<Type>*& p);
public:
	void TraversalForMiddle(Type* tp, Node<Type>* CheckNode);
	void FindMiddleElement(void(*visit)(Type&));
	Type MaxElement();//находит максимальное значение
	Type MinElement();//находит минимальное значение
};

template<class Type>
inline bool bSearchTreeType<Type>::search(Type& searchItem,void(*visit)(Type&), void(*menu)()) const
{
	if (this->root == nullptr)
		return false;
	else {
		Node<Type>* current = this->root;
		bool found = false;
		while (current != nullptr && !found) {
			if (current->info == searchItem) {
				menu();
				visit(current->info);
				found = true;
			}
			else if (current->info > searchItem) {
				current = current->lLink;
			}
			else current = current->rLink;
		}
		return found;
	}
}

template<class Type>
inline bool bSearchTreeType<Type>::insert(Type& insertItem)
{
	Node<Type>* NewNode = new Node<Type>(insertItem);
	if (this->root == nullptr) {
		this->root = NewNode;
	}
	else {
		Node<Type>* current = this->root;
		Node<Type>* trailCurrent = nullptr;
		while (current != nullptr)
		{
			trailCurrent = current;
			if (current->info == insertItem) {
				std::cout << "Елемент с таким ключом уже существует! ";
				return false; 
			}
			else if (current->info > insertItem)
				current = current->lLink;
			else current = current->rLink;
		}
		if (trailCurrent->info > insertItem) {
			trailCurrent->lLink = NewNode;
		}
		else trailCurrent->rLink = NewNode;
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////1442pages
template<class Type>
inline void bSearchTreeType<Type>::deleteNode(Type& deleteItem)
{
	if (this->root == nullptr) {
		std::cout << "Бинарное дерево ещё не выросло!" << std::endl;
	}
	Node<Type>* current = this->root;
	Node<Type>* trailCurrent = this->root;
	bool found = false;
	while (current != nullptr && !found) {

		if (current->info == deleteItem) {
			found = true;
		}
		else {
			trailCurrent = current;
			if (current->info > deleteItem) {
				current = current->lLink;
			}
			else {
				current = current->rLink;
			}
		}
	}
	if (current == nullptr) {
		std::cout << "Данный элемент не найден в дереве!" << std::endl;
	}
	else if (found) {
		if (current == this->root) {
			deleteFromTree(this->root);
		}
		else if (trailCurrent->info > deleteItem) {
			deleteFromTree(trailCurrent->lLink);
		}
		else
			deleteFromTree(trailCurrent->rLink);
		std::cout << "Элемент успешно удалён!";
	}
	else std::cout << "Данный элемент не найден в дереве!" << std::endl;
}

template<class Type>
inline void bSearchTreeType<Type>::deleteFromTree(Node<Type>*& p)
{
	Node<Type>* current = nullptr;
	Node<Type>* trailCurrent = nullptr;
	Node<Type>* tmp = nullptr;
	Node<Type>* main = this->root;
	if (p == nullptr) {
		std::cout << "Error: The node to be deleted does not exist." << std::endl;
	}
	else if (p->lLink == nullptr && p->rLink == nullptr) {
		tmp = p;
		p = nullptr;
		delete tmp;
	}
	else if (p->lLink == nullptr) {
		tmp = p;
		p = p->rLink;
		delete tmp;
	}
	else if (p->rLink == nullptr) {
		tmp = p;
		p = p->lLink;
		delete tmp;
	}
	else {
		trailCurrent = nullptr;
		current = p->lLink;
		while (current->rLink != nullptr) {
			trailCurrent = current;
			current = current->rLink;
		}
		p->info = current->info;
		if (trailCurrent == nullptr) {
			p->lLink = current->lLink;
		}
		else {
			trailCurrent->rLink = current->lLink;
		}
		delete current;
	}
}

template<typename Type>
inline Type bSearchTreeType<Type>::MinElement()
{
	Node<Type>* current = this->root;
	while (current->lLink != nullptr)
	{
		current = current->lLink;
	}
	return current->info;
}

template<typename Type>
inline Type bSearchTreeType<Type>::MaxElement()////////////////////////////////////////////////////////////////////////////////
{
	Node<Type>* current = this->root;
	while (current->rLink != nullptr)
	{
		current = current->rLink;
	}
	return current->info;
}
template<typename Type>
inline void bSearchTreeType<Type>::FindMiddleElement(void(*visit)(Type&))
{
	
	Type Arerage = (MaxElement() + MinElement()) / 2;
	Type Tmp3 = Arerage;
	Type TmpMain= Arerage-this->root->info;
	Type Tmp2= this->root->info;
	Type Answer= this->root->info;
	if (!(TmpMain > 0)) { TmpMain = TmpMain * (-1); }
	int i, n = 0;
	std::stack<Node<Type>*> Stack;
	Node<Type>* current = this->root;
	while ((current!=nullptr) || (!Stack.empty()))
	{
		if (current != nullptr) {
			Stack.push(current);
			current = current->lLink;
		}
		else {
			current = Stack.top();
			Stack.pop();
			Arerage = Tmp3;
			Tmp2 = Arerage - current->info;
			if (!(Tmp2 > 0)) {
				Tmp2 = Tmp2 * (-1);
			}
			if (TmpMain > Tmp2) {
				Answer = current->info;
				TmpMain = Tmp2;
			}
			current = current->rLink;
		}
	}

	visit(Answer);
}
template<typename Type>
inline void bSearchTreeType<Type>::TraversalForMiddle(Type* tp, Node<Type>* CheckNode)
{
	

}

//////Friend functions///////
void ShowMenuPrint();
Product EnterElemet();
Product EnterFullElement();
/////function prototype/////

template<typename T>
void ReadFromFileTree(bSearchTreeType<T>& tree) {
	Product tmp;
	bool Check = false;
	while (tmp.ReadInfoProduct()) {
		tree.insert(tmp);
		Check = true;
	}
	if (!Check) {
		std::cout << "В файле ничего нет =( ";
		return;
	}
	ShowMenuPrint();
	tree.preorderTraversal(PrintProduct);
}
template<typename T>
void WriteInfoInTree(bSearchTreeType<T>& tree) {
	if (tree.isEmpty()) {
		std::cout << "Простите, но я не могу записать пустое дерево =( ";
		return;
	}
	else { tree.preorderTraversal(WriteInFile); std::cout << "Данные записаны в файл =)"; }

}
template<typename T>
void PrintInfoInTree(bSearchTreeType<T>& tree) {
	if (tree.isEmpty()) {
		std::cout << "Просмотр пустого дерева не возможен!";
		return;
	}
	ShowMenuPrint();
	tree.preorderTraversal(PrintProduct);
	
}


template<typename T>
bool pointer(bSearchTreeType<T>& tree, int & ActiveMenu) {
	char ch;
	ch = _getch();
	if (ch == -32) ch = _getch(); // Отлавливаем стрелочки
	switch (ch)
	{
	case ESC:
		return false;
	case DOWN:
		if (ActiveMenu < 18)
			ActiveMenu++;
		break;
	case UP:
		if (ActiveMenu > 8)
			ActiveMenu--;
		break;
	case ENTRY:
		switch (ActiveMenu) {
		case 8:
			tree.destroyTree();
			ReadFromFileTree(tree);
			break;
		case 9:
			WriteInfoInTree(tree);
			break;
		case 10:
			PrintInfoInTree(tree);
			break;
		case 11:
			tree.destroyTree();
			std::cout << "Дерево срублено!";
			break;
		case 12: {
			Product deleteElement = EnterElemet();
			tree.deleteNode(deleteElement);
			break;
		}
		case 13: {
			Product searchElemnt = EnterElemet();
			if(tree.search(searchElemnt,PrintProduct, ShowMenuPrint)){}
			else { std::cout << "К сожалению, я не смог найти такой элемент!"; }
		}
			break;
		case 14:
			std::cout << "Высота дерева: " << tree.treeHeight();
			break;
		case 15:
			std::cout <<"Количество лепестков: " << tree.treeLeavesCount();
			break;
		case 16:
			if (tree.isEmpty()) {
				std::cout << "Дерево срублено!";
			}
			else { std::cout << "В дереве что-то есть =) "; }
			break;
		case 17:
			if (!tree.isEmpty()) {
				ShowMenuPrint();
				tree.FindMiddleElement(PrintProduct);
			}
			else std::cout << "Может сначала что-то надо ввести!";
			break;
		case 18: {
			Product insertElemnt = EnterFullElement();
			if (tree.insert(insertElemnt)) {
				std::cout << "Елемент успешно вставлен!";
			}
			break;
		}
		}
		std::cout << std::endl;
		system("pause");
		break;
	default:
		break;
	}
	return true;
}
#endif // !TREE_H