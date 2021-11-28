/* Muhammad Usman shahid
       20i-1797
	     T
*/


#ifndef CITIZENSDB_H
#define CITIZENSDB_H

//for strings
#include <string>
#include <cstring>

//for file reading
#include <fstream>

using namespace std;

template <class T>
struct Data
{
	//Node structure for data pipeline, implement data members as per requirement

	/*will read the data from the CCID will be store in this and when reading from the CBID the
	 criminal portion will be made null mean in the respective node of dataline no entry of crime and 
	 vice versa for CCID. */

	//for storing CBID
	// cnicCBID;	   //for holding the cninc that would be read from the file
	// name;		   //name of the person from file
	// fname;	   //father name
	// gender;	   //gender
	// age;		   //age
	//age doesn't exisit age is the street in the address thus updation will be done accordingly
	// address;	   //The address
	// nationality; //to fetch nationality

	//for storing CCID
	// cnicCCID;		  //cnic fetched from the criminal database
	// detailsofCrime; //details of crimes holder
	// punishment;	  //punishment holder
	// fine;			  //will carry the fine

	//the above all mentoned data will be store in the array of 11
	T infotoPopulate[11] = {};

	//a pointer that will point to the next
	Data<T> *next;
};

template <class T>
class DataPipeline
{
	/*	A linkedlist based queue to implement databases
		Implement additional functions as per requirement
	*/

	//in qeue we will maintain the two pointers of front and and rear
	Data<T> *front; //the first member in qeue
	Data<T> *rear;	//the last one in the qeue

public:
	DataPipeline()
	{
		//no qeue so pointing to null --- no front and no rear as no qeue exist
		front = NULL;
		rear = NULL;
	}

	//returns the data of the first in the queue
	T frontElement()
	{
		T toReturn = "null";

		if (is_empty())
		{
			cout << "\n\t\t Data Pipeline is empty " << endl;
			return toReturn;
		}
		else
		{
			toReturn = front->infotoPopulate[0];

			//for making a string from data array of datapipeline
			for (int i = 1; i < 11; i++)
			{
				toReturn += " " + front->infotoPopulate[i];
			}

			return toReturn;
		}
	}

	//returning the last element
	T back()
	{
		T toReturn = "null";

		if (is_empty())
		{
			cout << "\n\t\t Data Pipeline is empty " << endl;
			return toReturn;
		}
		else
		{
			toReturn = rear->infotoPopulate[0];

			//for making a string from data array of datapipeline
			for (int i = 1; i < 11; i++)
			{
				toReturn += " " + rear->infotoPopulate[i];
			}

			return toReturn;
		}
	}

	T splitWords(T &tobreak, int &pos)
	{
		T word;						   //a temporary words
		pos = tobreak.find(" ");	   //finding the space the first word
		word = tobreak.substr(0, pos); //taking that and storing as word

		pos++; //go to next index beacause word starts after space

		return word; //returning the word
	}

	//will read the file and will enter the data
	void enqueue(T fromFile, T type)
	{

		T temp;
		T dataExtraxted[11] = {}; //11 data entries all CBID and CCID

		int pos = 0;
		int last = 0;
		int i = 0;

		//copying the string taken from the file
		temp = fromFile;

		// fromfile is the string having the whole data that will be furthure spilleted and will be added into the qeue
		// type will see which data is going to be entered --- from which file

		// for CBID
		// 1. cninc 2.name 3.father name 4.gender 5.age 6.two words address 7.nationality
		// breaking the string accordingly
		if (type == "CBID")
		{
			//only first seven are related to the CBID
			for (i = 0; i < 7; i++)
			{
				//after each space the new data in string but only address is of two words
				//pos is containing the position where ended last
				dataExtraxted[i] = splitWords(temp, pos); //returning the word from the string

				// temp should be missing the starting one --- updating the temp in splitwords

				//the address of two words
				if (i == 5)
				{
					//finding the end of string
					last = temp.size();

					//updating the string
					temp = temp.substr(pos, last);

					dataExtraxted[i] += " " + splitWords(temp, pos); //adding the next word
				}

				//finding the end of string
				last = temp.size();

				//updating the string
				temp = temp.substr(pos, last);
			}

			//making all other null --- starting the i left
			for (; i < 11; i++)
			{
				dataExtraxted[i] = "null";
			}
		}
		else //for CCID thus weiting data for that
		{

			//for ccid all CBID data will be null thus
			for (i = 0; i < 7; i++)
			{
				dataExtraxted[i] = "null";
			}

			//the entries of crime thus --- starting i from the remaining
			for (; i < 11; i++)
			{

				dataExtraxted[i] = splitWords(temp, pos); //returning the word from the string

				//but the life punishment is 4 words thus
				if (i == 9)
				{
					//add three more words
					for (int j = 0; j < 3; j++)
					{
						//finding the end of string
						last = temp.size();
						//updating the string
						temp = temp.substr(pos, last);

						dataExtraxted[i] += " " + splitWords(temp, pos);
					}
				}

				//finding the end of string
				last = temp.size();
				//updating the string
				temp = temp.substr(pos, last);
			}
		}

		//now entering the data accordingly
		//the first entry
		if (is_empty())
		{
			Data<string> *temp = new Data<string>; //the node to be enter

			//enetring the info
			for (int i = 0; i < 11; i++)
			{
				temp->infotoPopulate[i] = dataExtraxted[i];
			}

			temp->next = NULL; //no else

			//front and rear pointing to only one element
			front = temp;
			rear = temp;
		}
		else //not the first member then
		{
			Data<string> *temp = new Data<string>; //the node to be enter

			//enetring the info
			for (int i = 0; i < 11; i++)
			{
				temp->infotoPopulate[i] = dataExtraxted[i];
			}

			rear->next = temp; //pointing to new added in qeue
			temp->next = NULL; //pointing to none
			rear = temp;	   //last one is now temp;
		}
	}

