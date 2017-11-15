//
//  Player.hpp
//  GameFirstDraft
//
//  Created by Joshua Seelye on 11/13/17.
//  Copyright © 2017 Josh Seelye. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include "Combatant.hpp"
#include "Inventory.hpp"

class Player : public Combatant
{
//private instance variables
private:
    Inventory inv;
    int level;

//public Functions
public:
    //basic singleton character creation
    void create()
    {
        std::string check = "";
        do
        {
            inv = Inventory();
            level = 1;
            hp  = 10;
            str = 1;
            def = 0;
            lck = 0;
            spd = 0;
            pp  = 5;
            gold = 0;
            exp = 0;
            std::cout << "Please enter your name: ";
            std::cin  >> Entity::_name;
            string x = "";
            std::cout << "Type 10 for info on skills" << std::endl;
            
            for(int i = 10; i != 0; i--)
            {
                std::cout << "Type number to increase:     1    2    3    4    5    6" << std::endl;
                std::cout << "Possible skills to increase: Hp   PP   Str  Def  Lck  Spd"<< std::endl;
                std::cout << "Current Stats:               " <<hp<<std::setw(4)<<pp<<std::setw(5)<<str<<std::setw(5)<<def<<std::setw(5)<<lck<<std::setw(5)<<spd<<std::endl;
                std::cout << "Remaining Points: " << i << std::endl;
                std::cin >> x;
                if(x == "1")
                {
                    hp+=5;
                }
                else if(x == "2")
                {
                    pp+=2;
                }
                else if(x == "3")
                {
                    str++;
                }
                else if(x == "4")
                {
                    def++;
                }
                else if(x == "5")
                {
                    lck++;
                }
                else if(x == "6")
                {
                    spd++;
                }
                else if(x == "10")
                {
                    std::cout << "Hp or Health is way to see how close you are to death" << std::endl << "Str or Strength is how you show yourself in combat" << std::endl << "Def or Defense shows how well you can defend yourself." << std::endl << "Lck or Luck is how lucky you are in certain situtations." << std::endl << "Spd or Speed is how fast you are to react in situations." << std::endl << "PP or PowerPoints is the cost per swing in combat" << std::endl;
                    i++;
                }
                else
                {
                    std::cout << std::endl << "Invalid Input" << std::endl << std::endl;
                    i++;
                }
            }
            std::cout << std::endl << std::endl << "Final Stats" << std::endl;
            std::cout << "Hp:       " << hp << std::endl;
            std::cout << "PP:       " << pp << std::endl;
            std::cout << "Strength: " << str << std::endl;
            std::cout << "Defense:  " << def << std::endl;
            std::cout << "Luck:     " << lck << std::endl;
            std::cout << "Speed:    " << spd << std::endl;
            std::cout << "Restart Build? [Yes] [No]" << std::endl;
            std::cin >> check;
        }while(check == "y" || check == "yes" || check == "Y" || check == "Yes");
    }
    
    void getStats()
    {
        std::cout << "Current Stats" << std::endl;
        std::cout << "Level:    " << level << std::endl;
        std::cout << "Exp lvl:  " << exp << "/" <<  nextLevel() << std::endl;
        std::cout << "Hp:       " << hp << std::endl;
        std::cout << "PP:       " << pp << std::endl;
        std::cout << "Strength: " << str << std::endl;
        std::cout << "Defense:  " << def << std::endl;
        std::cout << "Luck:     " << lck << std::endl;
        std::cout << "Speed:    " << spd << std::endl;
    }
    
    void increaseExp(int x)
    {
        exp+=x;
        if(exp>=nextLevel())
        {
            levelUp();
        }
    }
    
//private functions
private:
    int nextLevel()
    {
        return (int)round(sqrt((double)(20*level)));
    }
    
    void levelUp()
    {
        
    }
    
    
    
    
    
    
    
    
    
//singleton design pattern for player class
private:
    Player(){}
public:
    Player(Player const&)          = delete;
    void operator=(Player const&)  = delete;
    
    static Player& get()
    {
        static Player   instance;
        return          instance;
    }
};

#endif /* Player_h */
