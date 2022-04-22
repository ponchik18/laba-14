#include"Tree.h"

std::streampos Product::readPos = 0;
std::streampos Product::writePos = 0;

void PrintProduct(Product& pd)
{
	std::cout.setf(std::ios::left);
	std::cout.width(9);
	std::cout << pd.ProductCode;
	std::cout.width(25);
	std::cout << pd.Name;
	std::cout.width(20);
	std::cout << pd.Count;
	std::cout.width(20);
	std::cout << std::fixed;
	std::cout.precision(2);
	std::cout << pd.PriseForOne;
	std::cout << std::endl;
	std::cout.unsetf(std::ios::left);
}

void WriteInFile(Product& pd)
{
	pd.WriteInfoProduct();
}

void Product::WriteInfoProduct()
{
	std::ofstream into;
	if (writePos == 0) {
		into.open("Product.dat", std::ios::binary | std::ios::trunc);
		if (!into.is_open()) {
			exit(0);
		}
	}
	else {
		into.open("Product.dat", std::ios::binary | std::ios::app);
		if (!into.is_open()) {
			exit(0);
		}
	}
	into.seekp(writePos);
	into.write((char*)&this->ProductCode, sizeof(int));
	int SizeStr = this->Name.size() + 1;
	into.write((char*)&SizeStr, sizeof(int));
	into.write((char*)this->Name.c_str(), SizeStr);
	into.write((char*)&this->Count, sizeof(int));
	into.write((char*)&this->PriseForOne, sizeof(float));
	this->SetWritePos(into.tellp());
	into.close();

}
bool Product::ReadInfoProduct()
{
	std::ifstream out("Product.dat", std::ios::binary);
	if (!out.is_open()) {
		exit(0);
	}
	out.seekg(readPos, std::ios::beg);
	int tmp;
	if (!out.read((char*)&tmp, sizeof(int))) {
		out.close();
		return false;
	}
	this->ProductCode = tmp;
	int len = 0;
	out.read((char*)&len, sizeof(int));
	char* str = new char[len];
	out.read((char*)str, len);
	this->Name = str;
	delete[] str;
	out.read((char*)&this->Count, sizeof(int));
	out.read((char*)&this->PriseForOne, sizeof(float));
	this->SetReadPos(out.tellg());
	out.close();
	return true;
}


void SetCustomization();
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // Получаем дескриптор консоли
bool flagParametr = true;
void GotoY(short y, short x = 35) {
	SetConsoleCursorPosition(hStdOut, { x,y });
}
void ConsoleCursorVisible(bool show, short size) {
	CONSOLE_CURSOR_INFO CursorInfo;
	CursorInfo.bVisible = show;
	CursorInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &CursorInfo);
}
void ConsoleTextColor(int n, int ActiveMenu) {
	if (n == ActiveMenu) {
		SetConsoleTextAttribute(hStdOut, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		printf("->");
	}
	else {
		SetCustomization();
	}
}
void SetCustomization() {
	if (flagParametr) {
		system("color 25");
		ConsoleCursorVisible(false, 25);
		flagParametr = false;
	}
	else
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_RED | BACKGROUND_GREEN);
}

void menu(int ActiveMenu) {
	int n = 4; // для перехода по строкам меню
	//////////
	SetCustomization();
	CLEAN
		const char menuName[11][30] = {
		"Чтение с файла",
		"Запись в файл",
		"Просмотр данных в дереве",
		"Отчистить дерево",
		"Удалить из дерева по ключу",
		"Поиск по ключу",
		"Высота дерева",
		"Количестово лепестков",
		"Пустое ли дерево",
		"Средний(или почти) элемент",
		"Добавить продукт в дерево"
	};
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
	GotoY(n);
	for (int i = 0; i < 50; i++) {
		if (i == 0 || i == 49) {
			printf("+");
		}
		else printf("-");
	}
	n++;
	for (int i = 0, j = 0; i < 14; i++, n++) {
		if (i == 0) {
			GotoY(n);
			printf("|");
			GotoY(n, 57);
			SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_RED);
			printf("DIALOGUE");
			SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
			GotoY(n, 84);
			printf("|");
			n++;
			GotoY(n);
			for (int i = 0; i < 50; i++) {
				if (i == 0 || i == 49) {
					printf("+");
				}
				else printf("-");
			}
		}
		else if (i > 1 && i < 13) {

			GotoY(n);
			printf("|");
			GotoY(n, 50);
			ConsoleTextColor(n,ActiveMenu);
			printf("%s", menuName[j++]);
			SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
			GotoY(n, 84);
			printf("|");
		}
		else {
			GotoY(n);
			printf("|");
			GotoY(n, 84);
			printf("|");
		}
	}
	GotoY(n);
	for (int i = 0; i < 50; i++) {
		if (i == 0 || i == 49) {
			printf("+");
		}
		else printf("-");
	}
	GotoY(n+2,0);
	SetCustomization();

}
void ShowMenuPrint() {
	std::cout.setf(std::ios::left);
	std::cout.width(9);
	std::cout << "Код";
	std::cout.width(25);
	std::cout << "Название";
	std::cout.width(20);
	std::cout << "Количество";
	std::cout.width(20);
	std::cout << "Цена за 1 ед.";
	std::cout << std::endl;
	std::cout << "-----------------------------------------------------------------------";
	std::cout.unsetf(std::ios::left);
	std::cout << std::endl;
}

Product EnterElemet() {
	std::cout << "Введите код продукта: ";
	int code;
	std::cin >> code;
	ClEANCONSOLE
	std::cout << std::endl;
	Product tmp(code);
	return tmp;
}
Product EnterFullElement() {
	std::cout << "Введите код продукта: ";
	int code;
	std::cin >> code;
	ClEANCONSOLE
	std::cout << std::endl;
	std::cout << "Введите название продукта: ";
	std::string name;
	std::getline(std::cin, name);
	std::cout << std::endl;
	int col;
	std::cout << "Введите количетство данного продукта: ";
	std::cin >> col;
	ClEANCONSOLE
	std::cout << std::endl;
	std::cout << "Введите цену за 1 ед. продукта: ";
	float prise;
	std::cin >> prise;
	ClEANCONSOLE
	std::cout << std::endl;
	Product tmp(code, name, col, prise);
	return tmp;
}