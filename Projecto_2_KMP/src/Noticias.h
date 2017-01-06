/*
 * Noticias.h
 */

#ifndef NOTICIAS_H_
#define NOTICIAS_H_

#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <cstddef>
#include <cctype>
#include <vector>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <stdlib.h>
#include <dirent.h>

using namespace std;

/** Class Article */
class Article{
	const char* filename;
	string myArticle; //guarda o artigo numa só string
public:
	Article (const char* filename);
	void cleanUpWord();
	string replaceChar(string str);
	string getArticle();
	/**
	 * Class fileNotExists
	 */
	class fileNotExists{
	public:
		/**
		 * Construtor da Class fileNotExists
		 */
		fileNotExists(const char* myfile){
			stringstream ss;
			string s;
			ss << myfile;
			ss >> s;
			cout << "O ficheiro " << myfile << " nao existe." << endl;
			exit(0);
		}
	};
};
class Dicionario {
		string dicName;
		string filename;
	public:
		vector<string> dic;
		vector<string> dicKey;
		Dicionario(string dicName, string filename);
		void addWord(string word);
		void addDicKey(string dicKey);
		string getDicName();
};
class Dicionarios {
		vector<Dicionario *> myDicionarios;
	public:
		Dicionarios();
		void loadDicionarios();
		int getNumDicionarios() const;
		void addDicionario(Dicionario *d1);
		vector<Dicionario *> getDicionarios();
		vector<int> KMP(string S, string K);
		void searchWords(string myArticle);
		void getBestCategory();
		void PrintTotals();
		void printDictionary();
};
class Frase{
	string myFrase;
	string article;
public:
	Frase(string Frase, string article);
	int searchFrase();
};
#endif /* NOTICIAS_H_ */
