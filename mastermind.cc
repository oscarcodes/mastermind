/*

	Version 0.0
	FOPR_Q1_2019 mastermind
	Andrw Harol Garcia Romero
	Òscar Codes i Ramos
	Inicio		20191128
	Previsión Fin	20191215

*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>

using namespace std;

char demanar_opcio(){
	//Pre: 
	//Post: Retorna una opció valida 'J' o 'I'
	char opcio;
	cout<<"Mode Interactiu (I) o Joc de proves (J) : ";
	cin>>opcio;
	while (opcio!='J' and opcio!='I'){
	//Inv: Les opcions entrades fins ara son !='J' i !='I'
		cout<<"Mode de joc incorrecte."<<endl;
		cout<<"Mode Interactiu (I) o Joc de proves (J) : ";
		cin>>opcio;
	}
	cout<< endl;
	return opcio;
}

bool diferents(const vector<int>& v){
	//Pre: v es un vector d'enters no buit
	//Post: Retorn true si tots els elements de v son diferents sino retorna false
	bool trobat=false;
	unsigned int i=0;
	while (i<v.size() and not trobat){
		//Inv: els elements [0..i-1] no estan repetits
		unsigned int j=i+1;
		while (j<v.size() and not trobat) {
			//Inv: els elements [0..i-1] no estan repetits
			// i a més a més l'element i no està a [0..j-1]
			if (v[i]==v[j]) trobat=true;
			else ++j;
		}
		if (not trobat) ++i;
	}
	return not trobat;
}

string genera_resposta (const vector<int>& secret, const vector<int>& intent) {
	//Pre: secret i intent son vectors d'enters d'enters
	//Post: retorna la resposta amb de l'intent respecte al codi secret
	string resposta="";
	for (unsigned int i=0; i<intent.size(); ++i){
			bool trobat=false;
			unsigned int j=0;
			while (j<secret.size() and not trobat) {
					if (secret[j]==intent[i]) trobat=true;
					else ++j;
			}
			if (trobat){
				if (i==j) resposta+='X';
				else      resposta+='O';
			}
			else resposta+='-';
	}
	return resposta;
}

vector<int> separar (int x) {
//Pre : x es possitiu x=X
//Post : Retorna un vector amb els digits de x
vector<int> v;
while (x>0){
	// Invariant: tots els digits que estan a X i no a x estan dins del vector v
	v.push_back(x%10);
	x=x/10;
}

for (unsigned int i=0; i<v.size(); ++i) cout<<v[i]<<" ";
	cout<<endl;
//Girem el contingut
unsigned int n=v.size(), j;
for(unsigned int i=0; i<n/2; ++i){
	// Invariant: hem girat els numeros que estan entre 0 i i-1
	j= n-i-1;
	int aux=v[i];
	v[i]=v[j];
	v[j]=aux;
}
return v;
}


int main() {

	char mode;
	mode=demanar_opcio();

	cout<<"BENVINGUT AL JOC MASTERMIND!!"<<endl;

	// (DEMANAR EL CODI SECRET PER PANTALLA)

	cout << "Jugador A, escull el codi secret:"<<endl;	

	int codi_secret;

	cin>>codi_secret;

	cout<< codi_secret << endl;

	// Neteja pantalla o no depenen de si es mode Interactiu o no
	if (mode=='I') system("clear");

	// (Inicialitzar variables)

	bool fin_juego=false;
	int intents=0;
	
	while (not(fin_juego) and intents<15) {
		// (DEMANAR INTENT)
		int codigo_jugador_b;
		cin>> codigo_jugador_b;
		if (codigo_jugador_b==9999) fin_juego=true;
		cout<<"XXXX"<<endl;
		++intents;
		// (COMPARAR AMB EL CODI SECRET)
		// (MOSTRAR RESULTATS)
		// (Si resultat es "XXXX" llavors fin_juego es true sino sumar 1 als intents
	}
	
	// (MOSTRAR MISSATGE FINAL DEPENEN DE SI EL RESULTAT ES "XXXX" O NO




}
