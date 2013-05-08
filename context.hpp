#ifndef CONTEXT_HPP
#define CONTEXT_HPP

class Context {
    public:
        Context();
        ~Context();
        sf::RenderWindow& getApp() { return _mainWindow;};

    private:
        sf::RenderWindow _mainWindow;
};

#endif
