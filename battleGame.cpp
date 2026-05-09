
#include <iostream>
using namespace std;
class Character
{
    string name;
    int hp;
    int attackPower;

public:
    Character(string n, int h, int a) : name(n), hp(h), attackPower(a) {};
    string getName() const
    {
        return name;
    }
    int getHP() const
    {
        return hp;
    }
    int getAttackPower() const
    {
        return attackPower;
    }
    void setHP(int h)
    {
        hp = h;
    }
    bool isAlive()
    {
        if (hp > 0)
        {
            return true;
        }
        return false;
    }
    virtual void attack(Character &target)
    {
        target.hp -= this->attackPower;
        cout << target.name << " hp reduced by " << attackPower << "\nRemainig hp: " << target.hp << endl;
    }
    virtual void showStat() const
    {
        cout << "Name: " << name << endl
             << "hp: " << hp << endl
             << "attack power: " << attackPower << endl;
    }
};
class Warrior : public Character
{
    int armor;

public:
    Warrior(string n, int h, int a, int ar) : Character(n, h, a), armor(ar) {};
    int getArmor() const
    {
        return armor;
    }
    void attack(Character &target)
    {
        double newPower;
        newPower = getAttackPower() + (getAttackPower() * 50 / 100);
        cout << "with 50% extra power damage done" << endl;
        double hpReduced = target.getHP() - newPower;
        target.setHP(hpReduced);
        if (target.getHP() > 0)
        {
            cout << "remaining hp: " << target.getHP() << endl;
        }
        else
        {
            cout << target.getName() << " died" << endl;
        }
    }
    void defend(int incomomingDamage)
    {
        if (incomomingDamage > 0 && incomomingDamage > armor)
        {
            double attack = incomomingDamage - armor;
            double newHP = getHP() - attack;
            setHP(newHP);
            cout << "damage reduced by armor to: " << attack << endl;
            if (getHP() > 0)
            {
                cout << "new hp: " << newHP << endl;
            }
            else
            {
                cout << "you died" << endl;
            }
        }
        else
        {
            cout << incomomingDamage << " blocked\n";
        }
    }
};
class Mage : public Character
{
    int mana;

public:
    Mage(string n, int h, int a, int m) : Character(n, h, a), mana(m) {};
    void attack(Character &target)
    {
        if (mana >= 20)
        {
            mana -= 20;
            double hpReduced = target.getHP() - (this->getAttackPower() * 2);
            target.setHP(hpReduced);
            if (hpReduced > 0)
            {
                cout << "remaining hp: " << target.getHP() << endl;
            }
            else
            {
                cout << target.getName() << " died" << endl;
            }
        }
        else
        {
            double hpReduced = target.getHP() - (this->getAttackPower() / 2);
            target.setHP(hpReduced);
            if (hpReduced > 0)
            {
                cout << "remaining hp: " << target.getHP() << endl;
            }
            else
            {
                cout << target.getName() << " died" << endl;
            }
        }
    }
    void showStat() const
    {
        Character::showStat();
        cout << "Mana: " << mana << endl;
    }
};
int main()
{
    Character *c1;
    Warrior warrior("Warrior", 100, 10, 5);
    c1 = &warrior;
    Character *c2;
    Mage mage("Mage", 100, 23, 100);
    c2 = &mage;
    int attacker;
    cout << "You have 2 chars:\n1.Warrior\t2.Mage\nWho you want to attack first: ";
    cin >> attacker;
    while (cin.fail() || (attacker != 1 && attacker != 2))
    {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "invalid input!Enter again: ";
        cin >> attacker;
    }
    int countRounds = 0;
    do
    {
        if (attacker == 1)
        {
            warrior.attack(*c2);
            attacker = 2;
        }
        else
        {
            warrior.defend(c2->getAttackPower());
            attacker = 1;

            attacker = 1;
        }
        countRounds++;
        if (!warrior.isAlive())
        {
            cout << "mage is winner\n";
            break;
        }
        else if (!mage.isAlive())
        {
            cout << "warrior is winner\n";
            break;
        }
        cout << "After " << countRounds << " round:\n";
        warrior.showStat();
        mage.showStat();
    } while (c1->isAlive() == true && c2->isAlive() == true);

    return 0;
}