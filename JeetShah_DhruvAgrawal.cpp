#include <bits/stdc++.h>
using namespace std;
#define ALPHABET_SIZE (26)
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

struct node{
	string data;
	struct node *next;
};
  
struct TrieNode {
	struct TrieNode* children[ALPHABET_SIZE];
	bool isWordEnd;
};
struct TrieNode* getNode(void)
{
	struct TrieNode* pNode = new TrieNode;
	pNode->isWordEnd = false;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = NULL;
	return pNode;
}
void insert(struct TrieNode* root, const string key)
{
	struct TrieNode* pCrawl = root;

	for (int level = 0; level < key.length(); level++) {
		int index = CHAR_TO_INDEX(key[level]);
		if (!pCrawl->children[index])
			pCrawl->children[index] = getNode();

		pCrawl = pCrawl->children[index];
	}
	pCrawl->isWordEnd = true;
}
bool isLastNode(struct TrieNode* root)
{
	for (int i = 0; i < ALPHABET_SIZE; i++)
		if (root->children[i])
			return 0;
	return 1;
}
void suggestionsRec(struct TrieNode* root,string currPrefix)
{
	if (root->isWordEnd)
		cout << currPrefix << endl;

	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		if (root->children[i]) {
			char child = 'a' + i;
			suggestionsRec(root->children[i],currPrefix + child);
		}
	}		
}
int printAutoSuggestions(TrieNode* root, const string query)
{
	struct TrieNode* pCrawl = root;
	for (char c : query) 
	{
		int ind = CHAR_TO_INDEX(c);
		if (!pCrawl->children[ind])
			return 0;

		pCrawl = pCrawl->children[ind];
	}
	if (isLastNode(pCrawl)) {
		cout << query << endl;
		return -1;
	}
	suggestionsRec(pCrawl, query);
	return 1;
}
void autosuggestions(){
	struct TrieNode* root = getNode();
	insert(root, "asm");
	insert(root, "auto");
	insert(root, "bool");
	insert(root, "break");
	insert(root, "case");
	insert(root, "char");
	insert(root, "cin");
	insert(root, "cout");
	insert(root, "case");
	insert(root, "catch");
	insert(root, "class");
	insert(root, "const");
	insert(root, "continue");
	insert(root, "default");
	insert(root, "delete");
	insert(root, "do");
	insert(root, "double");
	insert(root, "else");
	insert(root, "enum");
	insert(root, "explicit");
	insert(root, "export");
	insert(root, "extern");
	insert(root, "false");
	insert(root, "float");
	insert(root, "for");
	insert(root, "friend");
	insert(root, "goto");
	insert(root, "if");
	insert(root, "inline");
	insert(root, "int");
	insert(root, "long");
	insert(root, "mutable");
	insert(root, "namespace");
	insert(root, "new");
	insert(root, "operator");
	insert(root, "private");
	insert(root, "protected");
	insert(root, "public");
	insert(root, "register");
	insert(root, "return");
	insert(root, "short");
	insert(root, "signed");
	insert(root, "sizeof");
	insert(root, "static");
	insert(root, "struct");
	insert(root, "switch");
	insert(root, "template");
	insert(root, "this");
	insert(root, "throw");
	insert(root, "true");
	insert(root, "try");
	insert(root, "typedef");
	insert(root, "typeid");
	insert(root, "typename");
	insert(root, "union");
	insert(root, "unsigned");
	insert(root, "using");
	insert(root, "virtual");
	insert(root, "void");
	insert(root, "volatile");
	insert(root, "while");
	string s;
	cout << "Enter the string for the possible auto-suggestions: ";
	cin>>s;
	cout << "Did you mean any of the below suggestions provided :->\n";
    int comp = printAutoSuggestions(root, s);
	if (comp == -1)
	{
		cout << "Sorry! There are no auto suugestions for the provided character."<<endl;
	}
	else if (comp == 0)
	{
		cout << "Sorry! There are no auto suugestions for the provided character."<<endl;
	}
}

struct undoCmd{
	int lineNumber;
	string text;
	int commandNumber;
	int mLine;
	int nLine;
};


