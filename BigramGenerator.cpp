#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include <sstream>
#include <iostream>

class BigramGenerator {
public:
    BigramGenerator(const std::string& filename) {
        std::ifstream file(filename);
        std::string word;
        while (file >> word) {
            corpus.push_back(word);
        }
    }

    std::vector<std::pair<const char*, const char*>> generateBigrams() const {
        std::vector<std::pair<const char*, const char*>> bigrams(corpus.size() - 1);
        for (size_t i = 0; i < corpus.size() - 1; ++i) {
            bigrams[i] = std::make_pair(&corpus[i][0], &corpus[i + 1][0]);
        }
        return bigrams;
    }

    std::vector<std::pair<const char*, const char*>> generateBigramsParallel(int num_threads) const {
        std::vector<std::pair<const char*, const char*>> bigrams(corpus.size() - 1);
        #pragma omp parallel num_threads(num_threads)
        #pragma omp for
            for (size_t i = 0; i < corpus.size() - 1; ++i) {
                bigrams[i] = std::make_pair(&corpus[i][0], &corpus[i + 1][0]);
            }

        return bigrams;
    }

private:
    std::vector<std::string> corpus;
};