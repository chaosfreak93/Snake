#include "Tail.cpp"

class Snake {
    private:
        int x;
        int y;
        int tailLength;
    public:
        Tail tail[100];
        int getX() {
            return x;
        }
        void setX(int x) {
            this->x = x;
        }
        int getY() {
            return y;
        }
        void setY(int y) {
            this->y = y;
        }
        int getTailLength() {
            return tailLength;
        }
        void setTailLength(int tailLength) {
            this->tailLength = tailLength;
        }
};