class linked_list
{
private:
	node *head;
	node *tail;
	int numOfLines = 0;
	int next = 1;
	stack<undoCmd> undoStack;
public:
	std::ofstream outfile;
	linked_list(){
		int choice = -1;
		head = NULL;
		tail = NULL;
		int prevPagePrinted = 1;
		cout<<endl;
		cout<<"-*-*-*-TEXT EDITOR-*-*-*-"<<endl;
		cout<<endl;
		while(choice != 0)
		{	
			cout<<"Please choose what you want to do"<<endl;
            cout<<"1. Insertion of text"<<endl;
			cout<<"2. Deletion of particular line"<<endl;
            cout<<"3. Swapping of text between two lines"<<endl;
            cout<<"4. Replace of text"<<endl;
			cout<<"5. Print all the contents of the text file"<<endl;
            cout<<"6. Save the contents in a new text file"<<endl;
            cout<<"7. Undo/reverse the operation"<<endl;
            cout<<"8. Open an existing text file"<<endl;
            cout<<"9. Show the contents of the previous page"<<endl;
            cout<<"10. Show the contents of the next page"<<endl;
            cout<<"11. Number of edit operations required"<<endl;
            cout<<"12. autosuggestions for the typed word"<<endl;
			cin>>choice;
			if(choice == 0){
				cout<<"Exiting the Editor !!"<<endl;
			}else{
				cout<<"The operation number "<<choice<<" is currently under execution"<<endl;
			}
			cout<<endl;
			if (choice == 1)
			{
				int lineGiven;
				string dataGiven;
				cout<<"Enter line you want the text to be placed into : ";
				cin >> lineGiven;
				cout<<"Enter text : ";
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
				getline(cin,dataGiven);
				if (lineGiven == 1)
				{
					addToHead(dataGiven);
				}
				else if (lineGiven > numOfLines)
				{
					insertFurtherAway(dataGiven,lineGiven);
				}
				else if (lineGiven < numOfLines)
				{
					insertTextInBetween(dataGiven,lineGiven);
				}
				else if (lineGiven == numOfLines)
				{
					int selection;
					cout<<"Enter 1 to replace the last line, enter 2 to insert a new line";
					cin>>selection;
					if (selection == 1)
					{
						replaceTextInLine(dataGiven,lineGiven);
					}
					else if (selection == 2)
					{
						addToTail(dataGiven);
					}
				}
			}
			else if (choice == 2)		
			{
				int lineGiven;
				cout<<"Enter the line you want to delete : ";
				cin>>lineGiven;
				deleteLine(lineGiven);
			}
			else if (choice == 3)		
			{
				int lineGiven1;
				int lineGiven2;
				cout<<"Enter line 1 you want to swap : ";
				cin>>lineGiven1;
				cout<<"Enter line 2 you want to swap : ";
				cin>>lineGiven2;
				moveNtoM(lineGiven1, lineGiven2);
			}
			else if (choice == 4)
			{
				int lineGiven;
				string dataGiven;
				cout<<"Enter line you want to change the content of : ";
				cin>>lineGiven;
				if (lineGiven > numOfLines)
				{
					cout<<"The line you entered exceeds the existing number of lines..."<<endl;
				}
				else{
					cout<<"Enter the new text : ";
					cin.ignore(numeric_limits<streamsize>::max(),'\n');
					getline(cin, dataGiven);
					replaceTextInLine(dataGiven, lineGiven);
				}
			}
			else if (choice == 5)		
			{
				printall();
			}
			else if (choice == 6)		
			{
				saveAll();
			}
			else if (choice == 7)
			{
				if (undoStack.empty())
				{
					cout<<"Nothing to undo."<<endl;
				}
				else{
					undo();
				}
			}
			else if (choice == 8)
			{
				node* current = head;
				node* next;
				while (current != NULL)
				{
				    next = current->next;
					  free(current);
				    current = next;
				}
				head = NULL;
				openFile();
			}
			else if (choice == 9)      
			{
				if (prevPagePrinted*10 > numOfLines)
				{
					printOnePage(prevPagePrinted);
				}
				else if (prevPagePrinted == 1)
				{
					printOnePage(1);
					prevPagePrinted++;
				}
				else{
					printOnePage(prevPagePrinted);
					prevPagePrinted++;
				}
			}
			else if (choice == 10)	
			{
				if (prevPagePrinted <= 0)
				{
					prevPagePrinted = 1;
					printOnePage(1);
				}
				else if (prevPagePrinted == 1)
				{
					prevPagePrinted--;
					printOnePage(1);
				}
				else{
					printOnePage(prevPagePrinted);
					prevPagePrinted--;
				}
			}
            else if (choice == 11)
            {
                string s1;
                string s2;
                cout << "The possible edit operations are: "<<endl;
                cout << "1) Insertion"<<endl;
                cout << "2) Deletion"<<endl;
                cout << "3) Replacement"<<endl;
                cout << "Statement -> 1"<<endl;
                cout << "Enter the string number 1: ";
                cin >> s1;
                cout << "Statement -> 2"<<endl;
                cout << "Enter the string number 2: ";
                cin >> s2;
                operations(s1,s2,s1.size(),s2.size());
            }
			else if (choice == 12)
			{
				autosuggestions();
			}
		}
	}
	void addToHead(string dataGiven){		
		if (head == NULL)					
		{
			node *temp;
			temp = new node;
			temp->data = dataGiven;
			temp->next = NULL;
			head = temp;
			tail = head;
			numOfLines++;
		}
		else 								
		{
			node *temp;
			temp = new node;
			temp->data = dataGiven;
			temp->next = NULL;
			temp->next = head;
			head = temp;
			numOfLines++;
		}
		undoCmd adddedToHead;
		adddedToHead.lineNumber = 1;
		adddedToHead.commandNumber = 1;
		undoStack.push(adddedToHead);
	}

