#include <iostream>
#include <cstdlib>
using namespace std;

const int POTION = 3;

int enemyChoice(int ptnCount){
    
    srand(time(NULL));
    int enemyAction = (rand() % 4) + 1;
    
    if (ptnCount == 0 && enemyAction == 3){
        enemyAction = 1;
    }
    
    return enemyAction;
}


int userChoice(){
    
    cout << endl << "Its your turn. Enter 1 to attack, 2 to block next incoming attack, 3 to heal, 4 to charge up your attack(each turn you charge up stacks up damage)." << endl;
    int userAction;
    cin >> userAction;
    
    while(userAction < 1 || userAction > 4){
        
        cout << "Your choice must be between 1-4. Choose again.";
        cin >> userAction;
    }
    
    return userAction;
}

string speedCheck(int userSpd, int enemySpd){
    
    string fasterChar;
    
    if (userSpd > enemySpd){
        cout << "You are faster than the enenmy. You will be moving first." << endl;
        fasterChar = "user";
    }
    else {
        cout << "You are slower than the enenmy. They will be moving first." << endl;
        fasterChar = "enemy";
    }
    
    return fasterChar;
}

void userCombatAction(int &userAttk, float &userHp, bool &userBlck, int &ptnCount, int &userChrge, float &enemyHp, bool &enemyBlck, int &userAct){
    
    if (userAct == 1){
        
        if (enemyBlck == 0){
            
            enemyHp -= userAttk;
            cout << "You have hit the enemy for " << userAttk << ". Their health is now " << enemyHp << "." << endl;
        }
        else {
            
            cout << "The enemy has blocked your attack" << endl;
            enemyBlck = false;
        }
    }
    else if (userAct == 2){
        
        cout << "You have raised your sheild and are prepared to block the next attack." << endl;
        userBlck = true;
    }
    else if (userAct == 3){
        
        if (ptnCount > 0){
            
            cout << "You have drank a potion and have healed for 3 hp. You are now at " << userHp << "." << endl;
            userHp += POTION;
            cout << "You have " << ptnCount << " potions left." << endl;
            ptnCount--;
        }
        else {
            
            cout << "You have no potions left. You wasted your time rummeging in your bag for a potion." << endl;
        }
    }
    else{
        
        cout << "You are charging up a heavy attack." << endl;
        userChrge ++;
    }
}

void enemyCombatAction(int &enemyAttk, float &enemyHp, bool &enemyBlck, int &ptnCount, int &enemyChrge, float &userHp, bool &userBlck, int &enemyAct){
    
    if (enemyAct == 1){
        
        if (userBlck == 0){
            
            userHp -= enemyAttk;
            cout << "The enemy hit you for " << enemyAttk << ". Your health is now " << userHp << "." << endl;
        }
        else {
            
            cout << "You blocked the enemy attack" << endl;
            userBlck = false;
        }
    }
    else if (enemyAct == 2){
        
        cout << "The enemy has raised their sheild and are prepared to block your next attack." << endl;
        enemyBlck = true;
    }
    else if (enemyAct == 3){
        
        enemyHp += POTION;
        cout << "The enemy has drank a potion." << endl;
        ptnCount--;
    }
    else if (enemyAct == 4){
        
        cout << "The enemy is charging up a heavy attack." << endl;
        enemyChrge++;
    }
    else {
        
        cout << "The enemy has raised their sheild and are prepared to block your next attack." << endl;
        enemyChrge++;
    }
}


int main()
{
    
    int userAttack = 5;
    float userHealth = 30;
    int userSpeed = 10;
    bool userBlock = false;
    int userCharge = 1;
    int userPotionCount = 3;
    
    int enemyAttack = 3;
    float enemyHealth = 35;
    int enemySpeed = 8;
    bool enemyBlock = false;
    int enemyCharge = 1;
    int enemyPotionCount = 3;
    
    int userAction;
    int enemyAction;
    string fasterCharacter;
    
    cout << "Prepare for a fight. Know that the enemy may faint raising their sheild then charge their attack instead. Don't fall for it!" << endl;
    
    int turnCount = 0;
    while (userHealth > 0 && enemyHealth > 0){
        
        if (turnCount == 0){
            fasterCharacter = speedCheck(userSpeed, enemySpeed);
        }
        
        enemyAction = enemyChoice(enemyPotionCount);
        userAction = userChoice();
        
        if (fasterCharacter == "enemy"){
            
            enemyCombatAction(enemyAttack, enemyHealth, enemyBlock, enemyPotionCount, enemyCharge, userHealth, userBlock, enemyAction);
            userCombatAction(userAttack, userHealth, userBlock, userPotionCount, userCharge, enemyHealth, enemyBlock, userAction);
        }
        else {
            
            userCombatAction(userAttack, userHealth, userBlock, userPotionCount, userCharge, enemyHealth, enemyBlock, userAction);
            enemyCombatAction(enemyAttack, enemyHealth, enemyBlock, enemyPotionCount, enemyCharge, userHealth, userBlock, enemyAction);
        }
        
        turnCount++;
    }
    
    if (userHealth < 1){
        
        cout << "You have died in battle. You'll get them next time!";
    }
    else {
        
        cout << "You've won in a battle of arms. Well fought!";
    }

    return 0;
}
