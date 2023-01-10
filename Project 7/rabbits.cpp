// rabbits.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the utterly trivial
// functions (marked TRIVIAL).  Then get Arena::display going.  That gives
// you more flexibility in the order you tackle the rest of the functionality.
// As you finish implementing each TODO: item, remove its TODO: comment.

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;               // max number of rows in the arena
const int MAXCOLS = 25;               // max number of columns in the arena
const int MAXRABBITS = 100;           // max number of rabbits allowed

const int NORTH = 0;
const int EAST = 1;
const int SOUTH = 2;
const int WEST = 3;
const int NUMDIRS = 4;

const int EMPTY = 0;
const int HAS_POISON = 1;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Arena;  // This is needed to let the compiler know that Arena is a
// type name, since it's mentioned in the Rabbit declaration.

class Rabbit
{
public:
    // Constructor
    Rabbit(Arena* ap, int r, int c);

    // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

    // Mutators
    void move();

private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_poisoned = 0;
    bool   m_wait = false;
};

class Player
{
public:
    // Constructor
    Player(Arena* ap, int r, int c);

    // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

    // Mutators
    string dropPoisonedCarrot();
    string move(int dir);
    void   setDead();

private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   m_dead;
};

class Arena
{
public:
    // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();

    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     rabbitCount() const;
    int     getCellStatus(int r, int c) const;
    int     numberOfRabbitsAt(int r, int c) const;
    void    display(string msg) const;

    // Mutators
    void setCellStatus(int r, int c, int status);
    bool addRabbit(int r, int c);
    bool addPlayer(int r, int c);
    void moveRabbits();

private:
    int     m_grid[MAXROWS][MAXCOLS];
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Rabbit* m_rabbits[MAXRABBITS];
    int     m_nRabbits;
    int     m_turns;

    // Helper functions
    void checkPos(int r, int c, string functionName) const;
    bool isPosInBounds(int r, int c) const;
};

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nRabbits);
    ~Game();

    // Mutators
    void play();

private:
    Arena* m_arena;

    // Helper functions
    string takePlayerTurn();
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int randInt(int lowest, int highest);
bool decodeDirection(char ch, int& dir);
bool attemptMove(const Arena& a, int dir, int& r, int& c);
bool recommendMove(const Arena& a, int r, int c, int& bestDir);
int nextTo(const Arena& a, int r, int c);
double touchingPoisonedCarrots(const Arena& a, int r, int c);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
//  Rabbit implementation
///////////////////////////////////////////////////////////////////////////

Rabbit::Rabbit(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** A rabbit must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1 || r > ap->rows() || c < 1 || c > ap->cols())
    {
        cout << "***** Rabbit created with invalid coordinates (" << r << ","
            << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
}

int Rabbit::row() const
{
    return m_row;
}

int Rabbit::col() const
{
    //Return what column the Rabbit is at
    
    return m_col;  
}

bool Rabbit::isDead() const
{
    //Return whether the rabbit is dead
    if (m_poisoned == 2) {  //uses create private member to decide if it is dead
        return true;
    }
    else {
        return false;
    }
}

void Rabbit::move()
{
    //   Return without moving if the rabbit has eaten one poisoned
    //   carrot (so is supposed to move only every other turn) and
    //   this is a turn it does not move.
    if (m_poisoned == 1) {
        if (m_wait == false) {  //M_wait flips back and forth if rabbit is poisoned so we return every OTHER turn
            m_wait = true;
            return;
        }
        m_wait = false;
    }
    int way = randInt(0, NUMDIRS - 1);  //randomly generates one # from 0 to 3
    //int r = row();
    //int c = col();
    //int count = 0;
    //if (m_poisoned == 1) {
    //    count++;
    //}

    //if (m_poisoned == 1 && m_wait == true && count % 2 != 0) { 
    //    return;
    //}
    switch (way) {
    case NORTH:
        if (m_row > 1) { //moves rabbit north if not going out of bounds
            m_row--;
            //r--;
        }
        break;
    case EAST:
        if (m_col < m_arena->cols()) { //moves rabbit east if not going out of bounds
            m_col++;
           // c++;
        }
        break;
    case SOUTH:
        if (m_row < m_arena->rows()) {  // " South "
            m_row++;
            //r++;
        }
        break;
    case WEST:
        if (m_col > 1) {    //" west "
            m_col--;
           // c--;
        }
        break;
    }
    if (m_arena->getCellStatus(m_row, m_col) == HAS_POISON) { //changing to r and c
        m_poisoned++;
        //m_health--;
        m_arena->setCellStatus(m_row, m_col, EMPTY);
    }
    //count++;
    
    //   If it lands on a poisoned carrot, eat the 
    //   carrot and remove it from the game (so it is no longer on that
    //   grid point).
}

