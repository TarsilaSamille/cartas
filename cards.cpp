/*
 * Exercicio:
 * 
 * 1) Ler cartas da entrada padrão.
 * 2) Implementar alg. find_if()
 * 3) Implementar alg. filter()
 * 4) Aplicar nas situações:
 *      4A) Usar find_if para: Achar a primeira carta cujo valor da face seja uma figura (valete, dama, rei).
 *      4B) Usar find_if para: Achar a primeira carta que seja vermelha.
 *      4C) Usar filter para: Selecioar em um vetor apenas as cartas de "hearts"
 *      4C) Usar filter para: Selecioar apenas as cartas com figuras.
 */

#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Card {
    enum class suit : int
    {
        clubs    = 0,
        diamonds = 1,
        hearts   = 2,
        spades   = 3,
    };

    suit s;
    unsigned short r; // rank
};

std::ostream& operator<<( std::ostream& os, const Card & c )
{
    std::string ranks_to_str[]{"as", "2", "3", "4", "5", "6", "7", "8", "9", "10", "jack", "queen", "king", "joker"};
    std::string suits_to_str[]{ "clubs", "diamonds", "hearts", "spades" };
    os << ranks_to_str[c.r];
    if ( c.r < 13 ) os << " of " << suits_to_str[static_cast<int>(c.s)];

    return os;
}

bool is_figure (const Card &c){
    if (c.r >= 11 and c.r <= 13)
        return true;
    return false;
}

Card * find_if ( Card *first, Card *last, bool (*pred)(const Card &) ){
    while (first != last){
        if (pred(*first))
        return first;
        first++;
    }
    return last;
}

int main(void)
{
    Card hand[] { {Card::suit::clubs, 2},
                  {Card::suit::hearts, 8},
                  {Card::suit::spades, 11} };


    Card c1{Card::suit::spades, 11}, c2{Card::suit::diamonds, 10};

    Card ct;

    string line;
    ifstream myfile ("input.txt");
    vector<string> cartaString;
    vector<Card> cartas;
    int x=0;

    if (myfile.is_open()){
        while ( getline (myfile,line) ){
            cartaString.push_back(line);
            x++;
        }
        myfile.close();
    }

    for ( const auto& e : cartaString )
    {
        char x1 = e[2];
        char x2 = e[3];
        int y = x2 == 0 ? (x1 - '0') : (x1 - '0')*10 +  (x2 - '0');
        ct.r = y;
        switch(e[0]){
            case '0'  :  ct.s = Card::suit::clubs;   break;
            case '1'  :  ct.s = Card::suit::diamonds;  break;
            case '2'  :  ct.s = Card::suit::hearts;  break;
            case '3'  :  ct.s = Card::suit::spades;  break;
        }
        cartas.push_back(ct);
    }
    for ( const auto& e : cartas )
    {
        std::cout << e << ", ";
    }

    Card * result = find_if( hand, hand+3, is_figure);
    std::cout << *result <<std::endl;

    return 0;
}
