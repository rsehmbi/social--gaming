#ifndef MAINMENUWINDOW_H
#define MAINMENUWINDOW_H

namespace mainmenuwindow {

    class MainMenuWindow {
        public:
            MainMenuWindow();
            int displayMainMenu(int argc, char **argv);
            int assessSelectedOption(char const *selectedOption);
            int pageDisplay(char const welcomeTitle[], char const *options[], int numberOfOptions);

    };
}

#endif