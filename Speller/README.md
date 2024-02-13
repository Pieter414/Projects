# Text Speller Checker
## Description
This program is able to 'filter' images, by changing RBG (Red, Blue, Green) data in file images and using an algorithm to essentially recolor the image as a filter. There are five types of filters that the program is able to run. Grayscale, to turn images black and white. Sepia, to turn images like old photos yellowish color. Rotate, to rotate the image horizontally. Blur, to blur the image. And lastly, Edges to identify the edge in the picture. 

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