	void whateverAddToTail(string dataGiven){	
		if (head == NULL)					
		{
			node *temp;
			temp = new node;
			temp->data = dataGiven;
			temp->next = NULL;
			head = temp;
			tail = head;
			numOfLines++;
		}
		else 								
		{
			node *temp;
			temp = new node;
			temp->data = dataGiven;
			temp->next = NULL;
			tail->next = temp;
			tail = temp;
			numOfLines++;
		}
	}

	void whateverDeleteTail(){				
		node *temp = head;
		if (head == NULL)
		{
			cout<<"Nothing to be deleted."<<endl;
		}
		else if (head == tail)
		{
			temp = head;
			string backup = temp->data;
			delete(temp);
			head = NULL;
			tail = NULL;
			numOfLines--;
		}
		else
		{
			while (temp->next != NULL && temp->next->next != NULL)
			{
				temp = temp->next;
			}
			tail = temp;
			delete temp->next;
			temp->next = NULL;
			numOfLines--;
		}
	}

	void addToTail(string dataGiven){		
		if (head == NULL)					
		{
			node *temp;
			temp = new node;
			temp->data = dataGiven;
			temp->next = NULL;
			head = temp;
			tail = head;
			numOfLines++;
		}
		else 								
		{
			node *temp;
			temp = new node;
			temp->data = dataGiven;
			temp->next = NULL;
			tail->next = temp;
			tail = temp;
			numOfLines++;
		}
		undoCmd addedToTail;
		addedToTail.lineNumber = 1;
		addedToTail.commandNumber = 8;
		undoStack.push(addedToTail);
	}

	void deleteHead(){					
		string backup = head->data;
		node *temp = head;
		node *nextNode = head->next;
		head = nextNode;
		delete(temp);
		numOfLines--;
		undoCmd deletedHead;
		deletedHead.text = backup;
		deletedHead.lineNumber = 1;
		deletedHead.commandNumber = 3;
		undoStack.push(deletedHead);
	}

	void deleteTail(){						
		node *temp = head;
		if (head == NULL)
		{
			cout<<"Nothing to be deleted."<<endl;
		}
		else if (head == tail)
		{
			temp = head;
			string backup = temp->data;
			delete(temp);
			head = NULL;
			tail = NULL;
			numOfLines--;
			undoCmd deletedTail;
			deletedTail.text = backup;
			deletedTail.lineNumber = 1;
			deletedTail.commandNumber = 7;
			undoStack.push(deletedTail);
		}
		else
		{
			while (temp->next != NULL && temp->next->next != NULL)
			{
				temp = temp->next;
			}
			tail = temp;
			string backup = temp->next->data;
			delete temp->next;
			temp->next = NULL;
			numOfLines--;
			undoCmd deletedTail;
			deletedTail.text = backup;
			deletedTail.lineNumber = 1;
			deletedTail.commandNumber = 7;
			undoStack.push(deletedTail);
		}
	}

