class PrimeNumberGenerator {
 public:
    int one_start;
    explicit PrimeNumberGenerator(int start) {
        one_start = start;
    }
    int GetNextPrime() {
        int check = 0;
        if (one_start == 1) {
            one_start++;
        }
        while (one_start) {
            for (int i = 2; i <= sqrt(one_start); i++) {
                if (one_start % i == 0) {
                    check = 1;
                    break;
                }
            }
            if (check == 0) {
                one_start++;
                return (one_start - 1);
            }
            one_start++;
            check = 0;
        }
        return 0;
    }
};
