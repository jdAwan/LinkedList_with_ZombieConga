#include "linkedlist.hpp"
#include "zombie.h"
#include <cstdlib> // For srand, rand
#include <ctime>   // For time
#include <iostream>

// Function declarations for Conga actions
void engine_action(LinkedList<Zombie> &congaLine, Zombie &randomZomb);
void caboose_action(LinkedList<Zombie> &congaLine, Zombie &randomZomb);
void jump_in_action(LinkedList<Zombie> &congaLine, Zombie &randomZomb,
                    int position);
void everyone_out_action(LinkedList<Zombie> &congaLine, Zombie &randomZomb);
void you_out_action(LinkedList<Zombie> &congaLine, Zombie &randomZomb);
void brains_action(LinkedList<Zombie> &congaLine, Zombie &randomZomb);
void rainbow_action(LinkedList<Zombie> &congaLine, Zombie &randomZomb);
void friends_action(LinkedList<Zombie> &congaLine, Zombie &randomZomb);

// Function to return Random Zombie
Zombie get_random_zombie();
// Function to display the Conga line
void displayCongaLine(const LinkedList<Zombie> &congaLine) {
  // std::cout << "The conga line is now:" << std::endl;
  std::cout << "Size: " << congaLine.length() << " :: ";
  congaLine.printList();
  std::cout << "**************************************************"
            << std::endl;
}

int main(int argc, char *argv[]) {
  // Seed the random number generator
  if (argc > 2 && std::string(argv[1]) == "-s") {
    srand(std::stoi(argv[2]));
  } else {
    srand(time(0));
  }

  // Create the initial Conga line
  LinkedList<Zombie> congaLine;

  // Run Rainbow Brains! action
  Zombie randomZomb = get_random_zombie();
  rainbow_action(congaLine, randomZomb);
  // displayCongaLine(congaLine);

  // Run 3 Brains actions
  for (int i = 0; i < 3; i++) {
    // randomZomb.setType(rand() % 6);
    brains_action(congaLine, randomZomb);
    // displayCongaLine(congaLine);
  }
  int rounds = 0;
  bool again = true;
  while (again) {
    // User interface

    std::cout << "How many rounds do you want to run? ";
    std::cin >> rounds;

    for (int round = 0; round < rounds; round++) {
      std::cout << "\nRound: " << round << std::endl;

      if (round % 5 == 0 && congaLine.length() > 0) {
        congaLine.removeFromFront();
        congaLine.removeFromEnd();
      }

      // display CongaLine
      std::cout << "Size: " << congaLine.length() << " :: ";
      congaLine.printList();
      std::cout << std::endl;

      Zombie randomZomb = get_random_zombie();
      int action = rand() % 8;

      std::cout << "New Zombie: [" << randomZomb.getType() << "] --";
      switch (action) {
      case 0:
        std::cout << " Action: [Engine!]";
        engine_action(congaLine, randomZomb);
        break;
      case 1:
        std::cout << " Action: [Caboose!]";
        caboose_action(congaLine, randomZomb);
        break;
      case 2:
        std::cout << " Action: [Jump In!]";
        int position;
        std::cout << "\nEnter the position to jump in: ";
        std::cin >> position;
        jump_in_action(congaLine, randomZomb, position);
        break;
      case 3:
        std::cout << " Action: [Everyone Out!]";
        everyone_out_action(congaLine, randomZomb);
        break;
      case 4:
        std::cout << " Action: [You Out!]";
        you_out_action(congaLine, randomZomb);
        break;
      case 5:
        std::cout << " Action: [Brains!]";
        brains_action(congaLine, randomZomb);
        break;
      case 6:
        std::cout << " Action: [Rainbow!]";
        rainbow_action(congaLine, randomZomb);
        break;
      case 7:
        std::cout << " Action: [New Friends!]";
        friends_action(congaLine, randomZomb);
        break;
      default:
        break;
      }
      std::cout << std::endl << "The conga line is now:" << std::endl;

      std::cout << "Size: " << congaLine.length() << " :: ";
      congaLine.printList();
      std::cout << "*************************************************"
                << std::endl;

      if (congaLine.length() == 0) {
        std::cout << "The Party is Over. Conga line is empty." << std::endl;
        again = false;
        break;
      }
    }

    std::cout << "\nDo you want to continue the party? (y/n): ";
    char choice;
    std::cin >> choice;

    if (choice == 'y' || choice == 'Y') {
      std::cout << "Enter the new number of rounds: ";
      std::cin >> rounds;
    } else {
      again = false;
    }
  }

  return 0;
}

void engine_action(LinkedList<Zombie> &congaLine, Zombie &randomZomb) {
  congaLine.addToFront(randomZomb);
}

void caboose_action(LinkedList<Zombie> &congaLine, Zombie &randomZomb) {
  congaLine.addToEnd(randomZomb);
}

void jump_in_action(LinkedList<Zombie> &congaLine, Zombie &randomZomb,
                    int position) {
  if (position <= congaLine.length()) {
    congaLine.addAtIndex(randomZomb, position);
  } else {
    std::cout << "Invalid position. Cannot jump in at position " << position
              << std::endl;
  }
}

void everyone_out_action(LinkedList<Zombie> &congaLine, Zombie &randomZomb) {
  congaLine.removeAllOf(randomZomb);
}

void you_out_action(LinkedList<Zombie> &congaLine, Zombie &randomZomb) {
  congaLine.removeTheFirst(randomZomb);
}

void brains_action(LinkedList<Zombie> &congaLine, Zombie &randomZomb) {
  congaLine.addToFront(randomZomb);
  congaLine.addToEnd(randomZomb);
  int middle = congaLine.length() / 2;
  congaLine.addAtIndex(randomZomb, middle);
}

void rainbow_action(LinkedList<Zombie> &congaLine, Zombie &randomZomb) {
  engine_action(congaLine, randomZomb);

  congaLine.addToEnd(Zombie('R'));
  congaLine.addToEnd(Zombie('Y'));
  congaLine.addToEnd(Zombie('G'));
  congaLine.addToEnd(Zombie('B'));
  congaLine.addToEnd(Zombie('C'));
  congaLine.addToEnd(Zombie('M'));
}

void friends_action(LinkedList<Zombie> &congaLine, Zombie &randomZomb) {
  Node<Zombie> *node = congaLine.find(randomZomb);
  if (node != nullptr) {
    int flip = rand() % 2;
    if (flip == 0) {
      congaLine.addBefore(node, randomZomb);
    } else {
      congaLine.addAfter(node, randomZomb);
    }
  } else {
    caboose_action(congaLine, randomZomb);
  }
}
Zombie get_random_zombie() {
  Zombie randomZomb;
  int random = rand() % 6;
  switch (random) {
  case 0:
    randomZomb = Zombie('R');
    break;
  case 1:
    randomZomb = Zombie('Y');
    break;
  case 2:
    randomZomb = Zombie('G');
    break;
  case 3:
    randomZomb = Zombie('B');
    break;
  case 4:
    randomZomb = Zombie('M');
    break;
  case 5:
    randomZomb = Zombie('C');
    break;
  default:
    break;
  }
  return randomZomb;
}
