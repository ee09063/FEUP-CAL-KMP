#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include "Noticias.h"

using namespace std;

int main()
{
	cout<<"START"<<endl;

	string name;

	cout << "NOME DO ARTIGO A AVALIAR:" << endl;
	
	getline(cin, name);

	name = name + ".txt";

	//carrega o artigo
	Article* article = new Article(name.c_str());

	//imprime o artigo
	cout << article->getArticle() << endl;

	//cria e carrega os dicionarios
	Dicionarios *dicionarios = new Dicionarios();

	//executa a procura e conta das palavras
	dicionarios->searchWords(article->getArticle());

	//imprime os totais e palavras chave
	dicionarios->PrintTotals();

	//decide a categoria
	dicionarios->getBestCategory();

	//imprime os dicionarios
	//dicionarios->printDictionary();

	cout<<"END"<<endl <<endl;

	//EXTRA -> procura uma expressão usando o algoritmo alternativo
	/*cout<<"::Procurar Frase::"<<endl;
	name = "text1.txt";
	string toSearch="estrutura de dados";
	Article* article2 = new Article(name.c_str());
	cout << article2->getArticle() << endl;
	Frase* frase = new Frase(toSearch,article2->getArticle());
	cout << "A frase: \"" << toSearch << "\" foi encontrada " << frase->searchFrase() << " vezes." << endl;*/

	return 0;
}
