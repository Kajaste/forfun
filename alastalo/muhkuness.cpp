/*
 * From a text file containing Finnish (a-z + åäö) text in UTF-8 encoding,
 * find the pairs of words (WORD1, WORD2) such that WORD1 != WORD2 and that
 * no other word pair contains a larger set of unique letters.
 */

#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>
#include <climits>
#include <set>
#include <string>
#include <vector>

typedef std::bitset<29> LetterSet;

// Unicode code points for the non-ASCII characters
#define AO 0xE5
#define AE 0xE4
#define OE 0xF6

class Word {
public:
    static std::vector<Word> getWords(const std::string& file)
    {
        std::wifstream f(file);
        f.imbue(std::locale("fi_FI.UTF-8"));
        std::set<Word> wordset;
        std::wstring word;
        while (f >> word) { wordset.emplace(word); }

        std::vector<Word> words(wordset.begin(), wordset.end());
        std::for_each(words.begin(), words.end(),
                      [](Word& w) { w.setLetters(); });
        return words;
    }

    bool operator<(const Word& other) const { return (word > other.word); }

    friend std::ostream& operator<<(std::ostream& os, const Word& w)
    {
        for (auto i : w.word)
        {
            switch (static_cast<unsigned char>(i))
            { // Unicode code point -> UTF-8
            case AO: os << "å"; break;
            case AE: os << "ä"; break;
            case OE: os << "ö"; break;
            default: os << i;
            }
        }
        return os;
    }

    std::string word;
    LetterSet letters;
    unsigned letterCount;

    explicit Word(const std::wstring& w) : word(), letters(), letterCount()
    {
        word.reserve(w.size());
        for (auto wletter : w)
        {
            if (wletter <= UCHAR_MAX && !std::ispunct(wletter))
            {
                word += std::towlower(wletter);
            }
        }
    }

private:
    void setLetters()
    {
        for (auto letter : word) { setLetterBit(letter); }
        letterCount = letters.count();
    }

    void setLetterBit(char letter)
    {
        if (letter >= 'a' && letter <= 'z') { letters.set(letter - 'a'); }
        else
        { // Non-ASCII code points
            switch (static_cast<unsigned char>(letter))
            {
            case AO: letters.set(26); return;
            case AE: letters.set(27); return;
            case OE: letters.set(28); return;
            }
        }
    }
};

typedef std::pair<Word, Word> WordPair;

std::vector<WordPair>
getMostMuhkuWordPairs(std::vector<Word>& words)
{
    std::sort(words.begin(), words.end(),
              [](const Word& w, const Word& o)
                { return (w.letterCount > o.letterCount); });

    std::vector<WordPair> pairs;
    unsigned maxMuhku = 0;
    for (auto i(words.begin()), e(words.end()); i != e; ++i)
    {
        if (i->letterCount * 2 < maxMuhku) { break; }

        for (auto j(i + 1); j != e; ++j)
        {
            if (i->letterCount + j->letterCount < maxMuhku) { break; }

            unsigned muhku = (i->letters | j->letters).count();
            if (muhku == maxMuhku) { pairs.emplace_back(*i, *j); }
            else if (muhku > maxMuhku)
            {
                maxMuhku = muhku;
                pairs = { WordPair(*i, *j) };
            }
        }
    }

    return pairs;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "USAGE: " << argv[0] << " TEXTFILE" << std::endl;
    }

    std::vector<Word> words(Word::getWords(argv[1]));
    std::vector<WordPair> pairs(getMostMuhkuWordPairs(words));

    for (auto i : pairs)
    {
        std::cout << i.first << ", " << i.second << std::endl;
    }
}
