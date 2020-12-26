#include <fstream>
#include <chrono>
#include <mutex>
#include <functional>
#include <thread>

using namespace std;

template<typename TimePoint>
class basic_time_meter
{
    function<TimePoint()> get_now_;
    function<double(TimePoint, TimePoint)> get_sec_;

    TimePoint begin_;
    TimePoint stop_;
    bool stopped_;

public:
    basic_time_meter(const function<TimePoint()>& gn, const function<double(TimePoint, TimePoint)>& gs) :
        get_now_(gn), get_sec_(gs),
        begin_(get_now_()), stopped_(false) { }

    double seconds() const
    {
        if (stopped_)
            return get_sec_(begin_, stop_);
        return get_sec_(begin_, get_now_());
    }

    double restart()
    {
        const TimePoint now = get_now_();
        double result = seconds(now);
        stopped_ = false;
        begin_ = now;
        return result;
    }

    double stop()
    {
        if (stopped_)
            return seconds();
        stop_ = get_now_();
        stopped_ = true;
        return seconds(stop_);
    }

    void start()
    {
        if (!stopped_)
            return;
        stopped_ = false;
        begin_ += get_now_() - stop_;
    }

    bool stopped() const
    {
        return stopped_;
    }

private:
    double seconds(TimePoint now) const
    {
        if (stopped_)
            return get_sec_(begin_, stop_);
        return get_sec_(begin_, now);
    }
};

class time_meter : public basic_time_meter<chrono::high_resolution_clock::time_point>
{
    using time_point = chrono::high_resolution_clock::time_point;

    static double get_seconds(time_point p1, time_point p2)
    {
        return static_cast<double>((p2 - p1).count()) / chrono::high_resolution_clock::period::den;
    }

public:
    time_meter() : basic_time_meter<time_point>(chrono::high_resolution_clock::now, get_seconds) { }
};

// **********************

void ___CaesarEncryptOneThread___(std::string* s)
{
    for (char& c : *s)
        c = 'a' + (c + 3 - 'a') % 26;
}

void CaesarAct(char* s, int len) {
    for (int i = 0; i < len; i++) {
        *s = 'a' + (*s + 3 - 'a') % 26;
        s += 1;
    }
}

void CaesarEncrypt(std::string* s) {
    size_t number_of_threads = std::thread::hardware_concurrency();
    size_t len_part = s->length() / number_of_threads;
    size_t len = len_part + s->length() % number_of_threads;
    std::vector<std::thread> threads;
    for (size_t i = 0; i < number_of_threads - 1; i++) {
        threads.push_back(std::thread([&]() { CaesarAct(s->data() + len_part * i, len_part); }));
    }
    threads.push_back(std::thread([&]() { CaesarAct(s->data() + len_part * (number_of_threads - 1), len); }));
    for (size_t i = 0; i < number_of_threads; i++) {
        threads[i].join();
    }
}


int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string s;
    input_file >> s;
    string s2 = s;

    time_meter tm;
    ___CaesarEncryptOneThread___(&s2);
    const double one_thread_result = tm.seconds();

    tm.restart();
    CaesarEncrypt(&s);
    const double result = tm.seconds();

    const double x = result / one_thread_result;
    if (x > 0.75) {
        output_file << "So sloooooow\n\n" << "time / time_one_thread = " << x << endl;
        output_file << "r: " << result << "; 1-t-r: " << one_thread_result << endl;
        output_file << s << endl;
    }
    else {
        output_file << s << endl;
    }

    return 0;
}