	T dequeue()
	{
		//will deque the whole string of data
		T toReturn = "null";

		if (is_empty())
		{
			cout << "\n\t\t Data pipeline is already empty " << endl;
			return toReturn;
		}
		else
		{
			toReturn = front->infotoPopulate[0];

			//for making a string from data array of datapipeline
			for (int i = 1; i < 11; i++)
			{
				toReturn += " " + front->infotoPopulate[i];
			}

			//deleting the element at start
			Data<string> *temp = front;
			front = front->next;

			//mean last in the queue
			if (front == NULL)
			{
				//the qeue is now empty
				front = NULL;
				rear = NULL;
			}

			delete temp;

			return toReturn;
		}
	}

	bool is_empty()
	{
		if (front == NULL && rear == NULL) //if front and rear are null mean no qeue
		{
			return true; //the qeue is empty
		}

		return false; //qeue is not empty
	}

	//the one that will read from the files and will enque in the datapipeline
	//first 50 will be CBID and next 10 will be CCID
	void moveIndataPipeline()
	{
		fstream toRead; //for reading

		//temporary taking string
		string tempData;

		//entering data from CBID file to the data pipeline
		//opening file CBID
		toRead.open("CBID.txt", ios::in);

		while (!toRead.eof())
		{
			getline(toRead, tempData);

			//enqueing the data
			enqueue(tempData, "CBID"); //CBID type
		}

		toRead.close();

		//entering data from CCID file to the data pipeline
		//opening file CCID
		toRead.open("CCID.txt", ios::in);

		while (!toRead.eof())
		{
			getline(toRead, tempData);

			//enqueing the data
			enqueue(tempData, "CCID"); //CCID type
		}

		toRead.close();
	}
};

//forward decalaration --- to avoid dependencies
template <class T>
class CCID_NODE;

template <class T>
struct CBID_NODE
{
	//Implement additional data members and functions as per requirement

	//making the data that is given for the CBID
	T cnicB;
	T name;
	T fatherName;
	T gender;
	//age is just the name for the street number also above in the code
	T age; //age doesn't exisit age is the street in the address thus updation will be done accordingly
	T address;
	T nationality;

	CBID_NODE<T> *next;			   //for next
	CBID_NODE<T> *previous;		   //for pervious
	CCID_NODE<T> *referencetoCCID; //refer to CCID

	//initallay having no reference
	CBID_NODE()
	{
		referencetoCCID = NULL;
	}
};

template <class T>
class CBIDList
{
	//Implement data members and functions as per requirement
	CBID_NODE<T> *head;
	CBID_NODE<T> *tail;

public:
	CBIDList()
	{
		//at starting no list is there
		head = NULL;
		tail = NULL;

		//also not pointing anywhere in CCID
	}

	//to acess head
	CBID_NODE<T> *getHead() const
	{
		return head;
	}