///////////////////////////////////////////////////////////////////////////
//  Player implementation
///////////////////////////////////////////////////////////////////////////

Player::Player(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** The player must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1 || r > ap->rows() || c < 1 || c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
            << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_dead = false;
}

int Player::row() const
{
    //Return what row the Player is at
    return m_row;  
}

int Player::col() const
{
    //Return what column the Player is at
    return m_col;  
}

string Player::dropPoisonedCarrot()
{
    if (m_arena->getCellStatus(m_row, m_col) == HAS_POISON)
        return "There's already a poisoned carrot at this spot.";
    m_arena->setCellStatus(m_row, m_col, HAS_POISON);
    return "A poisoned carrot has been dropped.";
}

string Player::move(int dir)
{
    switch (dir) {
    case NORTH:
        if (m_row > 1) {    //allow player to move north if not at top of arena
            m_row--;
            return "Player moved north.";
        }
        break;
    case EAST:
        if (m_col < m_arena->cols()) {  //allow player to move east if col isnt max
            m_col++;
            return "Player moved east.";
        }
        break;
    case SOUTH:
        if (m_row < m_arena->rows()) {//allow player to move south if not at bottom of arena
            m_row++;
            return "Player moved south.";
        }
        break;
    case WEST:
        if (m_col > 1) {    //allow player to move west if not at far left of arena
            m_col--;
            return "Player moved west.";
        }
        break;
    }
    if (m_arena ->numberOfRabbitsAt(m_row, m_col) >= 1){
        return "Player walked into a rabbit and died.";
    }
    //        Attempt to move the player one step in the indicated
    //        direction.  If this fails,
    //        return "Player couldn't move; player stands."
    //        A player who moves onto a rabbit, and this
    //        returns "Player walked into a rabbit and died."
    //        Otherwise, return one of "Player moved north.",
    //        "Player moved east.", "Player moved south.", or
    //        "Player moved west."
    return "Player couldn't move; player stands.";  // This implementation compiles, but is incorrect.
}

bool Player::isDead() const
{
    //Return whether the Player is dead
    return m_dead;
}

