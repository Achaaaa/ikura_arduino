class Prize {
  public:
    Prize() {}
    ~Prize() {}

    int prizePin;
    int prizeThreshold;
    boolean BallIn;
    boolean BallIn_prev;
    int prizeVal;

    void set(int _prizePin, int _prizeThreshold) {
      prizePin = _prizePin;
      prizeThreshold = _prizeThreshold;
    }

    void update() {
      prizeVal = analogRead(prizePin);
      Serial.print(prizeVal);
    }

    boolean observe() {
      if (prizeVal < prizeThreshold) {
        BallIn = true;
      } else {
        BallIn = false;
      }
      if (BallIn && !BallIn_prev) {
        return true;
      }
      BallIn_prev = BallIn;
      return false;
    }
};
