/************************************************************************
* Chess Game
* 
*         I've taught my computer everything I know about chess.
*  
*  Game play supports game rules including En passant, castling, and pawn 
*  promotion.
*************************************************************************/
#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <map>
#include <iterator>
using namespace std;

class Square
{
    public:
    Square() {};
    Square(int x, int y) {this->y = y; this->x = x; }
    void set(int x, int y) { this->x = x; this->y = y; }
    int getX() { return x; }
    int getY() { return y; }
    private:
    int x, y;
};

/*************************************************************************
* Piece 
* Base class for all chess pieces
**************************************************************************/
class Piece
{
    public:
    ~Piece() { if (this->square != NULL) delete [] this->square; }
    virtual bool move(int x, int y, bool capture, map<string, Piece *> pieces,
                        map<string, Piece *>:: iterator itr,  int player, Piece * piece) { return false; };
    virtual bool checkMate(int x, int y, map<string, Piece *> pieces,
                        map<string, Piece *>:: iterator itr, int player) { return false; }
    void moved() { this->moves++;}
    bool diagonal(float floatX, float floatY, float floatCurX, float floatCurY, map<string, Piece *> pieces, 
                map<string, Piece *>:: iterator itr) {
    if (floatCurX - floatX == 0)
        return false;
     if ((floatCurY - floatY) / (floatCurX - floatX) == -1.000) {
        if (floatX > floatCurX) {
            //moving top right
            for (itr = pieces.begin(); itr != pieces.end(); ++itr) {
                for (int X = floatCurX + 1, Y = floatCurY - 1; Y > floatY; Y--, X++) {
                    if (itr->second->square->getX() == X && 
                        itr->second->square->getY() == Y) {
                        if (itr->second->id == 'K' && itr->second->player != this->player) {
                            return false;
                        } else {
                            return true; 
                        }
                    }
                }
            }
        } else {
            //moving bottom left
            for (itr = pieces.begin(); itr != pieces.end(); ++itr) {
                for (int X = floatCurX - 1, Y = floatCurY + 1; Y < floatY; Y++, X--) {
                    if (itr->second->square->getX() == X && 
                        itr->second->square->getY() == Y) {
                            if (itr->second->id == 'K' && itr->second->player != this->player) {
                            return false;
                        } else {
                            return true; 
                        }
                    } 
                }
            }
        }
    } else if ((floatCurY - floatY) / (floatCurX - floatX) == 1.000) {
        //negative slope
        if (floatX > floatCurX) {
            // moving bottom right
            for (itr = pieces.begin(); itr != pieces.end(); ++itr) {
                for (int X = floatCurX + 1, Y = floatCurY + 1; Y < floatY; Y++, X++) {
                    if (itr->second->square->getX() == X && 
                        itr->second->square->getY() == Y) {
                        if (itr->second->id == 'K' && itr->second->player != this->player) {
                            return false;
                        } else {
                            return true; 
                        }
                    }
                }
            }
        } else {
            //moving top left
            for (itr = pieces.begin(); itr != pieces.end(); ++itr) {
                for (int X = floatCurX - 1, Y = floatCurY - 1; Y > floatY; Y--, X--) {
                    if (itr->second->square->getX() == X && 
                        itr->second->square->getY() == Y) {
                        if (itr->second->id == 'K' && itr->second->player != this->player) {
                            return false;
                        } else {
                            return true; 
                        }
                    }
                }
            }
        }
    } else { }
    return false;
}

bool grid(int x, int y, int curX, int curY, map<string, Piece *> pieces, 
                    map<string, Piece *>:: iterator itr) {
    if ((curX - x) == 0) {           //vertical
        if (y > curY) {      //moving down
            for (itr = pieces.begin(); itr != pieces.end(); ++itr) {
                for (int X = curX, Y = curY + 1; Y < y; Y++) {
                    if (itr->second->square->getX() == X && 
                        itr->second->square->getY() == Y) {
                        if (itr->second->id == 'K' && itr->second->player != this->player) {
                            return false;
                        } else {
                            return true;
                        }
                    }
                }
            }
        } else {
        //moving up
        for (itr = pieces.begin(); itr != pieces.end(); ++itr) {
            for (int X = curX, Y = curY - 1; Y > y; Y--) {
                if (itr->second->square->getX() == X && 
                    itr->second->square->getY() == Y) {
                        if (itr->second->id == 'K' && itr->second->player != this->player) {
                            return false;
                        } else {
                            return true; 
                        }
                    }
                }
            }
        }
    } else if ((curY - y) == 0) {
        //horizontal
        if (x > curX) {
            //moving right
            for (itr = pieces.begin(); itr != pieces.end(); ++itr) {
                for (int X = curX + 1, Y = curY; X < x; X++) {
                    if (itr->second->square->getX() == X && 
                        itr->second->square->getY() == Y) {
                        if (itr->second->id == 'K' && itr->second->player != this->player) {
                            return false;
                        } else {
                            return true; 
                        }
                    } 
                }
            }
        } else {
            //moving left
            for (itr = pieces.begin(); itr != pieces.end(); ++itr) {
                for (int X = curX - 1, Y = curY; X > x; X--) {
                    if (itr->second->square->getX() == X && 
                        itr->second->square->getY() == Y) {
                        if (itr->second->id == 'K' && itr->second->player != this->player) {
                            return false;
                        } else {
                            return true; 
                        }
                    } 
                }
            }
        }
    }
    return false;
}
    Square * square;
    int player, moves;
    char id;
};

