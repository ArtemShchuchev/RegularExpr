﻿#include <iostream>
#include <chrono>
#include "wordSearch.h"
#include "SecondaryFunction.h"
#include "Types.h"


int main()
{
    setRuLocale();
    consoleClear();

    WordSearch words;
    std::wstring s;
    {
        s = L"\
HTTP/1.1 200 OK\n\
Accept - Ranges: bytes\n\
Age : 522097\n\
Cache - Control : max - age = 604800\n\
Content - Type : text / html; charset = UTF - 8\n\
Date: Thu, 26 Oct 2023 13 : 28 : 11 GMT\n\
Etag : \"3147526947\"\n\
Expires : Thu, 02 Nov 2023 13 : 28 : 11 GMT\n\
Last - Modified : Thu, 17 Oct 2019 07 : 18 : 26 GMT\n\
Server : ECS(nyb / 1D1E)\n\
Vary : Accept - Encoding\n\
X - Cache : HIT\n\
Content - Length : 1256\n\
< !doctype html >\n\
<html>\n\
    <head>\n\
        <title>Example Domain< / title>\n\
        <meta charset = \"utf-8\" / >\n\
        <meta http - equiv = \"Content-type\" content = \"text/html; charset=utf-8\" / >\n\
        <meta name = \"viewport\" content = \"width=device-width, initial-scale=1\" / >\n\
            <style type = \"text/css\">\n\
                body{\n\
                    background - color: #f0f0f2;\n\
                    margin : 0;\n\
                    padding : 0;\n\
                    font - family: -apple - system, system - ui, BlinkMacSystemFont, \"Segoe UI\", \"Open Sans\", \"Helvetica Neue\", Helvetica, Arial, sans - serif;\n\
                }\n\
                div{\n\
                    width: 600px;\n\
                    margin: 5em auto;\n\
                    padding: 2em;\n\
                    background - color: #fdfdff;\n\
                    border - radius: 0.5em;\n\
                    box - shadow: 2px 3px 7px 2px rgba(0,0,0,0.02);\n\
                }\n\
                a:link, a : visited{\n\
                    color: #38488f;\n\
                    text - decoration: none;\n\
                }\n\
                @media(max - width: 700px) {\n\
                    div{\n\
                        margin: 0 auto;\n\
                        width: auto;\n\
                    }\n\
                }\n\
            < / style>\n\
        < / head>\n\
        <body>\n\
            <div>\n\
                <h1>Example Domain< / h1>\n\
                <p>Проверка проверка русских слов word45 слово45 45687 56apple 56яблоко This domain is for use in illustrative examples in documents.You may use this\n\
                domain in literature without prior coordination or asking മലയാളം for permission.< / p>\n\
                <p><a href=\"http://www.iana.org/domains/example\">More information...</a>< / p>\n\
                <p><a href=\"http://www.iana.org/domains/മലയാളം\">information...</a>< / p>\n\
                <a href=\"https://ru.wikibooks.org/wiki/%d0%97%d0%b0%d0%b3%d0%bb%d0%b0%d0%b2%d0%bd%d0%b0%d1%8f_%d1%81%d1%82%d1%80%d0%b0%d0%bd%d0%b8%d1%86%d0%b0\" hreflang=\"ru\"><span>викиучебник</span></a>\n\
                <p><a href=\"https://www.wikipedia.org/\">Wikipedia</a>< / p>\n\
            < / div>\n\
        </body>\n\
< / html>";
    }

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    auto [wordAmount, links](words.getWordLink(s, 3));
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> delta = end - start;
    double workTime = delta.count();

    std::wcout << L"Найдено ссылок: " << links.size()
        << L"\nНайдено слов: " << wordAmount.size()
        << L"\nПотрачено времени: " << workTime << L"ms\n";

    uint32_t listNum(0);
    for (const auto& link : links) {
        std::wcout << ++listNum << ") " << utf82wideUtf(link.link_str) << '\n';
    }
    std::wcout << '\n';

    listNum = 0;
    for (const auto& [word, amount] : wordAmount)
    {
        std::wcout << ++listNum << ") " << word << " - " << amount << '\n';
    }
    /*
    */

    // Слова от 3х до 32х символов
    /*
    wordRegex = R"(\s(\w{3,32})\s)";
    std::vector<std::string> words{
        std::sregex_token_iterator{str.begin(), str.end(), wordRegex, 1},
        std::sregex_token_iterator{}
    };
    listNum = 0;
    for (const auto& word : words) {
        std::cout << ++listNum << ") " << word << '\n';
    }
    */

    return EXIT_SUCCESS;
}
