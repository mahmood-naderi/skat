#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>

class Tokenizer {
public:
    inline explicit Tokenizer(std::string src) : main_src(std::move(src)) {}

    inline std::vector<char> tokenize() {
        std::vector<char> tokens;
        while(peak().has_value()) {
            tokens.push_back(consume());
        }

        return tokens;
    }
private:
    [[nodiscard]] std::optional<char> peak(int ahead = 1) const {
        if (main_index + ahead > main_src.length()) {
            return {};
        } else {
            return main_src.at(main_index);
        }
    }

    char consume() {
        main_src.at(main_index++);
    }
    const std::string main_src;
    int main_index;
};


int main(int argc, char* argv[]) {
    
    if (argc != 2) {
        std::cerr << "Wrong Usag <skat> ..." << std::endl;
        std::cerr << "Correct usage : skat <file_name>" << std::endl;
        return EXIT_FAILURE;
    }
    
    std::fstream inputFile(argv[1], std::ios::in);
    std::stringstream contentStream;
    contentStream << inputFile.rdbuf();
    inputFile.close();

    std::string fileContent = contentStream.str();
    
    Tokenizer tokenizer(std::move(fileContent));
    std::vector<char> tokens = tokenizer.tokenize();

    for(const char& token : tokens)
        std::cout << token << std::endl;

    //std::cout << fileContent << std::endl;

    return EXIT_SUCCESS;
}
