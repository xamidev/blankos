// Pseudo-random word generation program
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#include "../libc/stdio.h"
#include "../libc/crypto.h"
#include "../kernel/system.h"
#include "../libc/string.h"

// Small dictionary

char* words[] =
{
	// A
	"I", "us", "they", "my",
	"a", "an", "is", "are", "for", "while", "not", "none", "yes", "no",
	"absolutely", "addition", "additive", "afternoon", "architect", "ask",
	"ability", "above", "absence", "academy", "account", "achieve", "acquire",
	"adapt", "admit", "adventure", "affection", "agenda", "agreement", "airport",
	"alert", "alibi", "alive", "allow", "almond", "alphabet", "always",

	// B
	"be", "blindfold", "brilliant", "boy", "bring", "buddy",
	"balance", "bamboo", "band", "banjo", "bank", "banner", "barrel",
	"basic", "battery", "beach", "beacon", "beard", "behavior", "believe",
	"belt", "benefit", "berry", "bicycle", "bingo", "biology", "birthday",
	"biscuit", "bitter", "blanket", "blizzard", "blossom", "blueprint", "board",

	// C
	"career", "caterpillar", "change", "cheeky", "chop",
	"cabin", "cactus", "camera", "candle", "candy", "canoe", "canvas",
	"capital", "captain", "caravan", "carbon", "carpet", "cartoon", "castle",
	"casual", "catalog", "catch", "category", "celebrate", "ceremony", "certain",
	"chain", "chair", "chamber", "charge", "charity", "cheese", "chef",

	// D
	"decide", "demonstrate", "draw", "druggist",
	"daisy", "dance", "danger", "daring", "database", "debate", "decade",
	"decline", "decorate", "decrease", "dedicate", "defeat", "defend", "define",
	"degree", "delight", "delivery", "demand", "dentist", "deny", "depart",
	"depth", "describe", "deserve", "desire", "destroy", "develop", "device",

	// E
	"eagle", "ear", "effort", "evening",
	"early", "earn", "earth", "ease", "east", "easy", "echo",
	"eclipse", "economy", "edge", "edit", "educate", "effect", "effort",
	"egg", "eight", "either", "elder", "elect", "elegant", "element",
	"elephant", "elevator", "elite", "embark", "embrace", "emerge", "emotion",

	// F
	"fabric", "famous", "fuse",
	"face", "factor", "fail", "fair", "fall", "false", "fame",
	"family", "fancy", "fantasy", "farewell", "farm", "fashion", "fast",
	"fault", "favor", "feather", "feature", "federal", "feedback", "feeling",
	"female", "fence", "festival", "fever", "fiber", "fiction", "field",

	// G
	"generation", "generous", "girl", "gypsy", "grip",
	"gallery", "game", "garage", "garden", "garlic", "gas", "gate",
	"gather", "general", "genius", "gentle", "genuine", "geography", "gesture",
	"ghost", "giant", "gift", "giggle", "ginger", "giraffe", "glance",
	"glass", "globe", "glory", "glove", "glue", "goal", "gold",

	// H
	"habit", "handsome", "helmet", "help", "horror",
	"hair", "half", "hammer", "hand", "handle", "hang", "happen",
	"harbor", "hard", "harm", "harvest", "hat", "hate", "have",
	"head", "health", "heart", "heat", "heaven", "heavy", "hedge",
	"height", "hello", "heritage", "hero", "hesitate", "hidden", "high",

	// I
	"insist", "inventor", "itself", "ivory",
	"ice", "idea", "ideal", "identify", "ignore", "ill", "image",
	"imagine", "impact", "import", "impress", "improve", "impulse", "inch",
	"include", "income", "increase", "index", "industry", "infant", "inform",
	"insect", "inside", "inspire", "install", "instead", "insult", "intact",

	// J
	"jog", "joint", "joke", "judge",
	"jacket", "jaguar", "jail", "jam", "january", "jar", "jazz",
	"jealous", "jeans", "jelly", "jewel", "job", "join", "journey",
	"joy", "judge", "juice", "jump", "jungle", "junior", "justice",
	"just", "justify", "juggle", "juice", "jumper", "junction", "jury",

	// K
	"karate", "kebab", "kitchen",
	"kangaroo", "keen", "keep", "kettle", "key", "keyboard", "kick",
	"kid", "kidney", "king", "kiss", "kite", "knee", "knife",
	"knit", "knock", "knot", "know", "knowledge", "koala", "kudos",
	"keen", "kernel", "kit", "kitten", "knack", "knight", "knock",

	// L
	"lamb", "lawnmower", "left", "lock",
	"label", "labor", "lace", "ladder", "lady", "lake", "lamp",
	"land", "language", "large", "laser", "last", "later", "laugh",
	"launch", "law", "layer", "lead", "leaf", "learn", "least",
	"leather", "leave", "lecture", "legal", "legend", "lemon", "length",

	// M
	"math", "medicine", "most",
	"machine", "magnet", "mail", "main", "major", "make", "male",
	"manage", "mango", "manner", "manual", "map", "marble", "march",
	"mark", "market", "marriage", "master", "match", "material", "matter",
	"maximum", "mayor", "meal", "mean", "measure", "media", "memory",

	// N
	"noodles", "nowadays", "nowhere",
	"nail", "name", "narrow", "nation", "native", "nature", "navy",
	"near", "neat", "necessary", "neck", "need", "negative", "neglect",
	"neither", "nerve", "nest", "net", "network", "neutral", "never",
	"new", "news", "next", "nice", "night", "noble", "noise",

	// O
	"ocean", "older", "ounce",
	"object", "observe", "obtain", "occasion", "occupy", "occur", "ocean",
	"offer", "office", "often", "oil", "old", "olive", "olympic",
	"omit", "once", "one", "onion", "online", "only", "open",
	"opera", "opinion", "oppose", "option", "orange", "orbit", "order",

	// P
	"part", "pathetic", "pastime",
	"pace", "package", "page", "pain", "paint", "pair", "palm",
	"panel", "panic", "paper", "parent", "park", "part", "party",
	"pass", "path", "patient", "pattern", "pause", "peace", "peak",
	"pen", "pencil", "people", "pepper", "perfect", "perform", "permit",

	// Q
	"quite", "quits", "quotation",
	"quality", "quantity", "quarter", "queen", "query", "quest", "quick",
	"quiet", "quilt", "quit", "quote", "quiz", "quota", "quiver",
	"quirky", "quaint", "quake", "qualification", "qualify", "quark", "quartz",
	"queue", "quench", "question", "quote", "quiver", "quorum", "quote",

	// R
	"race", "raise", "reality",
	"rabbit", "race", "radio", "rain", "raise", "random", "range",
	"rapid", "rare", "rate", "rather", "ratio", "reach", "react",
	"read", "ready", "real", "reason", "rebel", "recall", "receive",
	"recipe", "record", "recover", "reduce", "refer", "reflect", "reform",

	// S
	"safe", "scare", "screen",
	"sack", "sail", "salad", "salt", "same", "sample", "sand",
	"save", "scale", "scan", "scar", "scene", "school", "science",
	"score", "scratch", "scream", "screen", "script", "search", "season",
	"seat", "second", "secret", "section", "secure", "see", "seed",

	// T
	"taught", "temple", "that", "this",
	"table", "tackle", "tail", "take", "tale", "talent", "talk",
	"tank", "tape", "target", "task", "taste", "tax", "teach",
	"team", "tear", "technology", "telephone", "television", "temperature", "tend",
	"tennis", "tent", "term", "test", "text", "thank", "theory",

	// U
	"unable", "unkind", "usual",
	"umbrella", "unable", "uncle", "under", "undo", "unfair", "unfold",
	"union", "unique", "unit", "universe", "unknown", "unless", "unlike",
	"unlock", "until", "unusual", "update", "upgrade", "upon", "upper",
	"upset", "urban", "urge", "use", "usual", "utility", "utter",

	// V
	"velvet", "vivid", "vote",
	"vacuum", "valid", "valley", "value", "vampire", "van", "vase",
	"vast", "vault", "vector", "vehicle", "velvet", "vendor", "venture",
	"verb", "verify", "version", "vessel", "veteran", "veto", "vibrate",
	"victory", "video", "view", "village", "violin", "virtue", "virus",

	// W
	"we", "warm", "watch",
	"wage", "wait", "walk", "wall", "wander", "want", "war",
	"wash", "waste", "watch", "water", "wave", "way", "wealth",
	"weapon", "wear", "weather", "weave", "wedding", "week", "weight",
	"welcome", "well", "west", "wheel", "when", "whisper", "white",

	// X
	"xylophone",
	"xenon", "xenophobia", "xerox", "xmas", "x-ray", "xylophone", "xylem",

	// Y
	"yolk", "young", "your",
	"yard", "yarn", "year", "yell", "yellow", "yes", "yesterday",
	"yet", "yield", "yogurt", "yoke", "youth", "yawn", "yearn",
	"yacht", "yummy", "yogurt", "yoga", "yardstick", "yonder", "yummy",

	// Z
	"zebra", "zodiac", "zucchini",
	"zero", "zone", "zoo", "zoom", "zeal", "zip", "zigzag",
	"zenith", "zest", "zipper", "zombie", "zonal", "zinc", "zephyr"
};

int words_size = sizeof(words)/sizeof(words[0]);

// Generates random words
void program_words(int argc, char* argv[])
{
	int amount;

	if (argc == 1)
	{
		amount = 10;
	} else if (argc == 2)
	{
		amount = atoi(argv[1]);
	}

	for (int i=0; i<amount; i++)
	{
		int random = randint(global_ticks);
		char* word = words[random%words_size];
		//printf("Global ticks: %d\nRandom integer: %d\nWord: %s\n", global_ticks, random, word);
		printf("%s ", word);
		delay(10);
	}
	puts("\n");
}