class K: public Piece
{
    public:
    K(int x, int y, int player) { this->square = new Square(x, y); this->player = player; this->id = 'K';this->moves = 0;};

    bool collision(float x, float y, int curX, int curY, map<string, Piece *> pieces, 
                    map<string, Piece *>:: iterator itr, bool capture) {
        if (x == 0 || x == 9 || y == 0 || y == 9)
            return true;      
        for (itr = pieces.begin(); itr != pieces.end(); ++itr) {
            if (itr->second->square->getX() == x && 
                itr->second->square->getY() == y) {
                if (capture && itr->second->player != this->player) {
                    return false;
                } else {
                    return true; 
                }
            }
        }
        return false;
    }

    bool checkMate(int x, int y,  map<string, Piece *> pieces, 
                    map<string, Piece *>:: iterator itr, int player) {
        try
        {
        // Squares 1 - 9 are the squares the King can potentially move to including 
        // the square the King currently occupies. A condition is flipped when the King
        // can stay on it's square or can legally move to another square. Square 1 = King's current location
        bool square1 = true, square2 = true, square3 = true, square4 = true, square5 = true, square6 = true;
        bool square7 = true, square8 = true, square9 = true, stalemate = true;

        int otherX = this->square->getX(), otherY = this->square->getY();
        for (itr = pieces.begin(); itr != pieces.end(); ++itr) {
            if (itr->second->player != this->player && itr->first != "BK_" && itr->first != "WK_") {
                if (itr->second->move(x, y, true, pieces, pieces.begin(), player, this)) {
                    if (this->square->getX() == x && this->square->getY() == y) 
                        square1 = false;
                    else 
                        return true;
                }    
            }
        }
        if (this->square->getX() == x && this->square->getY() == y) {
            if (this->move(otherX + 1, otherY - 1, true, pieces, itr, player, this)) 
                square2 = false;
            if (this->move(otherX + 1, otherY, true, pieces, itr, player, this)) 
                square3 = false; 
            if (this->move(otherX + 1, otherY + 1, true, pieces, itr, player, this)) 
                square4 = false;
            if (this->move(otherX, otherY - 1, true, pieces, itr, player, this)) 
                square5 = false;
            if (this->move(otherX, otherY + 1, true, pieces, itr, player, this)) 
                square6 = false; 
            if (this->move(otherX - 1, otherY - 1, true, pieces, itr, player, this)) 
                square7 = false; 
            if (this->move(otherX - 1, otherY, true, pieces, itr, player, this)) 
                square8 = false; 
            if (this->move(otherX - 1, otherY + 1, true, pieces, itr, player, this)) 
                square9 = false;           
            if (!square1) {
                if (square2 && square3 && square4 && square5 && square6 && square7 && square8 && square9) 
                    cout << "\n\t\tCheckmate!";
                else
                    cout << "\n\t\tCheck!";
                return true;
            } else {
                if (square2 && square3 && square4 && square5 && square6 && square7 && square8 && square9) {
                    for (itr = pieces.begin(); itr != pieces.end(); ++itr) {
                        if (itr->second->player == this->player && (itr->first != "WK_" &&
                            itr->first != "BK_"))
                            stalemate = false;
                    }
                    if (stalemate)
                        cout << "\n\tStalemate, :(";
                }
            }
        }
    }      
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
        return false;
    }