	void insertTextInBetween(string dataGiven, int lineGiven){	
		if (lineGiven == 1)
		{
			if (head == NULL)					
			{
				node *temp;
				temp = new node;
				temp->data = dataGiven;
				temp->next = NULL;
				head = temp;
				tail = head;
				numOfLines++;
			}
			else 								
			{
				node *temp;
				temp = new node;
				temp->data = dataGiven;
				temp->next = NULL;
				temp->next = head;
				head = temp;
				numOfLines++;
			}
			
			undoCmd insertedToHead;
			insertedToHead.lineNumber = 1;
			insertedToHead.commandNumber = 5;
			undoStack.push(insertedToHead);
			
		}
		else{
			node *prevNode = head;
			node *nextNode = head;
			node *temp = new node();
			temp->data = dataGiven;
			temp->next = NULL;
			int iterator = 2;
			while(iterator < lineGiven)
			{
				prevNode = prevNode->next;
				nextNode = nextNode->next;
				iterator++;
			}
			nextNode = nextNode->next;
			prevNode->next = temp;
			temp->next = nextNode;
			numOfLines++;
			undoCmd insertedInBetween;
			insertedInBetween.lineNumber = lineGiven;
			insertedInBetween.commandNumber = 6;
			undoStack.push(insertedInBetween);
		}
	}

	void replaceTextInLine(string dataGiven,int lineGiven){	
		if (numOfLines < lineGiven)
		{
			cout<<"You have tried to access the lines beyond the provided "<<numOfLines<<" number of lines!!"<<endl;
		}
		else if (numOfLines >= lineGiven )
		{
			node *temp = head;
			int goToLine = 1;
			while(goToLine < lineGiven)
			{
				temp = temp->next;
				goToLine++;
			}
			string backup = temp->data;
			temp->data = dataGiven;		
			undoCmd replacedLine;
			replacedLine.lineNumber = lineGiven;
			replacedLine.text = dataGiven;
			replacedLine.commandNumber = 4;
			undoStack.push(replacedLine);
		}
	}

	void deleteLine(int lineGiven){		
		if (head == NULL)
		{
			cout<<"The Editor is empty, no line has been written."<<endl;
		}
		else if(head == tail){
			node *temp = head;
			delete(temp);
			head = NULL;
			tail = NULL;
			numOfLines--;
		}
		else if(lineGiven == 1){
			string backup = head->data;
			node *temp = head;
			node *nextNode = head->next;
			head = nextNode;
			delete(temp);
			numOfLines--;
			undoCmd headRemoved;
			headRemoved.text = backup;
			headRemoved.lineNumber = 1;
			headRemoved.commandNumber = 12;
			undoStack.push(headRemoved);
		}
		else if(lineGiven == numOfLines){
			node *temp = head;
			undoCmd deletedLine;
			deletedLine.commandNumber = 11;
			while (temp->next != NULL && temp->next->next != NULL)
			{
				temp = temp->next;
			}
			tail = temp;
			string backup = temp->next->data;
			delete temp->next;
			temp->next = NULL;
			numOfLines--;
			deletedLine.text = backup;
			deletedLine.lineNumber = lineGiven;
			undoStack.push(deletedLine);

		}
		else if (lineGiven > numOfLines)
		{
			cout<<"You have tried to access the lines beyond the provided "<<numOfLines<<" number of lines!!"<<endl;
		}
		else if (lineGiven < numOfLines)
		{
			undoCmd deletedLine;
			deletedLine.commandNumber = 10;
			node *prevNode = head;
			node *nextNode = head;
			node *temp = head;
			int iterator = 2;
			while(iterator < lineGiven)
			{
				prevNode = prevNode->next;
				nextNode = nextNode->next;
				iterator++;
			}
			nextNode = nextNode->next;
			temp = nextNode;
			nextNode = nextNode->next;
			prevNode->next = nextNode;
			string backup = temp->data;
			delete(temp);
			numOfLines--;
			deletedLine.text = backup;
			deletedLine.lineNumber = lineGiven;
			undoStack.push(deletedLine);
		}
	}

	void insertFurtherAway(string dataGiven, int lineGiven){
		undoCmd insertedFurtherAway;
		insertedFurtherAway.lineNumber = 0;
		insertedFurtherAway.commandNumber = 9;
		if (head == NULL)
		{
			while(numOfLines < lineGiven-1)
			{
				whateverAddToTail("\n");
				insertedFurtherAway.lineNumber++;
			}
			whateverAddToTail(dataGiven);
		}
		else{
			while(numOfLines < lineGiven-1)
			{
				whateverAddToTail("\n");
				insertedFurtherAway.lineNumber++;
			}
			whateverAddToTail(dataGiven);
		}
		undoStack.push(insertedFurtherAway);
	}

