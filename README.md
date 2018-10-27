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
If you have at least 2 armies on a territory and that territory neighbors 
a territory owned by another player, you may attack it. Attacks are the sum 
of a number generated with the range \[armies, (armies - 1) * 6) vs the defenders 
number generated with the range (armies, armies * 6). If the attacker succeeds, 
he or she must move at least 1 army and up to (armies on attacking territory - 1),
at least 1 army must be left on the attacking territory. The current player may 
attack as many times as he or she legally can or can end his or her turn prematurely.

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
