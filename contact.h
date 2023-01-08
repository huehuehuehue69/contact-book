#include<bits/stdc++.h>
#include<fstream>
using namespace std;

class Contact{

    string firstName,lastName,phoneNumber;

public:

    Contact(string fName, string lName, string phNo){

        firstName=fName;
        lastName=lName;
        phoneNumber=phNo;
    }

    void getDetails(){

        cout<<firstName<<" "<<lastName<<" "<<phoneNumber<<endl;
    }

};

class ContactManagement{

    struct nodeName{

        bool last;
        int id;
        nodeName* child[26];

        nodeName(){
            id=-1;
            last = false;
//            isLastName = false;
            for(int i=0;i<26;i++){
                child[i]=NULL;
            }
        }

    };

    vector<int> idMatched;
    vector<Contact> listOfContacts;

    map<string,vector<int>> fNameToId,lNameToId,phoneNoToId;

    nodeName *root,*root2,*rootPhNo;


public:

    ContactManagement(){
        listOfContacts.clear();
        fNameToId.clear();
        lNameToId.clear();
        phoneNoToId.clear();
        idMatched.clear();
        root=new nodeName();
        root2=new nodeName();
        rootPhNo=new nodeName();
    }

    void addContact() {

        string fName, lName, phoneNo;

        ifstream myfile;
        myfile.open("sam.csv");
        while (myfile.good()) {

            getline(myfile, fName, ',');
            getline(myfile, lName, ',');
            getline(myfile, phoneNo, '\n');

            Contact newContact(fName, lName, phoneNo);

            if(phoneNo[0]=='+')
                phoneNo=phoneNo.substr(1);

            listOfContacts.push_back(newContact);

            int curSizeOfContacts = (int) listOfContacts.size();

            transform(fName.begin(), fName.end(), fName.begin(), ::tolower);
            transform(lName.begin(), lName.end(), lName.begin(), ::tolower);

            nodeName *temp;

            temp = root;
            for (int i = 0; i < (int) fName.size(); i++) {

                char ch = fName[i];

                if (temp->child[ch - 'a'] == NULL) {
                    nodeName *temp2 = new nodeName();
                    temp->child[ch - 'a'] = temp2;


                }

                temp = temp->child[ch - 'a'];

                if (i == (int) fName.size() - 1) {
                    temp->id = curSizeOfContacts - 1;
                }

            }
            temp->last = true;
            temp->id=curSizeOfContacts-1;

            temp = root2;

            for (int i = 0; i < (int) lName.size(); i++) {

                char ch = lName[i];

                if (temp->child[ch - 'a'] == NULL) {
                    nodeName *temp2 = new nodeName();
                    temp->child[ch - 'a'] = temp2;


                }

                temp = temp->child[ch - 'a'];



            }
            temp->last = true;
            temp->id=curSizeOfContacts-1;
            temp = rootPhNo;

            for (int i = 0; i < (int) phoneNo.size(); i++) {

                char ch = phoneNo[i];
                int x = ch - '0';


                if (temp->child[x] == NULL) {
                    nodeName *temp2 = new nodeName();
                    temp->child[x] = temp2;


                }

                temp = temp->child[ch - '0'];
            }

            temp->last=true;
            temp->id=curSizeOfContacts-1;
            cout << fName << " " << lName << " " << phoneNo << endl;

        }

    }

    vector<int> completeSearch(nodeName *rt, string &keyToMatch,char type){


        nodeName* temp;

        temp=rt;

        bool flag = false;
        for(int i=0;i<(int)keyToMatch.size();i++){

            char ch=keyToMatch[i];

            if(temp->child[ch-type]==NULL)
                break;

            temp=temp->child[ch-type];
            if((i==(int)keyToMatch.size()-1)&&temp->id>=0)
                flag = true;

        }

        if(flag)
            idMatched.push_back(temp->id);

        return idMatched;

    }
    void prefixSearchBFS( nodeName* root,string key,char type)
    {
        if(root==NULL) return ;
        nodeName* temp = root;

        for(int i=0;i<(int)key.size();i++)
        {
            int ind = int(key[i])-type;
            if( temp->child[ind] == NULL ) return ;

            temp = temp->child[ind];
        }

        queue<nodeName*> q;
        q.push(temp);
        while(!q.empty())
        {
            temp = q.front();
            if(temp->last) {
                idMatched.push_back(temp->id);
            }

            q.pop();
            for(int i=0;i<26;i++)
            {
                if( temp->child[i] !=NULL )
                {
                    q.push(temp->child[i]);
                }
            }
        }

    }



    void display(vector<int> &objectIds){

        if(objectIds.empty()){
            cout<<"Total Matched Found: "<<0<<endl;
            return;
        }

        cout<<"Total Matched Found: "<<(int)objectIds.size()<<endl;

        for(auto id:objectIds){

            listOfContacts[id].getDetails();
        }
    }


    void showCompleteSearchResult(int type,string keyToMatch){

        vector<int> ids;

        idMatched.clear();

        if(type==1)
            ids=completeSearch(root,keyToMatch,'a');

        else if(type ==2)
            ids=completeSearch(root2,keyToMatch,'a');

        else if(type==3)
            ids=completeSearch(rootPhNo,keyToMatch,'0');

        display(ids);
    }

    void showPrefixSearchResult(int type, string keyToMatch){

        vector<int> ids;
        idMatched.clear();

        if(type==1)
            prefixSearchBFS(root,keyToMatch,'a');

        else if(type ==2)
            prefixSearchBFS(root2,keyToMatch,'a');

        else if(type==3)
            prefixSearchBFS(rootPhNo,keyToMatch,'0');

        display(idMatched);

    }

};
