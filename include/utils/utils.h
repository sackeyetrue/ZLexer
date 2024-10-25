#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <chrono>
#include <string.h>
#include <fstream>

using namespace std;

namespace Timer
{
    class Scoped
    {
        using Clock = std::chrono::high_resolution_clock;
        using Timepoint = std::chrono::time_point<Clock>;

    public:
        /**
         *  @brief  String with Arrow.
         *  @param  name Input Text for String With Arrow.
         */
        Scoped(const char *name)
            : name(name)
        {
            startTimePoint = Clock::now();
        };

        /**
         *  @brief  String with Arrow.
         */
        Scoped()
            : name("")
        {
            startTimePoint = Clock::now();
        };

        ~Scoped()
        {
            auto endTimePoint = Clock::now();
            using namespace std::chrono;

            double duration = duration_cast<milliseconds>(endTimePoint - startTimePoint).count();
            double ms = duration * 0.001f;

            if (strlen(name) == 0)
                std::cout << "Duration :  (" << duration << ")us (" << ms << ")ms ]" << std::endl;
            else
                std::cout << name << " Took : [ Duration: (" << duration << ")us (" << ms << ")ms ]" << std::endl;
        };

    private:
        Timepoint startTimePoint;
        const char *name;
    };

    class Interval
    {
    public:
        using Clock = std::chrono::high_resolution_clock;
        using Timepoint = std::chrono::time_point<Clock>;

        /**
         *  @brief  String with Arrow.
         *  @param  name Input Text for String With Arrow.
         */
        Interval(const char *name);

        /**
         *  @brief  String with Arrow.
         */
        Interval();

        /**
         *  @brief  String with Arrow.
         */
        void start() { m_start = Clock::now(); };

        /**
         *  @brief  String with Arrow.
         */
        void stop() { m_stop = Clock::now(); };

        /**
         *  @brief  String with Arrow.
         */
        double getSeconds() const
        {
            using namespace std::chrono;
            double duration = duration_cast<milliseconds>(m_stop - m_start).count() * 0.001f * 0.001f;

            return duration;
        };

        /**
         *  @brief  String with Arrow.
         */
        double getMicroSeconds() const
        {
            using namespace std::chrono;
            double duration = duration_cast<milliseconds>(m_stop - m_start).count();
            return duration;
        };

        /**
         *  @brief  String with Arrow.
         */
        double getMilliSeconds() const
        {
            using namespace std::chrono;
            double duration = duration_cast<milliseconds>(m_stop - m_start).count() * 0.001f;
            return duration;
        };

        /**
         *  @brief  String with Arrow.
         */
        void outSeconds() const
        {
            double duration = getSeconds();
            if (strlen(name) == 0)
                std::cout << "Duration :  (" << duration << ")s " << std::endl;
            else
                std::cout << name << "Took : [ Duration: (" << duration << ")s " << std::endl;
        };

        /**
         *  @brief  String with Arrow.
         */
        void outMicroSeconds() const
        {
            double duration = getMicroSeconds();

            if (strlen(name) == 0)
                std::cout << "Duration :  (" << duration << ")us " << std::endl;
            else
                std::cout << name << "Took : [ Duration: (" << duration << ")us " << std::endl;
        };

        /**
         *  @brief  String with Arrow.
         */
        void outMilliSeconds() const
        {
            double duration = getMilliSeconds();

            if (strlen(name) == 0)
                std::cout << "Duration :  (" << duration << ")ms " << std::endl;
            else
                std::cout << name << "Took : [ Duration: (" << duration << ")ms " << std::endl;
        };

        operator double() const { return getMilliSeconds(); };

    private:
        Timepoint m_start;
        Timepoint m_stop;
        const char *name;
    };
};

namespace ZS
{
    /**
     *  @brief  String with Arrow.
     *
     *  @param  text Input Text for String With Arrow.
     *  @param  start_pos Start Position of String With Arrow.
     *  @param  end_pos End Position of String With Arrow.
     *  @param  limit Character Limit.
     */
    template <typename C, typename T>
    bool inContainer(C &container, T &value)
    {
        for (int i = 0; i < container.size(); i++)

            if (container[i] == value)

                return true;
    };

    /**
     *  @brief  String with Arrow.
     *
     *  @param  text Input Text for String With Arrow.
     *  @param  start_pos Start Position of String With Arrow.
     *  @param  end_pos End Position of String With Arrow.
     *  @param  limit Character Limit.
     */
    template <typename C, typename T, typename S>
    bool inContainer(C &container, T &value, S size)
    {
        for (int i = 0; i < size; i++)

            if (container[i] == value)

                return true;
    };

    /**
     *  @brief  String with Arrow.
     *
     *  @param  text Input Text for String With Arrow.
     *  @param  start_pos Start Position of String With Arrow.
     *  @param  end_pos End Position of String With Arrow.
     *  @param  limit Character Limit.
     */
    bool inRange(int &index, int &start, int &end)
    {
        if (index <= end && index >= start)
            return true;
        return false;
    };

    /**
     *  @brief  String with Arrow.
     *
     *  @param  text Input Text for String With Arrow.
     *  @param  start_pos Start Position of String With Arrow.
     *  @param  end_pos End Position of String With Arrow.
     *  @param  limit Character Limit.
     */
    std::string strarw(std::string &text, int &start_pos, int &end_pos, int limit = 50)
    {
        int index = 0;
        std::string resultarrow = "";
        try
        {
            std::string line = text;
            if (line.length() > limit)
                throw "too Lenghty";

            while (index < line.length())
            {
                char cchar = line[index];

                index++;
                if (inRange(index, start_pos, end_pos))
                {
                    if (cchar == ' ')
                    {
                        resultarrow += " ";
                    }
                    else
                    {
                        resultarrow += "^";
                    }
                }
                else
                {
                    resultarrow += " ";
                }
            };

            std::string stringarrow = line + "\n" + resultarrow + "\n";
            return stringarrow;
        }
        catch (const char *exe)
        {
            std::cout << exe << std::endl;
        }
    };

    /**
     *  @brief  String with Arrow.
     *
     *  @param  filename Input Text for String With Arrow.
     *  @param  line_number Start Position of String With Arrow.
     */
    std::string getLineText(std::string &filename, int &lineno)
    {

        fstream sourceFile;
        sourceFile.open(filename);
        if (sourceFile.is_open())
        {
            int start = 0;
            std::string linetext;
            while (start < lineno && std::getline(sourceFile, linetext))
            {
                if (start = lineno)
                {
                    return linetext;
                    break;
                }
            }
            sourceFile.close();
        }
        else
        {
            std::cerr << "Couldn't Open '" << filename << "'" << std::endl;
        }
    };
};

// struct AlocaMetrics
// {
//     uint32_t totalAllocated = 0;
//     uint32_t totalFreed = 0;

//     uint32_t currentUsage() { return totalAllocated - totalFreed; };
// };

// static AlocaMetrics alocaMetrics;

// static void printMemoryUsage()
// {
//     std::cout << "Memory Usage: " << alocaMetrics.currentUsage() << " bytes" << std::endl;
// };

// void *operator new(size_t size)
// {
//     alocaMetrics.totalAllocated += size;
//     std::cout << "Allocating: " << size << " bytes" << std::endl;
//     return malloc(size);
// };

// void operator delete(void *memory, size_t size)
// {
//     alocaMetrics.totalFreed += size;

//     std::cout << "Freeing: " << size << " bytes" << std::endl;
//     return free(memory);
// };

// // int main(int argc, char const *argv[])
// // {
// //     return 0;
// // };

#endif // UTILS_H