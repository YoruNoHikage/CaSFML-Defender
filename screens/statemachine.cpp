#include "../config.hpp"
#include "statemachine.hpp"

/** \brief ctor
 */
StateMachine::StateMachine()
{
}

/** \brief dtor
 */
StateMachine::~StateMachine()
{
    for(std::map<std::string, IState*>::iterator itr = _states.begin() ; itr != _states.end() ; ++itr)
        delete itr->second;
    _states.clear();
}

/** \brief Update the current state
 *
 * \param elapsedTime sf::Time
 * \return void
 *
 */
void StateMachine::update(sf::Time elapsedTime)
{
    _currentState->update(elapsedTime);
}


/** \brief Display the current state's content
 *
 * \param app sf::RenderWindow&
 * \return void
 *
 */
void StateMachine::draw(sf::RenderWindow& app)
{
    _currentState->draw(app);
}

/** \brief Change the current state into another one
 *
 * \param name std::string
 * \return void
 *
 */
void StateMachine::change(std::string name)
{
    if(_states[name] != NULL)
    {
        _currentState->onExit();
        _currentState = _states[name];
        _currentState->onEnter();
    }
}

/** \brief Add a state, the state machine is able to switch on it
 *
 * \param name std::string
 * \param state IState&
 * \return void
 *
 */
void StateMachine::add(std::string name, IState& state)
{
    _states.insert(std::pair<std::string, IState*>(name, &state));
}
