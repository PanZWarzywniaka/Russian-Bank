#include"card.hpp"

sf::Image Card::card_sheet = sf::Image();
sf::Vector2f Card::original_single_card_size = sf::Vector2f();
sf::Vector2f Card::actual_single_card_size = sf::Vector2f();

Card::Card(Value wart, Colour kol) // za każdym razem
{
    wartosc = wart;
    kolor = kol;
    
    const sf::Vector2i rect_positon = sf::Vector2i{original_single_card_size.x*static_cast<int>(wartosc),original_single_card_size.y*static_cast<int>(kolor)}; //zwróci {0,0} dla asa kier
    card_texture.loadFromImage(Card::card_sheet,sf::IntRect(rect_positon,static_cast<sf::Vector2i>(original_single_card_size)));
    card_sprite.setTexture(card_texture); //card sprite nie przechowuje tekstury tylko trzyma do niej wskaźnik, card_sheet nie powinno być kopiowane
 

    //skalowanie dla skali Game::scale = 1, rozmiar karty y=150

    card_sprite.setScale(actual_single_card_size.x/original_single_card_size.x,actual_single_card_size.y/original_single_card_size.y); // skala dla x i y taka sama 0.07666

    card_texture.setSmooth(true);
}


void Card::load_texuture() //wykona się raz dla całej klasy przed utworzeniem obietów
{
    card_sheet.loadFromFile("resources/card_sheet.png");

    Card::original_single_card_size = static_cast<sf::Vector2f>(card_sheet.getSize());
    Card::original_single_card_size.x /=13; //dzielimy rozmiar przez 13 bo tyle jest kart w rzędzie
    Card::original_single_card_size.y /= 4; //4 kart w kolumnie

    Card::actual_single_card_size = sf::Vector2f(150*(original_single_card_size.x/original_single_card_size.y),150); //x/y ratio
}




Card::Card(const Card& karta)
{
    this->wartosc=karta.wartosc;
    this->kolor=karta.kolor;
    this->card_sprite=karta.card_sprite;
    this->card_texture=karta.card_texture;
    this->card_sprite.setTexture(this->card_texture);
}

Card::Card(Card&& karta)
{
    wartosc = std::move(karta.wartosc);
    kolor = std::move(karta.kolor);
    card_sprite = std::move(karta.card_sprite);
    card_texture = std::move(karta.card_texture);
    card_sprite.setTexture(card_texture);
}


Card::Colour Card::get_colour() const
{
    return kolor;
}


Card::Value Card::get_value() const
{
    return wartosc;
}

bool Card::operator<(const Card& cx) const
{
    if(this->kolor==cx.kolor) 
    {
        return this->wartosc<cx.wartosc;
    }
    else return this->kolor<cx.kolor;
}

bool Card::operator==(const Card& card) const
{
    if(this->kolor==card.kolor&&this->wartosc==card.wartosc) return true;
        else return false;        
}

bool Card::is_black() const
{
    if(this->kolor==Card::Colour::spades || this->kolor==Card::Colour::clubs)
        return true;
    else
        return false;
}


void Card::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(card_sprite,states);
}

void Card::setPosition(float x, float y)
{
    this-> x = x;
    this-> y = y;
    card_sprite.setPosition(x,y);
}

std::ostream &operator<<(std::ostream& strumien,const Card& karta)
{
    auto pisz = [&](const char* a){
        strumien<<a<<' ';
    };

    switch (karta.get_colour())
    {
        case Card::Colour::spades:
            {
                pisz("pik");    
            }
            break;
        case Card::Colour::clubs:
            {
                pisz("trefl");    
            }
            break;
        case Card::Colour::hearths:
            {
                pisz("kier");    
            }
            break;
        case Card::Colour::dimonds:
            {
                pisz("karo");    
            }
            break;
        default:
            pisz("Halo coś coś się popsuło i nie było mnie słychać");
            break;
    }

    switch (karta.get_value())
    {
        case Card::Value::_2:
            pisz("2");
            break;
        case Card::Value::_3:
            pisz("3");
            break;
        case Card::Value::_4:
            pisz("4");
            break;
        case Card::Value::_5:
            pisz("5");
            break;
        case Card::Value::_6:
            pisz("6");
            break;
        case Card::Value::_7:
            pisz("7");
            break;
        case Card::Value::_8:
            pisz("8");
            break;
        case Card::Value::_9:
            pisz("9");
            break;
        case Card::Value::_10:
            pisz("10");
            break;
        case Card::Value::J:
            pisz("J");
            break;
        case Card::Value::Q:
            pisz("Q");
            break;
        case Card::Value::K:
            pisz("K");
            break;
        case Card::Value::Ace:
            pisz("As");
            break;
        default:
            pisz("Error");
            break;
    }

    return strumien;
}