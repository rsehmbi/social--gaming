#include "MainMenuWindow.h"

#include <stdio.h>
#include <menu.h>
#include <ncurses.h>
#include <string>
#include <stdlib.h>

using mainmenuwindow::MainMenuWindow;

MainMenuWindow::MainMenuWindow() {

}

int 
MainMenuWindow::assessSelectedOption(char const *selectedOption) {
    char const *options[] = {
        "Create Game",
        "Enter Game",
        "Help",
        "About",
        "Exit"
    };
    if(strncmp(selectedOption, "Create Game", 4) == 0) {
        return 1;
    }
    if(strncmp(selectedOption, "Enter Game", 4) == 0) {
        return 2;
    }
    if(strncmp(selectedOption, "Help", 4) == 0) {
        return 3;
    }
    if(strncmp(selectedOption, "About", 4) == 0) {
        return 4;
    }
    return 5;
}

int 
MainMenuWindow::pageDisplay(char const welcomeTitle[], char const *options[], int numberOfOptions)
{
    int i;

    int commandLineWidth, commandLineLength; //stores command line window's width and length

    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);

    if (has_colors() == false) {
    	endwin();
        printf("Your terminal does not support color\n");
        return 1;
    }


    // centers text based on current command line size
    getmaxyx(stdscr, commandLineWidth, commandLineLength);
    move(commandLineWidth/2, (commandLineLength-strlen(welcomeTitle))/2); // center welcome title

    printw(welcomeTitle);

    refresh(); // need to refresh, else it won't display
    WINDOW * menuwin=newwin(7, commandLineLength-12, commandLineWidth-9, 6); // define and create a window
    box(menuwin, 0, 0);
    refresh(); //refresh again so window appears
    wrefresh(menuwin); // let the window refresh itself
    keypad(menuwin, TRUE); // have the keyboard work in the window

    
    int keyPressed;
    int highlightedItem = 0;
    int selectedOption = 0;

    // all this loop is used to constantly create a menu with the highlight of the selected item
    while(1)
    {
        for(i = 0; i < numberOfOptions; i++) {
            if(i == highlightedItem)
                wattron(menuwin, A_REVERSE);
            mvwprintw(menuwin, i+1, 1, options[i]);
            if (i == highlightedItem)
                wattroff(menuwin, A_REVERSE);
        }

        keyPressed = wgetch(menuwin);
        switch(keyPressed)
        {
        case KEY_UP:
            highlightedItem--;
            if(highlightedItem < 0) highlightedItem = 0; // protection against leaving the menu box
            break;
        case KEY_DOWN:
            highlightedItem++;
            if(highlightedItem > 4) highlightedItem = 4;
            break;
        default:
            break;
        }

        // Enter key pressed
        if(keyPressed == 10) { 
            selectedOption = assessSelectedOption(options[highlightedItem]); 
            break;
        }
    }

    return selectedOption;
}

int 
MainMenuWindow::displayMainMenu(int argc, char **argv) {
    // Command line argument currently unused. Use in future to get uploaded JSON
    char const *options[] = {
        "Create Game",
        "Enter Game",
        "Help",
        "About",
        "Exit"
    };

    char const *options2[] = {
        "Back"
    };

    // perhaps use these variables in the future if we get json file from command line
    (void) argc;
    (void) argv;

    while (1) {
        clear();
        int returnValue = pageDisplay("WELCOME TO TEAM CHORIPAN'S GAME SERVER", options, 5);
        if (returnValue == 1) {
            clear();
            pageDisplay("Feature coming soon...", options2, 1);
        }
        if (returnValue == 2) {
            clear();
            pageDisplay("Feature coming soon...", options2, 1);
        }
        if (returnValue == 3) {
            clear();
            pageDisplay("Upload a JSON to create a game or join a game!", options2, 1);
        }
        if (returnValue == 4) {
            clear();
            pageDisplay("Created by: Avneet, Raman, Jack, Phillip, Amrit, Harman", options2, 1);
        }
        if (returnValue == 5) {
            break;
        }
    }
    clear();
    printw("\nPress any key to exit.");
    refresh();
    getch();
    endwin();
}