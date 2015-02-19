# MagicRealm
COMP3004 Term Project

##Rule Book
[2nd edition](http://people.scs.carleton.ca/~jeanpier//304W15/magic%20realm/magicRealm2ed.pdf)

###[Map for Iteration 1](http://i.imgur.com/TiyIbIQ.jpg)
the buildings have been labeled for better clarity than the original

##Characters that we must support
* Captain
 * AIM
 * REPUTATION
 * start at INN, HOUSE, GUARD house
 * starting equipment
    * Short Sword
    * Helmet
    * Breastplate
    * Shield
* Swordsman
 * BARTER
 * CLEVER
 * must start at INN
 * starting equipment
    * Thrusting sword
* Amazon
 * AIM
 * STAMINA
 * must start at INN
 * starting equipment
    * Short Sword
    * Helmet
    * Breastplate
    * Shield
* Dwarf
 * SHORT LEGS
 * CAVE KNOWLEDGE
 *  start at INN, GUARD house
 * starting equipment
    * Great Axe
    * Helmet
* Elf
 * ELUSIVENESS
 * ARCHER
 * must start at the INN
 * starting equipment
    * Light Bow
    * two spells, (type 3 and/or 4)
* Black Knight
 * AIM
 * FEAR
 * must start at the INN
 * starting equipment
    * Mace
    * Suit of Armor
    * Shield

##Day Breakdown
1. Birdsong: all players determine their moves for the day, each player has a limited number of action per day (see Phases)
2. Sunrise: one die is rolled to determine what monsters are prowling
3. Daylight: players take their turns in a random order (should not be the same day to day)
4. Sunset: all clearing that contain a player "place" an ATTENTION chit in a "pile"
5. Evening: ATTENTION chits are randomly selected, Characters in the selected clearing are able to rearrange belongings and trade with other players
6. Midnight: all face up Map chits are returned to their positions and turned face down


##Victory Points
* assign 0-5 points for each of the following categories
   * Great Treasures
      * multiply by 1
   * Spells
      * multiply by 2
   * Fame
      * multiply by 10
   * Notoriety
      * multiply by 20
   * Gold
      * multiply by 30
* belongings contribute to wards Fame and Notoriety, and must be owned at games end to count
* Gold 

##Communication for 1 day
1. Server calculates how many actions each player has and lets the clients know
2. Clients plan their moves using the activity numbers allotted
3. Clients send their plans, 
4. server waits for all then runs the day.
5. Server sends out updates after each action stating what happened

Hooray! a Readme file.
