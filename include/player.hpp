#include <stack>
#include <set>
#include <random>
#include <memory>
#include <list>
#include <chrono>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "deck.hpp"
#include "colour.hpp"

class Player: public sf::Drawable
{
    public:

    private: //do zmienienia prywatnosc

    Colour colour;
    std::shared_ptr<Deck> my_deck;
    std::shared_ptr<Deck> trash;

    public:

    Player() = delete; 
    Player(Colour); //inicjuje i tasuje talie graczy

    //gettery potrzebne do Game::player_move()
    std::shared_ptr<Deck> get_deck_pointer() const; //zwraca wskaźnik do talii
    std::shared_ptr<Deck> get_trash_pointer() const; //zwraca wskaźnik do kosza

    Card peek_trash_top() const; //zwraca karte zwierzchu kosza
    Card peek_deck_top() const; //zwraca karte zwierzchu tali

    Card draw_trash(); //zwraca karte zwierzchu kosza i uzuwa z niego
    Card draw_deck(); //zwraca karte zwierzchu tali i uzuwa z niej

    void push_trash(Card&&); //dodaje karte do kosza

    void take_trash_and_rotate(); //obsługa pustego decku
    void empty_trash_handle();//obsługa pustego trasha //obróć raz weź karte z góry do kosza i potem znowu obróć

    static void load_texuture();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override; //ta funkcja ju nie jest wirtualna ale musimy ja nadpisac

};