    bool validateMove(int x, int y, bool capture, map<string, Piece *> pieces, map<string,  Piece *>:: iterator itr, int player){
        if (checkMate(x, y, pieces, itr, player))
            return false;
        int curX = this->square->getX();
        int curY = this->square->getY();
        if (collision(x, y, curX, curY, pieces, itr, capture)) 
            return false;
        int Xdif = abs(curX - x);
        int Ydif = abs(curY - y);
        if ((Xdif == 1 || Xdif == 0) && (Ydif == 1 || Ydif == 0))
            return true;
        else 
            return false;
    }
        
    bool move(int x, int y, bool capture, map<string, Piece *> pieces,
                    map<string, Piece *>:: iterator itr,  int player, Piece * piece) { 
        if (validateMove(x, y, capture, pieces, itr, player)) 
            return true;
        else 
            return false;
    } 
};

class Q: public Piece
{
    public:
    Q(int x, int y, int player) { this->square = new Square(x, y); this->player = player; this->id = 'Q'; };

    bool collision(float x, float y, int curX, int curY, map<string, Piece *> pieces, 
                    map<string, Piece *>:: iterator itr) {
        if (diagonal(x, y, curX, curY, pieces, itr) || grid(x, y, curX, curY, pieces, itr)) 
            return true;
        else
            return false;
    }

    bool validateMove(int inputX, int inputY, map<string, Piece *> pieces,
                        map<string, Piece *>:: iterator itr) {
        float curX = this->square->getX(), curY = this->square->getY(), x = inputX, y = inputY;
        if (collision(x, y, curX, curY, pieces, itr)) 
            return false;
        if ((curX - x) == 0) {
            return true;
        } else {
            float slope = fabs((curY - y) / (curX - x));
            if (slope == 1.000 || curY == y) 
                return true;
        }
        return false;
    }

    bool move(int x, int y, bool capture, map<string, Piece *> pieces,
                        map<string, Piece *>:: iterator itr,  int player, Piece * piece) {
        if (validateMove(x, y, pieces, itr)) 
            return true;
        else 
            return false;
    };
};
 
class B: public Piece
{
    public:
    B(int x, int y, int player) { this->square = new Square(x, y); this->player = player; this->id = 'B'; };
    bool collision(float x, float y, int curX, int curY, map<string, Piece *> pieces, 
                    map<string, Piece *>:: iterator itr) {
        if(diagonal(x, y, curX, curY, pieces, itr)) 
            return true;
        else
            return false;
                            
    }
    bool validateMove(int xInput, int yInput, map<string, Piece *> pieces,
                        map<string, Piece *>:: iterator itr) {
        float curX = this->square->getX(), curY = this->square->getY(), x = xInput, y = yInput;
        if ((curX - x) == 0) 
            return false;
        if (collision(x, y, curX, curY, pieces, itr))
            return false;
        float slope = fabs((curY - y) / (curX - x));
        if (slope == 1.000) 
            return true;
        return false;
    }

    bool move(int x, int y, bool capture, map<string, Piece *> pieces,
                        map<string, Piece *>:: iterator itr,  int player, Piece * piece) {
        if (validateMove(x, y, pieces, itr)) 
            return true;
        else 
            return false;
    };
};

