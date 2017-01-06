/*
 * noticias.cpp
 */
#include "Noticias.h"

/** Construtor da Class Labirinto*/
Article::Article (const char* filename):filename(filename) //carrega o artigo, uma linha de cada vez
{
	ifstream infile(filename);
	if(!infile) throw fileNotExists(filename);
	string aux, article;
	while(getline(infile, aux))
		myArticle = myArticle + ' ' + aux;
	cleanUpWord();
}

void Article::cleanUpWord() //remove caracteres especiais e coloca para lowercase para procura
{
	//Alternativa 1 para remover caracteres
	/*myArticle.erase(remove( myArticle.begin(), myArticle.end(), '.' ), myArticle.end() );
	myArticle.erase(remove( myArticle.begin(), myArticle.end(), ',' ), myArticle.end() );
	myArticle.erase(remove( myArticle.begin(), myArticle.end(), '"' ), myArticle.end() );
	myArticle.erase(remove( myArticle.begin(), myArticle.end(), '(' ), myArticle.end() );
	myArticle.erase(remove( myArticle.begin(), myArticle.end(), ')' ), myArticle.end() );
	myArticle.erase(remove( myArticle.begin(), myArticle.end(), '[' ), myArticle.end() );
	myArticle.erase(remove( myArticle.begin(), myArticle.end(), ']' ), myArticle.end() );*/

	//Alternativa 2
	myArticle = replaceChar(myArticle);

	transform(myArticle.begin(), myArticle.end(), myArticle.begin(), ::tolower);
}

Dicionarios::Dicionarios()
{
	loadDicionarios();
}

void Dicionarios::loadDicionarios() // carrega todos os ficheiros que começem com o termo "Dicionario" como dicionarios
{
	DIR *dir = NULL;
	struct dirent *ent;
	dir = opendir (".");
	string strfilename;
	string DicionarioName ="";
	if (dir != NULL) {
	  /* acede a todos os ficheiros e directorios dentro do directorio */
	  while ((ent = readdir (dir)) != NULL)
	  {
		if(ent->d_name){
			stringstream ss;
			ss << ent->d_name;
			ss >> strfilename;
			if(strfilename.substr(0,10)=="Dicionario")
			{
				unsigned pos = strfilename.find(".txt");
				DicionarioName = strfilename.substr(11,pos-11);
				Dicionario *d1 =new Dicionario(DicionarioName,strfilename);
				addDicionario(d1);
				ifstream myFile;
				myFile.open(strfilename.c_str());
				string word;
				while(getline(myFile, word)) // carrega o ficheiro linha a linha de modo a poder procurar expressões e palavras
					d1->addWord(word);
				myFile.close();
			}
		}

	  }
	  closedir (dir);
	} else {
	  /* directorio não existe */
	  perror ("");
	  exit (1);
	}
}