void Player::setDead()
{
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Arena implementation
///////////////////////////////////////////////////////////////////////////

Arena::Arena(int nRows, int nCols)
{
    if (nRows <= 0 || nCols <= 0 || nRows > MAXROWS || nCols > MAXCOLS)
    {
        cout << "***** Arena created with invalid size " << nRows << " by "
            << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nRabbits = 0;
    m_turns = 0;
    for (int r = 1; r <= m_rows; r++)
        for (int c = 1; c <= m_cols; c++)
            setCellStatus(r, c, EMPTY);
}

Arena::~Arena()
{
    delete m_player;    //delete the only dynamically allocated player
    for (int i = 0; i < m_nRabbits; i++) {  //loop through and delete all rabbits
        delete m_rabbits[i];
    }
}

int Arena::rows() const
{
    //Return the number of rows in the arena
    return m_rows;  
}

int Arena::cols() const
{
    // Return the number of columns in the arena
    return m_cols; 
}

Player* Arena::player() const
{
    return m_player;
}

int Arena::rabbitCount() const
{
    //Return the number of rabbits in the arena
    return m_nRabbits; 
}

int Arena::getCellStatus(int r, int c) const
{
    checkPos(r, c, "Arena::getCellStatus");
    return m_grid[r - 1][c - 1];
}

int Arena::numberOfRabbitsAt(int r, int c) const
{
    int rabbitCount = 0;    //counter for # of rabbits
    for (int i = 0; i < m_nRabbits; i++) {
        if ((m_rabbits[i]->row() == r) && (m_rabbits[i]->col() == c)) { //if rabbits row value = to r and rabbits 
            rabbitCount++;                                              // col value = c, a rabbit is at that loc
        }
    }
    return rabbitCount;
}

void Arena::display(string msg) const
{
    char displayGrid[MAXROWS][MAXCOLS];
    int r, c;

    // Fill displayGrid with dots (empty) and stars (poisoned carrots)
    for (r = 1; r <= rows(); r++)
        for (c = 1; c <= cols(); c++)
            displayGrid[r - 1][c - 1] = (getCellStatus(r, c) == EMPTY ? '.' : '*');

    // Indicate each rabbit's position
    if (numberOfRabbitsAt(r, c) == 1) { //not sure why c is uninitialized memory, i do above
        displayGrid[r][c] = 'R';
    }
    int numrabs = 0;

    for (r = 1; r < rows() + 1; r++) {
        for (c = 1; c < cols() + 1; c++) {
            numrabs = numrabs + numberOfRabbitsAt(r, c);
            if (numberOfRabbitsAt(r, c) >= 9) {
                displayGrid[r - 1][c - 1] = 9 + '0';
            }   //adding '0' makes it so we can go through 2-8 bc they are contiguous in ASCII
            else if (numberOfRabbitsAt(r, c) >= 2) {
                displayGrid[r - 1][c - 1] = numberOfRabbitsAt(r, c) + '0';
            }
            else if (numberOfRabbitsAt(r, c) == 1) {
                displayGrid[r - 1][c - 1] = 'R';
            }
        }
    }
    //        If one rabbit is at some grid point, set the displayGrid char
    //        to 'R'.  If it's 2 though 8, set it to '2' through '8'.
    //        For 9 or more, set it to '9'.

    // Indicate the player's position
    if (m_player != nullptr)
        displayGrid[m_player->row() - 1][m_player->col() - 1] = (m_player->isDead() ? 'X' : '@');

    // Draw the grid
    clearScreen();
    for (r = 1; r <= rows(); r++)
    {
        for (c = 1; c <= cols(); c++)
            cout << displayGrid[r - 1][c - 1];
        cout << endl;
    }
    cout << endl;

    // Write message, rabbit, and player info
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << rabbitCount() << " rabbits remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player!" << endl;
    else if (m_player->isDead())
        cout << "The player is dead." << endl;
    cout << m_turns << " turns have been taken." << endl;
}

void Arena::setCellStatus(int r, int c, int status)
{
    checkPos(r, c, "Arena::setCellStatus");
    m_grid[r - 1][c - 1] = status;
}

bool Arena::addRabbit(int r, int c)
{
    if (!isPosInBounds(r, c))
        return false;

    // Don't add a rabbit on a spot with a poisoned carrot
    if (getCellStatus(r, c) != EMPTY)
        return false;

    // Don't add a rabbit on a spot with a player
    if (m_player != nullptr && m_player->row() == r && m_player->col() == c)
        return false;

    // If there are MAXRABBITS existing rabbits, return false.  Otherwise,
    // dynamically allocate a new rabbit at coordinates (r,c).  Save the
    // pointer to newly allocated rabbit and return true.
    if (m_nRabbits >= MAXRABBITS) {
        return false;
    }
    else {
        m_rabbits[m_nRabbits] = new Rabbit(this, r, c);
        m_nRabbits++;
        return true;
    }
}

bool Arena::addPlayer(int r, int c)
{
    if (!isPosInBounds(r, c))
        return false;

    // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;

    // Don't add a player on a spot with a rabbit
    if (numberOfRabbitsAt(r, c) > 0)
        return false;

    m_player = new Player(this, r, c);
    return true;
}

void Arena::moveRabbits()
{
    // Move all rabbits
    for (int i = 0; i < m_nRabbits; i++) {
        m_rabbits[i]->move();
        if (m_rabbits[i]->row() == m_player->row() && m_rabbits[i]->col() == m_player->col()) {
            m_player->setDead();
        }
        if (m_rabbits[i]->isDead()) {
            delete m_rabbits[i]; 
                m_rabbits[i] = nullptr;
            for (int j = i; j < m_nRabbits-1; j++) { //check all rabbits (except if out of scope "-1"
                m_rabbits[j] = m_rabbits[j+1];  //move all pointer values left 1 to make up for deleting m_rabbits at i
            }
            m_nRabbits--;
        }
    }
    // Another turn has been taken
    m_turns++;
}

bool Arena::isPosInBounds(int r, int c) const
{
    return (r >= 1 && r <= m_rows && c >= 1 && c <= m_cols);
}

void Arena::checkPos(int r, int c, string functionName) const
{
    if (!isPosInBounds(r, c))
    {
        cout << "***** " << "Invalid arena position (" << r << ","
            << c << ") in call to " << functionName << endl;
        exit(1);
    }
}

///////////////////////////////////////////////////////////////////////////
//  Game implementation
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nRabbits)
{
    if (nRabbits < 0)
    {
        cout << "***** Cannot create Game with negative number of rabbits!" << endl;
        exit(1);
    }
    if (nRabbits > MAXRABBITS)
    {
        cout << "***** Trying to create Game with " << nRabbits
            << " rabbits; only " << MAXRABBITS << " are allowed!" << endl;
        exit(1);
    }
    int nEmpty = rows * cols - nRabbits - 1;  // 1 for Player
    if (nEmpty < 0)
    {
        cout << "***** Game created with a " << rows << " by "
            << cols << " arena, which is too small too hold a player and "
            << nRabbits << " rabbits!" << endl;
        exit(1);
    }

    // Create arena
    m_arena = new Arena(rows, cols);

    // Add player
    int rPlayer;
    int cPlayer;
    do
    {
        rPlayer = randInt(1, rows);
        cPlayer = randInt(1, cols);
    } while (m_arena->getCellStatus(rPlayer, cPlayer) != EMPTY);
    m_arena->addPlayer(rPlayer, cPlayer);

    // Populate with rabbits
    while (nRabbits > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        if (r == rPlayer && c == cPlayer)
            continue;
        m_arena->addRabbit(r, c);
        nRabbits--;
    }
}

Game::~Game()
{
    delete m_arena;
}

string Game::takePlayerTurn()
{
    for (;;)
    {
        cout << "Your move (n/e/s/w/c or nothing): ";
        string playerMove;
        getline(cin, playerMove);

        Player* player = m_arena->player();
        int dir;

        if (playerMove.size() == 0)
        {
            if (recommendMove(*m_arena, player->row(), player->col(), dir))
                return player->move(dir);
            else
                return player->dropPoisonedCarrot();
        }
        else if (playerMove.size() == 1)
        {
            if (tolower(playerMove[0]) == 'c')
                return player->dropPoisonedCarrot();
            else if (decodeDirection(playerMove[0], dir))
                return player->move(dir);
        }
        cout << "Player move must be nothing, or 1 character n/e/s/w/c." << endl;
    }
}

void Game::play()
{
    m_arena->display("");
    Player* player = m_arena->player();
    if (player == nullptr)
        return;
    while (!player->isDead() && m_arena->rabbitCount() > 0)
    {
        string msg = takePlayerTurn();
        m_arena->display(msg);
        if (player->isDead())
            break;
        m_arena->moveRabbits();
        m_arena->display(msg);
    }
    if (player->isDead())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementation
///////////////////////////////////////////////////////////////////////////

  // Return a uniformly distributed random int from lowest to highest, inclusive
int randInt(int lowest, int highest)
{
    if (highest < lowest)
        swap(highest, lowest);
    static random_device rd;
    static default_random_engine generator(rd());
    uniform_int_distribution<> distro(lowest, highest);
    return distro(generator);
}

bool decodeDirection(char ch, int& dir)
{
    switch (tolower(ch))
    {
    default:  return false;
    case 'n': dir = NORTH; break;
    case 'e': dir = EAST;  break;
    case 's': dir = SOUTH; break;
    case 'w': dir = WEST;  break;
    }
    return true;
}

// Return false without changing anything if moving one step from (r,c)
// in the indicated direction would run off the edge of the arena.
// Otherwise, update r and c to the position resulting from the move and
// return true.
bool attemptMove(const Arena& a, int dir, int& r, int& c)
{
    switch (dir) {
    case NORTH:
        if (r > 1) {
            r--;
        }
        else {
            return false;
        }
        break;
    case EAST:
        if (c < a.cols()) {
            c++;
        }
        else {
            return false;
        }
        break;
    case SOUTH:
        if (r < a.rows()) {
            r++;
        }
        else {
            return false;
        }
        break;
    case WEST:
        if (c > 1) {
            c++;
        }
        else {
            return false;
        }
        break;
    }
    return true;  
}

bool rabbitsSurrounding(const Arena& a, int dir, int r, int c) {    //added function, check how many rabbits are surronding position
    int count = MAXRABBITS;
    if (dir == NORTH) {
        r--;
        count = a.numberOfRabbitsAt(r - 1, c) + a.numberOfRabbitsAt(r, c + 1) + a.numberOfRabbitsAt(r, c - 1);
    }
    else if (dir == EAST) {
        c++;
        count = a.numberOfRabbitsAt(r, c + 1) + a.numberOfRabbitsAt(r + 1, c) + a.numberOfRabbitsAt(r - 1, c);
    }
    else if (dir == WEST) {
        c--;
        count = a.numberOfRabbitsAt(r, c - 1) + a.numberOfRabbitsAt(r + 1, c) + a.numberOfRabbitsAt(r - 1, c);
    }
    else if (dir == SOUTH) {
        r++;
        count = a.numberOfRabbitsAt(r + 1, c) + a.numberOfRabbitsAt(r, c + 1) + a.numberOfRabbitsAt(r, c - 1);
    }
    return count;
}

// Recommend a move for a player at (r,c):  A false return means the
// recommendation is that the player should drop a poisoned carrot and
// not move; otherwise, this function sets bestDir to the recommended
// direction to move and returns true.

bool recommendMove(const Arena& a, int r, int c, int& bestDir)
{
    double minimumThreat = 100;
    double degreeThreat;
    double oddsDie = 0;

    //if threat level is least in NORTH direction, go NORTH
    if (r - 1 >= 1) {
        if (a.getCellStatus(r - 1, c) == HAS_POISON)
            oddsDie = .5;
        oddsDie += 0.1 * touchingPoisonedCarrots(a, r - 1, c);  //0.1 is just used to normalize touchingPoisonedCarrot value/double
        degreeThreat = nextTo(a, r - 1, c) + oddsDie;              //used the same way throughout the rest of code
        if (degreeThreat < minimumThreat) {
            bestDir = NORTH;
            minimumThreat = degreeThreat;   //establishes threat level of going NORTH
        }
    }

    oddsDie = 0;
    //if threat level is least in the EAST direction, go EAST
    if (c + 1 <= a.cols()) {
        if (a.getCellStatus(r, c + 1) == HAS_POISON)
            oddsDie = .5;
        oddsDie += 0.1 * touchingPoisonedCarrots(a, r, c + 1);
        degreeThreat = nextTo(a, r, c + 1) + oddsDie;
        if (degreeThreat < minimumThreat) {
            bestDir = EAST;
            minimumThreat = degreeThreat;   //compares this new threat level to previous NORTH threat level
        }
    }

    oddsDie = 0;
    //if threat level is least in the SOUTH direction, go SOUTH
    if (r + 1 <= a.rows()) {
        if (a.getCellStatus(r + 1, c) == HAS_POISON)
            oddsDie = .5;
        oddsDie += 0.1 * touchingPoisonedCarrots(a, r + 1, c);
        degreeThreat = nextTo(a, r + 1, c) + oddsDie;
        if (degreeThreat < minimumThreat) {
            bestDir = SOUTH;
            minimumThreat = degreeThreat; //compares this new THReat leaeal (South) to lowest level previosuly checked
        }
    }

    oddsDie = 0;
    //if threat level is least in the WEST direciton, go WEST
    if (c - 1 >= 1) {
        if (a.getCellStatus(r, c - 1) == HAS_POISON)
            oddsDie = .5;
        oddsDie += 0.1 * touchingPoisonedCarrots(a, r, c - 1);
        degreeThreat = nextTo(a, r, c - 1) + oddsDie;
        if (degreeThreat <= minimumThreat) {
            bestDir = WEST;
            minimumThreat = degreeThreat; //compares WEST threat level to lowest level out of n/s/e
        }
    }

    oddsDie = -.5;
    if (a.getCellStatus(r, c) == HAS_POISON)    //if cell doesnt have poison, oddsDie stays negative
        oddsDie = .5;
    oddsDie += 0.1 * touchingPoisonedCarrots(a, r, c);
    degreeThreat = nextTo(a, r, c) + oddsDie; //if threat is large next to player, oddsDie increases
    if (degreeThreat < minimumThreat) {       //so the odds you DIE increases
        return false;
    }
    return true;
}

int nextTo(const Arena& a, int r, int c) {

    int limit = 1; //edge of arena
    //if (c > a.cols() || c < 1 || r > a.rows() || r < 1)
    //	limit = 0;

    int degreeThreat = 0;
    degreeThreat += a.numberOfRabbitsAt(r - limit, c);  //calcs level of threat at n/s/e/w tiles/squares
    degreeThreat += a.numberOfRabbitsAt(r, c - limit);
    degreeThreat += a.numberOfRabbitsAt(r + limit, c);
    degreeThreat += a.numberOfRabbitsAt(r, c + limit);
    if (a.numberOfRabbitsAt(r, c) > 0)
        degreeThreat += 10000;  //10000 can be any number > degreeThreat, so probably larger than like 5
    return degreeThreat;
}

//returns value of if player is touching a poisoned carrot
//the greater the double means there is less likely to be a poison carrot at predicted position
double touchingPoisonedCarrots(const Arena& a, int r, int c) {
    double poisonedAmt = 0.0;

    if (r - 1 >= 1) {
        if (a.getCellStatus(r - 1, c) == HAS_POISON)
            poisonedAmt += 1;
    }
    else
        poisonedAmt += 1.5;
    if (r + 1 <= a.rows()) {
        if (a.getCellStatus(r + 1, c) == HAS_POISON)
            poisonedAmt += 1;
    }
    else
        poisonedAmt += 1.5;
    if (c + 1 <= a.cols()) {
        if (a.getCellStatus(r, c + 1) == HAS_POISON)
            poisonedAmt += 1;
    }
    else
        poisonedAmt += 1.5;
    if (c - 1 >= 1) {
        if (a.getCellStatus(r, c - 1) == HAS_POISON)
            poisonedAmt += 1;
    }
    else
        poisonedAmt += 1.5;

    return poisonedAmt;
}

//bool recommendMove(const Arena& a, int r, int c, int& bestDir)
//{
//    bool noRabbit = false;
//    int rabbitPos[NUMDIRS] = { MAXRABBITS, MAXRABBITS, MAXRABBITS, MAXRABBITS };
//
//    if (a.numberOfRabbitsAt(r + 1, c) != 0) { //checks south condition here (south == 0)
//        if (attemptMove(a, NORTH, r, c) == true && a.numberOfRabbitsAt(r - 1, c) == 0) {
//            rabbitPos[NORTH] = rabbitsSurrounding(a, NORTH, r, c);
//            noRabbit = true;
//        }
//        if (attemptMove(a, WEST, r, c) == true && a.numberOfRabbitsAt(r, c - 1) == 0) {
//            rabbitPos[WEST] = rabbitsSurrounding(a, WEST, r, c);
//            noRabbit = true;
//        }
//        if (attemptMove(a, EAST, r, c) == true && a.numberOfRabbitsAt(r, c + 1) == 0) {
//            rabbitPos[EAST] = rabbitsSurrounding(a, EAST, r, c);
//            noRabbit = true;
//        }
//        if (noRabbit == false) {
//            return false;
//        }
//
//        int count = MAXRABBITS;
//        int rightDir = 0;
//        for (int i = 0; i < NUMDIRS; i++) {
//            if (rabbitPos[i] < count) {
//                rightDir = i;
//                count = rabbitPos[i];
//            }
//        }
//        bestDir = rightDir;
//        return true;
//    }
//
//    //CHECKS IF RABBIT IS NORTH OF PLAYERS
//    if (a.numberOfRabbitsAt(r - 1, c) != 0) {
//        if (attemptMove(a, SOUTH, r, c) == true && a.numberOfRabbitsAt(r + 1, c) == 0) {
//            rabbitPos[SOUTH] = rabbitsSurrounding(a, SOUTH, r, c);
//            noRabbit = true;
//        }
//        if (attemptMove(a, WEST, r, c) == true && a.numberOfRabbitsAt(r, c - 1) == 0) {
//            rabbitPos[WEST] = rabbitsSurrounding(a, WEST, r, c);
//            noRabbit = true;
//        }
//        if (attemptMove(a, EAST, r, c) == true && a.numberOfRabbitsAt(r, c + 1) == 0) {
//            rabbitPos[EAST] = rabbitsSurrounding(a, EAST, r, c);
//            noRabbit = true;
//        }
//        if (noRabbit == false) {
//            return false;
//        }
//
//        int count = MAXRABBITS;
//        int rightDir = 0;
//        for (int i = 0; i < NUMDIRS; i++) {
//            if (rabbitPos[i] < count) {
//                rightDir = i;
//                count = rabbitPos[i];
//            }
//        }
//        bestDir = rightDir;
//        return true;
//    }
//
//    //CHECKS EAST
//    if (a.numberOfRabbitsAt(r, c + 1) != 0) {
//        if (attemptMove(a, SOUTH, r, c) == true && a.numberOfRabbitsAt(r + 1, c) == 0) {
//            rabbitPos[SOUTH] = rabbitsSurrounding(a, SOUTH, r, c);
//            noRabbit = true;
//        }
//        if (attemptMove(a, NORTH, r, c) == true && a.numberOfRabbitsAt(r - 1, c) == 0) {
//            rabbitPos[NORTH] = rabbitsSurrounding(a, NORTH, r, c);
//            noRabbit = true;
//        }
//        if (attemptMove(a, WEST, r, c) == true && a.numberOfRabbitsAt(r, c - 1) == 0) {
//            rabbitPos[WEST] = rabbitsSurrounding(a, WEST, r, c);
//            noRabbit = true;
//        }
//        if (noRabbit == false) {
//            return false;
//        }
//        int count = MAXRABBITS;
//        int rightDir = 0;
//        for (int i = 0; i < NUMDIRS; i++) {
//            if (rabbitPos[i] < count) {
//                rightDir = i;
//                count = rabbitPos[i];
//            }
//        }
//        bestDir = rightDir;
//        return true;
//    }
//
//    //CHECKS WEST
//    if (a.numberOfRabbitsAt(r, c - 1) != 0) {
//        if (attemptMove(a, SOUTH, r, c) == true && a.numberOfRabbitsAt(r+ 1, c) == 0) {
//            rabbitPos[SOUTH] = rabbitsSurrounding(a, SOUTH, r, c);
//            noRabbit = true;
//        }
//        if (attemptMove(a, NORTH, r, c) == true && a.numberOfRabbitsAt(r - 1, c) == 0) {
//            rabbitPos[NORTH] = rabbitsSurrounding(a, NORTH, r, c);
//            noRabbit = true;
//        }
//        if (attemptMove(a, EAST, r, c) == true && a.numberOfRabbitsAt(r, c + 1) == 0) {
//            rabbitPos[EAST] = rabbitsSurrounding(a, EAST, r, c);
//            noRabbit = true;
//        }
//        if (noRabbit == false){
//            return false;
//        }
//        int count = MAXRABBITS;
//        int rightDir = 0;
//        for (int i = 0; i < NUMDIRS; i++) {
//            if (rabbitPos[i] < count) {
//                rightDir = i;
//                count = rabbitPos[i];
//            }
//        }
//        bestDir = rightDir;
//        return true;
//    }
//
//    //Moves to another place with no poison pellet
//    if (a.getCellStatus(r, c) == HAS_POISON) {
//        if (attemptMove(a, NORTH, r, c) == true && a.numberOfRabbitsAt(r - 1, c) == 0) {
//            rabbitPos[NORTH] = rabbitsSurrounding(a, NORTH, r, c);
//        }
//        if (attemptMove(a, SOUTH, r, c) == true && a.numberOfRabbitsAt(r + 1, c) == 0) {
//            rabbitPos[SOUTH] = rabbitsSurrounding(a, SOUTH, r, c);
//        }
//        if (attemptMove(a, WEST, r, c) == true && a.numberOfRabbitsAt(r, c - 1) == 0) {
//            rabbitPos[WEST] = rabbitsSurrounding(a, WEST, r, c);
//        }
//        if (attemptMove(a, EAST, r, c) == true && a.numberOfRabbitsAt(r, c + 1) == 0) {
//            rabbitPos[EAST] = rabbitsSurrounding(a, EAST, r, c);
//        }
//
//        for (int i = 0; i < NUMDIRS; i++)
//            if (rabbitPos[i] == 0) 
//                switch (i)
//                {
//                case WEST:
//                    if (attemptMove(a, WEST, r, c) == true) {
//                        if (a.getCellStatus(r, c - 1) == EMPTY) {
//                            bestDir = i;
//                            return true;
//                        }
//                    }
//                    break;
//                case EAST:
//                    if (attemptMove(a, EAST, r, c) == true) {
//                        if (a.getCellStatus(r, c + 1) == EMPTY) {
//                            bestDir = i;
//                            return true;
//                        }
//                    }
//                    break;
//                case SOUTH:
//                    if (attemptMove(a, SOUTH, r, c) == true) {
//                        if (a.getCellStatus(r + 1, c) == EMPTY) {
//                            bestDir = i;
//                            return true;
//                        }
//                    }
//                    break;
//                case NORTH:
//                    if (attemptMove(a, NORTH, r, c) == true) {
//                        if (a.getCellStatus(r - 1, c) == EMPTY) {
//                            bestDir = i;
//                            return true;
//                        }
//                    }
//                    break;
//                }
//                return false;
//            }
//        return false;
//    }
    //if (a.numberOfRabbitsAt(r + 1, c) > 0 && a.numberOfRabbitsAt(r, c + 1) > 0 && a.numberOfRabbitsAt(r, c - 1) > 0) {
    //    bestDir = NORTH;
    //    return true;
    //}
    //if (a.numberOfRabbitsAt(r - 1, c) > 0 && a.numberOfRabbitsAt(r, c + 1) > 0 && a.numberOfRabbitsAt(r, c - 1) > 0) {
    //    bestDir = SOUTH;
    //    return true;
    //}
    //if (a.numberOfRabbitsAt(r, c + 1) > 0 && a.numberOfRabbitsAt(r - 1, c) > 0 && a.numberOfRabbitsAt(r + 1, c) > 0) {//all sides surrounded except one
    //    bestDir = WEST;
    //    return true;
    //}
    //if (a.numberOfRabbitsAt(r + 1, c) > 0 && a.numberOfRabbitsAt(r - 1, c) > 0 && a.numberOfRabbitsAt(r, c - 1) > 0) {
    //    bestDir = EAST;
    //    return true;
    //}

    //if (a.numberOfRabbitsAt(r + 1, c) > 0 && a.numberOfRabbitsAt(r, c + 1) > 0) {
    //    bestDir = NORTH;
    //    return true;
    //}
    //if (a.numberOfRabbitsAt(r + 1, c) > 0 && a.numberOfRabbitsAt(r, c - 1) > 0) {
    //    bestDir = NORTH;
    //    return true;
    //}
    //if (a.numberOfRabbitsAt(r - 1, c) > 0 && a.numberOfRabbitsAt(r, c + 1) > 0) {
    //    bestDir = WEST;
    //    return true;
    //}
    //if (a.numberOfRabbitsAt(r - 1, c) > 0 && a.numberOfRabbitsAt(r, c - 1) > 0) {
    //    bestDir = SOUTH;
    //    return true;
    //}
    //if (a.numberOfRabbitsAt(r + 1, c) > 0) {
    //    bestDir = NORTH;
    //    return true;
    //}
    //if (a.numberOfRabbitsAt(r - 1, c) > 0) {
    //    bestDir = SOUTH;
    //    return true;
    //}
    //if (a.numberOfRabbitsAt(r, c + 1) > 0) {
    //    bestDir = WEST;
    //    return true;
    //}
    //if (a.numberOfRabbitsAt(r, c - 1) > 0) {
    //    bestDir = EAST;
    //    return true;
    //}
    //return false;

//}

///////////////////////////////////////////////////////////////////////////
// main()
///////////////////////////////////////////////////////////////////////////

int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 5, 2);
    Game g(10, 12, 40);

    // Play the game
    g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANYTHING BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++/g31 UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _WIN32

#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
        &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not _WIN32

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr || strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif