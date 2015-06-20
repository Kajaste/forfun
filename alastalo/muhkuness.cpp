#include <bitset>
#include <fstream>
#include <iostream>
#include <set>
#include <string>

#include <boost/locale.hpp>

typedef std::bitset<29> LetterSet;

class Word {
public:
    explicit Word(const std::wstring& w)
    : word(boost::locale::conv::from_utf(w, "Latin1")),
      letters()
    {
        word.erase(std::remove_if(word.begin(),
                                  word.end(),
                                  (int(*)(int))std::ispunct),
                   word.end());
    }

    void setLetters()
    {
        for (auto letter : word) { setLetterBit(letters, letter); }
        letterCount = letters.count();
    }

    void setLetterBit(LetterSet& letters, char letter)
    {
        switch ((unsigned char)letter)
        {
        case 0xC5:                          // Å
        case 0xE5: letters.set(26); return; // å
        case 0xC4:                          // Ä
        case 0xE4: letters.set(27); return; // ä
        case 0xD6:                          // Ö
        case 0xF6: letters.set(28); return; // ö
        }
        if (letter >= 'a' && letter <= 'z') { letters.set(letter - 'a'); }
        else if (letter >= 'A' && letter <= 'Z') { letters.set(letter - 'A'); }
    }

    bool operator<(const Word& other) const { return (word > other.word); }

    std::string word;
    LetterSet letters;
    unsigned letterCount;
};

typedef std::pair<Word, Word> WordPair;

std::vector<Word> getWords(const std::string& file)
{
    boost::locale::generator gen;
    std::locale loc(gen("fi_FI.UTF-8"));
    std::locale::global(loc);

    std::wifstream f(file);
    std::set<Word> wordset;
    std::wstring word;
    while (f >> word) { wordset.emplace(Word(word)); }

    std::vector<Word> words(wordset.begin(), wordset.end());
    std::for_each(words.begin(), words.end(),
                  [](Word& w) { w.setLetters(); });
    return words;
}

std::vector<WordPair>
getMostMuhkuWordPairs(std::vector<Word>& words)
{
    std::sort(words.begin(), words.end(),
              [](const Word& w, const Word& o)
                { return (w.letterCount > o.letterCount); });

    std::vector<WordPair> pairs;
    unsigned max_muhku = 0;
    for (auto i(words.begin()), e = words.end(); i != e; ++i)
    {
        if (i->letterCount * 2 < max_muhku) { break; }

        for (auto j(i); j != e; ++j)
        {
            unsigned m = (i->letters | j->letters).count();
            if (m < max_muhku)
            {
                if (i->letterCount + j->letterCount < max_muhku) { break; }
                continue;
            }

            if (m > max_muhku)
            {
                max_muhku = m;
                pairs = { WordPair(*i, *j) };
            }
            else
            {
                pairs.push_back(WordPair(*i, *j));
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
    std::vector<Word> words(getWords(argv[1]));
    std::vector<WordPair> pairs(getMostMuhkuWordPairs(words));

    for (auto i : pairs)
    {
        std::cout << boost::locale::conv::to_utf<char>(i.first.word, "Latin1") << ", "
                  << boost::locale::conv::to_utf<char>(i.second.word, "Latin1") << std::endl;
    }
}
