#include <string>
#include <iostream>
#include "BigramGenerator.cpp"
#include <chrono>
#include <omp.h>

void generatePytonPlotPerCorpus(const std::vector<int>& num_words,
                              const std::vector<double>& sequential_times,
                              const std::vector<double>& parallel_times) {
    std::ofstream pythonScript("plot_script.py");
    if (!pythonScript.is_open()) {
        std::cerr << "Error: Unable to open plot_script.py for writing." << std::endl;
        return;
    }

    pythonScript << "import matplotlib.pyplot as plt\n"
                    "num_words = [";
    for (size_t i = 0; i < num_words.size(); ++i) {
        pythonScript << num_words[i];
        if (i != num_words.size() - 1) {
            pythonScript << ", ";
        }
    }
    pythonScript << "]\n";

    pythonScript << "sequential_times = [";
    for (size_t i = 0; i < sequential_times.size(); ++i) {
        pythonScript << sequential_times[i];
        if (i != sequential_times.size() - 1) {
            pythonScript << ", ";
        }
    }
    pythonScript << "]\n";

    pythonScript << "parallel_times = [";
    for (size_t i = 0; i < parallel_times.size(); ++i) {
        pythonScript << parallel_times[i];
        if (i != parallel_times.size() - 1) {
            pythonScript << ", ";
        }
    }
    pythonScript << "]\n";

    pythonScript << "plt.plot(num_words, sequential_times, marker='o', label='Sequential')\n"
                    "plt.plot(num_words, parallel_times, marker='o', label='Parallel')\n"
                    "plt.xlabel('Number of Words')\n"
                    "plt.ylabel('Time (seconds)')\n"
                    "plt.title('Parallel vs Sequential bigram generation')\n"
                    "plt.legend()\n"
                    "plt.grid(True)\n"
                    "plt.savefig('plot.png')\n"
                    "plt.show()\n";

    pythonScript.close();
}

void generatePytonPlotPerThreadNumber(const std::vector<int>& num_words,
                                const std::vector<double>& parallel_times) {

    std::ofstream pythonScript("plot_script_2.py");
    if (!pythonScript.is_open()) {
        std::cerr << "Error: Unable to open plot_script.py for writing." << std::endl;
        return;
    }
    pythonScript << "from matplotlib import colormaps\n";
    pythonScript << "import matplotlib.pyplot as plt\n"
                    "num_words = [";
    for (size_t i = 0; i < num_words.size(); ++i) {
        pythonScript << num_words[i];
        if (i != num_words.size() - 1) {
            pythonScript << ", ";
        }
    }
    pythonScript << "]\n";

    pythonScript << "times = {";
    for (size_t i = 0; i < parallel_times.size(); ++i) {
        pythonScript << i+1;
        pythonScript << ": ";
        pythonScript << parallel_times[i];
        if (i != parallel_times.size() - 1) {
            pythonScript << ",";
        }
    }
    pythonScript << "}\n";

    pythonScript << "color_map = colormaps['Set2']\n"
                    "plt.xticks(list(times.keys()))\n"
                    "plt.bar(list(times.keys()), list(times.values()), color=color_map.colors)\n"
                    "plt.xlabel('Number of cores')\n"
                    "plt.ylabel('Time taken (s)')\n"
                    "plt.savefig('bar_plot.png')\n";

    pythonScript.close();
}

float parallelGenerateBigrams(const std::string& filename, const std::string& numberOfWords, int numThreads) {
    BigramGenerator bigramGenerator(filename);

    // Start the timer
    auto start = std::chrono::steady_clock::now();

    // Generate bigrams in parallel
    auto result = bigramGenerator.generateBigramsParallel(numThreads);

    //print first 10 bigrams
    /*for (int i = 0; i < 10; i++) {
        std::cout << result[i].first << " " << result[i].second << std::endl;
    }*/

    // Stop the timer
    auto end = std::chrono::steady_clock::now();

    // Calculate the elapsed time
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time taken to parallel generate bigrams for "<< numberOfWords <<" words: "
    << duration.count() << " milliseconds" << "---->" << duration.count()/1000.0 << "seconds" << std::endl;
    return duration.count()/1000.0;
}

float generateBigrams(const std::string& filename, const std::string& numberOfWords){
    BigramGenerator bigramGen(filename);
    auto start = std::chrono::steady_clock::now();
    auto bigrams = bigramGen.generateBigrams();
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    //print first 10 bigrams
    /*for (int i = 0; i < 10; i++) {
        std::cout << bigrams[i].first << " " << bigrams[i].second << std::endl;
    }*/

    std::cout << "Time taken to generate bigrams for "<< numberOfWords <<" words: "
              << duration.count() << " milliseconds" << "---->" << duration.count()/1000.0 << "seconds" << std::endl;
    return duration.count()/1000.0;
}


