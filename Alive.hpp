#ifndef ALIVE_HPP
#define ALIVE_HPP

class Alive
{
    public:
        Alive() : _life(0) {};
        virtual ~Alive() {};

        void receiveDamages(const int damages)
        {
            _life -= damages;
            if(_life <= 0)
                _life = 0;
        };

        int getLife() { return _life; };
        bool isAlive() { return _life > 0; };

    protected:
        void setLife(const int life)
        {
            if(_life < 0)
                _life = 0;
            else
                _life = life;
        };

    private:
        int _life;
};


#endif // ALIVE_HPP
