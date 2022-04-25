bool WARNING;
class TrafficLight{
  class LED{
    private:
      int pin;
      bool selected;

    private:
      void set_pin_mode(){
        pinMode(this->pin, OUTPUT);
      }

    public:
      LED(int pin, bool selected){
        this->pin = pin;
        this->selected = selected;
        this->set_pin_mode();
      }
      void led_on(){
        digitalWrite(this->pin, HIGH);
      }

      void led_off(){
        digitalWrite(this->pin, LOW);
      }

    public:
      bool get_status(){
        return this->selected;
      }

      void click(){
        this->led_on();
        this->selected = true;
      }

      void unclick(){
        this->led_off();
        this->selected = false;
      }
  };

  public:
    void wait(int time_unit){
      delay(time_unit);
    }

  private:
    LED* led_red;
    LED* led_yellow;
    LED* led_green;

  public:
    TrafficLight(){
      led_red = new LED(D2, false);
      led_yellow = new LED(D3, false);
      led_green = new LED(D4, false);
    }

  // set all light to low
  private:
    void light_reset(){
      WARNING = false;
      this->led_red->unclick();
      this->led_yellow->unclick();
      this->led_green->unclick();
    }
  public:
    void light_go(){
      this->light_reset();
      this->led_green->click();
    }

    void light_stop(){
      this->light_reset();
      this->led_yellow->click();
      this->wait(3000);
      this->led_yellow->unclick();
      this->led_red->click();
    }

    void light_warning(){
      this->light_reset();
      WARNING = true;
      this->led_yellow->click();
      this->wait(1000);
      this->led_yellow->unclick();
      this->wait(1000);
    }
};

TrafficLight* tl;
int light_control(String command){
  Serial.print(command);
  if(command == "GO") tl->light_go();
  if(command == "STOP") tl->light_stop();
  if(command == "WARNING") tl->light_warning();
  return 0;
}

void setup() {
  Serial.begin(9600);
  WARNING = true;
  tl = new TrafficLight();
  Particle.function("LIGHT_CONTROL", light_control);
}

void loop() {
  // DEBUG
  // tl->light_go();
  // delay(5000);
  // tl->light_stop();
  // delay(5000);
  // tl->light_warning();
  // delay(1000);

  if(WARNING == true) tl->light_warning();
}