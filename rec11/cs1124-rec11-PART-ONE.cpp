/*
  rec11-part-one.cpp
  Starting code
 */

#include <iostream>
#include <vector>
using namespace std;

class Instrument{
    public:
        virtual void makeSound() const = 0;
};

void Instrument::makeSound() const{
    cout << "To make a sound... ";
}

class Musician {
public:
    Musician() : instr(nullptr) {}

    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    Instrument* giveBackInstr() { 
        Instrument* result(instr); 
        instr = nullptr;
        return result;
    }

    void testPlay() const {
        if (instr) instr->makeSound(); 
        else cerr << "have no instr\n";
    }

private:
    Instrument* instr;
};



class BrassInstrument : public Instrument{
    public:
        BrassInstrument(int s){
            if(s == 12 || s == 9 || s == 4){
                size = s;
            }
        }

        void makeSound() const{
            Instrument::makeSound();
            cout << "blow on a mouthpiece of size " << size << endl;
        }
    private:
        int size;
};

class StringInstrument : public Instrument{
    public:
        StringInstrument(int p) : pitch(p) {}

        void makeSound() const{
            Instrument::makeSound();
            cout << "bow a string with pitch " << pitch << endl;
        }
    private:
        int pitch;
};

class PercussionInstrument : public Instrument{
    public:
        void makeSound() const{
            Instrument::makeSound();
            cout << "hit me!" << endl;
        }
};

class Trumpet : public BrassInstrument{
    public:
        Trumpet(int s) : BrassInstrument(s) {}
};
class Trombone : public BrassInstrument{
    public:
        Trombone(int s) : BrassInstrument(s) {}
};

class Violin : public StringInstrument{
    public:
        Violin(int p) : StringInstrument(p) {}
};
class Cello : public StringInstrument{
    public:
        Cello(int p) : StringInstrument(p) {}
};

class Drum : public PercussionInstrument{
    public:

};
class Cymbal : public PercussionInstrument{
    public:

};

class MILL{
    public:
        void receiveInstr(Instrument& instr){
            instr.makeSound();
            for(size_t i = 0; i < instruments.size(); ++i){
                if (instruments[i] == nullptr){
                    instruments[i] = &instr;
                    return;
                }
            }
            instruments.push_back(&instr);
        }

        void dailyTestPlay(){
            for(size_t i = 0; i < instruments.size(); ++i){
                if(instruments[i] != nullptr){
                    instruments[i]->makeSound();
                }
            }
        }

        Instrument* loanOut(){  
            Instrument* temp;
            for(size_t i = 0; i < instruments.size(); ++i){
                if(instruments[i] != nullptr){
                    temp = instruments[i];
                    instruments[i] = nullptr;
                    return temp;
                }
            }
            return nullptr;
        }

    private:
        vector<Instrument*> instruments;
};

// PART ONE
int main() {

    cout << "Define some instruments ------------------------------------\n";
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12) ;
    Violin violin(567) ;
  
    // use the debugger to look at the mill
    cout << "Define the MILL --------------------------------------------\n";
    MILL mill;
  
    cout << "Put the instruments into the MILL --------------------------\n";
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);
  
    cout << "Daily test -------------------------------------------------\n"
	 << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    cout << "Define some Musicians---------------------------------------\n";
    Musician harpo;
    Musician groucho;
  	
    cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
    groucho.testPlay();	
    cout << endl;
    groucho.acceptInstr(mill.loanOut());
    cout << endl;
    groucho.testPlay();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
  
    cout << endl << endl;
  
    groucho.testPlay();	
    cout << endl;
    mill.receiveInstr(*groucho.giveBackInstr());
    harpo.acceptInstr(mill.loanOut());
    groucho.acceptInstr(mill.loanOut());
    cout << endl;
    groucho.testPlay();
    cout << endl;
    harpo.testPlay();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
  
    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
  
    // fifth
    mill.receiveInstr(*groucho.giveBackInstr());
    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());

  
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    cout << endl;
}
