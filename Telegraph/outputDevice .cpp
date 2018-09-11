class OutputDevice {
  public:
    virtual void output_symbol(const int length);
};

class Led : public OutputDevice {
  public:
    void output_symbol(const int length) {
// ...
    }
};

class Speaker : public OutputDevice {
  public:
    void output_symbol(const int length) {
    // ...
    }
};