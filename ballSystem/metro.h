class Metro {
  public:
    Metro() {}
    ~Metro() {}
    void set(int _ms) {
      ms = _ms;
      ms_stamp = millis();
    }
    boolean update(){
      if((millis()-ms_stamp) > ms){
        ms_stamp = millis();
        return true;
      }
      return false;
    }
    int ms;
    long ms_stamp;
};
