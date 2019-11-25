#include <iostream>
#include <string>
#include <functional>
#include <map>
#include <vector>
#include <algorithm>

//INSTRUCTIONS
/*Write a method that takes a DNA segment as shown below, displays the list of the codons 
(from most frequently appeared ones to least used ones) with how many times each codon that appears in a DNA segment.
Please use a map container in order to create a hash table and store frequency values of each codon that 
appears in the given DNA segment.*/

int makeHash(std::string codon)
{
   int num = 10;
   long hash = 0;
   for(int i = 0; i < codon.length(); i++)
   {
      hash = (hash * num) + codon[i];
   }
   return hash;
}

int main(){
        std::string dnaSequence; //initialize string used to get dna sequence
        std::string codon; //initialize string that will represent a segment of the given dna sequence
	//create 3 element map where string=codon and
	//pair= key from hash (unique to codon), value (frequency of that hash key)
	std::map<std::string, std::pair<int, int> > codonFrequency; 
	//std::map<int, int> hashValues;
	//std::map<int, std::string> codonKeys;

	//collect dna sequence from user
        std::cout << "Enter a dna sequence: ";
        std::cin >> dnaSequence;
	//loop through dna sequence and form codons with 3 chars
        for(int i=0; i <= dnaSequence.length()-3; i++){
	   codon += dnaSequence[i];
           codon += dnaSequence[i+1];
           codon += dnaSequence[i+2];
	   //send the codon to makeHash() to get specific key for that codon
	   int key = makeHash(codon);
	   //if there isn't a value for a codon/key, it means it's a new codon
	   //if there is a value, increment it- can't change pair, so have to
	   //erase entire codon, key, value map for that codon and re-initialize
	   if(codonFrequency[codon].second < 1){
		   codonFrequency[codon]=std::make_pair(key, 1); //initialize the new codon with value=1
	   }else{
		   int value = codonFrequency[codon].second; //get value
		   codonFrequency.erase(codon); //remove the map so you can re-initialize
		   value++; //increment value
		   codonFrequency[codon]=std::make_pair(key, value); //re-initialize
	   }
	   //need to clear out entire codon, key, value between repetitions otherwise it will
	   //append all codons together repeatedly
	   codon.clear();
	   //hashValues[key]++;
	   //codonKeys[key]=codon;
        }

	//unsorted
	/*for(auto it:hashValues){
	   std::cout << codonKeys[it.first] << ": " << it.second << "\n";
	}*/
	/*for(auto it:codonFrequency){
                std::cout << it.first << ": " << it.second.second << "\n";
        }*/
    
    //create vector with string=codon and int=value to sort in descending values
	std::vector<std::pair<std::string, int> > sortedCodons;
    //iterate through map
	for(auto it:codonFrequency){
        //add relevant elements from codonFrequency map to sortedCodons vector
		sortedCodons.push_back(std::make_pair(it.first, it.second.second));
	}
    //actually sort them, using method from sort algorithm built in
	sort(sortedCodons.begin(), sortedCodons.end(), [] 
	(std::pair<std::string, int> pair1, std::pair<std::string, int> pair2){
	   if(pair1.second != pair2.second){
	      return pair1.second > pair2.second;
	   }
	   return pair1.first > pair2.first;
	});
    
    //print out codon Frequency in descending frequency
	for(auto it:sortedCodons){
		std::cout << it.first << ": " << it.second << "\n";
	}

        return 0;
}