	//addition will be done assendingly
	void addTome(T toapend, DataPipeline<T> &D)
	{
		//making an array of 7 to hold the data
		T dataHolder[7] = {};
		int pos = 0, last = 0, indexofList = 0, curretIndex = 1;
		T temp = toapend;

		//only first seven are related to the CBID
		for (int i = 0; i < 7; i++)
		{
			//after each space the new data in string but only address is of two words
			//pos is containing the position where ended last
			dataHolder[i] = D.splitWords(temp, pos); //returning the word from the string

			// temp should be missing the starting one --- updating the temp in splitwords

			//the address of two words
			if (i == 5)
			{
				//finding the end of string
				last = temp.size();

				//updating the string
				temp = temp.substr(pos, last);

				dataHolder[i] += " " + D.splitWords(temp, pos); //adding the next word
			}

			//finding the end of string
			last = temp.size();

			//updating the string
			temp = temp.substr(pos, last);
		}

		//now will enter the data in that index
		//making the temp data to be inserted in the list
		CBID_NODE<string> *newData = new CBID_NODE<string>;

		//adding the data
		newData->cnicB = dataHolder[0];
		newData->name = dataHolder[1];
		newData->fatherName = dataHolder[2];
		newData->gender = dataHolder[3];
		newData->age = dataHolder[4];
		newData->address = dataHolder[5];
		newData->nationality = dataHolder[6];

		//cnic is in the first index --- finding the index of list where to insert
		//index is hypothetical that insert after that -- for first the entry will be at first thus
		if (!emptyList())
		{

			CBID_NODE<string> *iterator = head;

			//finding the destination index
			indexofList = findIndex_for_entry(dataHolder[0]);

			//iterate till you find null aur the counting index icreases the destination index
			while (iterator && curretIndex < indexofList)
			{

				curretIndex++;
				iterator = iterator->next;
			}

			if (iterator == NULL)
			{
				//inserting at last
				tail->next = newData;
				newData->previous = tail;
				newData->next = NULL;

				tail = newData;
			}
			else if (indexofList == 0)
			{
				//inserting in the start
				newData->next = head;
				head->previous = newData;
				newData->previous = NULL;
				head = newData;
			}
			else
			{
				//inserting in between
				//according to the iterator where iterator is stopeed

				newData->next = iterator->next;
				newData->previous = iterator;
				iterator->next = newData;
				iterator->next->previous = newData;
			}
		}
		else
		{
			//the first element thus
			newData->next = NULL; //nothing more
			newData->previous = NULL;
			head = newData; //stat and end are same
			tail = newData;
		}
	}

	//will be a finding index where to insert --- ascendingly
	int findIndex_for_entry(T cnic)
	{

		//stoi for converting the string to int for comparision
		int cnicEntered = stoi(cnic); //the enetered one --- the enqeueing
		int cnicAlready = 0;		  //in list

		int index = 0; //the iteration count where we are

		//for iterating
		CBID_NODE<string> *iterator = head;

		while (iterator) //while iterator not equal to null
		{
			cnicAlready = stoi(iterator->cnicB);

			if (cnicEntered < cnicAlready)
			{

				return index; //saving that lower value place --- fids any greter mean this is right place
			}

			index++;				   //going next
			iterator = iterator->next; //assigning next
		}

		return index; //if not means last
	}

	//for populating the data from data pipeline
	void populateMe(DataPipeline<T> &D)
	{
		T dataTopopulate;

		//as static database was given first 50 were the CBID in the dataPipeline
		for (int i = 0; i < 50; i++)
		{
			//the data will be whole string that would be breakdown further
			dataTopopulate = D.dequeue(); //making enteries to come out from qeue
			addTome(dataTopopulate, D);	  //adding in the list of CBID in a acsending manner of cnic
		}
	}

	//for checking is list empty or not
	bool emptyList()
	{
		//head and pointer pointing to nothing --- mean no list
		if (head == NULL && tail == NULL)
		{
			return true;
		}

		return false;
	}

	//will validate whether the cnic exist in list or not
	bool validateCNIC(int eCNIC)
	{
		int cnicR = 0;

		CBID_NODE<T> *current = head; //to iterate in the list

		while (current)
		{
			//taking the cnic in string
			cnicR = stoi(current->cnicB);

			if (cnicR == eCNIC)
			{
				return true; //found --- CNIC is correct
			}

			//going next
			current = current->next;
		}

		return false; //no found have seen the list
	}

	//for adding the reference
	void addReference(CCID_NODE<T> *C, int cnic)
	{
		//the cnic in database
		int cnicDB = 0;

		CBID_NODE<T> *temp = head;

		//iterating till end
		while (temp)
		{

			cnicDB = stoi(temp->cnicB); //the database cnic

			//to add reference for
			if (cnicDB == cnic)
			{
				//the required cnic
				temp->referencetoCCID = C; //referring to ccid member
				break;					   //done
			}

			//move next
			temp = temp->next;
		}
	}

	//serach it
	T searchbyCNIC(int eCNIC)
	{
		T searchedResult = "null"; //final results storing

		int cnicR = 0;
		CBID_NODE<T> *current = head; //to iterate in the list

		while (current)
		{
			//taking the cnic in string
			cnicR = stoi(current->cnicB);

			if (cnicR == eCNIC) //to aceess this one
			{
				//combining all data of the current other than cnic
				searchedResult = current->name + " " + current->fatherName + " " + current->gender + " " + current->age + " " + current->address + " " + current->nationality;
				if (current->referencetoCCID != NULL)
				{
					searchedResult += " " + current->referencetoCCID->crimesRead;
				}

				return searchedResult; //found --- CNIC is correct
			}

			//going next
			current = current->next;
		}

		return searchedResult;
	}

	//updates the name
	void updateName(int cnic, T nameE)
	{
		//the cnic in database
		int cnicDB = 0;

		CBID_NODE<T> *temp = head;

		//iterating till end
		while (temp)
		{

			cnicDB = stoi(temp->cnicB); //the database cnic

			//to add reference for
			if (cnicDB == cnic)
			{
				//the required cnic
				//changing the name and breaking
				temp->name = nameE;
				break; //done
			}

			//move next
			temp = temp->next;
		}
	}

