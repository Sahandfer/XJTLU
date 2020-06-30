public class ConcreteColleague extends Colleague {

    public ConcreteColleague(Mediator m) {
        super(m);
        // TODO Auto-generated constructor stub
    }

    public void receive(String message) {
  
      System.out.println("Colleague Received: " + message);
  
    }
  
  }