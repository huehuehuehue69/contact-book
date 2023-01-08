# **Contact Management**

This is a simple program written in C++ to manage a list of contacts. It allows you to add, search, and delete contacts based on the first name, last name, or phone number of a contact. The program reads in contact information from a file called "data.csv" and stores the information in a list of Contact objects as well as in three tries (data structures for efficiently storing and searching for strings). The program has a command-line interface and presents the user with a menu of options to choose from.

**Installation**

To use this program, follow these steps:

1. Download the files contact.h, and main.cpp.
2. Compile the files using a C++ compiler.
3. Run the executable file.

**Usage**

Run the executable file, and the program will prompt you to choose one of the following options:

1. Add a contact
2. Search for a contact

Follow the prompts to add, search, or delete a contact. To add a contact, the program will read in the contact information from "data.csv" and store it in the list of Contact objects as well as in the tries. To search for a contact, enter a search query and the program will return all the contacts in the list that match the query. To delete a contact, enter the first name, last name, or phone number of the contact you want to delete, and the program will remove the contact from the list and from the tries.

**File Descriptions**

- contact.h: This file contains the declaration of the Contact class, which represents a single contact with a first name, last name, and phone number and contains the implementation of the ContactManagement class, which manages the list of contacts and provides functions for adding, searching, and deleting contacts.

- main.cpp: This file contains the main function, which presents the user with a menu of options and calls the appropriate functions from the ContactManagement class.

**Contributing**

If you have suggestions for improvements, please open an issue or make a pull request.

**License**

This project is licensed under the MIT License.
