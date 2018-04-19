# OOP-Project

Project: Spell B

General Idea:
A game which is similar to spelling bee. It consists of two levels of different types where the user needs to input correct spelling to advance and collect points. 
Level 1: An audio file of the word to be spelled is played and the user is asked to input the correct answer. This level is not timed. The user has few options: 
1.	The audio file can be replayed maximum 3 times. 
2.	The user can ask for the word’s meaning and part of speech.
3.	The user can ask for the word to be used in a sentence. 
Level 2: The game generates a jumble of letters and the user enters the correct spelling of the word using all the letters from the jumble. This level is timed. 

Rules: 
The user cannot exit the game during a session. If they do then all progress is lost. The user needs to finish a level in one go. 
The first level is not timed but the second level is. 
The score level is determined by a bee hive. Every level is a separate bee hive. A correct word gives out a hexagon which makes up the hive. 
In the first level if you make a mistake you move on to the next word that is equivalent to restarting the level.
If you cannot complete the bee hive of one level then you have to replay the level from the beginning.
In level 1 the user needs to spell out 20 words correctly in one go to advance to the next level.
In level 2 the user needs to spell out 10 words in one go to advance to the next level. If you run out of time then you need to restart the level. That also goes for an incorrect spelling entered. You have to start the level again. 
In level 2 we will allow different permutations of the same jumbled letter. For example, “otps” can be “spot” or “tops” or “pots”. All are correct answers. 

Things to implement while development:
1.	In the first level, all the audio files are played in shuffle. 
2.	We keep a database of 200 audio files with its corresponding meanings, parts of speech and use in a sentence saved in a .txt file.
3.	In the second level we save 50 word jumbles and for each jumble we save every correct permutation of the jumble.  
4.	Before every level the rules and regulations for that level needs to be generated.
5.	There needs to be a give up option for the user to exit the game mid-level.
