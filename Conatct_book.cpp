#include <bits/stdc++.h>
#include <fstream>
using namespace std;
class Contact
{
    string firstName, lastName, phoneNumber;

public:
    Contact(string fName, string lName, string phNo)
    {

        firstName = fName;
        lastName = lName;
        phoneNumber = phNo;
    }

    void getDetails()
    {

        cout << firstName << " " << lastName << " " << phoneNumber << endl;
    }
};

class ContactManagement
{

    struct nodeName
    {

        bool last;
        int id;
        nodeName *child[26];

        nodeName()
        {
            id = -1;
            last = false;
            for (int i = 0; i < 26; i++)
            {
                child[i] = NULL;
            }
        }
    };

    vector<int> idMatched;
    vector<Contact> listOfContacts;

    nodeName *firstNameRoot, *lastNameRoot, *phNoRoot;

    void insertTrie(nodeName *rootOfField, string &fieldName, int curNoOfContacts, char type)
    {

        nodeName *temp = rootOfField;

        for (int i = 0; i < (int)fieldName.size(); i++)
        {

            char ch = fieldName[i];

            if (temp->child[ch - type] == NULL)
            {
                nodeName *temp2 = new nodeName();
                temp->child[ch - type] = temp2;
            }

            temp = temp->child[ch - type];
        }
        temp->last = true;
        temp->id = curNoOfContacts - 1;
    }


    ContactManagement()
    {
        listOfContacts.clear();
        idMatched.clear();
        firstNameRoot = new nodeName();
        lastNameRoot = new nodeName();
        phNoRoot = new nodeName();
    }
    bool isValidDetails(string fName,string lName,string phNo){

        if(fName.empty() || lName.empty() || phNo.empty()){
            return false;
        }

        for(char ch:fName){
            char t = tolower(ch);
            if(t<'a' || t>'z'){
                return false;
            }

        }

        for(char ch:lName){

            char t = tolower(ch);
            if(t<'a' || t>'z'){
                return false;
            }
        }

        /*if((phNo[0]!='+')||((phNo.size()<7 || phNo.size()>15))){
            return false;
        }


        if(phNo[0]=='+'){
            for(int i=1;i<(int)phNo.size();i++){
                if(phNo[i]<'0' || phNo[i]>'9'){
                    return false;
                }
            }
        }*/
        return true;
    }

    void addContact()
    {

        string fName, lName, phoneNo;

        ifstream myfile;
        myfile.open("data.csv");
        while (myfile.good())
        {

            getline(myfile, fName, ',');
            getline(myfile, lName, ',');
            getline(myfile, phoneNo, '\n');

            if(!isValidDetails(fName,lName,phoneNo)){
                cout<<"NOT VALID";
                continue;
            }

            Contact newContact(fName, lName, phoneNo);

            if (phoneNo[0] == '+')
                phoneNo = phoneNo.substr(1);

            listOfContacts.push_back(newContact);

            int curSizeOfContacts = (int)listOfContacts.size();

            transform(fName.begin(), fName.end(), fName.begin(), ::tolower);
            transform(lName.begin(), lName.end(), lName.begin(), ::tolower);

            insertTrie(firstNameRoot, fName, curSizeOfContacts, 'a');
            insertTrie(lastNameRoot, lName, curSizeOfContacts, 'a');
            insertTrie(phNoRoot, phoneNo, curSizeOfContacts, '0');
            cout<<fName<<" "<<lName<<" "<<phoneNo<<endl;
        }
    }

    vector<int> completeSearch(nodeName *rootOfField, string &keyToMatch, char type)
    {

        nodeName *temp;

        temp = rootOfField;

        bool flag = false;
        for (int i = 0; i < (int)keyToMatch.size(); i++)
        {

            char ch = keyToMatch[i];

            if (temp->child[ch - type] == NULL)
                break;

            temp = temp->child[ch - type];
            if ((i == (int)keyToMatch.size() - 1) && temp->id >= 0)
                flag = true;
        }

        if (flag)
            idMatched.push_back(temp->id);

        return idMatched;
    }
    void prefixSearchBFS(nodeName *rootOfField, string key, char type)
    {
        if (rootOfField == NULL)
            return;
        nodeName *temp = rootOfField;

        for (int i = 0; i < (int)key.size(); i++)
        {
            int ind = int(key[i]) - type;
            if (temp->child[ind] == NULL)
                return;

            temp = temp->child[ind];
        }

        queue<nodeName *> q;
        q.push(temp);
        while (!q.empty())
        {
            temp = q.front();
            if (temp->last)
            {
                idMatched.push_back(temp->id);
            }

            q.pop();
            for (int i = 0; i < 26; i++)
            {
                if (temp->child[i] != NULL)
                {
                    q.push(temp->child[i]);
                }
            }
        }
    }
public:
    void display(vector<int> &objectIds)
    {

        if (objectIds.empty())
        {
            cout << "Total Matched Found: " << 0 << endl;
            return;
        }

        cout << "Total Matched Found: " << (int)objectIds.size() << endl;

        for (auto id : objectIds)
        {

            listOfContacts[id].getDetails();
        }
    }

    void showCompleteSearchResult(int type, string keyToMatch)
    {

        vector<int> ids;

        idMatched.clear();

        if (type == 1)
            ids = completeSearch(firstNameRoot, keyToMatch, 'a');

        else if (type == 2)
            ids = completeSearch(lastNameRoot, keyToMatch, 'a');

        else if (type == 3)
            ids = completeSearch(phNoRoot, keyToMatch, '0');

        display(ids);
    }

    void showPrefixSearchResult(int type, string keyToMatch)
    {

        vector<int> ids;
        idMatched.clear();

        if (type == 1)
            prefixSearchBFS(firstNameRoot, keyToMatch, 'a');

        else if (type == 2)
            prefixSearchBFS(lastNameRoot, keyToMatch, 'a');

        else if (type == 3)
            prefixSearchBFS(phNoRoot, keyToMatch, '0');

        display(idMatched);
    }
};