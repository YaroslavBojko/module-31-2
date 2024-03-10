#include <iostream>

class Toy
{
public:
    Toy(std::string inName) : name(inName) {};
    ~Toy() = default;
private:
    std::string name;
};

class shared_ptr_toy
{
private:
    Toy* toy;
    int* count_toys;
public:
    shared_ptr_toy(std::string inName)
    {
        toy = new Toy(inName);
        count_toys = new int (1);
    }

    shared_ptr_toy(const shared_ptr_toy& oth)
    {
        toy = oth.toy;
        count_toys = oth.count_toys;
        ++(*count_toys);
    }

    void decrementRefCount()
    {
        --(*count_toys);
        if (*count_toys == 0)
        {
            delete count_toys;
            delete toy;
        }
    }

    shared_ptr_toy& operator=(const shared_ptr_toy& oth)
    {
        if (toy != oth.toy) {
            decrementRefCount();
            toy = oth.toy;
            count_toys = oth.count_toys;
            (*count_toys)++;
        }
        return *this;
    }

    ~shared_ptr_toy()
    {
        decrementRefCount();
    }

    Toy* get()
    {
        return toy;
    }

    int use_count()
    {
        return *count_toys;
    }
};

void make_shared_toy(std::string nameToy)
{
   shared_ptr_toy sp(nameToy);

}

int main() {

    make_shared_toy("Ball");

}
