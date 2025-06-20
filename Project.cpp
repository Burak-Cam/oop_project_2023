//Burak Çam 2200003720
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

// Player Class
class Player {
private:
    string username;  // Player's username.
    string gameName;  // Game's name.
    int score;        // Player's score.

public:
    // Constructor with parameters.
    Player(const string& uname, const string& gname)
        : username(uname), gameName(gname), score(0) {
        cout << "Constructor - Player" << endl;
    }

    // Default constructor.
    Player() : score(0) {
        cout << "Base constructor - Player" << endl;
    }

    // Destructor.
    ~Player() {
        cout << "Destructor - Player" << endl;
    }

    // Accessors.
    string getUsername() const { return username; }
    string getGameName() const { return gameName; }
    int getScore() const { return score; }

    // Mutators.
    void setUsername(const string& uname) { username = uname; }
    void setGameName(const string& gname) { gameName = gname; }
    void updateScore(int points) { score += points; }
};


// Base Game Class
class Game {
protected:
    string gameName;         // Name of the game.
    int attempts;            // Number of attempts allowed.
    Player* currentPlayer;   // Pointer to the current player.

public:
    // Constructor with parameters.
    Game(const string& name)
        : gameName(name), attempts(5), currentPlayer(nullptr) {
        cout << "Constructor - Game" << endl;
    }

    // Default constructor.
    Game() : attempts(0), currentPlayer(nullptr) {
        cout << "Base constructor - Game" << endl;
    }

    // Destructor.
    virtual ~Game() {
        cout << "Destructor - Game" << endl;
    }

    // Pure virtual function to start the game.
    virtual void start() = 0;

    // Function to display end game details.
    virtual void end() {
        if (currentPlayer) {
            cout << "Player: " << currentPlayer->getUsername() << ", Score: " << currentPlayer->getScore() << endl;
        }
        else {
            cout << "No current player set." << endl;
        }
    }

    // Virtual function to display game rules.
    virtual void rules() const {
        cout << "General rules of the game:" << endl;
    }
};



// Find the Synonym Game Class
class FindTheSynonym : public Game {
private:
    // Structure to hold word-synonym pairs
    struct WordSynonymPair {
        string word;
        string synonym;
    };

    // Array of word-synonym pairs for the game
    WordSynonymPair wordSynonyms[5] = {
        {"happy", "joyful"},
        {"sad", "unhappy"},
        {"fast", "swift"},
        {"slow", "sluggish"},
        {"big", "large"}
    };

public:
    // Constructor that takes the game's name
    FindTheSynonym(const string& name) : Game(name) {}

    void rules(){
        // Call the base class's rules method to display general rules.
        Game::rules();
        cout << "1. You will be given a word, and you have to provide its synonym." << endl;
        cout << "2. You have a maximum of 5 attempts to guess the correct synonym." << endl;
        cout << "3. Your score will be based on the number of remaining attempts when you guess correctly." << endl;
    }
    // Start the game
    void start() override {
        rules();  // Display game-specific rules

        // Randomly select a word and its synonym
        srand(time(nullptr));
        int randomIndex = rand() % 5;
        string selectedWord = wordSynonyms[randomIndex].word;

        cout << "Provide a synonym for the word: " << selectedWord << endl;

        // Set the current player with default values
        currentPlayer = new Player("DefaultName", "Find the Synonym");

        int attemptsLeft = 5;  // Number of attempts
        while (attemptsLeft > 0) {
            string guess;
            cout << "Enter your guess (" << attemptsLeft << " attempts left): ";
            cin >> guess;

            // Check if the guess is correct
            if (guess == wordSynonyms[randomIndex].synonym) {
                cout << "Congratulations! You guessed it right!" << endl;
                currentPlayer->updateScore(attemptsLeft * 10);  // Update player score
                end();  // End the game

                delete currentPlayer;  // Clean up
                currentPlayer = nullptr;

                return;
            }
            else {
                cout << "Incorrect guess. Try again." << endl;
            }

            attemptsLeft--;  // Decrease the number of attempts
        }

        delete currentPlayer;  // Clean up
        currentPlayer = nullptr;

        cout << "You ran out of attempts. The synonym was: " << wordSynonyms[randomIndex].synonym << endl;
        end();  // End the game
    }
};