class N: public Piece
{
    public:
    N(int x, int y, int player) { this->square = new Square(x, y); this->player = player; this->id = 'N'; };
    bool validateMove(int x, int y) {
        int curX = this->square->getX();
        int curY = this->square->getY();
        int difX = abs(curX - x);
        int difY = abs(curY - y);
        if ((difX == 2 && difY == 1) || (difX == 1 && difY == 2))
            return true;
        else
            return false;
    }
    bool move(int x, int y, bool capture, map<string, Piece *> pieces,
                        map<string, Piece *>:: iterator itr,  int player, Piece * piece) {
        if (validateMove(x, y)) 
            return true;
        else 
            return false;
    };
};

class R: public Piece
{
    public:
    R(int x, int y, int player) { this->square = new Square(x, y); this->player = player; this->id = 'R'; this->moves = 0;};
    bool collision(int x, int y, int curX, int curY, map<string, Piece *> pieces, 
                    map<string, Piece *>:: iterator itr) {
        if (grid(x, y, curX, curY, pieces, itr))
            return true;
        else
            return false;
    }
    bool validateMove(int x, int y, map<string, Piece *> pieces,
                        map<string, Piece *>:: iterator itr) {
        int curX = this->square->getX();
        int curY = this->square->getY();
        if (collision(x, y, curX, curY, pieces, itr)) 
            return false;
        if (curX == x || curY == y) 
            return true;
        else 
            return false;
    }
    bool move(int x, int y, bool capture, map<string, Piece *> pieces,
                        map<string, Piece *>:: iterator itr,  int player, Piece * piece) {
        if (validateMove(x, y, pieces, itr))
            return true;
        else 
            return false;
    };
};

class P: public Piece
{
    public:
    P(int x, int y, int player) {this->square = new Square(x, y); this->player=player; this->id = 'P'; this->moves = 0;};
    bool collision(int x, int y, int curX, int curY, map<string, Piece *> pieces, 
                map<string, Piece *>:: iterator itr) {
        for (itr = pieces.begin(); itr != pieces.end(); ++itr) {
            for (int X = curX, Y = curY - 1; Y > y; Y--) {
                if (itr->second->square->getX() == X && 
                    itr->second->square->getY() == Y) { 
                    if (itr->second->id == 'K' && itr->second->player != this->player) {
                        return false;
                    } else
                        return true;
                }
            }
        }
        return false;    
    }

    bool validateMove(int x, int y, bool capture, map<string, Piece *> pieces, 
                map<string, Piece *>:: iterator itr, Piece * piece) {
        int curX = this->square->getX(), curY = this->square->getY();
        int difX = abs(curX - x), difY = abs(curY - y);
        if ((this->player == 1 && curY < y) || (this->player == 2 && curY > y)) {
            return false;
        }
        if (!capture) {
            if (difX == 0 && (difY == 1 || (this->moves == 0 && difY == 2 ))) {
                if (collision(x, y, curX, curY, pieces, itr)) 
                    return false;
                return true;
            } else {
                return false;
            }
        } else {
            if (difX == 1 && difY == 1) {
                return true;
            } else if (difX == 1 && difY == 0 && piece->id == 'P'){
                if (piece->square->getY() == 5 && piece->moves == 1) {
                    piece->square->set(piece->square->getX(), piece->square->getY() + 1);
                    return true;
                } else if (piece->square->getY() == 4 && piece->moves == 1) { 
                    piece->square->set(piece->square->getX(), piece->square->getY() - 1);
                    return true;
                } else {}
            }         
        }
        return false;
    }
    bool move(int x, int y, bool capture, map<string, Piece *> pieces,
                        map<string, Piece *>:: iterator itr,  int player, Piece * piece) {
        if (validateMove(x, y, capture, pieces, itr, piece)) 
            return true;
        else 
            return false;
    };
}; 

