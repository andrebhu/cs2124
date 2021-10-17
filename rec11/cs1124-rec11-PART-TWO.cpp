/*
  rec11-part-two.cpp
  Starting code
 */

#include <iostream>
#include <vector>
using namespace std;


class Instrument{
    public:
        virtual void makeSound() const = 0;
        virtual void play() const = 0;
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

    void play() const{
      if (instr) instr->play();
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
          void play() const{
            cout << "Toot";
          }
};
class Trombone : public BrassInstrument{
    public:
        Trombone(int s) : BrassInstrument(s) {}
          void play() const{
            cout << "Blat";
          }
};

class Violin : public StringInstrument{
    public:
        Violin(int p) : StringInstrument(p) {}

        void play() const{
          cout << "Screech";
        }
};
class Cello : public StringInstrument{
    public:
        Cello(int p) : StringInstrument(p) {}

        void play() const{
          cout << "Squawk";
        }
};

class Drum : public PercussionInstrument{
    public:
      void play() const{
        cout << "Boom";
      }

};
class Cymbal : public PercussionInstrument{
    public:
      void play() const{
        cout << "Crash";
      }
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


class Orch{
  public:
    void addPlayer(Musician& m){
      musicians.push_back(&m);
    }

    void play(){
      for(size_t i = 0; i < musicians.size(); ++i){
        musicians[i]->play();
      }
    }
  private:
    vector<Musician*> musicians;
};


// PART TWO
int main() {
    // The initialization phase

    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12);
    Violin violin(567);

    MILL mill;
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);

    Musician bob;
    Musician sue;
    Musician mary;
    Musician ralph;
    Musician jody;
    Musician morgan;

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
	
    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

} // main

