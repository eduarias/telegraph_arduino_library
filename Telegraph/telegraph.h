#ifndef __TELEGRAPH_H__
#define __TELEGRAPH_H__


class OutputDevice {
  public:
    OutputDevice(const byte outputPin);
    virtual void outputSymbol(const int length) {};
  protected:
    byte _outputPin;
};

class Led : public OutputDevice {
  public:
    Led(const byte outputPin);
    void outputSymbol(const int length);
};


class Speaker : public OutputDevice {
  public:
    Speaker(const byte outputPin);
    void outputSymbol(const int length);
};

class Telegraph {
  public:
    Telegraph(OutputDevice* outputDevice, const int ditLength);
    void sendMessage(const char* message);

  private:
    void dit();
    void dah();
    void outputCode(const char* code);
    void outputSymbol(const int length);

    int _ditLength;
    int _dahLength;
    Led* _outputDevice;
};

#endif
