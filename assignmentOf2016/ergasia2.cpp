#include <iostream>
#include<fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
using namespace std;
int main(int argc,char *argv[]) {
	int P=atoi(argv[3]);									//convert string number to integer number
 	int N=atoi(argv[4]);									//convert string number to integer number
	srand(time(NULL));										//κάνω seed τον generator srand, με τη χρονική στιγμή έναρξης του προγράμματος, ώστε η rand να τροφοδοτείται κάθε φορά με διαφορετική ακολουθία αριθμών.
	char srcBuff[(int)ceil(log2(N*127))] ={};				//Ν*127 μέγιστος αριθμός, πόσα bits χρειάζονται για τον αριθμό αυτό;--> log2(N*127), άρα τοσες θα ειναι και οι θεσεις του πινακα.
	char destBuff[(int)ceil(log2(N*127))]={};				//ceil για στρογγυλοποιηση του log2 προς τα πάνω. (int) type cast απο double που γυρναει η ceil, σε int για να δεσμευθουν οι θέσεις του πίνακα.
	if(argc!=5){
		cout<< "\nError: You should provide 5 arguments."<<endl;
		cout<< "Usage: <"<<argv[0]<<"> <inputFile.txt> <outputFile.txt> <Possibility> <Key>."<<endl;
		return 0;}
	ifstream inFile(argv[1]);
	if(!inFile.is_open()){
		cout << "\nError: Could not open input file or file may not even exist." <<endl;
		return 0;}
	ofstream outFile(argv[2]);
	if(!outFile.is_open()){
		cout << "\nError: Could not create/open <"<<argv[2]<<"> file." <<endl;
		return 0;}
	char ch;
	int numberOfBits=0;										//numberOfBits γιατί οι επόμενες θέσεις του πίνακα περιέχουν ενδεχομένως απομεινάρια απο προηγούμενα στοιχεία με περισσότερα bits.
	int reps=0;												//επαναποστολές
	while(!inFile.eof()){
		inFile.get(ch);										//δε χρησιμοποιώ inFile >> ch  ώστε να δέχεται και το space.
		unsigned int ascii = (int)ch;						//type casting απο char σε int, unsigmed για να είναι πάντα θετικό. ch*N είναι  η κωδικοποίηση.
		unsigned  long int CryptAscii= ascii*N;				//Κ Ρ Υ Π Τ Ο Γ Ρ Α Φ Η Σ Η 		(N το κλειδί)
		int remainder=0;
		int i=0;
		numberOfBits=0;

//////////////////////////////// DECIMAL TO BINARY  ///////////////////////////////
		while (CryptAscii!=0){
			remainder = CryptAscii%2;						//υπόλοιπο
			if(remainder==1) srcBuff[i]='1';
			else srcBuff[i]='0';
			CryptAscii /= 2;
		    numberOfBits++;
		    ++i;}
//////////////////////////////// END DECIMAL TO BINARY //////////////////////////////

/////////////////////// ΜΕΤΑΦΟΡΑ ΑΠΟ srcBuff(ΑΠΟΣΤΟΛΕΑΣ) ΣΕ destBuff(ΠΑΡΑΛΗΠΤΗΣ) KAI MUTATION ME ΠΙΘΑΝΟΤΗΤΑ P  //////////////////////
		bool flag=true;
		while(flag){
			reps++;
			for(int i=0; i<numberOfBits; i++){								// μεταφορά από τον έναν buffer  στον άλλον.
				destBuff[i]=srcBuff[i];
				bool mutation = (rand() % 100)+1 <= P;						//η (rand()%100)+1 δίνει αριθμό μεταξύ 0 και 100. Η πιθανότητα αυτού του αριθμου να είναι <=Ρ είναι Ρ%.
				if(mutation) destBuff[i]=destBuff[i]=='1' ? '0' : '1';		//if destBuff[i]=='1' then destBuff[i]='0' else destBuff[i]='1'
			}
////////////////////////	 BINARY TO DECIMAL	/////////////////////////////////

			unsigned long int DecryptAscii=0;								//μηγενισμός και χτίσιμο από την αρχή
			int base=1;
			for(int i=0; i<numberOfBits; i++){
				if(destBuff[i]=='1') DecryptAscii +=  base;
				base *= 2;		}											// η δύναμη παντα 1, η βάση διπλασιάζεται σε κάθε επανάληψη. 1  2  4  8  16  32  64.....
//////////////////////////////////// END BINARY TO DECIMAL	//////////////////////////////////////

////////////////////// WRITE TO OUTPUT FILE   ////////////////////////////////////////////////////
			if(DecryptAscii%N==0){
				DecryptAscii/=N;											//ΑΠΟΚΡΥΠΤΟΓΡΑΦΗΣΗ
				if(DecryptAscii<=127) outFile<<(char)DecryptAscii;          //type cast απο int ascii σε char ascii
				else outFile<<"😣";
				DecryptAscii=0;
				flag=false;}
		}
	}
	inFile.close();
	outFile.close();
///////////////////////////// COMPARE INPUT AND OUTPUT FILE CHAR BY CHAR ///////////////////////////
	inFile.open(argv[1]);
	ifstream finalOutFile(argv[2]);
	char ich,och;
	int same=0; int diff=0;

	while(!inFile.eof()){
		inFile.get(ich);
		finalOutFile.get(och);
		if(ich==och) same++;
		else	diff++;}
	cout<<argv[1]<<"		"<<argv[3]<<"%"<<"	   "<<argv[4]<<"	     "<<reps<<"           "<<setprecision(3)<<(same/(float)(same+diff))*100<<"%"<<endl;
	inFile.close();
	finalOutFile.close();
	return 0;
}
