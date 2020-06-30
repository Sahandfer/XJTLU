public class MobileColleague extends Colleague {

    public MobileColleague(Mediator m) {
        super(m);
        // TODO Auto-generated constructor stub
    }

    public void receive(String message) {
  
      System.out.println("Mobile Received: " + message);
  
    }
  
  }