	void moveNtoM(int nLineGiven, int mLineGiven){	
		if (nLineGiven == 1)
		{
			string headText = head->data;
			deleteHead();
			insertTextInBetween(headText,mLineGiven);
		}
		else
		{
			node *temp = head;
			int iterator = 1;
			while(iterator < nLineGiven)
			{
				temp = temp -> next;
				iterator++;
			}
			string dataSaved = temp->data;
			deleteLine(nLineGiven);
			insertTextInBetween(dataSaved,mLineGiven);
		}
		undoCmd moveHeadToM;
		moveHeadToM.commandNumber = 2;
		moveHeadToM.nLine = nLineGiven;
		moveHeadToM.mLine= mLineGiven;
		undoStack.push(moveHeadToM);
	}

	void printOnePage(int pageGiven){
		node *temp = head;
		if (numOfLines < pageGiven*10)
		{
			int iterator = 1;
			while(iterator < (pageGiven*10)-9){
				temp = temp->next;
				iterator++;
			}
			for (int start = (pageGiven*10)-9 ; start <= numOfLines; start++)
			{
				cout<<start<<") "<<temp->data<<endl;
				temp = temp->next;
			}
			cout<<"_*_*_*_*_*_*_*_*_*_*_*_*_Page "<<pageGiven<<"_*_*_*_*_*_*_*_*_*_*_*_*_"<<endl;
		}
		else if (numOfLines >= pageGiven * 10)
		{
			int iterator = 1;
			while(iterator < (pageGiven*10)-9){
				temp = temp->next;
				iterator++;
			}
			for (int start = (pageGiven*10)-9 ; start <= pageGiven*10; start++)
			{
				cout<<start<<") "<<temp->data<<endl;
				temp = temp->next;
			}
			cout<<"_*_*_*_*_*_*_*_*_*_*_*_*_Page "<<pageGiven<<"_*_*_*_*_*_*_*_*_*_*_*_*_"<<endl;
		}
		else if (pageGiven * 10 > numOfLines)
		{
			cout<<"You cannot access an un-existing page. Please try again after writting on the new page"<<endl;
		}
	}

	void openFile(){	
		string fileName;
		cout<<"Enter the file name : ";
		cin>>fileName;
		fileName+=".txt";
		ifstream myfile;
		myfile.open(fileName);
		string s;
		while(getline(myfile,s))
		{
			addToTail(s);
		}
		myfile.close();
	}

	void undo(){			
		undoCmd temp = undoStack.top();
		if (temp.commandNumber == 1)
		{
			cout << "UNdoing the previous step"<<endl;
			cout << "Reversed the operation, check the status by clicking on choice-5"<<endl;
			deleteHead();
			undoStack.pop();
		}
		else if (temp.commandNumber == 2)
		{
			cout << "UNdoing the previous step"<<endl;
			cout << "Reversed the operation, check the status by clicking on choice-5"<<endl;
			moveNtoM(temp.mLine, temp.nLine);
			undoStack.pop();
		}
		else if (temp.commandNumber == 3)
		{
			cout << "UNdoing the previous step"<<endl;
			cout << "Reversed the operation, check the status by clicking on choice-5"<<endl;
			addToHead(temp.text);
			undoStack.pop();
		}
		else if (temp.commandNumber == 4)
		{
			cout << "UNdoing the previous step"<<endl;
			cout << "Reversed the operation, check the status by clicking on choice-5"<<endl;
			replaceTextInLine(temp.text,temp.lineNumber);
			undoStack.pop();
		}
		else if (temp.commandNumber == 5)
		{
			cout << "UNdoing the previous step"<<endl;
			cout << "Reversed the operation, check the status by clicking on choice-5"<<endl;
			deleteHead();
			undoStack.pop();
		}
		else if (temp.commandNumber == 6)
		{
			cout << "UNdoing the previous step"<<endl;
			cout << "Reversed the operation, check the status by clicking on choice-5"<<endl;
			deleteLine(temp.lineNumber);
			undoStack.pop();
		}
		else if (temp.commandNumber == 7)
		{
			cout << "UNdoing the previous step"<<endl;
			cout << "Reversed the operation, check the status by clicking on choice-5"<<endl;
			addToTail(temp.text);
			undoStack.pop();
		}
		else if (temp.commandNumber == 8)
		{
			cout << "UNdoing the previous step"<<endl;
			cout << "Reversed the operation, check the status by clicking on choice-5"<<endl;
			deleteTail();
			undoStack.pop();
		}
		else if (temp.commandNumber == 9)
		{
			int whatever = temp.lineNumber;
			while(whatever >= 0){
				whateverDeleteTail();
				whatever--;
			}
			undoStack.pop();
		}
		else if (temp.commandNumber == 10)
		{
			cout << "UNdoing the previous step"<<endl;
			cout << "Reversed the operation, check the status by clicking on choice-5"<<endl;
			insertTextInBetween(temp.text, temp.lineNumber);
			undoStack.pop();
		}
		else if (temp.commandNumber == 11)
		{
			addToTail(temp.text);
			undoStack.pop();
		}
		else if (temp.commandNumber == 12)
		{
			addToHead(temp.text);
			undoStack.pop();
		}
	}