Dicionario::Dicionario (string dicName, string filename):dicName(dicName),filename(filename){

}
void Dicionario::addWord(string word) //adiciona uma palavra ao vector com as palavras do dicionario
{
	dic.push_back(word);
}
void Dicionario::addDicKey(string dicKeyword) // adiciona uma palavra ao vector com as palavras chave
{
	dicKey.push_back(dicKeyword);
}
string Dicionario::getDicName(){
	return dicName;
}
string Article::replaceChar(string str)  //substitui caracteres especiais por caracter ' '
{
  for (unsigned int i = 0; i < str.length(); ++i) {
    if (str[i] == '.' || str[i] == ',' || str[i] == '"' || str[i] == '(' || str[i] == ')' || str[i] == '[' || str[i] == ']')
      str[i] = ' ';
  }
  return str;
}
string Article::getArticle(){
	return myArticle;
}
vector<int> Dicionarios::KMP(string S, string K) //aplicação do algoritmo KMP
{
    vector<int> T(K.size() + 1, -1);
	vector<int> matches;

	if(K.size() == 0)
	{
		matches.push_back(0);
		return matches;
	}

	for(unsigned int i = 1; i <= K.size(); i++)
	{
		int pos = T[i - 1];
		while(pos != -1 && K[pos] != K[i - 1])
			pos = T[pos];
		T[i] = pos + 1;
	}

	unsigned int sp = 0;
	unsigned int kp = 0;

	while(sp < S.size())
	{
		while(kp != -1 && (kp == K.size() || K[kp] != S[sp]))
			kp = T[kp];
		kp++;
		sp++;
		if(kp == K.size() && (S[sp] == ' ' || S[sp] == '\0') && S[sp-K.size()-1] == ' ') // deste modo encontra palavras completas em vez de só substrings
			matches.push_back(sp - K.size());
	}

	return matches;
}
vector<Dicionario *> Dicionarios::getDicionarios(){
	return myDicionarios;
}
int Dicionarios::getNumDicionarios() const{
	return myDicionarios.size();
}
void Dicionarios::addDicionario(Dicionario *d1){
	myDicionarios.push_back(d1);
}
void Dicionarios::searchWords(string article) // para cada palavra de cada dicionario aplica o algoritmo KMP
{
	vector<Dicionario *>::const_iterator it = myDicionarios.begin();
	while(it!=myDicionarios.end())
	{
		vector<int> count;
		for(unsigned int i = 0; i < (*it)->dic.size(); i++)
		{
			count = KMP(article, (*it)->dic[i]);
			if(count.size() != 0) //se encontrar a palavra
			{
				//adiciona ao vector de palavras chave a palavra e o número de vezes que aparece
				(*it)->dicKey.push_back((*it)->dic[i]);
				stringstream ss; ss << count.size();
				(*it)->dicKey.push_back(ss.str());
			}
		}
	it++;
	}
}
void Dicionarios::getBestCategory() // a melhor categoria é a que tiver mais palavras únicas
{
	vector<Dicionario *>::const_iterator it = myDicionarios.begin();
	unsigned int imax=0;
	Dicionario *d1 = new Dicionario("","");;
		while(it!=myDicionarios.end())
		{
			if((*it)->dicKey.size()/2>imax)
			{
				imax=(*it)->dicKey.size()/2;
				d1=*it;
			}
		it++;
		}

	cout << "ARTIGO DE " << d1->getDicName() << " QTD: " << imax << " Palavras Chave" << endl;

}
void Dicionarios::PrintTotals()
{
	vector<Dicionario *>::const_iterator it = myDicionarios.begin();
	cout << endl;
	while(it!=myDicionarios.end())
	{
		cout << endl;
		cout << (*it)->getDicName() << ":   " << (*it)->dicKey.size()/2  << endl;
		it++;
	}
	cout << endl;
	it = myDicionarios.begin();
	while(it!=myDicionarios.end()){
		cout << endl;
		cout << (*it)->getDicName() << " -> PALAVRAS-CHAVE: " << endl;
			for(unsigned int i = 0; i < (*it)->dicKey.size(); i++)
			{
				cout << (*it)->dicKey[i] << " ";
			}
		cout << endl;
		it++;
	}
	cout<< endl << endl;
}
void Dicionarios::printDictionary()
{
	vector<Dicionario *>::const_iterator it = myDicionarios.begin();
	cout << endl;
	while(it!=myDicionarios.end()){
		cout << (*it)->getDicName() << endl;
		for(unsigned int i = 0; i < (*it)->dic.size(); i++)
			cout << (*it)->dic[i] << endl;
		cout << endl;
		it++;
	}
}
Frase::Frase(string frase, string article):myFrase(frase),article(article){
}

int Frase::searchFrase() //algoritmo alternativo
{
	vector< string > strs;
	vector< string > strSearch;

	istringstream stm(article) ;
	string word ;
	while( stm >> word ){
		strs.push_back(word);
	}
	string buf;
	stringstream ss(myFrase);
	int ncount = 0;
	while (ss >> buf)
	strSearch.push_back(buf);
	for(unsigned int i=0; i<strs.size(); i++){
		unsigned int total=0;
		for(unsigned j=0; j<strSearch.size();j++){
			if((i+j)<strs.size()){
				if(strs[i+j]==strSearch[j])total++;
			}
		}
		if(total==strSearch.size())ncount++;
	}
	return ncount;
}
