#include <iostream>
#include <sstream>
#include <string>
#include <map>

// int main() {
//     std::string requestBuffer =
//         "GET /index.html HTTP/1.1\r\n"
//         "Host: www.example.com\r\n"
//         "User-Agent: Mozilla/5.0\r\n"
//         "Accept: text/html,application/xhtml+xml\r\n"
//         "Accept-Language: en-US,en;q=0.5\r\n"
//         "Connection: keep-alive\r\n"
//         "\r\n\r\n";

//     std::stringstream ss(requestBuffer);

//     std::map<std::string, std::string> tokensMap;

//     std::string line;
//     while (std::getline(ss, line)) {
//         std::stringstream lineSS(line);
//         std::string str;
//         lineSS >> str;
//         if (str == "GET") {
//             tokensMap.insert(std::make_pair("METHOD",str));
//             lineSS>>str;
//             tokensMap.insert(std::make_pair("PATH",str));
//         }
//     }

//     // Print the resulting map
//     std::cout << "Map contents:\n";
//     // for (std::map<std::string, std::string>::iterator it = tokensMap.begin(); it != tokensMap.end(); ++it) {
//     //     std::cout << it->first << " => " << it->second << "\n";
//     // }
//     std::cout << tokensMap.find("PATH")->second<< "\n";

//     return 0;
// }

#include <iostream>
#include <sstream>

int main() {
    std::string hex_str = "20"; // the hexadecimal string to convert
    std::istringstream iss(hex_str);
    int hex_val;
    iss >> std::hex >> hex_val; // read the hex value
    std::cout << "Decimal value:" << hex_val <<"------"<< std::endl; // output the decimal value
    return 0;
}