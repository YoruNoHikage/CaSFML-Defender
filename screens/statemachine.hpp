#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

class IState
{
    public:
        virtual void update(sf::Time elapsedTime) = 0;
        virtual void draw(sf::RenderWindow& app) = 0;
        virtual void onEnter() = 0;
        virtual void onExit() = 0;
};

class StateMachine
{
    public:
        StateMachine();
        ~StateMachine();

        // game loop logic
        void update(sf::Time elapsedTime);
        void draw(sf::RenderWindow& app);

        // state machine logic
        void change(std::string name);
        void add(std::string name, IState& state);

    private:
        std::map<std::string, IState*> _states;
        IState* _currentState;
};

#endif // STATEMACHINE_HPP