void displayBoard(map<string, Piece *> pieces, map<string, Piece *>:: iterator itr) {
    bool found = false;
    cout << "\t\t   1     2     3     4     5     6     7     8\n";
    cout << "\t\t_________________________________________________\n";
    for (int y = 1; y < 9; y++) {
        cout << "\t\t|     |     |     |     |     |     |     |     |\n\t      " << y << " ";
        for (int x = 1; x < 9; x++) {
           for (itr = pieces.begin(); itr != pieces.end(); ++itr) {
               if (itr->second->square->getX() == x && itr->second->square->getY() == y) {
                   cout << "| " << itr->first << " ";
                   found = true;
               }
            }
           if (!found) 
               cout << "|     ";
            else 
               found = false;
        }
        cout << "|\n\t\t|_____|_____|_____|_____|_____|_____|_____|_____|\n";
    }
}

bool capture(Piece * & piece, Piece * & target, map<string, Piece *> pieces,
                        map<string, Piece *>:: iterator itr, int player) 
{   return piece->move(target->square->getX(), target->square->getY(), true, pieces, itr, player, target);  }

void promote(string piece, map<string, Piece *> & pieces, map<string, Piece*>::iterator itr ) {
    char promotion;
    string name, nameNum, nameToString;
    int count = 0, player = pieces[piece]->player;
    bool promote = true;
    do
    {
    cout << "\n\tHow would you like to promote " << piece << "?\n\t(Q,B,N,R) ";
    cin >> promotion;
    if (promotion != 'Q' && promotion != 'B' && promotion != 'N' && promotion != 'R') {
        cout << "\n\t\tInvalid Response"; 
        promote = false;
    }
    for (itr = pieces.begin(); itr != pieces.end(); ++itr) {
                if (itr->second->id == promotion && itr->second->player == pieces[piece]->player) 
                    count++;
        }
        count++;
        nameNum = to_string(count);
        nameToString = promotion;
        Piece * p = NULL;
        if (player == 1)
            name = "W" + nameToString + nameNum; 
        else
            name = "B" + nameToString + nameNum;
        cout << "\n\tname = " << name << endl;
    switch(promotion) {
        case 'Q':
            p = new Q(pieces[piece]->square->getX(), pieces[piece]->square->getY(), player);
            pieces.insert(pair<string, Piece *>(name, p));
            break;
        case 'B':
            p = new B(pieces[piece]->square->getX(), pieces[piece]->square->getY(), player);
            pieces.insert(pair<string, Piece *>(name, p));
            break;
        case 'N':
            p = new N(pieces[piece]->square->getX(), pieces[piece]->square->getY(), player);
            pieces.insert(pair<string, Piece *>(name, p));
            break;
        case 'R':
            p = new R(pieces[piece]->square->getX(), pieces[piece]->square->getY(), player);
            pieces.insert(pair<string, Piece *>(name, p));
            break;
    }
     if (promote) { cout << "\n\t\tPawn " << piece << " successfully promoted!"; }
    } while (!promote);
    pieces.erase(piece);
    return;
}

