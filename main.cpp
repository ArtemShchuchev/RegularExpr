#include <iostream>
#include <regex>
#include <boost/locale.hpp>

int main()
{
    std::string s;
    {
        s = "\
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
                <p>This domain is for use in illustrative examples in documents.You may use this\n\
                domain in literature without prior coordination or asking for permission.< / p>\n\
                <p><a href = \"https://www.iana.org/domains/example\">More information...< / a>< / p>\n\
                <p><a href = \"https://www.wikipedia.org/\">Wikipedia< / a>< / p>\n\
            < / div>\n\
        < / body>\n\
< / html>";
    }

    // Убрал пробельные символы [ \f\n\r\t\v]
    std::regex wordRegex(R"(\s+)");
    s = std::regex_replace(s, wordRegex, " ");
    // Нашел body, извлек в str
    wordRegex = R"(< ?body ?>(.+)< ?/ ?body>)";
    std::sregex_token_iterator wordStart(s.begin(), s.end(), wordRegex, 1);
    std::string str(*wordStart);
    // Ищу ссылки
    const std::regex url_re(R"!!(<\s*A\s+[^>]*href\s*=\s*"([^"]*)")!!", std::regex::icase);
    std::vector<std::string> links{
        std::sregex_token_iterator{str.begin(), str.end(), url_re, 1},
        std::sregex_token_iterator{}
    };
    uint32_t listNum(0);
    for (const auto& link : links) {
        std::cout << ++listNum << ") " << link << '\n';
    }
    std::cout << '\n';

    // Нашел title, присоеденил к str
    wordRegex = R"(< ?title ?>(.+)< ?/ ?title>)";
    wordStart = std::sregex_token_iterator(s.begin(), s.end(), wordRegex, 1);
    str += *wordStart;

    // Убрал токены
    wordRegex = R"(<[^>]*>)";
    str = std::regex_replace(str, wordRegex, "");
    // Убрал знаки пунктуации
    wordRegex = R"(\W)";
    str = std::regex_replace(str, wordRegex, "  ");
    // Строку в нижний регистр
    // Create system default locale
    boost::locale::generator gen;
    std::locale loc = gen("");
    // Make it system global
    std::locale::global(loc);
    str = boost::locale::to_lower(str);

    // Разделяю на слова от 3х до 32х символов, добавляю в словарь
    std::unordered_map<std::string, int> wordAmount;
    
    std::stringstream stream(str);
    std::string word;
    while (std::getline(stream, word, ' ')) {
        if (word.size() > 2 && word.size() < 33)
            ++wordAmount[word];
    }

    listNum = 0;
    for (const auto& [word, amount] : wordAmount)
    {
        std::cout << ++listNum << ") " << word << " - " << amount << '\n';
    }

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

    return 0;
}