	//updates the father name
	void updateFname(int cnic, T nameE)
	{
		//the cnic in database
		int cnicDB = 0;

		CBID_NODE<T> *temp = head;

		//iterating till end
		while (temp)
		{

			cnicDB = stoi(temp->cnicB); //the database cnic

			//to add reference for
			if (cnicDB == cnic)
			{
				//the required cnic
				//changing the Father name and breaking
				temp->fatherName = nameE;
				break; //done
			}

			//move next
			temp = temp->next;
		}
	}

	//update the address
	void updateAddress(int cnic, T nameE)
	{
		//the first part is the street number thus spliting the enter word ansd assigning accordingly
		//the strret no is mentioned by age in the data
		int pos = 0, last = 0;

		T noinAddress;						//a temporary words
		pos = nameE.find(" ");				//finding the space the first word
		noinAddress = nameE.substr(0, pos); //taking that and storing as word

		pos++; //go to next index beacause word starts after space

		//now updating the string
		//finding the end of string
		last = nameE.size();
		//updating the string
		nameE = nameE.substr(pos, last); //now string contain address other tahn number

		//the cnic in database
		int cnicDB = 0;

		CBID_NODE<T> *temp = head;

		//iterating till end
		while (temp)
		{

			cnicDB = stoi(temp->cnicB); //the database cnic

			//to add reference for
			if (cnicDB == cnic)
			{
				//the required cnic

				//updating the address first part
				temp->age = noinAddress;

				//changing the remaining address and breaking
				temp->address = nameE;
				break; //done
			}

			//move next
			temp = temp->next;
		}
	}

	//updating nationality
	void updateNationality(int cnic, T nameE)
	{
		//the cnic in database
		int cnicDB = 0;

		CBID_NODE<T> *temp = head;

		//iterating till end
		while (temp)
		{

			cnicDB = stoi(temp->cnicB); //the database cnic

			//to add reference for
			if (cnicDB == cnic)
			{
				//the required cnic
				//changing the nationality and breaking
				temp->nationality = nameE;
				break; //done
			}

			//move next
			temp = temp->next;
		}
	}

	void display()
	{

		CBID_NODE<string> *iterator = head;

		while (iterator)
		{
			cout << iterator->cnicB << " ";
			iterator = iterator->next;
		}

		cout << endl;
	}
};

//for crimes list
template <class T>
struct crimesNode
{
	//making the singly list of crimes
	T crimeDetails;
	T crimePunishment;
	T crimeFine;

	crimesNode *next; //to trace the next --- singly linked list
};

//the singly linked list
template <class T>
class Crimes
{
private:
	crimesNode<T> *head;

public:
	Crimes()
	{
		head = NULL; //mean no list is there
	}

	crimesNode<T> *getHead() const
	{
		return head;
	}

	//will always append the data because only to make crimes list
	void addCrime(T dataAdd, DataPipeline<T> &D, T &addCrimedata)
	{
		//making the array of 3 that will store the data of crimes
		T crimeData[3] = {};

		int pos = 0, last = 0, indexofList = 0, curretIndex = 1;
		T temp = dataAdd;

		//spliting the data and saving in the array
		//the 3 data entry for CBID
		for (int i = 0; i < 3; i++)
		{
			crimeData[i] = D.splitWords(temp, pos); //returning the word from the string

			//finding the end of string
			last = temp.size();
			//updating the string
			temp = temp.substr(pos, last);

			//the punishment of 4 words
			if (i == 1)
			{
				//1 is taken already

				for (int j = 0; j < 3; j++)
				{
					//will store first the data and will not add if year was missing as in first data entry
					T temp2 = D.splitWords(temp, pos);

					if (temp2 != "-") //if not this grabage then add
					{
						crimeData[i] += " " + temp2;
					}

					//finding the end of string
					last = temp.size();
					//updating the string
					temp = temp.substr(pos, last);
				}
			}
		}

		//now adding that data into the crimes
		//the data slot to be added
		crimesNode<T> *tempC = new crimesNode<T>;

		tempC->crimeDetails = crimeData[0];
		tempC->crimePunishment = crimeData[1];
		tempC->crimeFine = crimeData[2];

		//now setting the pointer
		if (isEmpty()) //mean first element in the list
		{
			tempC->next = NULL;
			head = tempC;
		}
		else
		{
			//not the first
			crimesNode<T> *iterator = head;

			while (iterator->next) //go to the last element
			{
				iterator = iterator->next; //finding the last one so to append crimes list
			}

			//the last is found as iterator thus
			iterator->next = tempC;
			tempC->next = NULL;
		}

		if (addCrimedata == " ")
		{
			//saving things in addCrimedata --- that will update string of crime in the ccid
			addCrimedata = crimeData[0] + " " + crimeData[1] + " " + crimeData[2];
		}
		else
		{
			addCrimedata += " " + crimeData[0] + " " + crimeData[1] + " " + crimeData[2];
		}
	}

