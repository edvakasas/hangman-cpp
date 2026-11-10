# Hangman (C++ OOP)

A two-player console Hangman game written in C++ for the Object-Oriented Programming course at VILNIUS TECH (2025).

One player enters a secret word and an optional hint, and the other guesses letters before running out of 6 lives.

## What it shows

- An abstract base class `Zaidejas` (player) with a pure virtual `veiksmas()` method, and two derived classes, `ZodzioNustatytojas` (word setter) and `Spejikas` (guesser), that override it.
- A `Zaidimas` (game) class that owns the game state: `std::set` for correct and wrong guesses, `std::map` for an on-screen keyboard that marks used letters, and the remaining lives.
- An ASCII gallows that updates as lives are lost, plus a one-time hint.

## Run

```
g++ -std=c++17 -o hangman Hangman.cpp
./hangman
```

The screen is cleared with `system("cls")`, so it is meant for the Windows console. The game text is in Lithuanian.