void newGame(map<string, Piece *> & pieces, map<string, Piece *> & tempPiece, map<string, Piece *>:: iterator itr) {
    if (!pieces.empty()) {
        for (itr = pieces.begin(); itr != pieces.end(); ++itr) {
            if (itr->second != NULL) {
                delete itr->second;
                itr->second = NULL;
            }
        }
        pieces.clear();
    }
    if (!tempPiece.empty()) {
        for (itr = pieces.begin(); itr != pieces.end(); ++itr) {
            if (itr->second != NULL) {
                delete itr->second;
                itr->second = NULL;
            }
        }
        tempPiece.clear();
    }
    Piece * BK = new K(4, 1, 2), * WK = new K(5, 8, 1), * WQ = new Q(4, 8, 1), * BQ = new Q(5, 1, 2),
    * BB1 = new B(3, 1, 2), * BB2 = new B(6, 1, 2), * WB1 = new B(3, 8, 1), * WB2 = new B(6, 8, 1),
    * BN1 = new N(2, 1, 2), * BN2 = new N(7, 1, 2), * WN1 = new N(2, 8, 1),* WN2 = new N(7, 8, 1),* BR1 = new R(1, 1, 2),
    * BR2 = new R(8, 1, 2), * WR1 = new R(1, 8, 1), * WR2 = new R(8, 8, 1),* BP1 = new P(1, 2, 2),* BP2 = new P(2, 2, 2),
    * BP3 = new P(3, 2, 2),* BP4 = new P(4, 2, 2),* BP5 = new P(5, 2, 2), * BP6 = new P(6, 2, 2),* BP7 = new P(7, 2, 2),
    * BP8 = new P(8, 2, 2),* WP1 = new P(1, 7, 1), * WP2 = new P(2, 7, 1), * WP3 = new P(3, 7, 1),* WP4 = new P(4, 7, 1),
    * WP5 = new P(5, 7, 1),* WP6 = new P(6, 7, 1),* WP7 = new P(7, 7, 1),* WP8 = new P(8, 7, 1);
    array<Piece *, 32> values = {
        BK, WK, WQ, BQ, BB1, BB2, WB1, WB2, BN1, BN2, WN1, WN2, BR1, BR2, WR1, WR2, BP1,
        BP2, BP3, BP4, BP5, BP6, BP7, BP8, WP1, WP2, WP3, WP4, WP5, WP6, WP7, WP8 
    };
    array<string, 32> keys = { 
        "BK_", "WK_", "WQ_", "BQ_", "BB1", "BB2", "WB1", "WB2", "BN1", "BN2", "WN1", "WN2", "BR1", "BR2", "WR1", "WR2", "BP1",
        "BP2", "BP3", "BP4", "BP5", "BP6", "BP7", "BP8", "WP1", "WP2", "WP3", "WP4", "WP5", "WP6", "WP7", "WP8"
    };
    for (int v = 0; v < values.size(); v++) 
        pieces.insert(pair<string, Piece *>(keys[v], values[v]));
}

