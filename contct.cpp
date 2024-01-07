
#include<bits/stdc++.h>
using namespace std;

std::string fileName = "contacts_new1.dat";

class Contact {
private:
    std::string name;
    std::string phoneNumber;
    std::string email;

public:
    Contact() {}
    // Constructor
    Contact(const std::string& name, const std::string& phoneNumber, const std::string& email)
        : name(name), phoneNumber(phoneNumber), email(email) {}

    // Getters
    std::string getName() const { return name; }
    std::string getPhoneNumber() const { return phoneNumber; }
    std::string getEmail() const { return email; }

    // Setters
    void setPhoneNumber(const std::string& newPhoneNumber) { phoneNumber = newPhoneNumber; }
    void setEmail(const std::string& newEmail) { email = newEmail; }
    
};

class ContactManager {
private:

    
    

public:
    std::vector<Contact> contacts;
    // Add a new contact
    void addContact(const Contact& contact) {
        contacts.push_back(contact);
    }

    // Display all contacts
    void displayContacts() const {
        std::cout << "Contact List:" << std::endl;
        for (const auto& contact : contacts) {
            std::cout << "Name: " << contact.getName() << std::endl;
            std::cout << "Phone: " << contact.getPhoneNumber() << std::endl;
            std::cout << "Email: " << contact.getEmail() << std::endl;
            std::cout << "-------------------" << std::endl;
        }
    }

    // Search for a contact by name
    void searchContact(const std::string& name) const {
        bool found = false;
        for (const auto& contact : contacts) {
            if (contact.getName() == name) {
                std::cout << "Contact found:" << std::endl;
                std::cout << "Name: " << contact.getName() << std::endl;
                std::cout << "Phone: " << contact.getPhoneNumber() << std::endl;
                std::cout << "Email: " << contact.getEmail() << std::endl;
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "Contact not found!" << std::endl;
        }
    }

    // Delete a contact by name
    void deleteContact(const std::string& name) {
        contacts.erase(std::remove_if(contacts.begin(), contacts.end(),
                                      [name](const Contact& contact) { return contact.getName() == name; }),
                       contacts.end());
    }

    // Edit contact information
    void editContact(const std::string& name) {
        for (auto& contact : contacts) {
            if (contact.getName() == name) {
                std::string newPhoneNumber, newEmail;
                std::cout << "Enter new phone number: ";
                std::cin >> newPhoneNumber;
                contact.setPhoneNumber(newPhoneNumber);

                std::cout << "Enter new email: ";
                std::cin >> newEmail;
                contact.setEmail(newEmail);

                std::cout << "Contact information updated!" << std::endl;
                return;
            }
        }
        std::cout << "Contact not found!" << std::endl;
    }

   
};


    // Save contacts to a binary file
    static void saveContactsToFile(const std::vector<Contact>& contacts) {
        std::ofstream outFile(fileName, std::ios::binary | std::ios::out);
        if (outFile.is_open()) {
            for (const auto& contact : contacts) {
                // Write each field of the Contact object separately
                size_t nameLength = contact.getName().length();
                size_t phoneNumberLength = contact.getPhoneNumber().length();
                size_t emailLength = contact.getEmail().length();

                outFile.write(reinterpret_cast<const char*>(&nameLength), sizeof(size_t));
                outFile.write(contact.getName().c_str(), nameLength);

                outFile.write(reinterpret_cast<const char*>(&phoneNumberLength), sizeof(size_t));
                outFile.write(contact.getPhoneNumber().c_str(), phoneNumberLength);

                outFile.write(reinterpret_cast<const char*>(&emailLength), sizeof(size_t));
                outFile.write(contact.getEmail().c_str(), emailLength);
            }
            outFile.close();
            std::cout << "Contacts saved to file." << std::endl;
        } else {
            std::cout << "Error: Unable to open file for writing." << std::endl;
        }
    }

    // Load contacts from a binary file
    static std::vector<Contact> loadContactsFromFile() {
        std::vector<Contact> contacts;
        std::ifstream inFile(fileName, std::ios::binary | std::ios::in);
        if (inFile.is_open()) {
            while (true) {
                size_t nameLength, phoneNumberLength, emailLength;
                // Read the lengths of each field
                inFile.read(reinterpret_cast<char*>(&nameLength), sizeof(size_t));
                if (inFile.eof()) {
                    break;
                }

                // Read the fields
                std::string name(nameLength, ' ');
                inFile.read(&name[0], nameLength);

                inFile.read(reinterpret_cast<char*>(&phoneNumberLength), sizeof(size_t));
                std::string phoneNumber(phoneNumberLength, ' ');
                inFile.read(&phoneNumber[0], phoneNumberLength);

                inFile.read(reinterpret_cast<char*>(&emailLength), sizeof(size_t));
                std::string email(emailLength, ' ');
                inFile.read(&email[0], emailLength);

                contacts.emplace_back(name, phoneNumber, email);
            }
            inFile.close();
            std::cout << "Contacts loaded from file." << std::endl;
        } else {
            std::cout << "No contacts found in file." << std::endl;
        }
        return contacts;
    }


int main() {
    ContactManager contactManager;
    contactManager.contacts = loadContactsFromFile(); // Load contacts from the file (if any)

    while (true) {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Add Contact" << std::endl;
        std::cout << "2. Display Contacts" << std::endl;
        std::cout << "3. Search Contact" << std::endl;
        std::cout << "4. Delete Contact" << std::endl;
        std::cout << "5. Edit Contact" << std::endl;
        std::cout << "6. Save Contacts to File" << std::endl;
        std::cout << "7. Exit" << std::endl;
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string name, phoneNumber, email;
                std::cout << "Enter name: ";
                std::cin.ignore(); // Ignore any trailing newline characters
                std::getline(std::cin, name);

                std::cout << "Enter phone number: ";
                std::cin >> phoneNumber;

                std::cout << "Enter email: ";
                std::cin >> email;

                Contact newContact(name, phoneNumber, email);
                contactManager.addContact(newContact);
                std::cout << "Contact added successfully!" << std::endl;
                break;
            }
            case 2:
                contactManager.displayContacts();
                break;
            case 3: {
                std::string searchName;
                std::cout << "Enter name to search: ";
                std::cin.ignore(); // Ignore any trailing newline characters
                std::getline(std::cin, searchName);

                contactManager.searchContact(searchName);
                break;
            }
            case 4: {
                std::string deleteName;
                std::cout << "Enter name to delete: ";
                std::cin.ignore(); // Ignore any trailing newline characters
                std::getline(std::cin, deleteName);

                contactManager.deleteContact(deleteName);
                std::cout << "Contact deleted successfully!" << std::endl;
                break;
            }
            case 5: {
                std::string editName;
                std::cout << "Enter name to edit: ";
                std::cin.ignore(); // Ignore any trailing newline characters
                std::getline(std::cin, editName);

                contactManager.editContact(editName);
                break;
            }
            case 6:
                saveContactsToFile(contactManager.contacts); // Save contacts to the file
                break;
            case 7:
                std::cout << "Exiting..." << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Try again." << std::endl;
        }

        std::cout << std::endl;
    }

    return 0;
}
