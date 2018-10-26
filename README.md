# cs3250 #
This is a private repository to collaborate on a CS3250 Programming in C++ Semester-long project with Gibson, George, David, &amp; Emma.

## Concrete Rules ##

### Pre-Game: ###
Choose the number of players, 2-5. Choose your map. Take turns drafting 1 army
to an unowned territory round-robin style. Only after all territories are owned,
can you place more armies on an already owned territory (starting number of
armies per player TBD). 

### On Your Turn: ###
Draft the amount of armies you draft are your territory values divided by 
3 if your territory values are greater than 12, else your reinforcements
are set to 3. Place your armies on any territories you currently own.

### Attack Phase: ###
If you have at least 2 armies on a territory and that territory
neighbors a territory owned by another player, you may attack it. Input the
number of armies you want to attack with up to 5. The defender rolls with the
amount of armies he or she has on the defending territory up to 3. The attacker
drops the 2 lowest dice rolls and ties go to the defender. Once an attacker has
defeated all armies on the defending territory he or she must advance up to the
amount of armies on the attacking territory - 1 (at least 1 army must be left on
the attacking territory. The current player may attack as many times as he or
she legally can or can end his or her turn prematurely.

### Reinforcement Phase: ###
After the attack phase, the current player has an option to
reinforce an owned territory. This player may move the number of armies - 1 on
any one territory to another owned territory as long as there exists a path of
allied territories between the two.

### Misc Details: ###
Most territories contribute 1 to your owned territory count for
drafting armies on the beginning of your turn with the exception of certain
specific territories contributing more than 1. These territories will have bold
borders.

No one territory can sustain over 20 armies. If you have no options for
placement because all of your territories have the maximum number of armies on
them, those reserve armies are forfeit.

### End Of Game: ###
The game ends at the end of a players attack phase if no other
players control territories. That player has conquered the board.
