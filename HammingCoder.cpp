#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#include <numeric>

using namespace std;

int fastpow(int a, int n) {
	int res = 1;
	while (n) {
		if (n % 2) res *= a;
		a *= a;
		n >>= 1;
	}
	return res;
}

void add_extra_nulls(string& s) {

}

void remove_unused_symbols(string& s) {
	for (int i = 0; i < s.length(); ++i) {
		if (!isdigit(s[i])) {
			int cnt = 1;
			while (!isdigit(s[++i])) ++cnt;
			s.erase(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(i) - cnt, cnt);
		}
	}
}

void add_control_bits(string& s) {
	for (int iter = 1; iter < s.length(); iter*=2)
		s.insert(s.begin() + iter - 1, 'c');
}

void calc_control_bits(string& s) {
	for (int step = 0; step <= 3; ++step) {
		int c = fastpow(2, step), cnt = 0;
		for (int i = c + 1; i <= s.length(); ++i) {
			if (i & c)
				cnt += static_cast<int>(s[i-1]) - 48;
		}
		s[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(c) - 1] = static_cast<char>(48 + cnt % 2);
	}
}


vector<string> split_in_segments(const string& s) {
	vector<string> segments;

	for (int i = 0; i < s.length(); i += 11) {
		segments.push_back(s.substr(i, 11));
		add_control_bits(segments.back());
	}

	return segments;
}

string vector_to_str(vector<string>& codes) {
	string code;
	for (auto it = codes.begin(); it != codes.end(); ++it) code += *it;
	return code;
}

int main(){
	ios::sync_with_stdio(false);
	//fstream f("code.txt");
	string code;
	getline(cin, code);
	remove_unused_symbols(code);
	add_extra_nulls(code);
	vector<string> codes = split_in_segments(code);
	for (int i = 0; i < codes.size(); ++i)
		calc_control_bits(codes[i]);
	code = vector_to_str(codes);
	cout <<"Your code: "<< code;
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
