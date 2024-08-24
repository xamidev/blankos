// Pseudo-random word generation program
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#include "../libc/stdio.h"
#include "../libc/crypto.h"
#include "../kernel/system.h"

char* words[] =
{
	"I", "us", "they", "my",
	"a", "an", "is", "are", "for", "while", "not", "none", "yes", "no",
	"absolutely", "addition", "additive", "afternoon", "architect", "ask",
	"be", "blindfold", "brilliant", "boy", "brilliant", "bring", "buddy",
	"career", "caterpillar", "change", "cheeky", "chop",
	"decide", "demonstrate", "draw", "druggist",
	"eagle", "ear", "effort", "evening", 
	"fabric", "famous", "fuse",
	"generation", "generous", "girl", "gypsy", "grip",
	"habit", "handsome", "helmet", "help", "horror",
	"insist", "inventor", "itself", "ivory",
	"jog", "joint", "joke", "judge", 
	"karate", "kebab", "kitchen",
	"lamb", "lawnmower", "left", "lock",
	"math", "medicine", "most",
	"noodles", "nowadays", "nowhere",
	"ocean", "older", "ounce",
	"part", "pathetic", "pastime",
	"quite", "quits", "quotation",
	"race", "raise", "reality",
	"safe", "scare", "screen",
	"taught", "temple", "that", "this",
	"unable", "unkind", "usual",
	"velvet", "vivid", "vote",
	"we", "warm", "watch",
	"xylophone",
	"yolk", "young", "your",
	"zebra", "zodiac", "zucchini",
};

int words_size = sizeof(words)/sizeof(words[0]);

// Generates random words
void program_words()
{
	for (int i=0; i<10; i++)
	{
		int random = randint(global_ticks);
		char* word = words[random%words_size];
		//printf("Global ticks: %d\nRandom integer: %d\nWord: %s\n", global_ticks, random, word);
		printf("%s ", word);
		delay(10);
	}
	puts("\n");
}