// Guess Movie Game Class
class GuessMovie : public Game {
private:
    // Movie related variables
    string movieName;
    string hiddenMovieName;
    string twoWordMovies[3] = { "The Godfather", "Taxi Driver", "Pulp Fiction" };
    string threeWordMovies[3] = { "The Dark Knight", "Saving Private Ryan", "The Shawshank Redemption" };
    string fourWordMovies[2] = { "The Empire Strikes Back", "Back to the Future" };

public:
    // Constructor that takes the game's name and initializes movie-related variables, also it is parametrized
    GuessMovie(const string& name) : Game(name), movieName(""), hiddenMovieName("") {}

    // Display general and game-specific rules
    void rules() {
        Game::rules();  // Display general game rules
        cout << "Guess the movie based on hints or by guessing letters!. There are 3 modes:\n For easy, the movie will have 2 words\n For medium, it will have 3 words\n";
        cout << "For hard it will have 4 words. Good luck!" << endl;
    }

    // Start the game
    void start() override {
        currentPlayer = new Player("DefaultName", "Guess Movie");

        int mode;
        bool exitGame = false;  // Flag to determine if the player wants to exit
        rules();  // Display game-specific rules

        while (!exitGame) {
            cout << "Select game mode: \n1. Easy\n2. Medium\n3. Hard\n";
            

            // Keep prompting the user until a valid input is provided.
            while (true) {
                cout << "Enter an option (1, 2, or 3): ";
                cin >> mode;

                // If the input is valid, exit the loop.
                if (mode >= 1 && mode <= 3) {
                    break;
                }

                // If the user provides an invalid option, display an error message.
                cout << "Invalid option. Please enter 1, 2, or 3." << endl;
            }

            selectMovie(mode);  // Randomly select a movie based on the mode

            while (true) {
                cout << "Current Movie: " << hiddenMovieName << endl;
                cout << "Choose an option:\n1. Guess a letter\n2. Guess the movie\n3. Exit Game\n";
                int option;
                cin >> option;

                // Process user's choice
                if (option == 1) {
                    char letter;
                    // Keep prompting the user until a valid input is provided.
                    while (true) {
                        cout << "Enter a letter: ";
                        cin >> letter;

                        // If the input is a valid lowercase or uppercase letter, exit the loop.
                        if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z'))
                        {
                            break;
                        }

                        // If the user provides an invalid option, display an error message.
                        cout << "Invalid option. Please enter a valid letter." << endl;

                        // Consume any remaining characters until a newline character is encountered.
                        while (cin.get() != '\n');  // Discard all characters until a newline is reached
                    }
                     guessLetter(letter);  // Guess a letter
                }
                else if (option == 2) {
                    string guess;
                    cin.ignore();  // Clear input buffer
                    cout << "Enter your guess for the movie: ";
                    getline(cin, guess);  // Guess the movie name
                    if (guess == movieName) {
                        cout << "Congratulations! You guessed it right!" << endl;
                        currentPlayer->updateScore(100);  // Update player score for correct guess
                        exitGame = true;
                        end();  // End the game
                        break;
                    }
                    else {
                        cout << "Incorrect guess. Try again." << endl;
                    }
                }
                else if (option == 3) {
                    exitGame = true;  // Exit the game
                    break;
                }
                else {
                    cout << "Invalid option. Try again." << endl;
                }
            }
        }

        // Clean up player memory
        delete currentPlayer;
        currentPlayer = nullptr;
    }

private:
    // Select a movie based on the game mode
    void selectMovie(int mode) {
        srand(time(nullptr));
        switch (mode) {
        case 1:
            movieName = twoWordMovies[rand() % 3];
            break;
        case 2:
            movieName = threeWordMovies[rand() % 3];
            break;
        case 3:
            movieName = fourWordMovies[rand() % 2];
            break;
        default:
            cout << "Invalid mode. Please enter a valid option." << endl;
            break;
        }
        // Initialize hidden movie name with asterisks
        hiddenMovieName = string(movieName.size(), '*');
    }