	void printall(){						
		node *temp = head;
		int linePrinted = 1;
		int pagePrinted = 2;
		int choice;
		if (head == NULL)
		{
			cout<<"Nothing has been written yet !!"<<endl;
		}
		else{
			while(temp!=NULL)
			{
				if (linePrinted == 1)
				{
					cout<<"_*_*_*_*_*_*_*_*_*_*_*_*_Page "<<"1"<<"_*_*_*_*_*_*_*_*_*_*_*_*_"<<endl;
					cout << endl;
				}
				else if ((linePrinted-1) % 10 == 0)
				{
					cout<<"_*_*_*_*_*_*_*_*_*_*_*_*_Page "<<pagePrinted<<"_*_*_*_*_*_*_*_*_*_*_*_*_"<<endl;
					cout << endl;
					pagePrinted++;

				}
				cout<<linePrinted<<") "<<temp->data<<endl;
				temp = temp->next;
				linePrinted++;
			}
		}
	}

	void saveAll(){
		node *temp = head;
		int linePrinted = 1;
		int pagePrinted = 2;
		string fileName;
		cout<<"Enter the file name : ";
		cin>>fileName;
		fileName+=".txt";
		outfile.open(fileName, ios_base::app);
		while(temp!=NULL)
		{
			outfile<<temp->data<<endl;
			temp = temp->next;
			linePrinted++;
		}
		outfile.flush();
		outfile.close();
	}
    int insertoperations(string str1, string str2, int m, int n)
    {
        if (m == 0)
		    return n;
        if (n == 0)
		    return m;
        if (str1[m - 1] == str2[n - 1])
		    return insertoperations(str1, str2, m - 1, n - 1);
        int insertop = insertoperations(str1,str2,m,n-1);
        
        return 1 + insertop;
    }
    int deleteoperations(string str1, string str2, int m, int n)
    {
        if (m == 0)
		    return n;
        if (n == 0)
		    return m;
        if (str1[m - 1] == str2[n - 1])
		    return deleteoperations(str1, str2, m - 1, n - 1);
        int deleteop = deleteoperations(str1,str2,m-1,n);
        
        return 1 + deleteop;
    }
    int replaceoperations(string str1, string str2, int m, int n)
    {
        if (m == 0)
		    return n;
        if (n == 0)
		    return m;
        if (str1[m - 1] == str2[n - 1])
		    return replaceoperations(str1, str2, m - 1, n - 1);
        int replaceop = replaceoperations(str1,str2,m-1,n-1);
        
        return 1 + replaceop;
    }
    
    void operations(string str1, string str2, int m, int n)
    {
        int a = insertoperations(str1,str2,m,n);
        int b = deleteoperations(str1,str2,m,n);
        int c = replaceoperations(str1,str2,m,n);
        int bestop = min({a,b,c});
		cout << a <<endl << b <<endl << c<<endl;
        if (bestop == a){
            cout << "The best edit operation to be performed is: INSERT"<<endl;
            cout << "And the number of INSERT operations required is: "<<a<<endl;
        }
        if (bestop == b){
            cout << "The best edit operation to be performed is: DELETE"<<endl;
            cout << "And the number of DELETE operations required is: "<<b<<endl;
        }
        if (bestop == c){
            cout << "The best edit operation to be performed is: REPLACE"<<endl;
            cout << "And the number of REPLACE operations required is: "<<c<<endl;
        }
    }



};

int main(int argc, char const *argv[])
{
	linked_list ourList;
	cout<<endl;
	return 0;
}