	void displayCrimes()
	{
		crimesNode<T> *tempC = head;

		while (tempC)
		{
			cout << tempC->crimeDetails << " " << tempC->crimePunishment << " " << tempC->crimeFine << " " << endl;
			tempC = tempC->next;
		}
	}

	void update(T details, T punish, T fine)
	{

		//will update head data
		head->crimeDetails = details;
		head->crimePunishment = punish;
		head->crimeFine = fine;
	}

	bool deleteme(T details, T punish, T fine)
	{
		//for iterating in the list
		crimesNode<T> *tempDel = head;

		T toDelete = details + " " + punish + " " + fine;
		T already;

		while (tempDel)
		{
			already = tempDel->crimeDetails + " " + tempDel->crimePunishment + " " + tempDel->crimeFine;

			if (already == toDelete)
			{
				//delete the crime
				//finding the previous of tempDel
				crimesNode<T> *previousFinder = head;

				if (previousFinder != tempDel)
				{
					//iterate till that is not the next element
					while (previousFinder->next != tempDel)
					{
						previousFinder = previousFinder->next;
					}

					//deleteing the tempdel but setting pointers before that
					previousFinder->next = tempDel->next;
					delete tempDel;
					return true;
				}
				else
				{
					//to remove head data
					if(previousFinder->next != NULL)
					{
						delete previousFinder; //deleting
						head = tempDel->next;
					}
				}

				return true;
			}

			tempDel = tempDel->next;
		}

		return false;
	}

	//checking list is empty or not
	bool isEmpty()
	{
		if (head == NULL)
		{
			return true; //is empty
		}

		return false; //not empty
	}
};

template <class T>
struct CCID_NODE
{
	//Implement additional data members and functions as per requirement

	//amking the data for ccid node
	T cnicC;
	T crimesRead; //for storing whole crimes then will move to crime list

	//the singly crime list
	Crimes<T> crime;
	CCID_NODE<T> *next;		//for next
	CCID_NODE<T> *previous; //for previous

	//for reference to CBID
	CBID_NODE<T> *referencetoCBID;

	//initallay having no reference
	CCID_NODE()
	{
		referencetoCBID = NULL;
		crimesRead = " ";
	}

	void updateToread()
	{

		T newU;

		//will iterate whole in crime node
		crimesNode<T> *temp = crime.getHead();

		while (temp)
		{
			if (temp == crime.getHead())
			{

				newU = temp->crimeDetails + " " + temp->crimePunishment + " " + temp->crimeFine;
			}
			else
			{
				newU += " " + temp->crimeDetails + " " + temp->crimePunishment + " " + temp->crimeFine;
			}

			temp = temp->next;
		}

		//assigigning the new value
		crimesRead = newU;
	}
};

template <class T>
class CCIDList
{
	//Implement data members and functions as per requirement
	CCID_NODE<T> *head;
	CCID_NODE<T> *tail;

public:
	CCIDList()
	{
		//no list at the strtaing
		head = NULL;
		tail = NULL;
	}

	//returning the head
	CCID_NODE<T> *getHead() const
	{
		return head;
	}

	//addition will be done assendingly
	void addTome(T toapend, DataPipeline<T> &D)
	{

		//making string for holding cnic
		T cnic;

		int pos = 0, last = 0, indexofList = 0, curretIndex = 1;
		T temp = toapend;

		//the first 11 were of the CBID
		for (int i = 0; i < 7; i++)
		{
			D.splitWords(temp, pos); //returning the word from the string

			//finding the end of string
			last = temp.size();

			//updating the string
			temp = temp.substr(pos, last); //now temp only contains crime data
		}

		cnic = D.splitWords(temp, pos); //returning the word from the string

		//finding the end of string
		last = temp.size();
		//updating the string
		temp = temp.substr(pos, last); //now temp only contains crime list data

		//now will enter the data in that index
		//making the temp data to be inserted in the list
		CCID_NODE<string> *newData = new CCID_NODE<string>;

		//adding the data
		newData->cnicC = cnic;

		//now adding data in singly list --- will also add the crimes details without cnic in crimesRead
		newData->crime.addCrime(temp, D, newData->crimesRead); //crime will be added

		//cnic is in the first index --- finding the index of list where to insert
		//index is hypothetical that insert after that -- for first the entry will be at first thus
		if (!isEmpty())
		{
			CCID_NODE<string> *iterator = head;

			//finding the destination index
			indexofList = findIndex_for_entry(cnic);

			//iterate till you find head again aur the counting index icreases the destination index
			while (iterator->next != head && curretIndex < indexofList)
			{

				curretIndex++;
				iterator = iterator->next;
			}

			if (iterator->next == head)
			{
				//inserting at last
				tail->next = newData;
				newData->previous = tail;
				newData->next = head;

				tail = newData;
				head->previous = tail;
			}
			else if (indexofList == 0)
			{
				//inserting in the start
				newData->next = head;
				newData->previous = tail;

				head->previous = newData;
				head = newData;
			}
			else
			{
				//inserting in between
				//according to the iterator where iterator is stopeed
				newData->next = iterator->next;
				newData->previous = iterator;
				iterator->next = newData;
				iterator->next->previous = newData;
			}
		}
		else
		{
			//the first element thus
			head = newData; //stat and end are same
			tail = newData;

			newData->next = head; //nothing more --- again to head as circular
			newData->previous = tail;
		}
	}