    // Guess a letter in the movie name
    void guessLetter(char letter) {
        bool correctGuess = false;
        for (int i = 0; i < movieName.size(); ++i) {
            if (tolower(movieName[i]) == tolower(letter) && hiddenMovieName[i] == '*') {
                hiddenMovieName[i] = movieName[i];
                correctGuess = true;
            }
        }
        // Check if the user guessed correctly
        if (correctGuess) {
            cout << "Correct guess!" << endl;
            // If there are no '*' characters left in the hiddenMovieName:
            if (hiddenMovieName.find('*') == hiddenMovieName.length()){
                cout << "Congratulations! You guessed the movie!" << endl;
                currentPlayer->updateScore(50);  // Update player score for completing the movie name
                end();  // End the game
            }
        }
        else {
            cout << "Incorrect guess." << endl;
        }
    }
};



// Vampire Sheriff Game Class
class VampireSheriffGame : public Game {

public:
    public:
    // Constructor to initialize game-related variables
    VampireSheriffGame(const string& name) : Game(name) {
        // Initialize players array to nullptr
        for (int i = 0; i < 10; ++i) {
            players[i] = nullptr;
        }
        // Initialize all other pointers and counters
        sheriff = nullptr;
        vampire = nullptr;
        realPlayer = nullptr;
        realPlayerNumber = -1;
        playersAlive = 10;
    }

    void rules() {
        Game::rules();// Call base class rules
        // Display Vampire Sheriff specific rules
        cout << "Welcome to Vampire Sheriff game! The rules are simple:\nIf you are the Sheriff, you must find the Vampire by guessing his/her number.";
        cout << "But make sure that you find the Vampire before he / she finds you!" << endl;
        cout << "If you are the Vampire, then every night is your feast time but to feast with pleasure, first you need to find the Sheriff!" << endl;
        cout << "Good luck!" << endl;
    }
    //Start the game
    void start() override {
        rules(); // Display game rules
        assignRoles(); // Assign roles to players
        // Display the real player's username and number
        cout << "You are: " << realPlayer->getUsername() << " with number " << realPlayerNumber << endl;

        currentPlayer = realPlayer; // Set the current player to the real player initially

        bool gameEnded = false;

        // Main game loop for night and day phases
        while (!gameEnded) {
            gameEnded = nightPhase();
            if (!gameEnded) {
                gameEnded = dayPhase();
            }
        }
    }

private:
    // Private member variables for the game
    Player* players[10];
    Player* sheriff;
    Player* vampire;
    Player* realPlayer;
    int realPlayerNumber;
    int playersDead;
    int playersAlive;

    // Assign roles to players: Sheriff, Vampire, and others
    void assignRoles() {
        srand(time(nullptr)); // Seed for randomization

        int vampireIndex = rand() % 10;
        int sheriffIndex;
        do {
            sheriffIndex = rand() % 10;
        } while (sheriffIndex == vampireIndex);

        // Assign roles randomly
        for (int i = 0; i < 10; ++i) {
            if (i == sheriffIndex) {
                players[i] = sheriff = new Player("Sheriff", "VampireSheriff");
            }
            else if (i == vampireIndex) {
                players[i] = vampire = new Player("Vampire", "VampireSheriff");
            }
            else {
                players[i] = new Player(to_string(i + 1), "VampireSheriff");
            }
        }

        // Randomly decide whether the real player will be the sheriff or the vampire.
        int randomValue = rand() % 2;  // Generate a random value of 0 or 1.
        int realPlayerIndex;

        // Use the random value to determine the role of the real player.
        if (randomValue == 0) {
            realPlayerIndex = sheriffIndex;  // If randomValue is 0, the sheriff is the real player.
        }
        else {
            realPlayerIndex = vampireIndex;  // If randomValue is 1, the vampire is the real player.
        }

        // Set the real player and assign the corresponding player number.
        realPlayer = players[realPlayerIndex];
        realPlayerNumber = realPlayerIndex + 1;  // Convert the index to a player number.

    }

