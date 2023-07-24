#include<bits/stdc++.h>
#include "contact.h"

int main(){

    cout<<"-----------------------------    CONTACT MANAGEMENT SYSTEM      ---------------"<<endl;

    ContactManagement newSystem;

    while(1){
        cout<<endl;
        cout<<"1. Add Contact "<<endl;
        cout<<"2. Complete Search Contact"<<endl;
        cout<<"3. Prefix Search Contact"<<endl;

        cout<<"Enter your choice"<<endl;

        int ch;
        cin>>ch;

        switch(ch){

            case 1:
                newSystem.addContact();
                break;

            case 2:{

                cout<<"1. Search by first name"<<endl;
                cout<<"2. Search by last name"<<endl;
                cout<<"3. Search by phone number"<<endl;

                cout<<"Enter your choice"<<endl;

                int newCh;
                cin>>newCh;

                cout<<"Enter the key to search"<<endl;
                string key;
                cin>>key;

                transform(key.begin(),key.end(),key.begin(), :: tolower);
                newSystem.showCompleteSearchResult(newCh,key);

                break;
            }
            case 3:{

                cout<<"1. Search by first name"<<endl;
                cout<<"2. Search by last name"<<endl;
                cout<<"3. Search by phone number"<<endl;

                cout<<"Enter your choice"<<endl;

                int newCh;
                cin>>newCh;

                cout<<"Enter the key to search"<<endl;
                string key;
                cin>>key;

                transform(key.begin(),key.end(),key.begin(), :: tolower);

                newSystem.showPrefixSearchResult(newCh,key);
                break;
            }

            default:
                cout<<"Enter valid options"<<endl;
        }
    }
}
