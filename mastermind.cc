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

typedef	vector <int> jugada;
typedef	vector <jugada> matriu_jugades;


char demanar_joc(){
	//Pre: 
	//Post: Retorna una opció valida 'M' o 'A'
	char opcio;
	cout<<"Quin mode de joc vols triar, Manual (M)/ Aleatori (A)? : ";
	cin>>opcio;
	while (opcio!='M' and opcio!='A'){
	//Inv: Les opcions entrades fins ara son !='M' i !='A'
		cout<<endl<<"Mode de joc incorrecte.";
		cout<<endl<<"Quin mode de joc vols triar, Manual (M)/ Aleatori (A)? : ";
		cin>>opcio;
	}
	cout<< endl;
	return opcio;
}

char demanar_opcio(){
	//Pre: 
	//Post: Retorna una opció valida 'I' o 'J'
	char opcio;
	cout<<"Mode Interactiu (I) o Joc de proves (J) : ";
	cin>>opcio;
	while (opcio!='I' and opcio!='J'){
	//Inv: Les opcions entrades fins ara son !='J' i !='I'
		cout<<endl<<"Mode de joc incorrecte.";
		cout<<endl<<"Mode Interactiu (I) o Joc de proves (J) : ";
		cin>>opcio;
	}
	cout<< endl;
	return opcio;
}


bool correcte(const vector<int>& v){
	//Pre: v es un vector d'enters no buit
	//Post: Retorna true si la mida del vector es 4, tots els elements de v son diferents, 		//	i els elements es troben a [1..8]
	//	En cas contrari retorna false

	bool trobat=false;
	if (v.size()==4) {
		unsigned int i=0;
		while (i<v.size() and not trobat){
			//Inv: els elements [0..i-1] no estan repetits
			// i a més a més l'element i no està a [0..j-1]
			// ni es un 0, ni es un 9
			unsigned int j=i+1;
			if ((v[i]==0) or (v[i]==9)) {
				trobat=true;
			}

			while (j<v.size() and not trobat) {
				//Inv: els elements [0..i-1] no estan repetits
				if ((v[i]==v[j])) trobat=true;
				else ++j;
			}
			if (not trobat) ++i;
		}
	}
	else trobat=true;

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

	//for (unsigned int i=0; i<v.size(); ++i) cout<<v[i]<<" ";
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

bool tirada_aleatoria(vector<int> &tirada){
	
	vector <bool> nombre_posat(8,false);
	int digit;
	digit=1+rand()%8;
	tirada.push_back(digit);
	nombre_posat[digit]=true;
	for (int i=1;i<4;i++) {
 
		digit=1+rand()%8;
		while (nombre_posat[digit]) digit=1+rand()%8;
		tirada.push_back(digit);
		nombre_posat[digit]=true;
		
	}

	cout << tirada[0]<< tirada[1]<< tirada[2]<< tirada[3]<<endl;
	return true;
}


int main() {

	char mode;
	bool guanyat=false;
	mode=demanar_opcio();

	cout<<"BENVINGUT AL JOC MASTERMIND!!"<<endl;
	
	char joc;
	joc=demanar_joc();


	// (DEMANAR EL CODI SECRET PER PANTALLA)

	cout << "Jugador A, escull el codi secret: ";	

	int codi_secret;
	vector<int> v_codi_secret;

	cin>>codi_secret;
	v_codi_secret=separar(codi_secret);

	while (!(correcte(v_codi_secret))) {
		cout<<"codi secret incorrecte."<<endl;
		cout << "Jugador A, escull el codi secret: ";

		cin>>codi_secret;
		v_codi_secret=separar(codi_secret);
	}	

	// Neteja pantalla o no depenen de si es mode Interactiu o no
	if (mode=='I') system("clear");

	// (Inicialitzar variables)

	bool fin_juego=false;
	int intents=0;

	matriu_jugades m_jugades(1,jugada(4));

	while (not(fin_juego) and intents<15) {
		// (DEMANAR INTENT)

		cout<<"Jugador B, intent "<< (intents+1) << ": ";
		int codi_jugador_b;
		vector<int> v_codi_jugador_b;

		if (joc=='M') {
			cin>> codi_jugador_b;
			v_codi_jugador_b=separar(codi_jugador_b);
		}
		else
		{
			tirada_aleatoria(v_codi_jugador_b);

		}

		while (!(correcte(v_codi_jugador_b))) {
			cout<<"intent incorrecte."<<endl;
			cout<<"Jugador B, intent "<< (intents+1) << ": ";
			cin>>codi_jugador_b;
			v_codi_jugador_b=separar(codi_jugador_b);
		}	
		
		string resposta;
		
		if (correcte(v_codi_jugador_b)) {
			if (intents==0) m_jugades.pop_back(); 			
			m_jugades.push_back(v_codi_jugador_b);
			//cout<<v_codi_jugador_b.size()<<endl;			
			//cout<<m_jugades[0].size()<<endl;
			cout<<"Jugades:"<<endl;
			for(int k=0;k<=intents;++k){
				jugada tmp_jugada(4);
				tmp_jugada.assign(m_jugades[k].begin(),m_jugades[k].end());

				resposta = genera_resposta(v_codi_secret,tmp_jugada);
				if (((k+1)/10)==0) cout<<"0";
				cout<< (k+1)<<"   "	<< tmp_jugada[0]
							<< tmp_jugada[1]
							<< tmp_jugada[2]
							<< tmp_jugada[3]
							<< "   "
							<< resposta
							<<endl;
			}
		}

		//if (v_codi_jugador_b[0]==9 and v_codi_jugador_b[1]==9  
		//	and v_codi_jugador_b[2]==9 and v_codi_jugador_b[3]==9) fin_juego=true;
		if (resposta=="XXXX") {
			fin_juego=true;
			guanyat=true;
		}

		++intents;
		// (COMPARAR AMB EL CODI SECRET)
		// (MOSTRAR RESULTATS)
		// (Si resultat es "XXXX" llavors fin_juego es true sino sumar 1 als intents
	}
	
	// (MOSTRAR MISSATGE FINAL DEPENEN DE SI EL RESULTAT ES "XXXX" O NO

	if (intents==15) cout <<"Has esgotat els 15 intents."<<endl;
	if (guanyat) cout <<"Felicitats jugador B!! Has guanyat!!"<<endl;


}
