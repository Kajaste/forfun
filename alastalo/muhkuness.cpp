#include <fstream>
#include <iostream>
#include <list>
#include <set>
#include <string>

#include <boost/algorithm/string.hpp>
#include <boost/locale.hpp>

static const std::set<unsigned char> FINNISH_LETTERS
        {'a', 'b', 'c', 'd', 'e', 'f', 'g',
         'h', 'i', 'j', 'k', 'l', 'm', 'n',
         'o', 'p', 'q', 'r', 's', 't', 'u',
         'v', 'w', 'x', 'y', 'z', 0xE5, 0xE4, 0xF6 };

class Word {
public:
    Word(const std::wstring& w,
         const std::locale& loc) : word(),
                                   letters()
    {
        word = boost::locale::conv::from_utf(boost::locale::to_lower(w, loc),
                                             "Latin1");
        word.erase(std::remove_if(word.begin(),
                                  word.end(),
                                  (int(*)(int))std::ispunct),
                   word.end());

        std::set<unsigned char> letterset(word.begin(), word.end());
        std::set_intersection(letterset.begin(), letterset.end(),
                              FINNISH_LETTERS.begin(), FINNISH_LETTERS.end(),
                              std::inserter(letters, letters.begin()));
    }

    void printWord()
    {
        std::cout << boost::locale::conv::to_utf<char>(word, "Latin1") << std::endl;
    }
    void printLetters()
    {
        for (auto i : letters)
        {
            char arr[2] = {i, 0};
            std::cout << boost::locale::conv::to_utf<char>(std::string(arr), "Latin1") << std::endl;
        }
    }

    bool operator<(const Word& other) const { return (word > other.word); }

    std::string word;
    std::set<char> letters;

private:

};

typedef std::pair<Word, Word> WordPair;

std::list<Word> getWords(const std::string& file)
{
    boost::locale::generator gen;
    std::locale loc(gen("fi_FI.UTF-8"));
    std::locale::global(loc);

    std::wifstream f(file);
    std::set<Word> wordset;
    std::wstring word;
    while (f >> word)
    {
        wordset.emplace(Word(word, loc));
    }

    std::list<Word> words(wordset.begin(), wordset.end());
    return words;
}

std::vector<WordPair>
getMostMuhkuWordPairs(std::list<Word>& words)
{
    std::vector<WordPair> pairs;

    unsigned max_muhku = 0;

    words.sort([](const Word& w, const Word& o)
               { return (w.letters.size() > o.letters.size()); });

    std::vector<char> letterset;
    for (auto i(words.begin()), e = words.end(); i != e; ++i)
    {
        if (i->letters.size() * 2 < max_muhku)
        {
            break;
        }

        for (auto j(i); j != e; ++j)
        {
            letterset.clear();
            std::set_union(i->letters.begin(), i->letters.end(),
                           j->letters.begin(), j->letters.end(),
                           std::back_inserter(letterset));
            unsigned m = letterset.size();
            if (m < max_muhku)
            {
                if (i->letters.size() + j->letters.size() < max_muhku)
                {
                    break;
                }
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
    std::list<Word> words(getWords(argv[1]));

    std::vector<WordPair> pairs(getMostMuhkuWordPairs(words));

    std::cout << "Pairs:" << std::endl;
    for (auto i : pairs)
    {
        std::cout << boost::locale::conv::to_utf<char>(i.first.word, "Latin1") << ", "
                  << boost::locale::conv::to_utf<char>(i.second.word, "Latin1") << std::endl;
    }
}