int main() {
    std::vector<double> sequential_times = {};
    std::vector<double> parallel_times_corpus = {};
    std::vector<double> parallel_times_threads = {};

    /*sequential_times.push_back(generateBigrams("data/corpus_10000.txt", "10000"));
    sequential_times.push_back(generateBigrams("data/corpus_100000.txt", "100000"));
    sequential_times.push_back(generateBigrams("data/corpus_1000000.txt", "1000000"));
    sequential_times.push_back(generateBigrams("data/corpus_5000000.txt", "5000000"));
    sequential_times.push_back(generateBigrams("data/corpus_10000000.txt", "10000000"));
    sequential_times.push_back(generateBigrams("data/corpus_25000000.txt", "25000000"));
    sequential_times.push_back(generateBigrams("data/corpus_50000000.txt", "50000000"));
    sequential_times.push_back(generateBigrams("data/corpus_75000000.txt", "75000000"));
    sequential_times.push_back(generateBigrams("data/corpus_100000000.txt", "100000000"));

    parallel_times_corpus.push_back(parallelGenerateBigrams("data/corpus_10000.txt", "10000", 8));
    parallel_times_corpus.push_back(parallelGenerateBigrams("data/corpus_100000.txt", "100000", 8));
    parallel_times_corpus.push_back(parallelGenerateBigrams("data/corpus_1000000.txt", "1000000", 8));
    parallel_times_corpus.push_back(parallelGenerateBigrams("data/corpus_5000000.txt", "5000000", 8));
    parallel_times_corpus.push_back(parallelGenerateBigrams("data/corpus_10000000.txt", "10000000", 8));
    parallel_times_corpus.push_back(parallelGenerateBigrams("data/corpus_25000000.txt", "25000000", 8));
    parallel_times_corpus.push_back(parallelGenerateBigrams("data/corpus_50000000.txt", "50000000", 8));
    parallel_times_corpus.push_back(parallelGenerateBigrams("data/corpus_75000000.txt", "75000000", 8));
    parallel_times_corpus.push_back(parallelGenerateBigrams("data/corpus_100000000.txt", "100000000", 8));*/

    for(int num_threads=1; num_threads< 12+1; num_threads++){
        parallel_times_threads.push_back(parallelGenerateBigrams("data/corpus_100000000.txt", "100000000", num_threads));
    }

    std::vector<int> num_words = {10000, 100000, 1000000, 5000000, 10000000, 25000000, 50000000, 75000000, 100000000};

    //generatePytonPlotPerCorpus(num_words, sequential_times, parallel_times_corpus);
    generatePytonPlotPerThreadNumber(num_words, parallel_times_threads);

    // system("python plot_script.py");
    system("python plot_script_2.py");

    return 0;
}





/*
 std::vector<std::pair<const char*, const char*>> generateBigramsParallel(int num_threads) const {
    const int WORK_SIZE = 1024; // Adjust this value based on your corpus size and desired chunk size
    const int CHUNK_SIZE = 2 * WORK_SIZE;
    const int CORPUS_SIZE = corpus.size();
    const int NUM_CHUNKS = (CORPUS_SIZE - 1) / CHUNK_SIZE;

    std::vector<std::pair<const char*, const char*>> bigrams(NUM_CHUNKS);

    // Calculate start and end indices for each thread
    int start_index = 0;
    int end_index = CHUNK_SIZE;
    for (int i = 0; i < num_threads; ++i) {
        start_index = i * CHUNK_SIZE;
        end_index = std::min(start_index + CHUNK_SIZE, CORPUS_SIZE - 1);
        bigrams[i] = std::vector<std::pair<const char*, const char*>>();
    }

    #pragma omp parallel num_threads(num_threads)
    {
        // Each thread works on a different part of the corpus
        for (int i = 0; i < num_threads; ++i) {
            std::cout << "Thread " << omp_get_thread_num() << " working on chunk [" << start_index << ", " << end_index << ")\n";
            if (omp_get_thread_num() == 0) {
                // Combine results from all threads
                bigrams[0].insert(bigrams[0].end(), bigrams[i].begin(), bigrams[i].end());
            }
        }
    }

    return bigrams;
}
 */



/*
#include <vector>
#include <string>
#include <omp.h>

std::vector<std::pair<const char*, const char*>> generateBigramsParallel(int num_threads) const {
    std::vector<std::pair<const char*, const char*>> bigrams;
    std::cout<<"num_threads: "<<num_threads<<"\n";

    size_t corpus_size = corpus.size();
    size_t chunk_size = corpus_size / num_threads;

#pragma omp parallel num_threads(num_threads)
    {
        int thread_id = omp_get_thread_num();
        size_t start_index = thread_id * chunk_size;
        size_t end_index = (thread_id == num_threads - 1) ? corpus_size : (thread_id + 1) * chunk_size;

#pragma omp for
        for (size_t i = start_index; i < end_index; ++i) {
            bigrams.push_back(std::make_pair(&corpus[i][0], &corpus[i + 1][0]));
        }
    }

    return bigrams;
}
 */