	//will be a finding index where to insert --- ascendingly
	int findIndex_for_entry(T cnic)
	{
		//stoi for converting the string to int for comparision
		int cnicEntered = stoi(cnic); //the enetered one --- the enqeueing
		int cnicAlready = 0;		  //in list

		int index = 0; //the iteration count where we are
		//for iterating
		CCID_NODE<string> *iterator = head;

		cnicAlready = stoi(head->cnicC);

		while (iterator->next != head) //while iterator not equal to null
		{
			cnicAlready = stoi(iterator->cnicC);

			if (cnicEntered < cnicAlready)
			{
				return index; //saving that lower value place --- fids any greter mean this is right place
			}

			index++;				   //going next
			iterator = iterator->next; //assigning next
		}

		
		//checking for the last
		cnicAlready = stoi(iterator->cnicC);
		if (cnicEntered < cnicAlready)
		{
			return index; //saving that lower value place --- fids any greter mean this is right place
		}
		index++;				   //going next
		iterator = iterator->next; //assigning next

		return index; //if not means last
	}

	//for populating the data in
	void populateMe(DataPipeline<T> &D)
	{
		T dataTopopulate;

		//will deque until the pipeline is not empty because now data is only for the CCID
		while (!(D.is_empty()))
		{
			dataTopopulate = D.dequeue();
			addTome(dataTopopulate, D);
		}
	}

	//for adding the reference
	void addReference(CBID_NODE<T> *C, int cnic)
	{
		//cinc in the database
		int cnicDB = 0;

		CCID_NODE<T> *temp = head;

		//iterate till end
		while (temp->next != head)
		{

			cnicDB = stoi(temp->cnicC); //the database cnic

			//to update reference of
			if (cnicDB == cnic)
			{
				//the required cnic ---- referring to cbid member
				temp->referencetoCBID = C;
				break; //done
			}

			//move next
			temp = temp->next;
		}
	}

	//will validate whether the cnic exist in list or not
	bool validateCNIC(int eCNIC)
	{
		int cnicR = 0;

		CCID_NODE<T> *current = head; //to iterate in the list

		while (current->next != head)
		{
			//taking the cnic in string
			cnicR = stoi(current->cnicC);

			if (cnicR == eCNIC)
			{
				return true; //found --- CNIC is correct
			}

			//going next
			current = current->next;
		}

		current = current->next;
		//taking the cnic in string --- checking last
		cnicR = stoi(current->cnicC);

		if (cnicR == eCNIC)
		{
			return true; //found --- CNIC is correct
		}
		//going next
		current = current->next;

		return false; //no found have seen the list
	}

	//search it
	T searchbyCNIC(int eCNIC)
	{
		T searchedResult; //final results storing

		int cnicR = 0;
		CCID_NODE<T> *current = head; //to iterate in the list

		do 
		{
			//taking the cnic in string
			cnicR = stoi(current->cnicC);

			if (cnicR == eCNIC) //to aceess this one
			{
				//combining all data of the current other than cnic
				if (current->referencetoCBID != NULL)
				{
					searchedResult = current->referencetoCBID->name + " " + current->referencetoCBID->fatherName + " " + current->referencetoCBID->gender + " " + current->referencetoCBID->age + " " + current->referencetoCBID->address + " " + current->referencetoCBID->nationality;
		
				}

				searchedResult += " " + current->crimesRead;

				return searchedResult; //found --- CNIC is correct
			}

			//going next
			current = current->next;
		} while (current != head);

		return searchedResult;
	}

	void deleteNode(int cnic)
	{
		//finding the cnic
		int already;

		CCID_NODE<T> *temp = head;

		do
		{
			already = stoi(temp->cnicC);

			if (already == cnic)
			{
				
				//if first -- head
				if (temp->previous == tail)
				{
					CCID_NODE<T> *deleteMe = temp;

					temp->next->previous = tail;
					tail->next = temp->next;
					head = temp->next;

					delete deleteMe;
				}
				else if (temp->next == head) //mean end
				{
					CCID_NODE<T> *deleteMe = temp;

					temp->previous->next = head;
					head->previous = temp->previous;
					tail = temp->previous;

					delete deleteMe;
				}
				else
				{
					// in between

					CCID_NODE<T> *deleteMe = temp;
				
					temp->previous->next = temp->next;
					temp->next->previous = temp->previous;
					delete deleteMe;


				}

				CCIDList<T> temp;
				return;
			}

			temp = temp->next;
		} while (temp != head);
	}

