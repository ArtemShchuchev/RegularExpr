#include "wordSearch.h"

const std::wregex
    //WordSearch::space_reg{ LR"(\s+)" }, // [ \f\n\r\t\v]
    WordSearch::title_reg{ LR"(< ?title ?>(.+)< ?/ ?title>)" },
    //WordSearch::body_reg{ LR"(<body[^>]*>(.+)</body>)" },
    //WordSearch::body_reg{ LR"(<body[^>]*>([\s[:punct:]\w]+)body>)" },
    //WordSearch::body_reg{ LR"(<body[^>]*>([[:space:][:print:]]+)</body>)" }, // искать 1 (без токенов body)
    //WordSearch::body_reg{ LR"(<body([_%[:space:][:print:]]+)/body>)" },   // искать 0 (с токенами body)
    //WordSearch::body_reg{ LR"(<body([\%^S2]+)(/body>))" },   // искать 0 (с токенами body)
    //WordSearch::url_reg{ LR"!!(<\s*A\s+[^>]*href\s*=\s*"([^"]*)")!!", std::regex::icase },
    //WordSearch::url_reg{ LR"!!(<\s*A\s+href\s*=\s*"([^"]*)")!!", std::regex::icase },
    //WordSearch::url_reg{ LR"!!(<\s*A\s+[^>]*href\s*=\s*"(http[^"]*)")!!", std::regex::icase },
    //WordSearch::url_reg{ LR"!!(<\s?a href\s?=\s?"(http[^"]*))!!" },
    WordSearch::url_reg{ LR"!!(<a href="(http[^"]+))!!" },
    WordSearch::token_reg{ LR"(<[^>]*>)" },
    //WordSearch::punct_reg{ LR"([[:punct:]])" },
    WordSearch::word_reg{ LR"([^[:alpha:]]?([[:alpha:]]+)[^[:alpha:]]?)" };
    //WordSearch::number_reg{ LR"(\w*[0-9]\w*)" };

std::pair<WordMap, LinkList> WordSearch::getWordLink(std::wstring page, unsigned int recLevel)
{
    // Строку в нижний регистр
    // Create system default locale
    boost::locale::generator gen;
    std::locale loc = gen("");
    // Make it system global
    std::locale::global(loc);
    page = boost::locale::to_lower(page);

    // Убрал пробельные символы [ \f\n\r\t\v]
    //page = std::regex_replace(page, space_reg, L" ");
    // Нашел title
    auto it = std::wsregex_token_iterator(page.begin(), page.end(), title_reg, 1);
    std::wstring title;
    if (it != std::wsregex_token_iterator{}) title = *it;
    //std::wcout << "title: " << title << '\n';



    // Нашел body
    //std::wcout << "page: " << page << '\n';
    //it = std::wsregex_token_iterator(page.begin(), page.end(), body_reg, 0);
    //if (it != std::wsregex_token_iterator{}) page = *it;
    //else page.clear();
    page = { (page.begin() + page.find(L"<body") + 6),
        (page.begin() + page.rfind(L"</body")) };

    //std::wcout << "body: " << page << '\n';

    // Ищу ссылки
    LinkList links;
    auto it_start(std::wsregex_token_iterator{ page.begin(), page.end(), url_reg, 1 });
    auto it_end(std::wsregex_token_iterator{});
    --recLevel; // следующая глубина погружения
    for (auto it(it_start); it != it_end; ++it)
    {
        std::wstring link_ws(*it);
        std::string link_str(wideUtf2utf8(link_ws));
        links.push_back( { link_str, recLevel } );
    }

    // добавил к body, title
    page += std::move(title);
    // Убрал токены
    page = std::regex_replace(page, token_reg, L" ");

    // Ищу слова
    WordMap wordmap;
    it_start = std::wsregex_token_iterator{ page.begin(), page.end(), word_reg, 1 };
    it_end = std::wsregex_token_iterator{};
    std::wstring word;
    for (auto it(it_start); it != it_end; ++it) {
        word = *it;
        if (word.size() > 2 && word.size() < 33)
            ++wordmap[word];
    }

    /*
    // Убрал знаки пунктуации
    page = std::regex_replace(page, punct_reg, L" ");
    // Цифры и слова содержащие цифры
    page = std::regex_replace(page, number_reg, L" ");
    // Разделяю на слова от 3х до 32х символов, добавляю в словарь
    std::wstringstream stream(std::move(page));
    WordMap wordmap;
    std::wstring word;
    while (std::getline(stream, word, L' '))
    {
        if (word.size() > 2 && word.size() < 33)
            ++wordmap[word];
    }
    */

    return { wordmap, links };
}
