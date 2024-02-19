# Text Speller Checker
## Description
This program is able to check spelling mistakes in text files, by loading dictionaries in hash tables and checking every word from the text file. The dictionaries provided by the program are small dictionaries that contain small words and big dictionaries containing over 140.000+ words. The preloaded file contains 28 different texts to provide you how the program able to work.

## How to running the program
1. First, compile the filter.c into filter
```
make speller
```
2. To run the filter, use this command in the terminal
```
./speller [DICTIONARY] text
```
Example :
```
./speller Speller/texts/lalaland.txt
```
This command specify to use the default dictionary and check the lalaland text file (La La Land script)
```
./speller Speller/dictionaries/large Speller/keys/birdman.txt
```
This command specify to use the large dictionary and check the birdman text file <br>

## Output
```
MISSPELLED WORDS

Chazelle
L
TECHNO
L
Thelonious
Prius
MIA
L
MIA
Mia
...
Mia
Mia
Sebastian's
L

WORDS MISSPELLED:     955
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        17756
TIME IN load:         0.02
TIME IN check:        1.06
TIME IN size:         0.00
TIME IN unload:       0.00
TIME IN TOTAL:        1.08
```
```
MISSPELLED WORDS


WORDS MISSPELLED:     0
WORDS IN DICTIONARY:  5
WORDS IN TEXT:        6
TIME IN load:         0.00
TIME IN check:        0.00
TIME IN size:         0.00
TIME IN unload:       0.00
TIME IN TOTAL:        0.00
```