#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

string filename = "cardfile.txt";

struct Card {
    string owner;
    string phoneNumber;
    string time;
    bool paymentStatus;
    Card* left;
    Card* right;
};

Card* createCard(string owner, string phoneNumber, string time) {
    Card* newCard = new Card;
    newCard->owner = owner;
    newCard->phoneNumber = phoneNumber;
    newCard->time = time;
    newCard->paymentStatus = false;
    newCard->left = nullptr;
    newCard->right = nullptr;
    return newCard;
}

Card* insertCard(Card* root, string owner, string phoneNumber, string time) {
    if (root == nullptr) {
        return createCard(owner, phoneNumber, time);
    }

    if (phoneNumber < root->phoneNumber) {
        root->left = insertCard(root->left, owner, phoneNumber, time);
    }
    else if (phoneNumber > root->phoneNumber) {
        root->right = insertCard(root->right, owner, phoneNumber, time);
    }

    return root;
}

void displayCardFile(Card* root) {
    if (root != nullptr) {
        displayCardFile(root->left);
        cout << "Owner: " << root->owner << "\tPhone Number: " << root->phoneNumber << "\tTime: " 
            << root->time;
        cout << "\tPayment Status: " << (root->paymentStatus ? "Paid" : "Unpaid") << endl;
        displayCardFile(root->right);
    }
}

Card* searchCard(Card* root, string phoneNumber, string time) {
    if (root == nullptr || root->phoneNumber == phoneNumber || root->time == time) {
        return root;
    }

    if (phoneNumber < root->phoneNumber) {
        return searchCard(root->left, phoneNumber, time);
    }

    return searchCard(root->right, phoneNumber, time);
}

void updatePaymentStatus(Card* card) {
    card->paymentStatus = true;
    cout << "Payment status updated. Telephone conversation paid." << endl;
}

void writeCardFileToFile(Card* root, ofstream& file) {
    if (root != nullptr) {
        writeCardFileToFile(root->left, file);
        file << "Owner: " << root->owner << "\tPhone number: " << root->phoneNumber << "\tTime: " 
            << root->time << "\tPayment status: " << root->paymentStatus << endl;
        writeCardFileToFile(root->right, file);
    }
}

void writeCardFile(Card* root, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        writeCardFileToFile(root, file);
        file.close();
        cout << "Card file written to " << filename << " successfully." << endl;
    }
    else {
        cout << "Unable to open the file " << filename << " for writing." << endl;
    }
}

void deallocateMemory(Card* root) {
    if (root != nullptr) {
        deallocateMemory(root->left);
        deallocateMemory(root->right);
        delete root;
    }
}

int main() {
    Card* cardFile = nullptr;
    string owner, phoneNumber, time;
    while (true) {
        cout << "1. Add a card\n2. Display the card file\n3. Pay for a telephone conversation"
            <<"\n4. Write to the file\n5. Exit"<< endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cout << endl;
        if (choice == 1) {
            cout << "Enter the owner's name: ";
            cin.ignore();
            getline(cin, owner);
            cout << "Enter the phone number: ";
            cin >> phoneNumber;
            cout << "Enter the time: ";
            cin >> time;
            cardFile = insertCard(cardFile, owner, phoneNumber, time);
            cout << "Card added successfully." << endl;
        }
        else if (choice == 2) {
            cout << "Card File:" << endl;
            displayCardFile(cardFile);
        }
        else if (choice == 3) {
            cout << "Enter the phone number: ";
            cin >> phoneNumber;
            Card* card = searchCard(cardFile, phoneNumber, time);
            if (card != nullptr) {
                if (card->paymentStatus) {
                    cout << "Telephone conversation has already been paid." << endl;
                }
                else {
                    updatePaymentStatus(card);
                }
            }
            else {
                cout << "Card not found." << endl;
            }
        }
        else if (choice == 4) {
            writeCardFile(cardFile, filename);
        }
        else if (choice == 5) {
            break;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
        cout << endl;
    }
    writeCardFile(cardFile, filename);

    //deallocateMemory(cardFile);

    return 0;
}