	//to see the list is empty or not
	bool isEmpty()
	{
		//head and tail point to nothing mean empty
		if (head == NULL && tail == NULL)
		{
			return true; //yes is empty
		}

		return false; //not empty
	}

	void display()
	{

		CCID_NODE<string> *iterator = head;

		cout << iterator->cnicC << " ";

		while (iterator->next != head)
		{
			//cout << iterator->cnicC << " ";
			iterator = iterator->next;
			cout << iterator->cnicC << " ";
		}

		cout << endl;
	}
};

template <class T>
class Database
{

	CBIDList<T> CBID; //CBID Database
	CCIDList<T> CCID; //CCID Database
	DataPipeline<T> dataPipeline;

public:
	Database(const T &filename, const T &filename1)
	{
		/*
			Initialize the data from the given file and populate database
		*/

		//filling the data pipeline
		//will read from the files and will insert in the data pipeline
		dataPipeline.moveIndataPipeline();

		//data will be deque from the data pipe line and will be stored respectively
		//for CBID list
		CBID.populateMe(dataPipeline); //popuplating the CBID
		
		//remaining data will be deque from the datapipeline as CBID is deque only CCID is remaining
		CCID.populateMe(dataPipeline); //populating CCID
		
		//now creating the relations with each other CCID and CBID pointing initallay to null
		developRelations(CBID, CCID);
	}

	//will develop the relation between CBID and CCID  enteries
	void developRelations(CBIDList<T> cb, CCIDList<T> ci)
	{
		int cnicinCCID = 0;
		int cnicinCBID = 0;

		//will check for each data record in ccid and if found in cbid will maintain the relations and if not will make null as all before
		CCID_NODE<T> *temp = ci.getHead();
		CBID_NODE<T> *tempB = cb.getHead();

		//will move till not find the head again of ccid as circular list
		while (temp->next != ci.getHead())
		{
			//ccid cnic
			cnicinCCID = stoi(temp->cnicC);
			//again start from first one
			tempB = cb.getHead();

			//find each of ccid in cbid
			while (tempB)
			{
				//the CBID cnic
				cnicinCBID = stoi(tempB->cnicB);

				//both are same so make the relation
				if (cnicinCBID == cnicinCCID)
				{
					//making reference;
					// will add the references
					cb.addReference(temp, cnicinCCID);	//refering to ccid in cbid
					ci.addReference(tempB, cnicinCCID); //referring to cbid in ccid

					break; //no need to see more
				}

				tempB = tempB->next;
			}

			temp = temp->next; //next CCID entery
		}

		
	}

	void deleteRelations(CBIDList<T> cb, CCIDList<T> ci, int cnic)
	{

		int cnicAlready;

		//will iterate in the both lists and find the cnic and update the reference
		CBID_NODE<T> *tempCBID = cb.getHead();

		//iterate in list
		while (tempCBID)
		{
			cnicAlready = stoi(tempCBID->cnicB);

			if (cnic == cnicAlready)
			{
				//remove the relation
				tempCBID->referencetoCCID = NULL;
				break;
			}

			//going to next
			tempCBID = tempCBID->next;
		}

		//now in ccid
		//will iterate in the both lists and find the cnic and update the reference
		CCID_NODE<T> *tempCCID = ci.getHead();

		//iterate in list
		while (tempCCID->next != ci.getHead())
		{
			cnicAlready = stoi(tempCCID->cnicC);

			if (cnic == cnicAlready)
			{
				//remove the relation
				tempCCID->referencetoCBID = NULL;
				return;
			}

			//going to next
			tempCCID = tempCCID->next;
		}

		//checking for last one
		cnicAlready = stoi(tempCCID->cnicC);

		if (cnic == cnicAlready)
		{
			//remove the relation
			tempCCID->referencetoCBID = NULL;
		}

		//going to next
		tempCCID = tempCCID->next;
	}

	/*Return a string in following format "Name FName Gender Address Nationality Crimes(if any) Charges punishment fine number network activation_date deactivation_date status"
     Refer to test cases for further clerification*/
	T CBID_Search_by_CNIC(int cnic)
	{
		T toReturn = "null";

		if (CBID.validateCNIC(cnic))
		{
			toReturn = CBID.searchbyCNIC(cnic);
			return toReturn;
		}
		else
		{
			cout << "\n\t\t :::: No CNIC found in the data ::::" << endl;
			return toReturn;
		}
	}

	//search from CCID
	T CCID_Search_by_CNIC(int cnic)
	{
		T toReturn = "null";

		if (CCID.validateCNIC(cnic))
		{
			toReturn = CCID.searchbyCNIC(cnic);
			return toReturn;
		}
		else
		{
			cout << "\n\t\t :::: No CNIC found in the data ::::" << endl;
			return toReturn;
		}
	}

	bool updateCBIDName(T Name, int cnic)
	{
		/*update and return true when cnic found else return false*/

		//if cnic found then will return true else false ---- that wrong updation --- not found
		if (CBID.validateCNIC(cnic))
		{
			//now updating the name in cbid
			CBID.updateName(cnic, Name);

			return true; //the cnic was right
		}

		return false; //cnic was false
	}

