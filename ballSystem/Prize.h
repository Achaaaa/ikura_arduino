class Prize {
  public:
    Prize() {}
    ~Prize() {}

    int prizePin;
    boolean BallIn;
    boolean BallIn_prev;

    void set(int _prizePin) {
      prizePin = _prizePin;
    }

    boolean update() {
      if (analogRead(prizePin) < 30) {
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