int main() {
    map<string, Piece *> pieces, tempPiece;
    map<string, Piece *>:: iterator itr, titr;
    newGame(pieces, tempPiece, itr);
    cout << "\n\tWelcome to chess\n";
    bool playing = true;
    int player = 1;
    string instruct, input, x, y, piece, target;
    int X, Y, tempX, tempY, attackX, attackY;
    do 
    {
        cout << "\n\tPlayer " << player << "'s turn.\nSelect an option\n";
        cout << "\t1 - Display Board\n\t2 - Move Piece\n\t3 - Capture\n\t4 - Quit\n\t5 - New Game\n >>";
        cin >> instruct;
        try
        {
        int num = stoi(instruct);
        switch(num) 
        {
            case 1:
                displayBoard(pieces, itr);
                break;
            case 2:
                cout << "\tPiece to move\n >>";
                cin >> piece;
                itr = pieces.find(piece);
                if (itr == pieces.end()) {
                    cout << "\n\t\"" << piece << "\" is not a piece.";
                    break;
                }
                if (pieces[piece]->player != player) {
                    cout << "\n\t\t" << piece << " is not your piece.";
                    break;
                }
                cout << "\tX coordinate\n >>";
                cin >> x;
                X = stoi(x);
                cout << "\tY coordinate\n >>";
                cin >> y;
                Y = stoi(y);
                if (X == 0 || X == 9 || Y == 0 || Y == 9) {
                    cout << "\tInvalid move\n";
                    break;
                }
                if(pieces[piece]->move(X, Y, false, pieces, itr, player, pieces[piece])) {
                    tempX = pieces[piece]->square->getX();
                    tempY = pieces[piece]->square->getY();
                    pieces[piece]->square->set(X, Y);
                    if (player == 2) {
                        if (pieces["BK_"]->checkMate(pieces["BK_"]->square->getX(), 
                                             pieces["BK_"]->square->getY(), pieces, itr, 2)) {
                                    pieces[piece]->square->set(tempX, tempY);
                                    cout << "\n\t\tIllegal move.";
                                    break;
                                             }
                    } else {
                        if (pieces["WK_"]->checkMate(pieces["WK_"]->square->getX(), 
                                               pieces["WK_"]->square->getY(), pieces, itr, 1)) {
                                    pieces[piece]->square->set(tempX, tempY);
                                    cout << "\n\tIllegal move.";
                                    break;
                                               }
                    }
                    if (pieces[piece]->id == 'P' && (Y == 1 || Y == 8))
                        promote(piece, pieces, itr);
                    else {
                        cout << "\n\t" << piece << " moved successfully.\n";
                        pieces[piece]->moved();
                    }
                    if (player == 1) 
                        player = 2;
                    else 
                        player = 1;
                } else 
                    cout << "\n\t\tIllegal move.";
                break;
            case 3:
                cout << "\tPiece capturing\n >>";
                cin >> piece;
                cout << "\tPiece to capture\n >>";
                cin >> target;
                if (target == "WK_" || target == "BK_") {
                    cout << "\n\tOops! Cannot capture King!\n";
                    break;
                }
                itr = pieces.find(piece);
                titr = pieces.find(target);
                if (itr == pieces.end() || titr == pieces.end()) {
                    cout << "\n\t\"" << piece << "\" or \"" << target << "\" are not pieces.";
                    break;
                }
                if (pieces[piece]->player != player) {
                    cout << "\n\t\t" << piece << " is not your piece.";
                    break;
                }
                if (pieces[target]->player == player) {
                    cout << "\n\t\tFriendly capture!";
                    break;
                }
                attackX = pieces[piece]->square->getX();
                attackY = pieces[piece]->square->getY();
                tempX = pieces[target]->square->getX();
                tempY = pieces[target]->square->getY();
                tempPiece.insert(pair<string, Piece *>(target, pieces[target]));
                if (capture(pieces[piece], pieces[target], pieces, itr, player)) {
                    pieces[piece]->square->set(pieces[target]->square->getX(), pieces[target]->square->getY());
                    pieces.erase(target);
                         if (player == 2) {
                            if (pieces["BK_"]->checkMate(pieces["BK_"]->square->getX(), 
                                             pieces["BK_"]->square->getY(), pieces, itr, 2)) {
                                cout << "\n\t\tIllegal move.";
                                pieces[piece]->square->set(attackX, attackY);
                                pieces.insert(pair<string, Piece *>(target, tempPiece[target]));
                                pieces[target]->square->set(tempX, tempY);
                                break;
                            }
                        } else {
                            if (pieces["WK_"]->checkMate(pieces["WK_"]->square->getX(), 
                                               pieces["WK_"]->square->getY(), pieces, itr, 1)) {
                                cout << "\n\tIllegal move.";
                                pieces[piece]->square->set(attackX, attackY);
                                pieces.insert(pair<string, Piece *>(target, tempPiece[target]));
                                pieces[target]->square->set(tempX, tempY);
                                break;
                            }
                        }
                    cout << "\tPiece " << target << " captured successfully!\n";
                    pieces[piece]->moved();
                    if (pieces[piece]->id == 'P' && (tempY == 1 || tempY == 8))
                        promote(piece, pieces, itr);
                    if (player == 1) 
                        player = 2;
                    else 
                        player = 1;
                } else 
                    cout << "\tFailed to capture " << target << " :(\n";
                break;
            case 4:
                playing = false;
                    if (!pieces.empty()) {
                        for (itr = pieces.begin(); itr != pieces.end(); ++itr) {
                            if (itr->second != NULL) {
                                delete itr->second;
                                itr->second = NULL;
                            }
                        }
                        pieces.clear();
                    }
                    if (!tempPiece.empty()) {
                        for (itr = pieces.begin(); itr != pieces.end(); ++itr) {
                            if (itr->second != NULL) {
                                delete itr->second;
                                itr->second = NULL;
                            }
                        }
                        tempPiece.clear();
                    }
                break;
            case 5:
                newGame(pieces, tempPiece, itr);
                break;
            default:
                cout << "\tInvalid choice\n";
                break;
        }
        pieces["BK_"]->checkMate(pieces["BK_"]->square->getX(), pieces["BK_"]->square->getY(), pieces, itr, 2);
        pieces["WK_"]->checkMate(pieces["WK_"]->square->getX(), pieces["WK_"]->square->getY(), pieces, itr, 1);
        }
        catch(const std::exception& e)
        {
            cout << "You've encountered an error\n";
        }
    } while(playing);
    return 0;
}