	bool updateCBIDFName(T Father_Name, int cnic)
	{
		/*update and return true when cnic found else return false*/
		//if cnic found then will return true else false ---- that wrong updation --- not found
		if (CBID.validateCNIC(cnic))
		{
			//now updating the name in cbid
			CBID.updateFname(cnic, Father_Name);

			return true; //the cnic was right
		}

		return false; //cnic was false
	}

	bool updateCBIDAddress(T Address, int cnic)
	{
		/*update and return true when cnic found else return false*/

		//if cnic found then will return true else false ---- that wrong updation --- not found
		if (CBID.validateCNIC(cnic))
		{
			//now updating the name in cbid
			CBID.updateAddress(cnic, Address);

			return true; //the cnic was right
		}

		return false;
	}

	bool updateCBIDNationality(T Nationality, int cnic)
	{
		/*update and return true when cnic found else return false*/

		//if cnic found then will return true else false ---- that wrong updation --- not found
		if (CBID.validateCNIC(cnic))
		{
			//now updating the name in cbid
			CBID.updateNationality(cnic, Nationality);

			return true; //the cnic was right
		}

		return false;
	}

	bool addCrime(int cnic, T charges, T punishment, T fine)
	{
		/*update and return true when crime found else return false*/

		//if cnic is founded inthe CBID will add the crime agains it
		//if cnic not in cbid reurn false
		//if cnic found then will return true else false ---- that wrong updation --- not found
		if (CBID.validateCNIC(cnic))
		{
			if (CCID.validateCNIC(cnic)) //if exists in ccid then append the crime
			{
				int cnicR = 0;

				//implementing that only crime will be append
				T toAppend = charges + " " + punishment + " " + fine;

				//will iterate in the ccid to find the entry aginst which to append
				CCID_NODE<T> *temp = CCID.getHead();

				//iterating in the ccid
				while (temp->next != CCID.getHead())
				{
					//the cnic in the record
					cnicR = stoi(temp->cnicC);

					if (cnicR == cnic)
					{
						//to enter in this iteration --- bcz data found
						temp->crime.addCrime(toAppend, dataPipeline, temp->crimesRead);

						//all work done thus
						return true; //the data appended
					}

					temp = temp->next;
				}
			}
			else //the make new crime data and link with it in database
			{
				T cnicS = to_string(cnic); //converting int to string

				//the concatenated string
				T toPass = cnicS + " " + charges + " " + punishment + " " + fine;

				//adding data to data pipeline then will be transfered next
				dataPipeline.enqueue(toPass, "CCID");
				T toPass2 = dataPipeline.dequeue();

				//now updating the crime against in cbid
				//first making a new entry in ccid
				CCID.addTome(toPass2, dataPipeline); //will add data to the ccid ascendingly

				//now creating the relations
				developRelations(CBID, CCID);

				//crime has been added accordingly
			}

			return true; //the cnic was right
		}

		return false; //not valid
	}

	bool updateCrime(int cnic, T charges, T punishment, T fine)
	{
		/*update and return true when crime found else return false*/
		int cnicAlready = 0;

		//if cnic not found mean crime aslo not found
		if (CCID.validateCNIC(cnic))
		{

			//iterating till  cnic
			CCID_NODE<T> *iterate = CCID.getHead();

			while (iterate->next != CCID.getHead())
			{
				cnicAlready = stoi(iterate->cnicC);

				if (cnicAlready == cnic)
				{
			
					iterate->crime.update(charges, punishment, fine);
					//updating the read crime string
					iterate->updateToread();

					return true; //crime also found and updated
				}

				iterate = iterate->next;
			}

			return true; //the cnic exist and updated
		}

		return false; //false
	}

	bool deleteCrime(int cnic, T charges, T punishment, T fine)
	{

		//checking whether cnic exixt in ccid or not because then bpossible to delete
		if (CCID.validateCNIC(cnic))
		{
			int already = 0;

			//finding the special node in ccid
			CCID_NODE<T> *temp = CCID.getHead();

			do
			{
				already = stoi(temp->cnicC);

				//if the both entered and existing nodes are same
				if (cnic == already)
				{
					//delete the crimes for temp node
					if (temp->crime.deleteme(charges, punishment, fine)) //will delete and return true if successfully deleted
					{
						//to see if the last element was deleted then also remove the relations of ccid node at this cnic
						if (temp->crime.isEmpty())
						{
							//relations develped will be deleted
							deleteRelations(CBID, CCID, cnic);

							//also deleting trace from the ccid
							CCID.deleteNode(cnic);
							
							//to Read will also be empt
							temp->updateToread();
							return true;
						}

						//updating the to read
						temp->updateToread();

						return true; //deleted so return
					}
					else
					{

						return false; //not deleted
					}
				}

				temp = temp->next;
			} while (temp != CCID.getHead()); //again when reach temp stop it

			return true;
		}

		return false;
	}

};

#endif