    bool nightPhase() {
        if (currentPlayer == vampire) {
            // If the current player is the Vampire
            int victim;
            cout << "Choose a victim to eliminate (Enter a number between 1-10): ";
            cin >> victim;

            // Validate victim choice
            while (victim < 1 || victim > 10 || players[victim - 1] == nullptr||victim==realPlayerNumber) {
                cout << "Invalid choice. Choose again: ";
                cin >> victim;
            }
           // If victim is the Sheriff
            if (players[victim - 1] == sheriff) {
                playersDead++;
                cout << "Game Over! Vampire killed the Sheriff." << endl;
                currentPlayer->updateScore(50);
                return true;
            }
            // If victim is other player
            cout << "Player " << victim << " has died at night." << endl;
            playersDead++;
            delete players[victim - 1];
            players[victim - 1] = nullptr;
            return false;
        }
        else { // For the computer-controlled sheriff
            return eliminateRandomPlayer();
        }
    }



    //If the computer is the Vampire
    bool eliminateRandomPlayer() {
        int randVictim;
        do {
            randVictim = (rand() % 10) + 1;
        } while (players[randVictim - 1] == nullptr || randVictim == realPlayerNumber);

        if (checkGameEnd(randVictim)) {
            delete players[randVictim - 1];
            players[randVictim - 1] = nullptr;
            return checkGameEnd(randVictim);
        }
        cout << "Player " << randVictim << " has died at night." << endl;
        delete players[randVictim - 1];
        players[randVictim - 1] = nullptr;
        return checkGameEnd(randVictim);
    }

    // Check if the game ends based on the victim
    bool checkGameEnd(int victimNumber) {
        if (players[victimNumber - 1] == sheriff) {
            cout << "Game Over! Vampire killed the Sheriff." << endl;
            playersAlive--;
            currentPlayer->updateScore(playersAlive * 5);
            return true;
        }
        playersAlive--;
        return false;
    }

    //If the Sheriff is computer controlled
    bool checkRandomPlayer() {
        int randPlayer;
        do {
            randPlayer = (rand() % 10) + 1;
        } while (players[randPlayer - 1] == nullptr || randPlayer == realPlayerNumber);

        // Check if the random player is the Vampire
        if (players[randPlayer - 1] == vampire) {
            cout << "Game Over! Now the town is safe! The Sheriff has won by eliminating the Vampire." << endl;
            currentPlayer->updateScore(playersDead * 5);
            return true;
        }
        else {
            cout << "The Sheriff guessed the wrong player. Vampire is still lurking!" << endl;
            return false;
        }
    }

    bool dayPhase() {
        
        // If the current player is the Sheriff
        if (currentPlayer == sheriff) {
            int guess;
            cout << "You are the Sheriff. Guess who the Vampire is! ";
            cin >> guess;

            while (guess < 1 || guess > 10 || guess == realPlayerNumber || players[guess - 1] == nullptr) {
                cout << "Invalid choice. Guess again: ";
                cin >> guess;
            }

            // If Sheriff guesses correctly
            if (players[guess - 1] == vampire) {
                cout << "Game Over! The Sheriff has won by eliminating the Vampire. Now the town is safe!" << endl;
                currentPlayer->updateScore(50);
                return true;
            }
            else {
                playersAlive--;
                cout << "The Sheriff guessed the wrong player. Vampire is still lurking!" << endl;
                return false;
            }
        }
        else { // If the real player is the Vampire
            return checkRandomPlayer();
        }
    }
};






// Main Menu Function
void mainMenu() {
    cout << "Welcome to Game App!" << endl;
    cout << "1. Find the Synonym" << endl;
    cout << "2. Guess Movie" << endl;
    cout << "3. Vampire Sheriff" << endl;
    cout << "4. Exit" << endl;
}

// Main Function
int main() {
    bool exitGame = false;
    while (!exitGame) {
        mainMenu();
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            FindTheSynonym game("Find the Synonym");
            game.start();
            game.end();
            break;
        }
        case 2: {
            GuessMovie game("Guess Movie");
            game.start();
            game.end();
            break;
        }
        case 3:
        {
            VampireSheriffGame game("Vampire Sheriff");
            game.start();
            game.end();
            break;
        }
        case 4: {  // 
            exitGame = true;
            cout << "Exiting the game.\n";
            break;
        }
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0; 
}