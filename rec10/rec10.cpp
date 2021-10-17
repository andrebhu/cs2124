/*
Andre Hu
4/9
Inheritance
*/


#include <iostream>
#include <vector>
using namespace std;

class PrintedMaterial {
public:
    PrintedMaterial(unsigned numPages)
	: numOfPages(numPages)
    {}

    virtual void displayNumPages() const = 0;

private:
    unsigned numOfPages;
};

void PrintedMaterial::displayNumPages() const {
    cout << numOfPages << endl;
}

class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned numPages)
	: PrintedMaterial(numPages)
    {}

    // virtual - NOTE even without writing "virtual"
    // again, this overriden method IS virtual
    // viruality cannot be removed once installed
    // Also note that the = 0 has is not there
    void displayNumPages() const {
	cout << "Magazine ";
	PrintedMaterial::displayNumPages();
    }

private:
};

class Book : public PrintedMaterial {
public:
    Book(unsigned numPages)
	: PrintedMaterial(numPages)
    {}

private:
};

class TextBook : public Book {
public:
    TextBook(unsigned numPages, unsigned numIndxPgs)
	: Book(numPages),
	  numOfIndexPages(numIndxPgs)
    {}

    void displayNumPages() const {
	cout << "Textbook ";
	PrintedMaterial::displayNumPages();
	cout << "Index pages: ";
	cout << numOfIndexPages << endl; 
    }

private:
    unsigned numOfIndexPages;
};

class Novel : public Book {
public:
    Novel(unsigned numPages)
	: Book(numPages)
    {}
    void displayNumPages() const {
	cout << "Novel ";
	PrintedMaterial::displayNumPages();
    }
private:
};


// tester/modeler code
int main() {
    TextBook text(5430, 23);
    Novel novel(213);
    Magazine mag(6);

    text.displayNumPages();
    novel.displayNumPages();
    mag.displayNumPages();
    cout << "===========\n";
    PrintedMaterial* pmPtr;
    pmPtr = &text;
    pmPtr->displayNumPages();
    cout << "===========\n";

    vector<PrintedMaterial*> storage;
    storage.push_back(&text);
    storage.push_back(&novel);
    storage.push_back(&mag);
    for(size_t i = 0; i < storage.size(); ++i){
        storage[i]->displayNumPages();
    }
   
}