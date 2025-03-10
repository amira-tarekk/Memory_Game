#define ROUNDS_TO_WIN 5
#define CHOICE_RED 0
#define CHOICE_GREEN 1
#define CHOICE_BLUE 2
#define CHOICE_YELLOW 3
#define CHOICE_OFF 4

byte gameBoard[ROUNDS_TO_WIN];
byte gameRound = 0;

void setLEDs(byte which) {}

void buzz_sound(int duration, int frequency) {}

byte wait_for_button() {
    return random(0, 4);
}

void add_to_moves() {
    gameBoard[gameRound] = random(0, 4);
    gameRound++;
}

void playMoves() {
    for (byte i = 0; i < gameRound; i++) {
        toner(gameBoard[i], 300);
        delay(500);
    }
}

boolean play_memory() {
    randomSeed(millis());
    gameRound = 0;
    while (gameRound < ROUNDS_TO_WIN) {
        add_to_moves();
        playMoves();
        for (byte currentMove = 0; currentMove < gameRound; currentMove++) {
            byte choice = wait_for_button();
            if (choice != gameBoard[currentMove]) return false;
        }
        delay(1000);
    }
    return true;
}

boolean play_battle() {
    gameRound = 0;
    while (1) {
        byte newButton = wait_for_button();
        if (newButton == 0) return false;
        gameBoard[gameRound++] = newButton;
        for (byte currentMove = 0; currentMove < gameRound; currentMove++) {
            byte choice = wait_for_button();
            if (choice != gameBoard[currentMove]) return false;
        }
        delay(100);
    }
    return true;
}

void toner(byte which, int buzz_length_ms) {
    setLEDs(which);
    buzz_sound(buzz_length_ms, which == CHOICE_RED ? 1136 :
                              which == CHOICE_GREEN ? 568 :
                              which == CHOICE_BLUE ? 851 :
                              which == CHOICE_YELLOW ? 638 : 0);
    setLEDs(CHOICE_OFF);
}
