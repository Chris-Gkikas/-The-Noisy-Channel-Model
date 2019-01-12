#include <iostream>
#include<fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>

using namespace std;

int main(int argc,char *argv[]) {
	
	int P=atoi(argv[3]);							//convert string number to integer number
 	int N=atoi(argv[4]);							//convert string number to integer number
	srand(time(NULL));							//seed the generator sran
	char srcBuff[(int)ceil(log2(N*127))] ={};				//Ν*127 maxNumber,how many bits do we need??-->  log2(N*127), so this is going to be the array capacity
	char destBuff[(int)ceil(log2(N*127))]={};	
	
	if(argc!=5){
		cout<< "\nError: You should provide 5 arguments."<<endl;
		cout<< "Usage: <"<<argv[0]<<"> <inputFile.txt> <outputFile.txt> <Possibility> <Key>."<<endl;
		return 0;
	}
	ifstream inFile(argv[1]);
	
	if(!inFile.is_open()){
	
		cout << "\nError: Could not open input file or file may not even exist." <<endl;
		return 0;
	}
	ofstream outFile(argv[2]);
	if(!outFile.is_open()){
		cout << "\nError: Could not create/open <"<<argv[2]<<"> file." <<endl;
		return 0;
	}
	char ch;
	int numberOfBits=0;							//numberOfBits because probably it's going to have some leftovers from previous elements with much more bits 
	int reps=0;								//resends
	while(!inFile.eof()){
		inFile.get(ch);										
		unsigned int ascii = (int)ch;					// ch*N a very simple encoder
		unsigned  long int CryptAscii= ascii*N;				// ENCRYPTION (N is the key)
		int remainder=0;
		int i=0;
		numberOfBits=0;

//////////////////////////////// DECIMAL TO BINARY  ///////////////////////////////
		while (CryptAscii!=0){
			remainder = CryptAscii%2;						
			if(remainder==1) srcBuff[i]='1';
			else srcBuff[i]='0';
			CryptAscii /= 2;
		    numberOfBits++;
		    ++i;
		}
//////////////////////////////// END DECIMAL TO BINARY //////////////////////////////
		
		
		

/////////////////////// transfer from srcBuff(sender) to destBuff(reciever) and a chance of mutation with possibility P //////////////////////
		bool flag=true;
		while(flag){
			reps++;
			for(int i=0; i<numberOfBits; i++){								
				destBuff[i]=srcBuff[i];
				bool mutation = (rand() % 100)+1 <= P;						//(rand()%100)+1 gives a number between 0 and 100. The possibility of this number being <=Ρ it's Ρ%.
				if(mutation) destBuff[i]=destBuff[i]=='1' ? '0' : '1';	
			}
////////////////////////	 BINARY TO DECIMAL	/////////////////////////////////

			unsigned long int DecryptAscii=0;							
			int base=1;
			for(int i=0; i<numberOfBits; i++){
				if(destBuff[i]=='1') DecryptAscii +=  base;
				base *= 2;		}							// power always 1, the base doubles in every iteration. 1  2  4  8  16  32  64.....
//////////////////////////////////// END BINARY TO DECIMAL	//////////////////////////////////////

////////////////////// WRITE TO OUTPUT FILE   ////////////////////////////////////////////////////
			if(DecryptAscii%N==0){
				DecryptAscii/=N;								// DECRYPTION
				if(DecryptAscii<=127) outFile<<(char)DecryptAscii;         
				else outFile<<"😣";
				DecryptAscii=0;
				flag=false;
			}
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
		else	diff++;
	}
	cout<<argv[1]<<"		"<<argv[3]<<"%"<<"	   "<<argv[4]<<"	     "<<reps<<"           "<<setprecision(3)<<(same/(float)(same+diff))*100<<"%"<<endl;
	inFile.close();
	finalOutFile.close();
	return 0;
}
