class Num {
 public:
    Num(int value, int modulo) {
        this->modulo = modulo;
        if (modulo == 0){
            this->value = value;
        } else {
            this->value = value % modulo;
        }
    }
    Num(const Num& other) {
        this->value = other.value;
        this->modulo = 0;
    }
    int value;
    int modulo;
};
